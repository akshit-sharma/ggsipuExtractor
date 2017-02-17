//
// Created by akshi on 1/18/2017.
//

#include <unistd.h>
#include <sys/param.h>
#include <string>
#include <iostream>

#include "GlobalSetting.h"

using namespace std;


GlobalSetting* GlobalSetting::instance = NULL;

GlobalSetting::GlobalSetting() {

    this->getCurrentLoc();
    this->setWorkingLocation(currentLoc);

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

GlobalSetting* GlobalSetting::get(){

    if(!instance)
        instance = new GlobalSetting;

    return GlobalSetting::instance;

}

void GlobalSetting::setWorkingLocation(char *location) {

    string loc(location);

    currentLoc = loc;

    workingLocation = currentLoc;
    workingLocation = workingLocation.append("/ggsipu");

}

void GlobalSetting::setWorkingLocation(string location) {

    currentLoc = location;

    workingLocation = currentLoc;
    workingLocation = workingLocation.append("/ggsipu");

}

string GlobalSetting::getWorkingLocation() {

    return workingLocation;

}

const char * GlobalSetting::getWorkingLocationC() {

    return workingLocation.c_str();

}

std::vector<std::string> GlobalSetting::getWebsiteLinks() {

    std::vector<std::string> website_links;

    for(int i=0; i<4; i++){
        website_links.push_back(websiteLinks[i]);
    }

    return website_links;

}
