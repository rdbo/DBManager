#include "dbmgr.hpp"

DBMgr::DBMgr(std::string path, bool bcreate)
{
    dbpath = path;
    create = bcreate;
}

DBMgr::~DBMgr()
{
    dbpath = "";
    db =     NULL;
    create = false;
}

bool DBMgr::open()
{
    std::ifstream fs(dbpath.c_str());
    int exit_code = -1;
    if(fs.good() || create)
    {
        exit_code = sqlite3_open(dbpath.c_str(), &db);
    }

    return (fs.good() || create) && (exit_code == SQLITE_OK);
}

bool DBMgr::close()
{
    return (sqlite3_close(db) == SQLITE_OK);
}

int DBMgr::exec_callback(void* unused, int count, char** data, char** columns)
{
    /*
    for(int i = 0; i < count; i++)
        std::cout << columns[i] << ": " << data[i];
    */
    return 0;
}

bool DBMgr::exec(std::string sql_cmd, char** error_msg)
{
    int exit_code = -1;
    if(open())
    {
        char* temp;
        exit_code = sqlite3_exec(db, sql_cmd.c_str(), exec_callback, NULL, error_msg == NULL ? &temp : error_msg);
        close();
    }

    return exit_code == SQLITE_OK;
}