cmake_minimum_required(VERSION 3.1)

find_package(NLopt REQUIRED)

include_directories(${NLopt_INCLUDE_DIRS})

file(GLOB files *.cpp *.h ../*.cpp ../*.h)
add_executable(AugmentedLagrangianNlopt ${files})
target_link_libraries(AugmentedLagrangianNlopt ${NLopt_LIBRARIES})
