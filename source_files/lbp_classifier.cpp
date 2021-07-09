#include "../header_files/lbp_classifier.hpp"

LBPClassifier::LBPClassifier(){
    // cout << this->outputClasses << endl;
    // lbpd = new LBPDescriptor();

    
    // this->loadData(rootTestPath, this->imageTestList);

    // for ( Image image :  this->imageTrainList) {
    //     cout << image.getClassLabel() << endl;
    // }

    // cout << imageTrainList.size() <<  endl; 

}

void LBPClassifier::train(string rootTrainPath){
    this->loadData(rootTrainPath, this->imageTrainList);
    for ( Image &image :  this->imageTrainList) {
        image.setCIELabDescriptor();
    }
    saveDescriptorToJson("train.json", this->imageTrainList);
}

void LBPClassifier::predict(string rootTestPath, string observableValue){
    this->loadDescriptorFromJson("train.json", this->imageTrainList);
    this->loadData(rootTestPath, this->imageTestList);

    double minDistance = 0;
    string classLabel;
    bool first = true;
    vector<string> predictionList;
    for ( Image &imageTest : imageTestList ) {
        first = true;
        classLabel = "";
        minDistance = 0;
        for ( Image &imageTrain : imageTrainList ) {
            imageTest.setCIELabDescriptor();
            double distanceL = getEuclideanDistance(imageTest.lChannel, imageTrain.lChannel);
            double distanceA = getEuclideanDistance(imageTest.aChannel, imageTrain.aChannel);
            double distanceB = getEuclideanDistance(imageTest.bChannel, imageTrain.bChannel);

            double distanceTotal = distanceL + distanceA + distanceB;

            if (first) {
                first = false;
                classLabel = imageTrain.getClassLabel();
                minDistance = distanceTotal;
            }

            if ( distanceTotal < minDistance ) {
                classLabel = imageTrain.getClassLabel();
                minDistance = distanceTotal;
            }
        }
        predictionList.push_back(classLabel);
    }

    int nTest = (int)imageTestList.size();
    int tp = 0;
    int tn = 0;
    int fp = 0;
    int fn = 0;
    cout << endl;
    for (int i = 0; i < nTest; i++) {
        bool correct = imageTestList[i].getClassLabel() == predictionList[i] ? true : false;
        
        if (correct && imageTestList[i].getClassLabel() == observableValue) {
            tp += 1;
        } else if (correct && imageTestList[i].getClassLabel() != observableValue) {
            tn += 1;   
        } else if (!correct && imageTestList[i].getClassLabel() == observableValue) {
            fp += 1;
        } else {
            fn += 1;
        }
        cout << "Original: " << imageTestList[i].getClassLabel() << "\t Preddiction: " << predictionList[i] << "\tCorrect: " << correct << endl;
    }

    double precision = (double)tp / ((double)tp + (double)fp);

    cout << endl;
    cout << "Observable Variable: " << observableValue << "\tPrecision: " << precision << endl;
    cout << "TP: " << tp << "\tFN: " << fn << "\tTN: " << tn << "\tFP: " << fp << endl;
}

double LBPClassifier::getEuclideanDistance(vector<int> histogram1, vector<int> histogram2) {
     double distance = 0.0;
    if (histogram1.size() == histogram2.size()) {
        int nHist = (int)histogram1.size();
        distance = 0.0;
        for (int i = 0; i < nHist; i++) {
            distance += distance 
                + pow( (double)histogram1[i] - (double)histogram2[i], 2.0 );
        }
        distance = sqrt(distance);
    } else{
        cout << "\n[ERROR] Classifier::calculateTotalDistance(vector<Mat> hist1, "
        "vector<Mat> hist2) >> histogram1 y histogram2 Deben ser del mismo tamaño" << endl;
    }
    return distance;
}

void LBPClassifier::loadData(string rootPath, vector<Image> &outputData, bool clear){
    if ( clear ) outputData.clear();
    for (auto & p : fs::directory_iterator(rootPath)) {
        vector<string> catPath = split(p.path().string(), '/');
        if (catPath.size() == 1) {
            catPath = split(p.path().string(), '\\');
        }
        string cat = catPath[catPath.size() - 1];
        for (auto & pInside : fs::directory_iterator(rootPath + "/" + cat)){
            Image image(pInside.path().string(), cat);
            outputData.push_back(image);
        }
    }
}

void LBPClassifier::saveDescriptorToJson(string path, vector< Image > imageList){

    string json_to_save = "{";

    for (int i = 0; i < imageList.size(); i++) {
        // descriptorJSON.push_back({imageList[i].getClassLabel(), {{1,2,3}, {1,2,3}, {1,2,3}}});
        string name = imageList[i].getClassLabel() + "-" + to_string(i);
        string lChannel = "[";
        string aChannel = "[";
        string bChannel = "[";

        for (int j = 0; j < imageList[i].lChannel.size(); j++) {
            lChannel += "" + to_string(imageList[i].lChannel[j]);
            aChannel += "" + to_string(imageList[i].aChannel[j]);
            bChannel += "" + to_string(imageList[i].bChannel[j]);

            if (j < imageList[i].lChannel.size() - 1) {
                lChannel += ",";
                aChannel += ",";
                bChannel += ",";
            }
        }

        lChannel += "]";
        aChannel += "]";
        bChannel += "]";

        json_to_save += "\t\"" + name + "\": {\n";
        json_to_save += "\t\t\"l\": " + lChannel + ",\n";
        json_to_save += "\t\t\"a\": " + aChannel + ",\n";
        json_to_save += "\t\t\"b\": " + bChannel + "\n";
        json_to_save += "\t}";

        if (i < imageList.size() - 1) {
            json_to_save += ",";
        }
        json_to_save += "\n";
    }

    json_to_save += "}";
    

    // cout << text << endl;
    json j_complete = json::parse(json_to_save);
    // std::cout << std::setw(4) << j_complete << std::endl;
    std::ofstream o(path, std::ofstream::trunc);
    o << std::setw(4) << j_complete << std::endl;
    o.close();
    cout << "[INFO] Successfully saved " << imageList.size() << " items" << endl;
}

void LBPClassifier::loadDescriptorFromJson(string path, vector<Image> &imageList){
    std::ifstream i(path);
    json j;
    i >> j;

    imageList.clear();
    for (json::iterator it = j.begin(); it != j.end(); ++it) {
        // std::cout << it.key() << " : " << it.value()["a"] << "\n";
        vector<string> classLabel = split(it.key(), '-');
        if (classLabel.size() > 1) {
            Image image("", classLabel[0]);
            image.lChannel = it.value()["l"].get<std::vector<int>>();
            image.aChannel = it.value()["a"].get<std::vector<int>>();
            image.bChannel = it.value()["b"].get<std::vector<int>>();
            imageList.push_back(image);
        } else {
            cout << it.key() << " | Not loaded" << endl;
        }
    }
    i.close();
    cout << "[INFO] Successfully loaded " << imageList.size() << " items" << endl;
}

vector<string> LBPClassifier::split(string cad, char sep){
    stringstream ss;
    ss << cad;
    vector<string> data;

    string token = "";
    while( ( getline(ss, token, sep) ) ){
        data.push_back(token);
    }

    return data;
}