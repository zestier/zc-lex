# ---- Add dependencies via CPM ----

CPMAddPackage("gh:catchorg/Catch2@2.13.7")
include("${Catch2_SOURCE_DIR}/contrib/Catch.cmake")

# ---- Collect souce files ----

# Note: globbing sources is considered bad practice as CMake's generators may not detect new files
# automatically. Keep that in mind when changing files, or explicitly mention them here.
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/**.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sources})

# ---- Create library ----

add_executable(${PROJECT_NAME}-test ${sources})
target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME} Catch2)

# ---- Attach tests ----

catch_discover_tests(${PROJECT_NAME}-test)