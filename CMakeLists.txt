cmake_minimum_required(VERSION 3.20)

project(blockchain)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external)

add_executable(pow examples/pow.cc)
target_include_directories(pow PUBLIC . include)
target_link_libraries(pow PRIVATE streebog merkletree schnorr)

add_executable(txn_gen aux/txn_gen.cc)
target_include_directories(txn_gen PUBLIC include)

target_link_libraries(txn_gen PRIVATE streebog)
