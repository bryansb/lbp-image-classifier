#ifndef BASE_INCLUDED
#define BASE_INCLUDED
    #include "./base.hpp"
#endif

#ifndef OPENCV_HEADERS_INCLUDED
#define OPENCV_HEADERS_INCLUDED
    #include "./opencv_headers.hpp"
#endif

#include "../header_files/lbp_descriptor.hpp"

class Image {

    private:
        string classLabel;
        string imagePath;

        LBPDescriptor *lbpd;

        void convertToCIELab(Mat &img);

    public:
        vector<int> lChannel;
        vector<int> aChannel;
        vector<int> bChannel;

        Image(string imagePath, string classLabel = "empty");
        cv::Mat readImage();

        void setCIELabDescriptor();

        string getClassLabel();
        string getImage();
};