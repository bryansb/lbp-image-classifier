#include "../header_files/lbp_classifier.hpp"

int main(int argc, char *argv[]){

    LBPClassifier *lblClassifier = new LBPClassifier();

    /**
     * Una vez realizado el entrenamiento, comentar la misma y descomentar
     * la predicción (predict).
     **/
    lblClassifier->train("../resources_files/train");
    // lblClassifier->predict("../resources_files/test", "forest");


    /*
        Las siguientes líneas corresponde al Corpus más extenso y variado.
    */
    // lblClassifier->train("../resources_files/corpus-extendido/train");
    // lblClassifier->predict("../resources_files/corpus-extendido/test", "buildings", false);
    // cout << endl;
    // lblClassifier->predict("../resources_files/corpus-extendido/test", "forest", false);
    // cout << endl;
    // lblClassifier->predict("../resources_files/corpus-extendido/test", "glacier", false);
    // cout << endl;
    // lblClassifier->predict("../resources_files/corpus-extendido/test", "mountain", false);
    // cout << endl;
    // lblClassifier->predict("../resources_files/corpus-extendido/test", "sea", false);
    // cout << endl;
    // lblClassifier->predict("../resources_files/corpus-extendido/test", "street", false);
    // cout << endl;

    return 0;
}