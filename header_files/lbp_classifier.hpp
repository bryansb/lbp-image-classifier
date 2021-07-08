#ifndef OPENCV_HEADERS_INCLUDED
#define OPENCV_HEADERS_INCLUDED
    #include "../header_files/opencv_headers.hpp"
#endif

class LBPClassifier {
    private:

    public:
        LBPClassifier();

        void convertToCIELab(Mat &image);
};