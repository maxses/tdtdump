/**---------------------------------------------------------------------------
 *
 * @file    main.hpp
 * @brief   Main file for tdtdump
 *
 * Just instanciates the class and enters the event loop.
 *
 * @date      20241214
 * @author    Maximilian Seesslen <mes@seesslen.net>
 * @copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include "tdtdump.hpp"
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QLoggingCategory>
#include <canhub/connectorCan.hpp>
#include <canhub/connectorTcpClient.hpp>


/*--- Implementation -------------------------------------------------------*/


int main(int argc, char *argv[])
{
   QCoreApplication app(argc, argv);
   CTdtDump tdtDump;
   QCommandLineParser parser;
   CANHub::CConnector *connector = nullptr;

   parser.setApplicationDescription("TDT message dumper");
   parser.addHelpOption();
   parser.addVersionOption();

   QCommandLineOption oInterface("i", "Use CAN-Adapter <interface> directly without TCP server", "interface");
   QCommandLineOption oHost("host", "Use host <host> instead of localhost", "host");
   QCommandLineOption oDebug("d", "Enable debug output");
   QCommandLineOption oFilter("f", "Filter; show only IDs of comma seperated list <Node-IDs>", "Node-IDs");
   parser.addOptions( { oInterface, oHost, oDebug , oFilter} );
   parser.process(app);

   qSetMessagePattern("[%{time process}] %{function}: %{message}");

   if( ! parser.isSet(oDebug) )
   {
      QLoggingCategory::setFilterRules("*.debug=false");
   }

   if( parser.isSet( oInterface ) )
   {
      qInfo("direct CAN adapter connection" );
      connector = new CANHub::CConnectorCan( &app, "TDTDump", parser.value( oInterface ) );
   }
   else
   {
      qInfo("TCP over TCP connection" );
      if( parser.isSet( oHost ) )
      {
         qDebug("Connecting to %s", qPrintable( parser.value( oHost ) ) );
         connector = new CANHub::CConnectorTcpClient( &app, "TDTDump", parser.value( oHost ) ) ;
      }
      else
      {
         connector = new CANHub::CConnectorTcpClient( &app ) ;
      }
   }
   
   tdtDump.setFilter( parser.value( oFilter ) );
   
   if( connector )
   {
      tdtDump.setConnector( connector );
   }

   return app.exec();
}


/*--- Fin ------------------------------------------------------------------*/
