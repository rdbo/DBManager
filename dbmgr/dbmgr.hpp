#pragma once
#include <sqlite3.h>
#include <iostream>
#include <fstream>

class DBMgr
{
    private:
    std::string dbpath = "";
    sqlite3* db        = NULL;
    bool create        = false;

    public:
    DBMgr(std::string path, bool bcreate = false);
    ~DBMgr();

    bool open();
    bool close();
    bool exec(std::string sql_cmd, char** error_msg = NULL);
    static int exec_callback(void* unused, int count, char** data, char** columns);
};