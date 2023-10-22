#include <iostream>

#include "module1/ClassMat.hpp"
#include "module2/ClassEigenMat.hpp"


int main() {
    const auto mat_module1 = ClassMat();
    const auto mat_module2 = ClassEigenMat();
    std::cout << "exec_module1and2.cpp Success!" << std::endl;

    return 0;
}