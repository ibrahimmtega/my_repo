cmake_minimum_required(VERSION 3.16)

project(my_repo LANGUAGES CXX)

# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)




# include(FetchContent)

# Declare 'my_repo_2' using the same variable name
# FetchContent_Declare(
#   my_repo_2
#   GIT_REPOSITORY git@github.com:ibrahimmtega/my_repo_2.git
#   # GIT_TAG        v1.0
# )

# FetchContent_GetProperties(my_repo_2)
# if(NOT my_repo_2_POPULATED)
#   FetchContent_Populate(my_repo_2)
#   add_subdirectory(${my_repo_2_SOURCE_DIR} ${my_repo_2_BINARY_DIR})
# endif()
include(ExternalProject)
ExternalProject_Add(
  my_repo_2
  GIT_REPOSITORY git@github.com:ibrahimmtega/my_repo_2.git
  # GIT_TAG        v2.0
  PREFIX ${CMAKE_SOURCE_DIR}/vendor/my_repo_2
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/my_repo_2-install # Arguments passed to CMake of the external project
)

add_executable(my_repo
  main.cpp
)
# target_link_libraries(my_repo Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(my_repo ${CMAKE_BINARY_DIR}/my_repo_2-install/my_repo_2_lib)


