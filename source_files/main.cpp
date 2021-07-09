#include "../header_files/lbp_classifier.hpp"

int main(int argc, char *argv[]){

    LBPClassifier *lblClassifier = new LBPClassifier();
    
    lblClassifier->predict("../resources_files/test", "forest");
    cout << endl;
    cout << endl;
    lblClassifier->predict("../resources_files/test", "buildings");

    return 0;
}