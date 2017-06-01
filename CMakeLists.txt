cmake_minimum_required(VERSION 3.7)
project(Octo)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(Octo ${SOURCE_FILES})

enable_testing()

add_subdirectory(deps/googletest)

# For Google Test
include_directories(deps/googletest/googletest/include)
include_directories(deps/googletest/googlemock/include)

##OpenSSL
#add_subdirectory(deps/OpenSSL-CMake)

##Curl
#add_subdirectory(deps/curl)

#Twitter Library
add_subdirectory(deps/twitcurl/libtwitcurl)
include_directories(deps/twitcurl/libtwitcurl)
include_directories(src/Twitter)
add_library(twitter src/Twitter/TwitterHost.cpp src/Twitter/TwitterOAuth.cpp)
target_link_libraries(twitter twitcurl -lcurl)

# Test executables
add_executable(twitter_test deps/googletest/googletest/src/gtest_main.cc test/twitter_basic.cpp)
target_link_libraries(twitter_test gtest twitter)