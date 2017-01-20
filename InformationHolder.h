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
            int scheme_prog_code,
            std::string prog_name,
            long scheme_id,
            std::string prog_sem_year,
            std::string prepared_date,
            std::string declared_date,
            int institute_code,
            std::string institution_name,
            int s_no,
            int paper_id,
            std::string paper_code,
            std::string subject_name,
            int credits,
            std::string type,
            std::string exam,
            std::string mode,
            std::string kind,
            int minor,
            int major,
            int max_marks,
            int pass_marks
    );

    void insert_result(
            int scheme_prog_code,
            std::string prepared_date,
            std::string declared_date,
            std::string prog_name,
            std::string prog_sem_year,
            int batch,
            std::string examination,
            int institute_code,
            std::string institute_name,
            long rollnumber,
            std::string name,
            long sid,
            long result_scheme_id,
            int paperCode,
            int credit,
            int minor,
            int major,
            int total
    );

};


#endif //GGSIPUEXTRACTOR_INFORMATIONHOLDER_H
