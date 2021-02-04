project(timeMaster)
set(CMAKE_CXX_STANDARD 17)
add_executable(main main.cpp Response.cpp Header.cpp Request.cpp RequestParser.cpp)
target_link_libraries(main ws2_32.lib)
