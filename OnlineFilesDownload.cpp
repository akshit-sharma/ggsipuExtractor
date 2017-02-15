//
// Created by akshi on 1/18/2017.
//

#include <openssl/md5.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <set>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "OnlineFilesDownload.h"
#include "GlobalSetting.h"
#include "InformationExtractor.h"

using namespace std;

OnlineFilesDownload::OnlineFilesDownload() {

    struct stat st = {0};

    GlobalSetting * gs = GlobalSetting::get();

    _mkdir((gs->getDownloadLocation()+"/pdfs").c_str());
    _mkdir((gs->getDownloadLocation()+"/html").c_str());

}

void OnlineFilesDownload::filesAvailable(){

    vector<string> websiteLinks = GlobalSetting::get()->getWebsiteLinks();

    vector<string>::iterator iter = websiteLinks.begin();

    std::set<std::string> list_of_files;

    if(!GlobalSetting::get()->skip_request_pdf_list){

        while (iter != websiteLinks.end()){

             string readBuffer  = sendRequest((*iter).c_str());

             trimPDFLinks(list_of_files, readBuffer, (*iter).c_str());

            cout<<"Pass "<<*iter<<" length of set "<<list_of_files.size()<<endl;

             iter++;
        }

    }else{

        list_of_files.insert("One time pass");

    }

    //Download JDK
    //https://gist.githubusercontent.com/hgomez/4697585/raw/5ba0e8d5a726df92ee069aceac917de4e680bfd0/oracledownload >> shell script >> jdk.tar >> extract
    //http://download.oracle.com/otn-pub/java/jdk/8u112-b15/jdk-8u112-linux-x64.tar.gz >> tar >> extract
    string fileName = GlobalSetting::get()->getDownloadLocation();
    chdir(fileName.c_str());

    if(!GlobalSetting::get()->skip_jdk_download) {
        system("wget --no-cookies --no-check-certificate --header \"Cookie: gpw_e24=http%3A%2F%2Fwww.oracle.com%2F; oraclelicense\" \"http://download.oracle.com/otn-pub/java/jdk/8u112-b15/jdk-8u112-linux-x64.tar.gz\"");
    }
    if(!GlobalSetting::get()->skip_jdk_extract){
        system("tar xf jdk-8u112-linux-x64.tar.gz");
    }


    if(!GlobalSetting::get()->skip_pdfbox_download) {

        // Download http://www-us.apache.org/dist/pdfbox/2.0.4/pdfbox-app-2.0.4.jar
        fileName = GlobalSetting::get()->getDownloadLocation();
        fileName = fileName + "/pdfbox-app-2.0.4.jar";
        char temp[FILENAME_MAX];
        strcpy(temp, fileName.c_str());
        const char *pdfbox_url = "http://www-us.apache.org/dist/pdfbox/2.0.4/pdfbox-app-2.0.4.jar";
        download_file(temp, pdfbox_url);

    }

    string command_name = "jdk1.8.0_112/bin/java -jar pdfbox-app-2.0.4.jar ";
    string command_cmd = "ExtractText ";
    string command_options = "-html ";

    for(set<string>::iterator iter = list_of_files.begin();
            iter != list_of_files.end();    ++iter) {

        int returnValue;

        string temp_name = (*iter).substr((*iter).find_last_of("\\/")+1);
        temp_name = fileName_encode(temp_name);

        string downloadFileName = GlobalSetting::get()->getDownloadLocation()+"/pdfs/"+temp_name+".pdf";

        string outputFile = GlobalSetting::get()->getDownloadLocation()+"/html/"+temp_name+".html";

        string command_full = command_name + command_cmd + command_options + downloadFileName + " " + outputFile;

        if (!GlobalSetting::get()->skip_file_download) {
            char temp[FILENAME_MAX];
            strcpy(temp, downloadFileName.c_str());
            cout << "Downloading " << *iter << endl;
            cout << " to " << downloadFileName << endl;
            download_file(temp, (*iter).c_str());
        }

        returnValue = 0;
        if (!GlobalSetting::get()->skip_file_convert) {
            std::cout<<"Executing cmd : "<<std::endl;
            std::cout<<command_full<<std::endl;
            returnValue = system(command_full.c_str());
            if(returnValue!=0){
                std::cout<<"Value of return is "<<returnValue<<std::endl;
                if(!GlobalSetting::get()->skip_interactive_mode){
                    char input;
                    std::fflush(stderr);
                    std::cout<<"Press c to continue : ";
                    std::fflush(stdout);
                    std::cin>>input;
                    if(input!='c' || input!='C')
                        break;
                }else{
                    perror("Handing parsing error and continuing next ... \n");
                    std::fflush(stderr);
                }
            }
        }

        if(returnValue==0) {
            try {
                InformationExtractor informationExtractor(outputFile);
                informationExtractor.start();
            } catch (runtime_error) {
                std::string message_err = "Error from parsing file " + *iter + "\n";
                perror(message_err.c_str());

                if (!GlobalSetting::get()->skip_interactive_mode) {
                    char input;
                    std::fflush(stderr);
                    std::cout << "Press c to continue : ";
                    std::fflush(stdout);
                    std::cin >> input;
                    if (input != 'c' || input != 'C')
                        break;
                } else {
                    perror("Handing runtime error and continuing next ... \n");
                    std::fflush(stderr);
                }

            }
        }

        if (exists_test1(downloadFileName)) {
            if (remove(downloadFileName.c_str()) != 0)
                perror("Error deleting pdf file");
        }

        if (exists_test1(outputFile)) {
            if (remove(outputFile.c_str()) != 0)
                perror("Error deleting html file");
        }


    }


}

