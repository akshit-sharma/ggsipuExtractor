#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/param.h>

#include "GlobalSetting.h"
#include "OnlineFilesDownload.h"
#include "InformationHolder.h"


int main(int argc, char** argv) {

    GlobalSetting* gs = GlobalSetting::get();

    if(argc>=2){
        gs->setDownloadLocation(argv[1]);
    }else {
        gs->getCurrentLoc();
    }

    std::string loc = gs->getDownloadLocation();
    std::cout<<"Download location is set to "<<loc<<std::endl;


    InformationHolder::get()->open_file_scheme();
    InformationHolder::get()->open_file_result();

    OnlineFilesDownload ofd;

    ofd.filesAvailable();

    InformationHolder::get()->close_file_result();
    InformationHolder::get()->close_file_scheme();


    return 0;
}