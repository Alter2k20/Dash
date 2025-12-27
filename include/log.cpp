#include "log.hpp"
#include <iostream>

const int cap = 10;

Log::Logger::Logger(const std::string& filepath){
    // load existing or create new
       file.open(filepath, std::ios::app);
       if (file.is_open()) {
           file_status  = true;
           // parse existing file content
       }else{
           std::cout << "No Log File\n";
       }
}

void Log::Logger::log(const std::string& message){
    file << "message : " << message << "\n";
    log_count++;
    if(log_count == 10)
    {
        save_point();
        log_count = 0;
    }
}

void Log::Logger::save_point(){
    file << "<SAVE_POINT>\n";
}

void Log::Logger::rollback(){
    //Roll back to to previous savepoint
}

Backup::BackupUnit::BackupUnit(const std::string& filepath) {
    file.open(filepath, std::ios::app);
    if (file.is_open()) {
        backup_status = true;
        // parse existing file content
    }
    else {
        std::cout << "Cannot open file File\n";
    }
}

int Backup::BackupUnit::Backup(const std::unordered_map<std::string, std::string>& data) {
    if (!backup_status) {
        return 0; 
	}
    for (const auto& [key, value] : data) {
        file << key << '\t' << value << '\n'; // or a safer serialization
    }

	return 1; 
}

void Backup::BackupUnit::Restore(const std::string& filepath) {
    file.open(filepath, std::ios::out);
    if (!file.is_open()) {
        std::cout << "Cannot open file File\n";
        return;
	}

    data.clear();

    std::string line;
    std::ifstream in(filepath);
    while (std::getline(in, line)) {
        auto pos = line.find('\t');
        if (pos == std::string::npos) continue;

        //creaete instance of dash
        //data.line.substr(0, pos) = line.substr(pos + 1);
        
    }
    //readfile and set to std::unordered_map<std::string, std::string>data
    

    
}