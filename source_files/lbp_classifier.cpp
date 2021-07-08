#include "../header_files/lbp_classifier.hpp"

LBPClassifier::LBPClassifier(){}

void LBPClassifier::convertToCIELab(Mat &image){
    cvtColor(image, image, cv::COLOR_BGR2Lab);
}