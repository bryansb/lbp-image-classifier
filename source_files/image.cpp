#include "../header_files/image.hpp"

Image::Image(string imagePath, string classLabel){
    this->imagePath = imagePath;
    this->classLabel = classLabel;

    lbpd = new LBPDescriptor();
}

cv::Mat Image::readImage(){
    return cv::imread(imagePath);
}

void Image::convertToCIELab(Mat &img){
    cvtColor(img, img, cv::COLOR_BGR2Lab);
}

void Image::setCIELabDescriptor(){
    Mat img = readImage();
    convertToCIELab(img);

    vector<Mat> channels;
    split(img, channels);

    this->lChannel = lbpd->lbp(channels[0]);
    this->aChannel = lbpd->lbp(channels[1]);
    this->bChannel = lbpd->lbp(channels[2]);

    // cout << lChannel[0]<< endl;
}

string Image::getClassLabel() {
    return classLabel;
}

string Image::getImage(){
    return imagePath;
}
