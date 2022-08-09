cmake_minimum_required(VERSION 3.0)

project(Market)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE DEBUG)

add_library(order_book STATIC src/order_book.cpp)
target_include_directories(order_book PUBLIC include)

add_library(engine STATIC src/engine.cpp)
target_link_libraries(engine PUBLIC order_book)
target_include_directories(engine PUBLIC include)

add_library(order_matches STATIC src/order_matches.cpp)
target_link_libraries(order_matches PUBLIC order_book)
target_include_directories(order_matches PUBLIC include)

add_executable(marketPredictor src/main.cpp)
target_link_libraries(marketPredictor PUBLIC order_book engine order_matches)
target_include_directories(marketPredictor PUBLIC include)