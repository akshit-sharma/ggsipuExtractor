cmake_minimum_required(VERSION 2.9)
project(ggsipuExtractor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp OnlineFilesDownload.cpp OnlineFilesDownload.h GlobalSetting.cpp GlobalSetting.h InformationExtractor.cpp InformationExtractor.h InformationHolder.cpp InformationHolder.h)
add_executable(ggsipuExtractor ${SOURCE_FILES})
target_link_libraries(ggsipuExtractor curl)
target_link_libraries(ggsipuExtractor crypto)