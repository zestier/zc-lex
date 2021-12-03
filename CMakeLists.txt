cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

# ---- Options ----

option(ZC_LEX_BUILD_TESTS "Build AST unit tests" OFF)

# ---- Project ----

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
  zc-lex
  VERSION 0.1
  LANGUAGES CXX
)

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

# ---- Add dependencies via CPM ----

include(cmake/CPM.cmake)
CPMUsePackageLock(package-lock.cmake)

# PackageProject.cmake will be used to make our target installable
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.6.0")

# ---- Collect souce files ----

# Note: globbing sources is considered bad practice as CMake's generators may not detect new files
# automatically. Keep that in mind when changing files, or explicitly mention them here.
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/inc/**.h")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/**.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${headers} ${sources})

# ---- Create library ----

add_library(${PROJECT_NAME} ${headers} ${sources})
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
  $<INSTALL_INTERFACE:inc>
)

# ---- Add tests ----

if(ZC_LEX_BUILD_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()

# ---- Create an installable target ----

packageProject(
  NAME ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  BINARY_DIR ${PROJECT_BINARY_DIR}
  INCLUDE_DIR ${PROJECT_SOURCE_DIR}/inc
  INCLUDE_DESTINATION inc/${PROJECT_NAME}-${PROJECT_VERSION}
  VERSION_HEADER "${PROJECT_NAME}/version.h"
  EXPORT_HEADER "${PROJECT_NAME}/export.h"
  COMPATIBILITY SameMajorVersion
  DISABLE_VERSION_SUFFIX YES
)