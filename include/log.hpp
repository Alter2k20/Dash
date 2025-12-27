/*
 * Persistence.hpp
 * Logging and back up data
 */
#pragma once
#include <string>
#include <fstream>
#include <unordered_map>


namespace Log{
    class Logger{

        public:
            Logger(const std::string& filename);
            void log(const std::string& message);
            void save_point();
            void rollback();
        private:
            std::ofstream file;
            int log_count = 0;
            bool file_status = false;
    };
}

namespace Backup {
    class BackupUnit {
    public:
        BackupUnit() = default;
        BackupUnit(const std::string& filepath);
        int Backup(const std::unordered_map<std::string, std::string> &data);
        void Restore(const std::string& filepath);
    private: 
        std::ofstream file;
        std::string data;
        bool backup_status = false;
    };
}


