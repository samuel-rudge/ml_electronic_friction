file(GLOB SCRIPT_FILES "*.cpp")

foreach(SCRIPT ${SCRIPT_FILES})
    get_filename_component(TARGET_NAME ${SCRIPT} NAME_WE) # filename without extension
    add_executable(${TARGET_NAME} ${SCRIPT})
    target_link_libraries(${TARGET_NAME} utils)
endforeach()