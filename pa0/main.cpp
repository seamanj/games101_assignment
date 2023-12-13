#include<cmath>
#include<Eigen/Core>
#include<Eigen/Dense>
#include<iostream>

int main(){


    Eigen::Vector3f p(2.0f,1.0f,1.0f);  
    float cos45 = std::cos(45.0/180.0);
    float sin45 = std::sin(45.0/180.0);
    Eigen::Matrix3f R;
    R << cos45, -sin45, 1, sin45, cos45, 2, 0, 0, 1;
    Eigen::Vector3f p1 = R * p;
    std::cout << p1 << std::endl;
    return 0;
}