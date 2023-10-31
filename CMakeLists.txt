# <CMake에서 반드시 포함되어야 하는> 두 개의 라인
cmake_minimum_required(VERSION 3.27)
project(
    HELLO_CMAKE # <프로젝트 이름> SCREAMING_CASE로 작성
    LANGUAGES CXX # [언어] 사용하는 언어
    VERSION 0.1.0 # [프로젝트 버전] 참고: 다른 CMake에서 명시할 때 주의
    DESCRIPTION "Let's study CMake Build System!" # [설명]
    HOMEPAGE_URL "https://github.com/ProtossDragoon/learn-cmake" # [홈페이지]
)

# CMake의 상태에 대한 간단한 디버거이자 설명
# PROJECT_ prefix를 가진 변수들은 project() 함수에서 자동으로 할당됨
message(STATUS "Project ${PROJECT_NAME} (v${PROJECT_VERSION}) is now being configured.") # 일반적인 설명
message(WARNING "I'm CMake Beginner") # 설명을 조금 더 강조
# 에러를 만드는 경우 configuration은 되지만 빌드가 되지는 않는다. message(SEND_ERROR "메시지")
# 치명적인 에러를 만드는 경우 configuration 조차도 되지 않는다. message(FATAL_ERROR "메시지")

# set 은 변수에 값을 설정하는 함수.
set(${PROJECT_NAME}_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# 변수명의 CMAKE_ prefix는 CMAKE 시스템을 위한 예약어를 암시함.
# <C++을 사용하는 경우 반드시 사용함>
set(CMAKE_CXX_STANDARD 14)

# 자율주행 도메인의 소프트웨어는 cpp 버전을 규제로 강제하곤 함.
# 일반적으로 그 버전은 C++11 혹은 C++14 임.
# 이것이 없으면 상위 버전(15, 16 ...)을 사용하더라도 WARNING만 뜨고 끝남.
# <일반적으로 C++을 사용하는 경우 반드시 사용함>
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 빌드를 하게 되면 build 디렉토리 안에 Makefile이 생성됨.
# 이것을 ON으로 세팅하면 configuration 에서 있었던 일들을 파일로 추출
# [이왕이면 사용하는 것이 좋음]
set(CMAKE_VERBOSE_MAKEFILE ON)

# 지정한 디렉토리 내의 CMakeLists.txt 를 실행하겠다는 것을 의미함.
add_subdirectory(modules)

# 실행 파일을 만드는 함수.
# 우리가 만들 실행 파일의 이름, 해당 실행파일을 만들기 위해 사용되는 소스코드를 지정.
# main.cpp 에 대한 실행파일
add_executable(hello-cmake main.cpp)

# 주어진 스캐폴드에서 examples는 엔트리포인트 파일들이 저장되는 위치임.
# exec_module1.cpp 에 대한 실행파일
add_executable(exec-module1 examples/exec_module1.cpp)

target_link_libraries(exec-module1 PRIVATE
    module1
)

# exec_module1and2.cpp 에 대한 실행파일
add_executable(exec-module1and2 examples/exec_module1and2.cpp)

target_link_libraries(exec-module1and2 PRIVATE
    module1
    module2
)
