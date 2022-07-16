#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>


int main() {

        cv::Mat image = cv::imread("Images.jpg", cv::IMREAD_GRAYSCALE);
	cv::Mat dest;
	cv::Mat hist;
	int histSize = 255;
	float range[] = {0, 256}; //the upper boundary is exclusive
        const float* histRange[] = {range};
	bool uniform = true, accumulate = false;
	cv::calcHist(&image, 1, 0, cv::Mat(), hist, 1, &histSize, histRange, uniform, accumulate);
	std::cout << image.cols << " " << image.rows << std::endl;
	/*
	int sum = 0;
	for(int i = 0; i < 255; ++i){
	std::cout<<hist.at<float>(i)<<" ";
	sum += hist.at<float>(i);
	}
	std::cout << std::endl;
	std::cout <<sum << " " << image.cols * image.rows;
	*/
	double omega1 = 0, omega2 = 0;
	double sigmaB = 0;
        long double mean1, mean2;
	double max_sigmaB = 0;
	int thresh = 0;
	for(int i = 0; i < 256; ++i){
	    mean1 = mean2 = 0;
	    omega1 = omega2 = 0;
	    long long count = 0;
	    for(int j = 0; j <= i; ++j){
		omega1 += hist.at<float>(j);
		mean1 += j*hist.at<float>(j);
		count += hist.at<float>(j);
	    }
	    mean1 /= count;
	    //std::cout<<mean1<<" ";
	    omega1 /= (image.cols * image.rows);
	    //std::cout<<omega1<<" ";
	    count = 0;
	    for(int j = i + 1; j < 256; ++j){
	        omega2 += hist.at<float>(j);
		mean2 += j*hist.at<float>(j);
	        count += hist.at<float>(j);
	    }
	    if (count != 0){
	    mean2 /= count;
	    }
	    //std::cout<<mean2<<" ";
	    omega2 /= (image.cols * image.rows);
	    //std::cout<<omega2<<" ";
	    sigmaB = omega1 * omega2 * ((mean1 - mean2) * (mean1 - mean2));
	    if (sigmaB > max_sigmaB) { 
		max_sigmaB = sigmaB;
		thresh = i;
	    }
	}
	std::cout<<"\n\n\n";
	std::cout << thresh;
	cv::Mat destik;
	cv::Mat destik2;
	cv::threshold(image, destik, thresh, 255, cv::THRESH_BINARY);
	cv::threshold(image, destik2, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
	cv::imshow("myalgo", destik);
	cv::imshow("opencv-algo", destik2);
	cv::imshow("image", image);
	cv::waitKey(0);	

}
