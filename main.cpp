#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include "include/dash.hpp"
#include "include/log.hpp"

int main() {
    std::string db_name = "mydb";
    DB_ptr db = db_instance(db_name);
    std::unique_ptr<Log::Logger> Log_obj = std::make_unique<Log::Logger>("Log.txt");
    std::cout << "type EXIT to quit.\n.......................................\n";
    std::string line;

    while (true) {

        std::cout << "/> ";
        if (!std::getline(std::cin, line))
            break; // EOF or error

        // Trim input
        if (line.empty())
            continue;

        // Convert to uppercase for command parsing
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        // Normalize command
        for (auto& c : cmd) c = toupper(c);

        if (cmd == "EXIT") {
            break;
        }

        else if (cmd == "SET") {
            std::string key, value;
            ss >> key;
            std::getline(ss, value);

            // remove first space before value
            if (!value.empty() && value[0] == ' ')
                value.erase(0, 1);

            if (key.empty() || value.empty()) {
                std::cout << "Usage: SET <key> <value>\n";
                continue;
            }

            if (db->SET(key, value))
            {
                std::cout << "OK\n";
                Log_obj->log("inserted data with key : " + key);
            }
            else {
                std::cout << "Not OK\n";
            }

        }

        else if (cmd == "GET") {
            std::string key;
            ss >> key;

            if (key.empty()) {
                std::cout << "Usage: GET <key>\n";
                continue;
            }

            std::string result = db->GET(key);
            if (result.empty())
            {
                std::cout << "(nil)\n";
            }
            else {
                std::cout << result << "\n";
            }
        }

        else if (cmd == "BACKUP") {
            std::string key;
            ss >> key;
            if (key.empty()) {
                std::cout << "Usage: GET <backup_filename_withou_extension>\n";
                continue;
            }

            std::unique_ptr<Backup::BackupUnit>  bckp = std::make_unique<Backup::BackupUnit>(key);
            if (bckp->Backup(db->data)) {
                std::cout << "success \n";
            }
            else {
                std::cout << "failure \n";
            }
        }

        

        else {
            std::cout << "Unknown command: " << cmd << "\n";
        }
    }

    
    std::cout << "Closing\n";
    return 0;
}
