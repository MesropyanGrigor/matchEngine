cmake_minimum_required(VERSION 3.0)

project(Market)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#add_subdirectory(extern/portaudio)
add_library(order_book STATIC src/order_book.cpp)
target_include_directories(order_book PUBLIC include)

add_library(engine STATIC src/engine.cpp)
target_link_libraries(engine PUBLIC order_book)
target_include_directories(engine PUBLIC include)


#add_library(audio_data_player OBJECT src/audio_data_player.cc)
#target_link_libraries(audio_data_player PUBLIC portaudio_static
#                                               audio_data)
#target_include_directories(audio_data_player PUBLIC include)
add_executable(marketPredictor src/main.cpp)
target_link_libraries(marketPredictor PUBLIC order_book engine)
target_include_directories(marketPredictor PUBLIC include)

#target_link_libraries(marketPredictor PUBLIC main) 
                                             
                                             
                                             
                                             


#add_subdirectory(src/formats)