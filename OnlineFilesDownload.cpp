//
// Created by akshi on 1/18/2017.
//

#include <curl/curl.h>
#include <sys/stat.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <string>

#include "OnlineFilesDownload.h"
#include "GlobalSetting.h"

using namespace std;

OnlineFilesDownload::OnlineFilesDownload() {

    struct stat st = {0};

    GlobalSetting * gs = GlobalSetting::get();

    _mkdir(gs->getDownloadLocationC());

}

void OnlineFilesDownload::filesAvailable(){


    vector<string> websiteLinks = GlobalSetting::get()->getWebsiteLinks();

    vector<string>::iterator iter = websiteLinks.begin();

    while (iter != websiteLinks.end()){

         string readBuffer  = sendRequest((*iter).c_str());

         trimPDFLinks(readBuffer);

         iter++;
    }

}

std::string OnlineFilesDownload::sendRequest(const char * site) {
    CURL *curl;
    CURLcode res;
    string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, site);
        /* example.com is redirected, so we tell libcurl to follow redirection */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);
    }

    cout<<"site : "<<site<<" "<<res<<endl;

    return readBuffer;

}

size_t OnlineFilesDownload::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void OnlineFilesDownload::_mkdir(const char *dir) {

    char tmp[256];
    char *p = NULL;
    size_t len;

    snprintf(tmp, sizeof(tmp),"%s",dir);
    len = strlen(tmp);
    if(tmp[len - 1] == '/')
        tmp[len - 1] = 0;
    for(p = tmp + 1; *p; p++)
        if(*p == '/') {
            *p = 0;
            mkdir(tmp, S_IRWXU);
            *p = '/';
        }
    mkdir(tmp, S_IRWXU);

}

std::vector<std::string> OnlineFilesDownload::trimPDFLinks(std::string response) {

    size_t starting;

    if((starting=response.find("<h2><center><br>EXAMINATIONS RESULTS</center></h2>"))!=std::string::npos){
        size_t start,end;

        start = response.find("<tbody>")+ sizeof("<tbody>");
        end = response.find("<tr class=\"auto-style2\" >");

        std::string table = response.substr(start, end-start);

        response.clear();



    }

    return vector<string>();
}
