#ifndef CTDTDUMP_HPP
#define CTDTDUMP_HPP
/**---------------------------------------------------------------------------
 *
 * @file    tdtdump.hpp
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


#include <canhub/connector.hpp>
#include <tdt/message.hpp>
#include <tdt/printer.hpp>


/*--- Declarations ---------------------------------------------------------*/


class CTdtDump : public QObject
{
   Q_OBJECT

public:
   CTdtDump(QObject *parent = nullptr);
   ~CTdtDump();
   void setConnector( CANHub::CConnector* connector );
   void dumpMessage( const Tdt::CMessage &tdtMessage
            , const CANHub::SMessage& msg, CANHub::CConnector* source );
   void setFilter( QString filter );
   Tdt::CPrinter m_tdtPrinter;

private:
   CANHub::CConnector* m_connector = nullptr;
   QList<int> m_filter;

public slots:
   void slotDataIn( const CANHub::SMessage& msg, CANHub::CConnector* source );
};


/*--- Fin ------------------------------------------------------------------*/
#endif // CTDTDUMP_HPP
