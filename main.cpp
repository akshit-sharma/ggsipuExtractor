#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/param.h>

#include "GlobalSetting.h"



int main(int argc, char** argv) {
    std::cout << "Hello, World!" << std::endl;

    GlobalSetting gs = GlobalSetting::get();

    if(argc>=2){
        gs.setDownloadLocation(argv[1]);
    }else{

        gs.getCurrentLoc();
        std::string loc = gs.getDownloadLocation();

        std::cout<<"Download location is set to "<<loc;

    }





    return 0;
}