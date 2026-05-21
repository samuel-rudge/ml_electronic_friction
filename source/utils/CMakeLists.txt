# This CMakeLists.txt is inside source/
# It just adds the subdirectories (heom, utils, etc.)

file(GLOB FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)

foreach(SUBDIR ${SUBDIRS})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR})    
    add_subdirectory(${SUBDIR})
    endif()
endforeach()