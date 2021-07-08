#ifndef BASE_INCLUDED
#define BASE_INCLUDED
    #include "./base.hpp"
#endif

#ifndef OPENCV_HEADERS_INCLUDED
#define OPENCV_HEADERS_INCLUDED
    #include "./opencv_headers.hpp"
#endif

#ifndef IMAGE_INCLUDED
#define IMAGE_INCLUDED
    #include "image.hpp"
#endif

#include <iomanip>

#include <fstream>

#include <experimental/filesystem>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace fs =  std::experimental::filesystem;

class LBPClassifier {
    private:
        // LBPDescriptor *lbpd;
        
        vector<Image> imageTrainList;
        vector<Image> imageTestList;

        double getEuclideanDistance(vector<int> histogram1, vector<int> histogram2);
        void loadData(string rootPath, vector<Image> &outputData, bool clear = true);

        void saveDescriptorToJson(string path, vector< Image > imageList);
        void loadDescriptorFromJson(string path, vector< Image > &imageList);

    public:
        const string OUTPUT_CLASSES [2] = {"forest", "buildings"};

        LBPClassifier();
        void train(string rootTrainPath);
        void predict(string rootTestPath);

        vector<string> split(string cad, char sep);
};