//
// Created by akshi on 1/18/2017.
//

#ifndef GGSIPUEXTRACTOR_GLOBALSETTING_H
#define GGSIPUEXTRACTOR_GLOBALSETTING_H

#include <string>
#include <vector>


class GlobalSetting {
private:
    std::string workingLocation;
    std::string currentLoc;
    static GlobalSetting* instance;

    GlobalSetting();

    const std::string websiteLinks [4] = {
            "http://164.100.158.135/ExamResults/ExamResultsmain.htm",
            "http://ipu.ac.in/exam_results.php",
            "http://ggsipuresults.nic.in/ipu/results/resultsmain.htm",
            "http://ggsipuresults.nic.in/ipu/results/resultsmainold231015.htm"
    };

public:
    bool skip_interactive_mode = true;
    bool skip_request_pdf_list = false;
    bool skip_jdk_download = false;
    bool skip_jdk_extract = false;
    bool skip_pdfbox_download = false;
    bool skip_file_download = false;
    bool skip_file_convert = false;

    std::vector<std::string> getWebsiteLinks();

    size_t getCurrentLoc();

    static GlobalSetting* get();

    void setWorkingLocation(char *location);
    void setWorkingLocation(std::string location);
    std::string getWorkingLocation();
    const char * getWorkingLocationC();

};



#endif //GGSIPUEXTRACTOR_GLOBALSETTING_H
