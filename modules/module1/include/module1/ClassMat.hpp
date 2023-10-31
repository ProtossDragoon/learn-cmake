// '헤더 가드'는 C++ 에서 유일하게 메크로가 허용되는 경우임
// 꿀팁: 언더스코어 두 개 '__'로 계층 구조를 관리하면 좋음
#ifndef MODULE_1__CLASSMAT_HPP
#define MODULE_1__CLASSMAT_HPP

#include "opencv2/opencv.hpp"

class ClassMat
{
public:
    ClassMat() = default;

private:
    cv::Mat cv_mat_;
};

#endif
