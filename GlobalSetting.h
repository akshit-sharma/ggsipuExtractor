//
// Created by akshi on 1/18/2017.
//

#ifndef GGSIPUEXTRACTOR_GLOBALSETTING_H
#define GGSIPUEXTRACTOR_GLOBALSETTING_H

#include <string>
#include <vector>


class GlobalSetting {
private:
    std::string downloadLocation;
    std::string currentLoc;
    GlobalSetting();

    const std::string websiteLinks [3] = {
            "http://164.100.158.135/ExamResults/ExamResultsmain.htm",
            "http://ggsipuresults.nic.in/ipu/results/resultsmain.htm",
            "http://ggsipuresults.nic.in/ipu/results/resultsmainold231015.htm"
    };

public:
    std::vector<std::string> getWebsiteLinks();

    size_t getCurrentLoc();

    static GlobalSetting &get();

    void setDownloadLocation(char *location);
    void setDownloadLocation(std::string location);
    std::string getDownloadLocation();

};


#endif //GGSIPUEXTRACTOR_GLOBALSETTING_H
