//
// Created by akshit on 20/1/17.
//

#ifndef GGSIPUEXTRACTOR_INFORMATIONEXTRACTOR_H
#define GGSIPUEXTRACTOR_INFORMATIONEXTRACTOR_H


#include <fstream>

class InformationExtractor {

private:

    bool scheme = false;
    bool result = false;

    bool both_false();

    std::string outputFile;

public:
    InformationExtractor(std::string outputFile);
    void start();


    struct schemeHolder{

    };

};


#endif //GGSIPUEXTRACTOR_INFORMATIONEXTRACTOR_H
