#include <iostream>
#include <string>

#include "GlobalSetting.h"


int main(int argc, char** argv) {
    std::cout << "Hello, World!" << std::endl;

    if(argc>=2){
        GlobalSetting::downloadLocation = argv[1];
    }else{
        GlobalSetting::downloadLocation =
    }



    return 0;
}