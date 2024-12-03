set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

# add_definitions(-DSUPPORT_CUSTOM_FRAME_CONTROL)
add_subdirectory("raylib")
# remove_definitions(-DSUPPORT_CUSTOM_FRAME_CONTROL)

set(BUILD_RAYGUI_EXAMPLES OFF)
add_subdirectory("raygui/projects/CMake")