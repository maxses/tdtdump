/**---------------------------------------------------------------------------
 *
 * @file       test_dummy.cpp
 * @brief      Dummy test for tdtdump
 *
 * @date       20261013
 * @author     Maximilian Seesslen <src@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#if defined ( CATCH_V3 )
   #include <catch2/catch_test_macros.hpp>
#elif defined ( CATCH_V2 )
   #include <catch2/catch.hpp>
#elif defined ( CATCH_V1 )
   #include <catch/catch.hpp>
#else
   #error "Either 'catch' or 'catch2' has to be installed"
#endif

#define TEST_ALL
#define STOP_ON_FAIL


/*--- Implementation -------------------------------------------------------*/


TEST_CASE( "Dummy", "[default]" )
{
   SECTION( "Dummy" )
   {
      REQUIRE( 105 == 105 );
   }
}


/*--- Fin ------------------------------------------------------------------*/
