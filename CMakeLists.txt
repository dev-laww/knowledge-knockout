cmake_minimum_required(VERSION 3.10)

project(KnowledgeKnockout)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(fmt CONFIG REQUIRED)

add_executable(KnowledgeKnockout src/main.cpp)

target_link_libraries(KnowledgeKnockout PRIVATE fmt::fmt)

add_custom_command(TARGET KnowledgeKnockout POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:KnowledgeKnockout>/assets
)

add_custom_command(TARGET KnowledgeKnockout POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:KnowledgeKnockout>/data
)