# 이 모듈도 하나의 번듯한 라이브러리가 되고자 하는 것.
# 이것도 하나의 C++ 프로젝트라고 볼 수 있음.
# 따라서 상위 디렉토리의 CMakeLists.txt 에는 별다른 것을 적지 않았지만
# 이것은 최상위 디렉토리의 CMakeLists.txt 처럼 작성해 주어야 함.
cmake_minimum_required(VERSION 3.27)
project(
    module1
    LANGUAGES CXX
)

set(${PROJECT_NAME}_PATH ${CMAKE_CURRENT_SOURCE_DIR})
cmake_path(APPEND ${PROJECT_NAME}_SOURCE_PATH ${${PROJECT_NAME}_PATH} "src")
cmake_path(APPEND ${PROJECT_NAME}_INCLUDE_PATH ${${PROJECT_NAME}_PATH} "include")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
    MODULE1_SOURCE_FILES
    ${${PROJECT_NAME}_SOURCE_PATH}/ClassMat.cpp
)

# 이 모듈을 라이브러리로서 사용하고 싶으므로, 라이브러리로 빌드하고자 함.
# cpp 파일과 헤더 파일이 필요함.
add_library(
    ${PROJECT_NAME} # 기본값은 STATIC .a 파일, SHARED: .dylib 파일(Linux, Mac), MODULE
    ${MODULE1_SOURCE_FILES}
)

# 기본적으로 전역에 설치되어 있는 라이브러리를 먼저 찾음.
# REQUIRED가 붙어 있는 경우, 이것을 찾지 못하면 빌드를 안하겠다는 것.
# 전역이 아니라 임의의 설치 경로를 추가하고자 하는 경우 HINTS를 사용.
# CMAKE_ prefix는 CMake 시스템에서 제공하는 예약 변수라고 했음.
# CMAKE_SOURCE_DIR은 최초로 호출된 CMake가 존재하는 디렉토리 정보를 가짐.
# find_package 함수와 호환이 되는 모든 라이브러리들은 다음 파일을 가지고 있음.
# lib/cmake/라이브러리이름/라이브러리이름Config.cmake
# 이 파일이 존재하는 디렉토리를 연결할 것.
# 이 CMake파일에는 OpenCV_INCLUDE_DIRS이나 OpenCV_LIBS와 같은 변수들이 접근가능하도록 정의되어 있어 편리하게 사용 가능함.
find_package(OpenCV REQUIRED HINTS ${CMAKE_SOURCE_DIR}/thirdparty/opencv/install/lib/cmake/opencv4)

# find_package 함수를 통해 라이브러리를 찾거나, 실패한 결과는
# 패키지이름_FOUND 이라는 변수에 자동으로 불리언 값을 할당.
if (OpenCV_FOUND)
    # message 함수는 출력에 자주 사용함.
    # 마찬가지로 패키지이름_DIR 값을 자동으로 할당.
    message(STATUS "OpenCV Found! - ${OpenCV_DIR}")
endif()

# CMake에서 타겟은 실행가능한 파일 또는 CMake에서 빌드되는 라이브러리임.
# 타겟(여기에서는 module1)이 include해서 사용할 헤더파일의 경로들을 명시함.
# public으로 하는 경우 프로젝트의 상위에서 타깃을 include했을 때 사용 가능.
# 예를 들어, 라이브러리 A를 B가 사용하고, B가 C를 사용했을 때, C에서 A를 사용할 수 있음.
# private으로 하는 경우 외부에 노출되지 않음.
# 예를 들어, 라이브러리를 A를 B가 사용하고, B가 C를 사용했을 때, C가 A를 사용할 수 없음.
# 따라서 include는 일반적으로 PUBLIC 으로 사용하는 것을 권장함.
# 한편, 변수 OpenCV_INCLUDE_DIRS는 find_package(OpenCV...) 를 통해 할당됨.
# 여기서 OpenCV_INCLUDE_DIRS를 PRIVATE로 지정한다면
# 따라서 examples 디렉토리의 엔트리포인트 파일을 컴파일할 때 include 디렉토리에 있는 헤더파일을 읽다가
# 최상위 CMakeLists.txt에서는 OpenCV 헤더파일 위치를 읽을 수 없어 OpenCV_INCLUDE_DIRS를 찾을 수 없게 되므로
# OpenCV 헤더파일을 불러오는 헤더파일을 읽을 수 없다는 문제가 발생함.
target_include_directories(
    ${PROJECT_NAME} PUBLIC
    include
    ${OpenCV_INCLUDE_DIRS}
)

# 최종 바이너리파일을 생성하기 위해서는 링킹이라는 과정이 필요함.
# 컴파일이야 헤더파일만 있으면 되지만, 링킹을 위해서는 의존하는 라이브러리의 바이트코드를 가져올 수 있어야 함.
# 아래는 의존하는 라이브러리 OpenCV의 바이트코드를 가져오는 과정임.
# 변수 OpenCV_LIBS는 find_package(OpenCV...) 를 통해 할당됨.
target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    ${OpenCV_LIBS}
)

# 메모리 누수 문제 등을 미연에 발견하는 것을 돕는 컴파일러 옵션들을 지정할 수 있음.
# Makefile 등 빌드 파일에 자동으로 작성될 것이라고 예상할 수 있음.
# e.g. https://github.com/ProtossDragoon/epita-w6-prog-http-server/blob/master/ttt_server/Makefile
# 컴파일러, 운영체제 등에 의존적이므로 확인 필요.
target_compile_options(
    ${PROJECT_NAME} PRIVATE
    -Wall -Wextra -Wpedantic -Werror
)
