/*
 * Dash : in memory cache database string only
 * following singleton
 */

#pragma once
#include <memory>
#include<string>
#include<unordered_map>

namespace db {


    using namespace std;
    /*
     * soft info
     */
    typedef struct DB_INFO{
    const std::string dash_version = "0.0.1";
    const std::string dash_cli_version = "0.0.1";
    const std::string  name = "Dash@" + dash_version;
    } DB_INFO;


    typedef struct DB{
        std::string Db_name;
        std::unordered_map<std::string, std::string> data;

        /*
         * Initialize the DB
         */
         DB(std::string name) : Db_name(std::move(name)) {}

        /*
         *helpers
         */
        bool SET(std::string &key, std::string &value);
        std::string GET(std::string &key);
    } DB;



}
using DB_ptr = std::shared_ptr<db::DB>;
DB_ptr db_instance(std::string);
