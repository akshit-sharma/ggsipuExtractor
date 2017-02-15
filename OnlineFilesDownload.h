//
// Created by akshi on 1/18/2017.
//

#ifndef GGSIPUEXTRACTOR_ONLINEFILESDOWNLOAD_H
#define GGSIPUEXTRACTOR_ONLINEFILESDOWNLOAD_H

#include <string>
#include <set>

class OnlineFilesDownload {
private:
    void _mkdir(const char *dir);
    std::string sendRequest(const char * site);
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
    void trimPDFLinks(std::set<std::string> &list_of_files, std::string response, const char *url);
    std::string getCorrectFileURL(std::string file, const char * url);
    static void replaceAll(std::string& str, const std::string& from, const std::string& to);
    int download_file(char *outfilename, const char *url);
    inline bool exists_test1 (const std::string& name);
    std::string url_encode(const std::string &value);
    std::string fileName_encode(const std::string &value);

public:
    OnlineFilesDownload();
    void filesAvailable();

};


#endif //GGSIPUEXTRACTOR_ONLINEFILESDOWNLOAD_H
