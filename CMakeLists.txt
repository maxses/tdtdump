#-----------------------------------------------------------------------------
#
# \brief	CMakeLists.txt file for "tdtdump"
#
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.5)

project( tdtdump LANGUAGES CXX )

set( CMAKE_INCLUDE_CURRENT_DIR ON )

set( CMAKE_AUTOUIC ON )
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

find_package( QT NAMES Qt5 Qt6 COMPONENTS Core Xml REQUIRED )
find_package( Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Xml )

set( TDT_CONFIGURED 1 )

add_subdirectory ( canhub )
add_subdirectory ( libtdt )

include_directories(
   include/
)

add_executable(
   tdtdump
      src/main.cpp
      src/tdtdump.cpp
      include/tdtdump.hpp
)

target_link_libraries(
   tdtdump
   PRIVATE
      Qt${QT_VERSION_MAJOR}::Core
      canhub
      tdt
)


file( CREATE_LINK tdtdump TDTDump SYMBOLIC )


#--- Fin ---------------------------------------------------------------------
