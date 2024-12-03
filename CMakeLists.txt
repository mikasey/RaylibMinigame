cmake_minimum_required(VERSION 3.16)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("Raylib game" CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/out/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/out/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/out/lib")

# Adding Raylib
add_subdirectory("libs")
add_subdirectory("export")

# Adding our source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/sources/*.cpp") # Define PROJECT_SOURCES as a list of all source files
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/sources/") # Define PROJECT_INCLUDE to be the path to the include directory of the project

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    # /ENTRY:mainCRTStartup keeps the same "main" function instead of requiring "WinMain"
    set(EXE_NO_CONSOLE WIN32)
else()
    set(EXE_NO_CONSOLE )
endif()


# Declaring our executable
add_executable(Raylib_game ${EXE_NO_CONSOLE})

target_sources(Raylib_game PRIVATE ${PROJECT_SOURCES})
target_include_directories(Raylib_game PRIVATE ${PROJECT_INCLUDE})
target_link_libraries(Raylib_game PRIVATE raylib raygui)
add_dependencies(Raylib_game copy_assets)
target_link_options(Raylib_game PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/ENTRY:mainCRTStartup>)