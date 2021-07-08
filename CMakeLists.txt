cmake_minimum_required(VERSION 3.0.0)
project(lbp-to-classify-textures VERSION 0.1.0)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "../bin")
add_compile_definitions(
    _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
)

include(CTest)
enable_testing()

find_package( OpenCV REQUIRED )
find_package( Threads REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(${PROJECT_NAME}
    "source_files/main.cpp"
    "source_files/lbp_descriptor.cpp"
    "source_files/lbp_classifier.cpp"
)

if (UNIX)
  target_link_libraries(${PROJECT_NAME} 
    ${OpenCV_LIBS} 
    ${CMAKE_THREAD_LIBS_INIT} 
    stdc++fs
  )
endif (UNIX)

if (WIN32) 
  target_link_libraries(${PROJECT_NAME} 
    ${OpenCV_LIBS} 
    ${CMAKE_THREAD_LIBS_INIT}
  )
endif(WIN32)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
