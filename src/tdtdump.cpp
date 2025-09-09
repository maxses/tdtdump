/**---------------------------------------------------------------------------
 *
 * @file    tdtdump.cpp
 * @brief   TDT dump
 *
 * Dumps TDT objects to terminal.
 *
 * @date      20241214
 * @author    Maximilian Seesslen <mes@seesslen.net>
 * @copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include "tdtdump.hpp"
#include <QObject>
#include <QDebug>
#include <tdt/printer.hpp>
#include <tdt/message.hpp>
#include <tdt/canMessage.hpp>


/*--- Includes -------------------------------------------------------------*/


/**
 * @brief Le constructeur
 * @param parent Parent qt object
 */
CTdtDump::CTdtDump(QObject *parent)
   : QObject(parent)
{
}


/**
 * @brief Le destructeur
 */
CTdtDump::~CTdtDump()
{
}


/**
 * @brief Set the canhub connector
 * @param connector Pointer to canhub connectur
 */
void CTdtDump::setConnector( CANHub::CConnector* connector )
{
   bool success;

   m_connector = connector;

   success = connect( m_connector, SIGNAL( dataIn( const CANHub::SMessage&, CANHub::CConnector* ) ),
               this, SLOT( slotDataIn( const CANHub::SMessage&, CANHub::CConnector* ) ),Qt::DirectConnection );
   Q_ASSERT(success);
}


void CTdtDump::slotDataIn( const CANHub::SMessage& msg, CANHub::CConnector* source )
{
   qDebug("Data in");
   SCanMessage canMessage( msg.getId(), msg.getLen(), msg.getData());
   Tdt::CMessage tdtMessage(canMessage);
   QString sender=msg.getSenderName();
   sender.resize(16, ' ');

   qDebug() << "TDT-Message["<< sender << "]:"
            << " ID: 0x" << std::hex << tdtMessage.getNodeId()
            << "; Object: 0x" << (int)tdtMessage.getTdtObject()
            << "; Value: " << m_tdtPrinter.printValue( canMessage );
   dumpMessage( tdtMessage, msg, source);
}


void CTdtDump::dumpMessage( const Tdt::CMessage& tdtMessage
         , const CANHub::SMessage& msg, CANHub::CConnector* source )
{
   QString text;
   
   if( m_filter.count() )
   {
      if( ! m_filter.contains( tdtMessage.getNodeId() ) )
      {
         return;
      }
   }

   text=m_tdtPrinter.printValue( tdtMessage );
   qDebug() << "TDT printed value: " << text;

   // Example from candump from cant-utils
   //   can0  464   [8]  0B 04 30 00 D4 1B 00 00
   
   QString senderName=msg.getSenderName();
   senderName.resize(16, '.');

   printf("   <%s>  Id: 0x%X; Size: %d; Data: "
          , qPrintable( senderName ), tdtMessage.getId()
          , tdtMessage.getLen());
   for(int i1=0; i1<tdtMessage.getLen(); i1++)
   {
      printf(" %02X", (unsigned char)tdtMessage.getData()[i1]);
   }
   printf("\n");
   printf("            Node ID: 0x%X\n", (int)tdtMessage.getNodeId() );
   printf("            Function code: %s [0x%X]\n"
          , m_tdtPrinter.getFunctionCodeString( tdtMessage )
          , (int)tdtMessage.getFunctionCode() );
   printf("            Object: %s [0x%X]\n"
          , m_tdtPrinter.getObjectString( tdtMessage ), (int)tdtMessage.getTdtObject() );
   printf("            Unit: %s [0x%X]\n", m_tdtPrinter.getUnitString( tdtMessage )
          , (int)tdtMessage.getTdtUnit() );
   printf("            Value: %s [0x%X]\n"
          , qPrintable( m_tdtPrinter.printValue( tdtMessage ) )
          , (int)tdtMessage.getTdtValue()->_uint );

   return;
}


/**
 * @brief Filter out nodes when dumping
 * @param filter  This is a string of comma seperated node IDs
 */
void CTdtDump::setFilter( QString filter )
{
   QStringList list( filter.split(','));
   
   for( const QString& s:list )
   {
      if( !s.isEmpty() )
      {
         int value=s.toInt( nullptr, 0 );
         m_filter+=value;
         qDebug("Add filter for nodeID %d", value);
      }
   }
}


/*--- Fin ------------------------------------------------------------------*/
