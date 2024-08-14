#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

cv::Mat createTransformation(float angle, float tx, float ty, float sx, float sy, float skew_factor, float persp1, float persp2)
{
    // 1- Translation [ 3x3 transformation matrix represent 2D translation transformation]
    cv::Mat Translation = cv::Mat::eye(3, 3, CV_32F);
    Translation.at<float>(0, 2) = tx;
    Translation.at<float>(1, 2) = ty;

    // 2- Rotation [ 3x3 transformation matrix represent a 2D rotation]
    cv::Mat Rotation = cv::Mat::eye(3, 3, CV_32F);
    Rotation.at<float>(0, 0) = cos(angle);
    Rotation.at<float>(0, 1) = -sin(angle);
    Rotation.at<float>(1, 0) = sin(angle);
    Rotation.at<float>(1, 1) = cos(angle);

    // 3- Scaling [ 3x3 transformation matrix represents a 2D scaling]
    cv::Mat Scale = cv::Mat::eye(3, 3, CV_32F);
    Scale.at<float>(0, 0) = sx;
    Scale.at<float>(1, 1) = sy;

    // 4- Skewing [3x3 transformation matrix that represents a 2D skewing transformation]
    cv::Mat Skew = cv::Mat::eye(3, 3, CV_32F);
    Skew.at<float>(0, 1) = skew_factor;

    cv::Mat Result = Translation * Rotation * Skew * Scale;

    // 5- Perspective transformation [do distortion for the image]
    Result.at<float>(2, 0) = persp1;
    Result.at<float>(2, 1) = persp2;

    return Result;
}

cv::Mat applyTransformation(cv::Mat& img, cv::Mat T, bool isPerspective)
{
    cv::Mat newImg = cv::Mat::zeros(img.size(), CV_8UC3);
    int HEIGHT = img.size().height;
    int WIDTH = img.size().width;

    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            cv::Mat p(3, 1, CV_32F);
            p.at<float>(0, 0) = i;
            p.at<float>(1, 0) = j;
            p.at<float>(2, 0) = 1.f;

            cv::Mat newP = T * p;
            float newZ = 1.f;
            if (isPerspective) // In case of perspective transformation, homogeneous division is needed!
            {
                newZ = newP.at<float>(2, 0);
            }

            int newX = newP.at<float>(0, 0) / newZ;
            int newY = newP.at<float>(1, 0) / newZ;

            if (0 <= newX && newX < HEIGHT && 0 <= newY && newY < WIDTH)
            {
                newImg.at<cv::Vec3b>(newX, newY) = img.at<cv::Vec3b>(i, j);
            }
        }
    }

    return newImg;
}

int main()
{
    cv::Mat img = cv::imread("T:\\OpenCV-4.6.0\\opencv\\sources\\samples\\data\\apple.jpg");

    if (img.empty())
    {
        std::cout << "Couldn't read image!" << std::endl;
        return 0;
    }

    float angle = 0.81; // controls the angle for the translation
    float tx = 200; // controls the horizontal translation, which moves the image left or right.
    float ty = 150; // controls the vertical translation, which moves the image up or down
    float sx = 0.5; // represents the scaling factor in the x-axis. It allows you to stretch or compress the image horizontally.
    float sy = 0.5; // represents the scaling factor in the y-axis. It allows you to stretch or compress the image vertically.
    float skew_factor = 0.2; //  introduces a skew effect to the image. It distorts the image by shearing it along one axis.
    float persp1 = 0.0001; // introduces perspective distortion to the image, specifically along the x-axis.
    float persp2 = 0.002;  // introduces perspective distortion to the image, specifically along the y-axis.

    cv::Mat T = createTransformation(angle, tx, ty, sx, sy, skew_factor, persp1, persp2);
    cv::Mat newImg;

    while (true)
    {
        newImg = applyTransformation(img, T , true); // Update newImg within the loop
        cv::imshow("Transformations", newImg);

        int key = cv::waitKey(3); // Small delay for keyboard input

        if (key == 27) // Escape key
            break;
        else if (key == 'b') // Decrease angle [ Rotation]
            angle -= 0.1;
        else if (key == 'e') // Increase angle [ Rotation]
            angle += 0.1;
        else if (key == 'u') // Increase ty [move up]
            ty += 50;
        else if (key == 'd') // Decrease ty [move down]
            ty -= 50;
        else if (key == 'l') // Decrease tx [move left]
            tx -= 30;
        else if (key == 'r') // Increase tx [move right]
            tx += 30;
        else if (key == 'x') // Decrease scale
            sx -= 0.7;
        else if (key == 'y') // Increase scale
            sx += 0.7;
        else if (key == 'a') // Reset to default
        {
            angle = 0.81;
            tx = 200;
            ty = 150;
            sx = 0.5;
            sy = 0.5;
            skew_factor = 0.2;
            persp1 = 0.0001;
            persp2 = 0.002;
        }

        T = createTransformation(angle, tx, ty, sx, sy, skew_factor, persp1, persp2);
    }

    return 0;
}
