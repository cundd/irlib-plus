cmake_minimum_required(VERSION 3.1)
    project(irlib - plus)

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_BINARY_DIR "build")
#set(EXECUTABLE_OUTPUT_PATH "build")

            set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ CMAKE_BINARY_DIR } / lib)
                set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ CMAKE_BINARY_DIR } / lib)
                    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ CMAKE_BINARY_DIR } / bin)

                        include_directories("${PROJECT_SOURCE_DIR}/src")
#set(SOURCE_FILES main.cpp)

                            file(GLOB HEADER_FILES "*.h*")
                                file(GLOB IMPLEMENTATION_FILES "*.cpp")
#add_library(irlib - plus - lib ${ HEADER_FILES })

                                    add_executable(irlib - plus $ {HEADER_FILES } ${ IMPLEMENTATION_FILES })
#add_executable(irlib - plus main.cpp Parser.cpp Tokenizer.cpp ExpressionTypeAnalyzer.cpp)
#add_executable(irlib - plus ${ SOURCE_FILES } Parser.h)
