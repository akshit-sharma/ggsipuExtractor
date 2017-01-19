//
// Created by akshi on 1/18/2017.
//

#ifndef GGSIPUEXTRACTOR_ONLINEFILESDOWNLOAD_H
#define GGSIPUEXTRACTOR_ONLINEFILESDOWNLOAD_H

#include <string>

class OnlineFilesDownload {
private:
    void _mkdir(const char *dir);
    std::string sendRequest(const char * site);
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
    std::vector<std::string> trimPDFLinks(std::string response);

public:
    OnlineFilesDownload();
    void filesAvailable();

};


#endif //GGSIPUEXTRACTOR_ONLINEFILESDOWNLOAD_H
