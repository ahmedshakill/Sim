CMAKE_MINIMUM_REQUIRED (VERSION 3.16)
project(Sim)

# set(CMAKE_SYSTEM_NAME "Generic")
# set(CMAKE_SYSTEM_PROCESSOR "riscv")
# set(CATCH_CONFIG_NO_POSIX_SIGNALS ON)
set(CMAKE_CXX_STANDARD 23)

# SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
SET(CMAKE_EXE_LINKER_FLAGS 
          "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,/opt/gcc-latest/lib64/")
include(CTest)
Include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
  
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)

file(GLOB decoder 
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        )

add_executable(decode  main.cpp ${decoder} )

# target_compile_features(decode PUBLIC cxx_std_23)
include_directories(
        ${PROJECT_SOURCE_DIR}/test
)
file (GLOB test
"${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(mytest  ${test}  )

target_link_libraries(mytest 
                      GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(mytest)

