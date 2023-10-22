cmake_minimum_required(VERSION 3.27)
project(module2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MODULE2_SOURCE_FILES
    src/ClassEigenMat.cpp
)

add_library(module2
    ${MODULE2_SOURCE_FILES}
)

find_package(Eigen3 REQUIRED HINTS ${CMAKE_SOURCE_DIR}/thirdparty/eigen3/install/share/eigen3/cmake)

if (Eigen3_FOUND)
    message(STATUS "Eigen3 Found! - ${Eigen3_DIR}")
    set(Eigen3_LIBS Eigen3::Eigen)
endif()

target_include_directories(module2 PUBLIC
    include
    ${Eigen3_INCLUDE_DIRS}
)

# Eigen3와 같은 경우에는, 'header-only 라이브러리'이기 때문에 이것이 PUBLIC으로 작성되어야 한다고 함.
target_link_libraries(module2 PUBLIC
    ${Eigen3_LIBS}
)
