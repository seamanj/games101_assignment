//
// Created by LEI XU on 4/27/19.
//

#ifndef RASTERIZER_TEXTURE_H
#define RASTERIZER_TEXTURE_H
#include "global.hpp"
#include <Eigen/Eigen>
#include <opencv2/opencv.hpp>
class Texture{
private:
    cv::Mat image_data;

public:
    Texture(const std::string& name)
    {
        image_data = cv::imread(name);
        cv::cvtColor(image_data, image_data, cv::COLOR_RGB2BGR);
        width = image_data.cols;
        height = image_data.rows;
    }

    int width, height;

    Eigen::Vector3f getColor(float u, float v)
    {
        auto u_img = u * width;
        auto v_img = (1 - v) * height;
        auto color = image_data.at<cv::Vec3b>(v_img, u_img);
        return Eigen::Vector3f(color[0], color[1], color[2]);
    }

    Eigen::Vector3f getColorBilinear(float u, float v)
    {
        auto u_img = u * width;
        auto v_img = (1 - v) * height;
        auto t1 = u_img - int(u_img);
        auto t2 = v_img - int(v_img);

        auto a_color = image_data.at<cv::Vec3b>(v_img, u_img);
        auto b_color = image_data.at<cv::Vec3b>(v_img, u_img+1);
        auto c_color = image_data.at<cv::Vec3b>(v_img+1, u_img+1);
        auto d_color = image_data.at<cv::Vec3b>(v_img+1, u_img);

        auto e_color = (1 - t1) * a_color + t1 * b_color;
        auto f_color = (1 - t1) * d_color + t1 * c_color;


        auto color = (1 - t2) * e_color + t2 * f_color;
        return Eigen::Vector3f(color[0], color[1], color[2]);
    }


};
#endif //RASTERIZER_TEXTURE_H
