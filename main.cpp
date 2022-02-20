#include "Server.h"
#include <iostream>

int main(int argc,char* argv[])
{
    if(argc<=3)
    {
        printf("need basename,ThreadNum and requestNum");
        return 1;
    }
    std::string programName=argv[1];
    int maxThreadNum=atoi(argv[2]);
    std::cout<<maxThreadNum<<std::endl;
    int maxRequestNum=atoi(argv[3]);
    Server mServer;
    mServer.run(maxThreadNum,maxRequestNum);
    return 0;
}
