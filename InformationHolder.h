//
// Created by akshit on 20/1/17.
//

#ifndef GGSIPUEXTRACTOR_INFORMATIONHOLDER_H
#define GGSIPUEXTRACTOR_INFORMATIONHOLDER_H


#include <fstream>

class InformationHolder {

private:
    static InformationHolder* instance;
    InformationHolder();

    std::string scheme_file_name;
    std::string result_file_name;

    std::ofstream scheme_stream;
    std::ofstream result_stream;

public:
    static InformationHolder* get();

    void open_file_scheme();
    void open_file_result();
    void close_file_scheme();
    void close_file_result();

    void insert_scheme(
            std::string scheme_prog_code,
            std::string prog_name,
            std::string scheme_id,
            std::string prog_sem_year,
            std::string prepared_date,
            std::string declared_date,
            std::string institute_code,
            std::string institution_name,
            std::string s_no,
            std::string paper_id,
            std::string paper_code,
            std::string subject_name,
            std::string credits,
            std::string type,
            std::string exam,
            std::string mode,
            std::string kind,
            std::string minor,
            std::string major,
            std::string max_marks,
            std::string pass_marks
    );

    void insert_result(
            std::string scheme_prog_code,
            std::string prepared_date,
            std::string declared_date,
            std::string prog_name,
            std::string prog_sem_year,
            std::string batch,
            std::string examination,
            std::string institute_code,
            std::string institute_name,
            std::string rollnumber,
            std::string name,
            std::string sid,
            std::string result_scheme_id,
            std::string paperCode,
            std::string credit,
            std::string minor,
            std::string major,
            std::string total
    );

};


#endif //GGSIPUEXTRACTOR_INFORMATIONHOLDER_H
