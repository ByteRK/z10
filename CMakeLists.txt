cmake_minimum_required (VERSION 3.8)
project(z10 C CXX)

set(CMAKE_CXX_STANDARD 11)

include_directories(
   ./
   ./src/libs
   ./src/comm
   ./src/project
   ./src/window
   ${CDROID_INCLUDE_DIRS}
   ${CDROID_DEPINCLUDES}
   ${CMAKE_BINARY_DIR}/include
   ${CMAKE_BINARY_DIR}/include/gui
   ${CMAKE_BINARY_DIR}/include/porting
   ${CMAKE_BINARY_DIR}/include/cairo
   ${CMAKE_BINARY_DIR}/include/epg
   ${CMAKE_BINARY_DIR}/include/freetype2
   
)
aux_source_directory(./ Z10)
aux_source_directory(./src/libs Z10)
aux_source_directory(./src/comm Z10)
aux_source_directory(./src/project Z10)
aux_source_directory(./src/window Z10)

add_definitions(--include cdtypes.h)
add_definitions(--include cdlog.h)
link_directories(${CMAKE_BINARY_DIR}/lib)
add_executable(z10 ${Z10})

CreatePAK(z10 ${PROJECT_SOURCE_DIR}/assets ${PROJECT_BINARY_DIR}/z10.pak ${PROJECT_SOURCE_DIR}/R.h)

message("CDROID_LIBRARIES=${CDROID_LIBRARIES} CDROID_INCLUDE_DIRS=${CDROID_INCLUDE_DIRS}")
target_link_libraries(z10 PRIVATE cdroid)

install(TARGETS z10 DESTINATION bin)

