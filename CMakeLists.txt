cmake_minimum_required(VERSION 3.10)

project(KnowledgeKnockout)

find_package(fmt CONFIG REQUIRED)

add_executable(KnowledgeKnockout src/main.cpp)

target_link_libraries(KnowledgeKnockout PRIVATE fmt::fmt)