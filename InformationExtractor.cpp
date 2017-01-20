//
// Created by akshit on 20/1/17.
//

#include <cstring>
#include <iostream>
#include <set>
#include "InformationExtractor.h"
#include "InformationHolder.h"


using namespace std;


InformationExtractor::InformationExtractor(string outputFile) {

    this->outputFile = outputFile;

}

void InformationExtractor::start(){

    ifstream inputFile(outputFile);
    //inputFile.open(outputFile,ios::in);

    cout<<"openning file : "<<outputFile<<endl;

    std::string line;

    int LineNumber = 0;

    int scheme_prog_code = 0;
    std::string prog_name;
    long scheme_id = 0;
    std::string prog_sem_year;
    std::string prepared_date;
    std::string declared_date;
    int institute_code = 0;
    std::string institution_name;
    int batch = 0;
    std::string examination;

    long roll_number;
    std::string name;
    long sid;
    long result_scheme_id;

    int paperCode;
    int credit;
    int minor;
    int major;
    int total;

    enum what_parsed_last {
        RTSID, RollNumber, Name, SID, SchemeID, PaperCode, Minor_Major, Total, Credits
    };

    enum what_parsed_last stateHolder;

    while(std::getline(inputFile, line)){

        LineNumber++;

        size_t pos;

        if (scheme) {


            size_t posi = line.find("Scheme of Programme Code:");

            if (posi != std::string::npos) {

                posi += strlen("Scheme of Programme Code:");

                while (line[posi] == ' ')
                    posi++;

                scheme_prog_code = 0;
                while (line[posi] >= '0' && line[posi] <= '9') {
                    scheme_prog_code *= 10;
                    scheme_prog_code += (line[posi] - '0');
                    posi++;
                }

                if (scheme_prog_code == 0) {
                    string message = "Scheme of Programme Code not found At LineNumber ";
                    throw std::runtime_error(message.c_str());
                }

            }

            size_t posi_programme = line.find("Programme Name:");

            if (posi_programme != std::string::npos) {

                posi_programme += strlen("Programme Name:");

                while (line[posi_programme] == ' ')
                    posi_programme++;

                size_t posi_programme_end = line.find("SchemeID");

                prog_name = "";
                prog_name = line.substr(posi_programme,posi_programme_end-posi_programme);

                prog_name = trim(prog_name);

                if (prog_name.length() <= 1) {
                    string message = "Programme Name not found At LineNumber ";
                    throw std::runtime_error(message.c_str());
                }

            }

            size_t posi_sch = line.find("SchemeID:");

            if (posi_sch != std::string::npos) {

                posi_sch += strlen("SchemeID:");

                while (line[posi_sch] == ' ')
                    posi_sch++;

                scheme_id = 0;
                while (line[posi_sch] >= '0' && line[posi_sch] <= '9') {
                    scheme_id *= 10;
                    scheme_id += (line[posi_sch] - '0');
                    posi_sch++;
                }

                if (scheme_id == 0) {
                    string message =  "SchemeID not found At LineNumber ";
                    throw std::runtime_error(message.c_str());
                }

            }

            size_t posi_sem_year = line.find("Sem./Year:");

            if (posi_sem_year != std::string::npos) {

                posi_sem_year += strlen("Sem./Year:");

                while (line[posi_sem_year] == ' ')
                    posi_sem_year++;

                prog_sem_year = "";
                while (line[posi_sem_year]!='\0') {
                    prog_sem_year += line[posi_sem_year];
                    posi_sem_year++;
                }

                if (prog_sem_year.length()<=3) {
                    string message = "Sem./Year not found At LineNumber ";
                    throw std::runtime_error(message.c_str());
                }


            }

            size_t posi_pre_date = line.find("Prepared Date:");

            if (posi_pre_date != std::string::npos) {

                posi_pre_date += strlen("Prepared Date:");

                while (line[posi_pre_date] == ' ')
                    posi_pre_date++;

                prepared_date = "";
                while ((line[posi_pre_date]!='\0')&&line[posi_pre_date]!=' ') {
                    prepared_date += line[posi_pre_date];
                    posi_pre_date++;
                }

                if (prepared_date.length() <= 1) {
                    string message = "Prepared date not found At LineNumber ";
                    throw std::runtime_error(message.c_str());
                }

            }

            size_t posi_dec_date = line.find("Declared Date:");

            if (posi_dec_date != std::string::npos) {

                posi_dec_date += strlen("Declared Date:");

                while (line[posi_dec_date] == ' ')
                    posi_dec_date++;

                declared_date = "";
                while ((line[posi_dec_date]!='\0')&&line[posi_dec_date]!=' ') {
                    declared_date += line[posi_dec_date];
                    posi_dec_date++;
                }

                if (declared_date.length() <= 1) {
                    string message = "Declared date not found At LineNumber ";
                    throw std::runtime_error(message.c_str());
                }

            }

            size_t posi_insti_code = line.find("Institution Code:");

            if (posi_insti_code != std::string::npos) {

                posi_insti_code += strlen("Institution Code:");

                while (line[posi_insti_code] == ' ')
                    posi_insti_code++;

                institute_code = 0;
                while (line[posi_insti_code] >= '0' && line[posi_insti_code] <= '9') {
                    institute_code *= 10;
                    institute_code += (line[posi_insti_code] - '0');
                    posi_insti_code++;
                }

                if (institute_code == 0) {
                    string message =  "Scheme of Programme not found At LineNumber ";
                    throw std::runtime_error(message.c_str());
                }

            }

            size_t posi_insti_name = line.find("Institution:");

            if (posi_insti_name != std::string::npos) {

                posi_insti_name += strlen("Institution:");

                while (line[posi_insti_name] == ' ')
                    posi_insti_name++;

                institution_name = "";
                while ((line[posi_insti_name]!='\0')) {
                    institution_name += line[posi_insti_name];
                    posi_insti_name++;
                }

                if (institution_name.length() <= 1) {
                    string message = "Institution name not found At LineNumber ";
                    throw std::runtime_error(message.c_str());
                }

            }

            if(line.find("<p><b>")==0){
                size_t position = 6;

                if(line[position]>='0' && line[position]<='9') {
                    int s_no;
                    int paper_id;
                    std::string paper_code;
                    std::string subject_name;
                    int credits;
                    std::string type;
                    std::string exam;
                    std::string mode;
                    std::string kind;
                    int minor;
                    int major;
                    int max_marks;
                    int pass_marks;

                    s_no = 0;
                    do {
                        s_no *= 10;
                        s_no += line[position] - '0';
                        position++;
                    }while(line[position]>='0' && line[position]<='9');

                    while(line[position]==' ')
                        position++;

                    paper_id = 0;
                    do {
                        paper_id *= 10;
                        paper_id += line[position] - '0';
                        position++;
                    }while(line[position]>='0' && line[position]<='9');

                    while(line[position]==' ')
                        position++;

                    paper_code = "";
                    do {
                        paper_code += line[position];
                        position++;
                    }while(line[position] != ' ');

                    while(line[position]==' ')
                        position++;

                    subject_name = "";
                    do {
                        subject_name += line[position];
                        position++;
                    }while(((line[position] != ' ') && (line[position+1] != ' '))
                           || (((line[position] != ' ')) &&
                            ((line[position+1]>='0' && line[position+1]<='9'))));

                    while(line[position]==' ')
                        position++;

                    credits = 0;
                    do {
                        credits *= 10;
                        credits += line[position]-'0';
                        position++;
                    }while((line[position]>='0' && line[position]<='9'));

                    while(line[position]==' ')
                        position++;

                    type = "";
                    do {
                        type += line[position];
                        position++;
                    }while(line[position] != ' ');

                    while(line[position]==' ')
                        position++;

                    exam = "";
                    do {
                        exam += line[position];
                        position++;
                    }while(line[position] != ' ');

                    while(line[position]==' ')
                        position++;

                    mode = "";
                    do {
                        mode += line[position];
                        position++;
                    }while(line[position] != ' ');

                    while(line[position]==' ')
                        position++;

                    kind = "";
                    do {
                        kind += line[position];
                        position++;
                    }while(line[position] != ' ');

                    while(line[position]==' ')
                        position++;

                    minor = 0;
                    if(line[position]=='-' && line[position+1]=='-')
                        minor = 0;
                    else{
                        minor = 0;
                        do {
                            minor *= 10;
                            minor += line[position]-'0';
                            position++;
                        }while((line[position]>='0' && line[position]<='9'));
                    }

                    while(line[position]==' ')
                        position++;

                    major = 0;
                    if(line[position]=='-' && line[position+1]=='-')
                        major = 0;
                    else{
                        major = 0;
                        do {
                            major *= 10;
                            major += line[position]-'0';
                            position++;
                        }while((line[position]>='0' && line[position]<='9'));
                    }

                    while(line[position]==' ')
                        position++;

                    max_marks = 0;
                    if(line[position]=='-' && line[position+1]=='-')
                        max_marks = 0;
                    else{
                        max_marks = 0;
                        do {
                            max_marks *= 10;
                            max_marks += line[position]-'0';
                            position++;
                        }while((line[position]>='0' && line[position]<='9'));
                    }

                    while(line[position]==' ')
                        position++;

                    pass_marks = 0;
                    if(line[position]=='-' && line[position+1]=='-')
                        pass_marks = 0;
                    else{
                        pass_marks = 0;
                        do {
                            pass_marks *= 10;
                            pass_marks += line[position]-'0';
                            position++;
                        }while((line[position]>='0' && line[position]<='9'));
                    }

                    InformationHolder * informationHolder = InformationHolder::get();
                    informationHolder->insert_scheme(scheme_prog_code,prog_name,scheme_id, prog_sem_year,
                                                        prepared_date, declared_date, institute_code, institution_name,
                                                        s_no, paper_id, paper_code, subject_name, credits, type, exam,
                                                        mode, kind, minor, major, max_marks, pass_marks);

                }

            }else if(line.find("</b></p>")!=std::string::npos
                     || line.find("</div></div>")!=std::string::npos
                     || line[0]=='\0'){

            }else{
                string message = "Parser not ready for this file not found At LineNumber ";
                cout<<message<<endl;
//                throw std::runtime_error(message.c_str());
            }


        }

        if(result){

            size_t posi = line.find("Result of Programme Code:");

            if (posi != std::string::npos) {

                posi += strlen("Result of Programme Code:");

                while (line[posi] == ' ')
                    posi++;

                while (line[posi] >= '0' && line[posi] <= '9') {
                    scheme_prog_code *= 10;
                    scheme_prog_code += (line[posi] - '0');
                    posi++;
                }

                if (scheme_prog_code == 0) {
                    string message = "Result of Programme Code not found At LineNumber ";
                    throw std::runtime_error(message.c_str());
                }

            }

            size_t posi_pre_date = line.find("Result Prepared on:");

            if (posi_pre_date != std::string::npos) {

                posi_pre_date += strlen("Result Prepared on:");

                while (line[posi_pre_date] == ' ')
                    posi_pre_date++;

                prepared_date = "";
                while ((line[posi_pre_date]!='\0')&&line[posi_pre_date]!=' ') {
                    prepared_date += line[posi_pre_date];
                    posi_pre_date++;
                }

                if (prepared_date.length() <= 1) {
                    string message = "Result prepared date not found At LineNumber ";
                    throw std::runtime_error(message.c_str());
                }

            }

            size_t posi_dec_date = line.find("Result Declared on:");

            if (posi_dec_date != std::string::npos) {

                posi_dec_date += strlen("Result Declared on:");

                while (line[posi_dec_date] == ' ')
                    posi_dec_date++;

                declared_date = "";
                while ((line[posi_dec_date]!='\0')&&line[posi_dec_date]!=' ') {
                    declared_date += line[posi_dec_date];
                    posi_dec_date++;
                }

                if (declared_date.length() <= 1) {
                    string message = "Result declared date not found At LineNumber ";
                    throw std::runtime_error(message.c_str());
                }

            }


            size_t posi_programme = line.find("Programme Name:");

            if (posi_programme != std::string::npos) {

                posi_programme += strlen("Programme Name:");

                while (line[posi_programme] == ' ')
                    posi_programme++;

                size_t posi_programme_end = line.find("SchemeID");

                prog_name = "";
                prog_name = line.substr(posi_programme,posi_programme_end-posi_programme);

                prog_name = trim(prog_name);

                if (prog_name.length() <= 1) {
                    string message = "Programme Name not found At LineNumber ";
                    throw std::runtime_error(message.c_str());
                }

            }


            size_t posi_sem_year = line.find("Sem./Year:");

            if (posi_sem_year != std::string::npos) {

                posi_sem_year += strlen("Sem./Year:");

                while (line[posi_sem_year] == ' ')
                    posi_sem_year++;

                prog_sem_year = "";
                while (!(line[posi_sem_year] == ' ' && line[posi_sem_year+1] == ' ')) {
                    prog_sem_year += line[posi_sem_year];
                    posi_sem_year++;
                }

                if (prog_sem_year.length()<=3) {
                    string message = "Sem./Year not found At LineNumber ";
                    throw std::runtime_error(message.c_str());
                }


            }

            size_t posi_batch = line.find("Batch:");

            if (posi_batch != std::string::npos) {

                posi_batch += strlen("Batch:");

                while (line[posi_batch] == ' ')
                    posi_batch++;

                batch = 0;
                while (line[posi_batch] >= '0' && line[posi_batch] <= '9') {
                    batch *= 10;
                    batch += (line[posi_batch] - '0');
                    posi_batch++;
                }

                if (batch == 0) {
                    string message =  "Batch not found At LineNumber ";
                    throw std::runtime_error(message.c_str());
                }

            }

            size_t posi_examination = line.find("Examination:");

            if (posi_examination != std::string::npos) {

                posi_examination += strlen("Examination:");

                while (line[posi_examination] == ' ')
                    posi_examination++;

                examination = "";
                while (line[posi_examination]!='\0') {
                    examination += line[posi_examination];
                    posi_examination++;
                }

                if (examination.length()<=3) {
                    string message = "Examination not found At LineNumber ";
                    throw std::runtime_error(message.c_str());
                }


            }

            size_t posi_insti_code = line.find("Institution Code:");

            if (posi_insti_code != std::string::npos) {

                posi_insti_code += strlen("Institution Code:");

                while (line[posi_insti_code] == ' ')
                    posi_insti_code++;

                institute_code = 0;
                while (line[posi_insti_code] >= '0' && line[posi_insti_code] <= '9') {
                    institute_code *= 10;
                    institute_code += (line[posi_insti_code] - '0');
                    posi_insti_code++;
                }

                if (institute_code == 0) {
                    string message =  "Scheme of Programme not found At LineNumber ";
                    throw std::runtime_error(message.c_str());
                }

            }

            size_t posi_insti_name = line.find("Institution:");

            if (posi_insti_name != std::string::npos) {

                posi_insti_name += strlen("Institution:");

                while (line[posi_insti_name] == ' ')
                    posi_insti_name++;

                institution_name = "";
                while ((line[posi_insti_name]!='\0')) {
                    institution_name += line[posi_insti_name];
                    posi_insti_name++;
                }

                if (institution_name.length() <= 1 ) {
                    string message = "Institution name not found At LineNumber ";
                    throw std::runtime_error(message.c_str());
                }

            }

            if(line.find("RTSID")!=std::string::npos){
                stateHolder = RTSID;
            }

            if(line.find("<p><b>")==0){
                size_t position = 6;

                if(line[position]>='0' && line[position]<='9') {

                    if(stateHolder == RTSID || stateHolder == credit){

                        roll_number = 0;
                        do {
                            roll_number *= 10;
                            roll_number += line[position]-'0';
                            position++;
                        }while(line[position]>='0' && line[position]<='9');

                        stateHolder = RollNumber;

                    }
                }

            }

            if(line.find("<p><b>")==0){
                size_t position = 6;

                if(line[position]>='A' && line[position]<='Z') {

                    if(stateHolder == RollNumber){

                        name = "";
                        do {
                            name += line[position];
                            position++;
                        }while(line[position]!='\0');

                        stateHolder = Name;

                    }
                }

            }

            if(line.find("<p><b>SID:")!=std::string::npos){
                size_t position = 10;

                while(line[position]==' ')
                    position++;

                if(stateHolder==Name){

                    sid = 0;
                    do {
                        sid *= 10;
                        sid += line[position]-'0';
                        position++;
                    }while(line[position]>='0' && line[position]<='9');

                    stateHolder = SID;

                }

            }
            if(line.find("<p><b>SchemeID:")!=std::string::npos){
                size_t position = 15;

                while(line[position]==' ')
                    position++;

                if(stateHolder==SID){

                    result_scheme_id = 0;
                    do {
                        result_scheme_id *= 10;
                        result_scheme_id += line[position]-'0';
                        position++;
                    }while(line[position]>='0' && line[position]<='9');

                    stateHolder = SchemeID;

                }

            }

            if(line.find("<p><b>")==0){
                size_t position = 6;

                if(line[position]>='0' && line[position]<='9') {

                    if((stateHolder == SchemeID || stateHolder == Total)
                       &&  (line.find('(')!=std::string::npos)){

                        paperCode = 0;
                        do {
                            paperCode *= 10;
                            paperCode += line[position]-'0';
                            position++;
                        }while(line[position]>='0' && line[position]<='9');

                        if(line[position]!='('){
                            string message = "Paper code not found At LineNumber ";
                            throw std::runtime_error(message.c_str());
                        }
                        position++;

                        credit = 0;
                        do {
                            credit *= 10;
                            credit += line[position]-'0';
                            position++;
                        }while(line[position]>='0' && line[position]<='9');

                        stateHolder = PaperCode;

                    }
                }

            }

            if(line.find("<p><b>")==0) {
                size_t position = 6;

                while(line[position]==' ')
                    position++;

                if(stateHolder == paperCode){

                    minor = 0;
                    do {
                        minor *= 10;
                        minor += line[position]-'0';
                        position++;
                    }while(line[position]>='0' && line[position]<='9');

                    while(line[position]==' ')
                        position++;

                    major = 0;
                    do {
                        major *= 10;
                        major += line[position]-'0';
                        position++;
                    }while(line[position]>='0' && line[position]<='9');

                    stateHolder = Minor_Major;

                }

                if(line.find("<p><b>")==0) {
                    size_t position = 6;

                    while (line[position] == ' ')
                        position++;

                    if (stateHolder == Minor_Major) {

                        total = 0;
                        do {
                            total *= 10;
                            total += line[position] - '0';
                            position++;
                        } while (line[position] >= '0' && line[position] <= '9');

                        stateHolder = Total;

                        InformationHolder * informationHolder = InformationHolder::get();
                        informationHolder->insert_result(scheme_prog_code, prepared_date,
                                declared_date, prog_name, prog_sem_year,  batch,
                                examination, institute_code, institution_name, roll_number,
                                name, sid, result_scheme_id, paperCode, credit, minor,
                                major, total);


                    }

                }

                if(line.find("<p><b>")==0) {
                    size_t position = 6;

                    while (line[position] == ' ')
                        position++;

                    if (stateHolder == Total) {

                        int temp = 0;
                        do {
                            temp *= 10;
                            temp += line[position] - '0';
                            position++;
                        } while (line[position] >= '0' && line[position] <= '9');

                        stateHolder = Credits;

                    }
                }
            }


        }

        if (line.find("(SCHEME OF EXAMINATIONS)") != std::string::npos) {
            scheme = true;
            result = false;
        }else if (line.find("RESULT TABULATION SHEET") != std::string::npos) {
            scheme = false;
            result = true;
        }else if(line.find("</div>") != std::string::npos){
            scheme = false;
            result = false;
        }

    }




   // inputFile.close();

}

string InformationExtractor::trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

bool InformationExtractor::both_false(){
    return scheme || result;
}