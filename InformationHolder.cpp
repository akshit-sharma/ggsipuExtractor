//
// Created by akshit on 20/1/17.
//

#include <unistd.h>
#include <sys/param.h>
#include <string>
#include <iostream>

#include "InformationHolder.h"
#include "GlobalSetting.h"


InformationHolder* InformationHolder::instance = NULL;

InformationHolder::InformationHolder() {
    scheme_file_name = GlobalSetting::get()->getDownloadLocation()+"/scheme.csv";
    result_file_name = GlobalSetting::get()->getDownloadLocation()+"/results.csv";
}

InformationHolder *InformationHolder::get() {

    if(!instance)
        instance = new InformationHolder;

    return InformationHolder::instance;

}

void InformationHolder::open_file_scheme() {
    scheme_stream.open(scheme_file_name, std::ios::out | std::ios::app );

    scheme_stream<<"scheme_prog_code,prog_name,scheme_id,prog_sem_year,prepared_date,";
    scheme_stream<<"declared_date,institute_code,institution_name,s_no,paper_id,";
    scheme_stream<<"paper_code,subject_name,credits,type,exam,mode,kind,minor,major,";
    scheme_stream<<"max_marks,pass_marks"<<std::endl;

}


void InformationHolder::close_file_scheme() {
    scheme_stream.close();
}

void InformationHolder::close_file_result() {
    result_stream.close();
}

void
InformationHolder::insert_scheme(int scheme_prog_code, std::string prog_name, long scheme_id, std::string prog_sem_year,
                                 std::string prepared_date, std::string declared_date, int institute_code,
                                 std::string institution_name, int s_no, int paper_id, std::string paper_code,
                                 std::string subject_name, int credits, std::string type, std::string exam,
                                 std::string mode, std::string kind, int minor, int major, int max_marks,
                                 int pass_marks) {

        scheme_stream<<scheme_prog_code <<","<<prog_name<<","<<scheme_id<<","<<prog_sem_year<<",";
        scheme_stream<<prepared_date<<","<<declared_date<<","<<institute_code<<","<<institution_name<<","<<s_no<<",";
        scheme_stream<<paper_id<<","<<paper_code<<","<<subject_name<<","<<credits<<","<<type<<","<<exam<<",";
        scheme_stream<<mode<<","<<kind<<","<<minor<<","<<major<<","<<max_marks<<","<<pass_marks;
        scheme_stream<<std::endl;

}

void InformationHolder::open_file_result() {
    result_stream.open(result_file_name, std::ios::out | std::ios::app );

    result_stream<<"scheme_prog_code,prepared_date,declared_date,prog_name,prog_sem_year,";
    result_stream<<"batch,examination,institute_code,institute_name,rollnumber,name,sid,";
    result_stream<<"result_scheme_id,credit,minor,major,total"<<std::endl;

}
void InformationHolder::insert_result(int scheme_prog_code, std::string prepared_date, std::string declared_date,
                                      std::string prog_name, std::string prog_sem_year, int batch,
                                      std::string examination, int institute_code, std::string institute_name,
                                      long rollnumber, std::string name, long sid, long result_scheme_id, int paperCode,
                                      int credit, int minor, int major, int total) {

        result_stream<<scheme_prog_code<<","<<prepared_date<<","<<declared_date<<",";
        result_stream<<prog_name<<","<<prog_sem_year<<","<<batch<<","<<examination<<",";
        result_stream<<institute_code<<","<<institute_name<<","<<rollnumber<<","<<name<<",";
        result_stream<<sid<<","<<result_scheme_id<<","<<paperCode<<","<<credit<<",";
        result_stream<<minor<<","<<major<<","<<total<<std::endl;

}
