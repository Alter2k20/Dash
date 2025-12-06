#include "persistence.hpp"
#include <iostream>

const int cap = 10;

log::Logger::Logger(const std::string& filepath){
    // load existing or create new
       file.open(filepath, std::ios::app);
       if (file.good()) {
           std::cout << "Loading existing data...\n";
           // parse existing file content
       }
}

void log::Logger::log(const std::string& message){
    file << "message : " << message << "\n";
    log_count++;
    if(log_count > 10)
    {
        save_point();
    }
}

void log::Logger::save_point(){
    file << "<SAVE_POINT>\n";
}

void log::Logger::rollback(){
    //Roll back to to previous savepoint
}
