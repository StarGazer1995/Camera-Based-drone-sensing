//
// Created by Zhao Gong on 10/4/20 at DTU.
//

#ifndef SPECIALCOURSE_CALPHOTO_H
#define SPECIALCOURSE_CALPHOTO_H

#endif //SPECIALCOURSE_CALPHOTO_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace std;
using namespace cv;

class CalPhoto{
    public:
        void Init(VideoCapture capture) {
            if (!capture.isOpened()) {
                cerr << "the Camera is not opened!" << endl;
                return;
            }
            Mat Img;
            capture >> Img;
            Mat Img_with_marker = circuitDetection(Img);
            RotatedRect marker = circuit(Img);
            cout<<"Land place is fould"<<endl;
            cout<<"The center if the place is: "<< marker.center<<endl;
            cout<<"The area if the place is: "<< M_1_PI * marker.size.height * marker.size.width<<endl;
            cout<<"The hight of the camera is: "<<endl; //TODO: I need to calculate it out.
            //marker.center TODO:

        }

        float DisCalculate(Mat &img){
            float dis=0.0;
            return dis;
        }

    private:
        Mat circuitDetection(Mat img){
            Mat gray_img;
            cv::Size2i kernel_size={5,5};
            cv::cvtColor(img,gray_img,cv::COLOR_RGB2GRAY);
            cv::GaussianBlur(gray_img,gray_img,kernel_size,0);
            Mat edge;
            cv::Canny(gray_img,edge,35,125);
            vector<vector<int>> contours;
            Mat hierarchy;
            cv::findContours(edge,contours,hierarchy,cv::RETR_TREE,cv::CHAIN_APPROX_SIMPLE);
            for(auto i:contours){
                if(i.size()>50){
                    double area = cv::contourArea(i);
                    cv::RotatedRect ell = cv::fitEllipse(i);
                    cv::Size2d size = ell.size;
                    double area2 = M_1_PI * size.height * size.width;
                    if(area2/area>0.2){
                        cv::ellipse(img,ell,{0,255,0});
                    }
                }
            }
            return img;
        }
        RotatedRect circuit(Mat img){
            Mat gray_img;
            cv::Size2i kernel_size={5,5};
            cv::cvtColor(img,gray_img,cv::COLOR_RGB2GRAY);
            cv::GaussianBlur(gray_img,gray_img,kernel_size,0);
            Mat edge;
            cv::Canny(gray_img,edge,35,125);
            vector<vector<int>> contours;
            Mat hierarchy;
            cv::findContours(edge,contours,hierarchy,cv::RETR_TREE,cv::CHAIN_APPROX_SIMPLE);
            double area_temp=0.0;
            RotatedRect ans;
            for(auto i:contours){
                if(i.size()>50){
                    double area = cv::contourArea(i);
                    cv::RotatedRect ell = cv::fitEllipse(i);
                    cv::Size2d size = ell.size;
                    double area2 = M_1_PI * size.height * size.width;
                    if(area2/area>0.2){
                        if(area==max(area,area_temp))
                            ans = ell;
                    }
                }
            }
            return ans;
    }
};