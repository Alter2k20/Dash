#include <iostream>

#include "dash.hpp"

/*
* Create a new instance of the DB class.
*/
DB_ptr db_instance(std::string name) {
    db::DB_INFO inf;
    std::cout << "dash_cli_version: " << inf.dash_cli_version << "\ndash_version:" << inf.name << "\n";
    DB_ptr instance = std::make_shared<db::DB>(name);
    return instance;
}

bool db::DB::SET(std::string &key, std::string &value) {
    data[key] = value;
    return true;
}

std::string db::DB::GET(std::string &key){
    return data[key];
}
