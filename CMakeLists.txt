cmake_minimum_required(VERSION 3.16)

project(my_repo LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED Qt6_DIR)
    message(FATAL_ERROR "please set Qt6_DIR")
endif()

if(NOT DEFINED VENDOR_BINARY_DIR OR NOT DEFINED VENDOR_PREFIX_DIR OR NOT DEFINED VENDOR_SRC_DIR)
    message(FATAL_ERROR "please set vendor paths")
endif()

include(${Qt6_DIR}/qt.toolchain.cmake)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

include(ExternalProject)

if(NOT TARGET my_repo_2)
    ExternalProject_Add(
      my_repo_2
      GIT_REPOSITORY https://github.com/ibrahimmtega/my_repo_2.git
      GIT_TAG main
      BINARY_DIR ${VENDOR_BINARY_DIR}/my_repo_2
      PREFIX ${VENDOR_PREFIX_DIR}/my_repo_2
      SOURCE_DIR ${VENDOR_SRC_DIR}/my_repo_2
      INSTALL_COMMAND ""
      BUILD_ALWAYS ON
      GIT_PROGRESS ON
      CMAKE_ARGS
        -DVENDOR_SRC_DIR=${VENDOR_SRC_DIR}
        -DVENDOR_BINARY_DIR=${VENDOR_BINARY_DIR}
        -DVENDOR_PREFIX_DIR=${VENDOR_PREFIX_DIR}
        -DQt6_DIR=${Qt6_DIR}
     )
endif()

add_library(my_repo_lib INTERFACE IMPORTED GLOBAL)

set_target_properties(my_repo_lib PROPERTIES
  # IMPORTED_LOCATION ${BINARY_DIR}/${LIB_NAME}
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include
  # INTERFACE_SOURCES ${SOURCES}
)
target_link_libraries(my_repo_lib INTERFACE Qt${QT_VERSION_MAJOR}::Core)

if(NOT TARGET my_repo_2_lib)
    add_library(my_repo_2_lib INTERFACE IMPORTED)
    set_target_properties(my_repo_2_lib PROPERTIES
      IMPORTED_LOCATION ${VENDOR_BINARY_DIR}/my_repo_2/libmy_repo_2_lib.a
      INTERFACE_INCLUDE_DIRECTORIES ${VENDOR_SRC_DIR}/my_repo_2
    )
endif()
add_dependencies(my_repo_2_lib my_repo_2)
target_link_libraries(my_repo_lib INTERFACE  my_repo_2_lib)
