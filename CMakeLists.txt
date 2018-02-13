cmake_minimum_required(VERSION 3.1)
enable_testing()

project(ConstrainedOptimization)

set(CMAKE_CXX_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

add_subdirectory(Penalty)
add_subdirectory(AugmentedLagrangian)
add_subdirectory(AugmentedLagrangianNlopt)

add_test(NAME Penalty COMMAND $<TARGET_FILE:Penalty>)
add_test(NAME AugmentedLagrangian COMMAND $<TARGET_FILE:AugmentedLagrangian>)
add_test(NAME AugmentedLagrangianNlopt COMMAND $<TARGET_FILE:AugmentedLagrangianNlopt>)
