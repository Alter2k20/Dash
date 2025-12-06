/*
 * Persistence.hpp
 * Logging and back up data
 */
#pragma once
#include <string>
#include <fstream>


namespace log{
    class Logger{

        public:
            Logger(const std::string& filename);
            void log(const std::string& message);
            void save_point();
            void rollback();
        private:
            std::ofstream file;
            int log_count = 0;
    };
}
