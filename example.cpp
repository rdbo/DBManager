#include "dbmgr/dbmgr.hpp"
#include <unistd.h>
#include <limits.h>

std::string GetCurDir() {
    char cpath[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", cpath, PATH_MAX);
    std::string path = std::string(cpath, (count > 0) ? count : 0);

    std::size_t found = path.find_last_of("/");
    return path.substr(0,found);
}

int main(int argc, char** argv)
{
    std::cout << "<< DBMgr by rdbo >>" << std::endl;
    if(argc != 2)
    {
        std::cout << "[!] Invalid amount of arguments" << std::endl;
    }

    std::string sql_cmd = argv[1];
    std::string path = std::string(GetCurDir() + "/test.db");
    std::cout << "[*] DB Path: " << path << std::endl;
    DBMgr dbmgr = DBMgr(path, true);
    std::cout << "[*] Executing command: " << sql_cmd << "..." << std::endl;
    std::cout << "[*] Exit code: " << dbmgr.exec(sql_cmd) << std::endl;
    return 0;
}