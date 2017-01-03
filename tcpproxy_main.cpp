#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "tcpproxy_server.hpp"

int main(int argc,char* argv[])
{
    try
    {
        if(5!= argc)
        {
            std::cerr<<"Usage: tcpproxy <local port> <server ip> <server_port> <[thread size>\n";
            std::cerr<<"local port: local port used to accept login client\n";
            std::cerr<<"server ip: analysing server address, ip string in decimal dot format\n";
            std::cerr<<"server port: analysing server port, an unsigned short value\n";
            std::cerr<<"thread size: number of threads to running tcpproxy server\n";
            return 1;
        }
        tcpproxy_server srv(atoi(argv[1]), argv[2],atoi(argv[3]),atoi(argv[4]));

        srv.run();
    }
    catch(std::exception& e)
    {
        std::cerr<<"exception: "<<e.what()<<"\n";
    }

    return 0;
}