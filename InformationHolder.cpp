//
// Created by akshit on 20/1/17.
//

#include <unistd.h>
#include <sys/param.h>
#include <string>
#include <iostream>
#include <cstring>

#include "InformationHolder.h"
#include "GlobalSetting.h"


InformationHolder* InformationHolder::instance = NULL;

InformationHolder::InformationHolder() {
    scheme_file_name = GlobalSetting::get()->getWorkingLocation()+"/scheme.csv";
    result_file_name = GlobalSetting::get()->getWorkingLocation()+"/results.csv";

    std::cout<<"scheme_file_name : "<<scheme_file_name<<std::endl;
    std::cout<<"result_file_name : "<<result_file_name<<std::endl;

}

InformationHolder *InformationHolder::get() {

    if(!instance)
        instance = new InformationHolder;

    return InformationHolder::instance;

}

void InformationHolder::open_file_scheme() {
    scheme_stream.open(scheme_file_name, std::ios::out | std::ios::app );

    if(!scheme_stream){
        std::cout<<"error"<<strerror(errno);
        std::string message = scheme_file_name+" not made ";
        throw std::runtime_error(message.c_str());
    }

    scheme_stream<<"scheme_prog_code,prog_name,scheme_id,prog_sem_year,prepared_date,";
    scheme_stream<<"declared_date,institute_code,institution_name,s_no,paper_id,";
    scheme_stream<<"paper_code,subject_name,credits,type,exam,mode,kind,minor,major,";
    scheme_stream<<"max_marks,pass_marks"<<std::endl;

    scheme_stream.flush();

}


void InformationHolder::close_file_scheme() {
    scheme_stream.close();
}

void InformationHolder::close_file_result() {
    result_stream.close();
}

void
InformationHolder::insert_scheme(std::string scheme_prog_code, std::string prog_name, std::string scheme_id, std::string prog_sem_year,
                                 std::string prepared_date, std::string declared_date, std::string institute_code,
                                 std::string institution_name, std::string s_no, std::string paper_id, std::string paper_code,
                                 std::string subject_name, std::string credits, std::string type, std::string exam,
                                 std::string mode, std::string kind, std::string minor, std::string major, std::string max_marks,
                                 std::string pass_marks) {

        scheme_stream<<scheme_prog_code <<","<<prog_name<<","<<scheme_id<<","<<prog_sem_year<<",";
        scheme_stream<<prepared_date<<","<<declared_date<<","<<institute_code<<","<<institution_name<<","<<s_no<<",";
        scheme_stream<<paper_id<<","<<paper_code<<","<<subject_name<<","<<credits<<","<<type<<","<<exam<<",";
        scheme_stream<<mode<<","<<kind<<","<<minor<<","<<major<<","<<max_marks<<","<<pass_marks;
        scheme_stream<<std::endl;

    scheme_stream.flush();

}

void InformationHolder::open_file_result() {
    result_stream.open(result_file_name, std::ios::out | std::ios::app );


    if(!result_stream){
        std::cout<<"error "<<strerror(errno);
        std::string message = result_file_name+" not made ";
        throw std::runtime_error(message.c_str());
    }


    result_stream<<"scheme_prog_code,prepared_date,declared_date,prog_name,prog_sem_year,";
    result_stream<<"batch,examination,institute_code,institute_name,rollnumber,name,sid,";
    result_stream<<"result_scheme_id,paper_code,credit,minor,major,total"<<std::endl;

    result_stream.flush();

}
void InformationHolder::insert_result(std::string scheme_prog_code, std::string prepared_date, std::string declared_date,
                                      std::string prog_name, std::string prog_sem_year, std::string batch,
                                      std::string examination, std::string institute_code, std::string institute_name,
                                      std::string rollnumber, std::string name, std::string sid, std::string result_scheme_id, std::string paperCode,
                                      std::string credit, std::string minor, std::string major, std::string total) {

        result_stream<<scheme_prog_code<<","<<prepared_date<<","<<declared_date<<",";
        result_stream<<prog_name<<","<<prog_sem_year<<","<<batch<<","<<examination<<",";
        result_stream<<institute_code<<","<<institute_name<<","<<rollnumber<<","<<name<<",";
        result_stream<<sid<<","<<result_scheme_id<<","<<paperCode<<","<<credit<<",";
        result_stream<<minor<<","<<major<<","<<total<<std::endl;

    result_stream.flush();

}
