#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/param.h>

#include "GlobalSetting.h"
#include "OnlineFilesDownload.h"


int main(int argc, char** argv) {

    GlobalSetting* gs = GlobalSetting::get();

    if(argc>=2){
        gs->setDownloadLocation(argv[1]);
    }else {
        gs->getCurrentLoc();
    }

    std::string loc = gs->getDownloadLocation();
    std::cout<<"Download location is set to "<<loc<<std::endl;

    OnlineFilesDownload ofd;

    ofd.filesAvailable();



    return 0;
}