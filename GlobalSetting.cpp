//
// Created by akshi on 1/18/2017.
//

#include <unistd.h>
#include <sys/param.h>
#include <string>

#include "GlobalSetting.h"

using namespace std;

GlobalSetting::GlobalSetting() {

    this->getCurrentLoc();
    this->setDownloadLocation(currentLoc);

}

size_t GlobalSetting::getCurrentLoc(){

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        currentLoc = cwd;
    }
    else
        perror("getcwd() error");
    return 0;

}

GlobalSetting& GlobalSetting::get(){

    static GlobalSetting instance;
    return instance;

}

void GlobalSetting::setDownloadLocation(char *location) {

    string loc(location);

    currentLoc = loc;

    downloadLocation = currentLoc;
    downloadLocation = downloadLocation.append("/download");

}

void GlobalSetting::setDownloadLocation(string location) {

    currentLoc = location;

    downloadLocation = currentLoc;
    downloadLocation = downloadLocation.append("/download");

}

string GlobalSetting::getDownloadLocation() {

    return downloadLocation;

}

std::vector<std::string> GlobalSetting::getWebsiteLinks() {

    std::vector<std::string> website_links;

    for(int i=0; i<websiteLinks->size(); i++){
        website_links[i] = websiteLinks[i];
    }

    return website_links;

}
