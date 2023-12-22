#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>

std::vector<cv::Point2f> control_points;

void mouse_handler(int event, int x, int y, int flags, void *userdata) 
{
    if (event == cv::EVENT_LBUTTONDOWN) //&& control_points.size() < 4
    {
        std::cout << "Left button of the mouse is clicked - position (" << x << ", "
        << y << ")" << '\n';
        control_points.emplace_back(x, y);
    }     
}

void naive_bezier(const std::vector<cv::Point2f> &points, cv::Mat &window) 
{
    auto &p_0 = points[0];
    auto &p_1 = points[1];
    auto &p_2 = points[2];
    auto &p_3 = points[3];

    for (double t = 0.0; t <= 1.0; t += 0.001) 
    {
        auto point = std::pow(1 - t, 3) * p_0 + 3 * t * std::pow(1 - t, 2) * p_1 +
                 3 * std::pow(t, 2) * (1 - t) * p_2 + std::pow(t, 3) * p_3;

        window.at<cv::Vec3b>(point.y, point.x)[2] = 255;
    }
}

cv::Point2f recursive_bezier(const std::vector<cv::Point2f> &control_points, float t) 
{
    // TODO: Implement de Casteljau's algorithm

    int sz = control_points.size();

    if (sz == 1)
        return control_points[0];

    std::vector<cv::Point2f> new_control_points(sz - 1);
    for(int i = 0; i < sz - 1; ++i)
    {
        cv::Point2f point = control_points[i] * (1 - t) + control_points[i + 1] * t;
        new_control_points[i] = point;
    }
    return recursive_bezier(new_control_points, t);
}
float get_haffuman_dist(int x, int y, cv::Point2f point)
{
    float x_center = (float)x + 0.5f;
    float y_center = (float)y + 0.5f;

    return fabs(point.x - x_center) + fabs(point.y - y_center);
}
void bezier(const std::vector<cv::Point2f> &control_points, cv::Mat &window) 
{
    // TODO: Iterate through all t = 0 to t = 1 with small steps, and call de Casteljau's 
    // recursive Bezier algorithm.

    for (double t = 0.0; t <= 1.0; t += 0.001)
    {
        auto point = recursive_bezier(control_points, t);

 

        // window.at<cv::Vec3b>(point.y, point.x)[1] = 255;


        int x = std::min(window.cols - 1, std::max(0, (int)point.x));
        int y = std::min(window.rows - 1, std::max(0, (int)point.y));
        int inc[3] = {0, -1, 1};
        for (int j = 0; j < 3; ++j)
            for (int k = 0; k < 3; ++k)
            {
                int new_x = std::min(window.cols - 1, std::max(0, x + inc[j]));
                int new_y = std::min(window.rows - 1, std::max(0, y + inc[k]));
                float dist = get_haffuman_dist(new_x, new_y, point);
                if (dist >= 2.0f)
                    continue;
                window.at<cv::Vec3b>(new_y, new_x)[1] = std::max(window.at<cv::Vec3b>(new_y, new_x)[1], (uint8_t)((2.0f - dist) * 255 / 2.0f));
            }
      
    }
}

int main()
{
    cv::Mat window = cv::Mat(700, 700, CV_8UC3, cv::Scalar(0));
    cv::cvtColor(window, window, cv::COLOR_BGR2RGB);
    cv::namedWindow("Bezier Curve", cv::WINDOW_AUTOSIZE);

    cv::setMouseCallback("Bezier Curve", mouse_handler, nullptr);

    int key = -1;
    while (key != 27) 
    {
        window.setTo(cv::Scalar::all(0));
        for (auto &point : control_points) 
        {
            cv::circle(window, point, 3, {255, 255, 255}, 3);
        }

        // if (control_points.size() == 4) 
        // {
        //     naive_bezier(control_points, window);
            

        //     cv::imshow("Bezier Curve", window);
        //     cv::imwrite("my_bezier_curve.png", window);
        //     key = cv::waitKey(20);

        //     // return 0;
        // }

        if (control_points.size() > 0)
        {
            bezier(control_points, window);
            cv::imwrite("new_bezier_curve.png", window);
        }
            

        cv::imshow("Bezier Curve", window);
        key = cv::waitKey(20);
    }

return 0;
}
