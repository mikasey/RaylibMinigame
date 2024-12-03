# Copy all directories in here to binary directory

set(ASSETS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(ASSETS_OUTPUT_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

add_custom_target(copy_assets ALL
    COMMENT "Copying updated asset files to binary directory..."
)

file(GLOB_RECURSE ASSET_FILES
    "${ASSETS_SOURCE_DIR}/*"
)

foreach(FILE ${ASSET_FILES})
    # Removing CMakeLists.txt from here
    if (FILE MATCHES "CMakeLists.txt")
        continue()
    endif()

    file(RELATIVE_PATH REL_PATH "${ASSETS_SOURCE_DIR}" "${FILE}")
    set(FULL_PATH "${ASSETS_OUTPUT_DIR}/${REL_PATH}")

    # Copy command
    add_custom_command(
        TARGET copy_assets PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${ASSETS_OUTPUT_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${FILE}" "${FULL_PATH}"
        COMMENT "Copying: ${REL_PATH}"
    )
endforeach()