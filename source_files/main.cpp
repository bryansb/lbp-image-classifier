#include "../header_files/lbp_descriptor.hpp"


int main(int argc, char *argv[]){

    Mat imagen = imread("../resources_files/textura.png", IMREAD_GRAYSCALE);

    LBPDescriptor *lbpd = new LBPDescriptor();

    vector<int> des = lbpd->lbp(imagen);

    for (int i = 0; i < des.size(); i++) {
        cout << des[i] << ", ";
    }

    cout << endl;

    // namedWindow("Textura", WINDOW_AUTOSIZE);
    // imshow("Textura", imagen);
    // waitKey(0);

    cv::destroyAllWindows();
      

    return 0;
}