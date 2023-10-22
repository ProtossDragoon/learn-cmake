cmake_minimum_required(VERSION 3.27)
project(hello-cmake LANGUAGES CXX)

# set 은 변수에 값을 설정하는 함수.
# 변수명의 CMAKE_ prefix는 CMAKE 시스템을 위한 예약어를 암시함.
set(CMAKE_CXX_STANDARD 14)

# 자율주행 도메인의 소프트웨어는 cpp 버전을 규제로 강제하곤 함.
# 일반적으로 그 버전은 C++11 혹은 C++14 임.
# 이것이 없으면 상위 버전(15, 16 ...)을 사용하더라도 WARNING만 뜨고 끝남.
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
