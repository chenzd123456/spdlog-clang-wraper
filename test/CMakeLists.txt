project(test CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_definitions(-DTEST)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} gtest_main gtest gmock spdlog::spdlog spdlogc)
add_test(NAME all_test COMMAND ${PROJECT_NAME})