#include <iostream>
#include <sstream>
#include <string>
#include "dash.hpp"

int main() {
    DB_ptr db = db_instance("mydb");

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
        for (auto &c : cmd) c = toupper(c);

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

            if(db->SET(key, value))
            {
                std::cout << "OK\n";
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
            }else{
                std::cout << result << "\n";
            }
    }

        else {
            std::cout << "Unknown command: " << cmd << "\n";
        }
    }

    std::cout << "Bye!\n";
    return 0;
}
