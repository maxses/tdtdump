#------------------------------------------------------------------------------
#
# \brief	CMakeLists.txt file for "tdtdump"
#
#------------------------------------------------------------------------------


cmake_minimum_required(VERSION 3.10.2)
project( vodi_tests )

find_package(Catch2 3 QUIET)
if (Catch2_FOUND)
    add_definitions( "-DCATCH_V3" )
    set(CATCH2_TARGET Catch2::Catch2WithMain)
else()
    find_package(Catch2 2 REQUIRED)
    add_definitions( "-DCATCH_V2" )
    set(CATCH2_TARGET Catch2::Catch2)
endif()

set(
   headers

)

set(
   sources
      test_main.cpp
      test_dummy.cpp
)

add_executable(
   vodi_tests
      ${sources}
      ${headers}
)


target_link_libraries(
   vodi_tests
   PRIVATE
      ${CATCH2_TARGET}
      Qt${QT_VERSION_MAJOR}::Core
)


add_test(
   NAME vodi_tests
   COMMAND vodi_tests
   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)


#------------------------------------------------------------------------------
