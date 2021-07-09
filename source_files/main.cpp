#include "../header_files/lbp_classifier.hpp"

int main(int argc, char *argv[]){

    setlocale(LC_ALL, "");

    // Mat imagen = imread("../resources_files/textura.png", IMREAD_GRAYSCALE);

    // LBPDescriptor *lbpd = new LBPDescriptor();

    // vector<int> des = lbpd->lbp(imagen);

    // for (int i = 0; i < des.size(); i++) {
    //     cout << des[i] << ", ";
    // }

    // cout << endl;

    LBPClassifier *lblClassifier = new LBPClassifier();
    // lblClassifier->train("../resources_files/train");
    lblClassifier->predict("../resources_files/test", "forest");
    cout << endl;
    cout << endl;
    lblClassifier->predict("../resources_files/test", "buildings");

    // lblClassifier->printMap(lblClassifier->OUTPUT_CLASSES);

    // cout << lblClassifier->OUTPUT_CLASSES << endl;
    // namedWindow("Textura", WINDOW_AUTOSIZE);
    // imshow("Textura", imagen);
    // waitKey(0);

    // cv::destroyAllWindows();
      

    return 0;
}