inline bool OnlineFilesDownload::exists_test1 (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
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

    return readBuffer;

}

size_t OnlineFilesDownload::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int OnlineFilesDownload::download_file(char outfilename[FILENAME_MAX], const char * url) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        /* always cleanup */
        curl_easy_cleanup(curl);
        fclose(fp);
    }
    return 0;
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

void OnlineFilesDownload::trimPDFLinks(std::set<std::string> &list_of_files, std::string response, const char *url) {

    size_t starting;

    vector<string> ret;

    size_t start,end;
    size_t length;

    start = response.find("<table>")+ sizeof("<table>");
    end = response.find("</table>",start);

    std::string table = response.substr(start, end-start);
    length = end-start;

    response.clear();

    const char * buffer = table.c_str();
    size_t breakpoint = 0;

    for(size_t i=0; i<length; i++){

        char c = buffer[i];

        if(c=='h' && buffer[i+1]=='r' && buffer[i+2]=='e' && buffer[i+3]=='f'){
            start = table.find('"',i) + 1;
            end = table.find('"',start);
            string partialName = table.substr(start,end-start);
            if(partialName.find("pdf")!=std::string::npos)
                list_of_files.insert(getCorrectFileURL(partialName,url));

            i = end;
        }

    }

}

std::string OnlineFilesDownload::getCorrectFileURL(std::string file, const char * url) {

    std::string url_home = std::string(url);
    std::string web_home = std::string(url);

    url_home = url_home.substr(0, url_home.find("ExamResultsmain.htm"));
    web_home = web_home.substr(0, web_home.find("/",7));

    std::string full_url;

    OnlineFilesDownload::replaceAll(file,"&amp;","&");
    OnlineFilesDownload::replaceAll(file,"&#8211;","-");

    if(file.find("http://") != std::string::npos ){
        full_url = file;
    }else if(file[0]=='/'){
        full_url = web_home.append(file);
    }else{
        full_url = url_home.append(file);
    }

//    cout<<"adding "<<full_url<<endl;

    return url_encode(full_url);
}


std::string OnlineFilesDownload::url_encode(const std::string &value) {
    ostringstream escaped;
    escaped.fill('0');
    escaped << hex;

    for (string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
        string::value_type c = (*i);

        // Keep alphanumeric and other accepted characters intact
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~' || c == ':' || c == '/') {
            escaped << c;
            continue;
        }

        if(c == '%'){
            escaped << c;
            escaped << *(i+1);
            escaped << *(i+2);
            i += 2;
            continue;
        }

        // Any other characters are percent-encoded
        escaped << uppercase;
        escaped << '%' << setw(2) << int((unsigned char) c);
        escaped << nouppercase;
    }

    return escaped.str();
}

std::string OnlineFilesDownload::fileName_encode(const std::string &value) {
    unsigned char result[MD5_DIGEST_LENGTH];
    MD5((unsigned char*)value.c_str(), value.size(), result);

    std::ostringstream sout;
    sout<<std::hex<<std::setfill('0');
    for(long long c: result)
    {
        sout<<std::setw(2)<<(long long)c;
    }
    return sout.str();
}

void OnlineFilesDownload::replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}
