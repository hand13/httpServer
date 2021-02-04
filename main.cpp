#include <chrono>
#include <WinSock2.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include "Response.h"
#include <ctime>
#include "Request.h"
#include "RequestParser.h"
#include <filesystem>
#include <fstream>
namespace fs=std::filesystem;
using namespace std::chrono;
const char * static_path = "d:/inside/timeworld/static";
bool ctrlHandler(DWORD fdwctrltype) {
  switch(fdwctrltype) {
    case CTRL_C_EVENT:
      std::cout<<"啊我死了"<<std::endl;
      ExitProcess(-1);
      break;
    default:
      break;
  }
  return false;
}
std::string now() {
    time_t now;
    time(&now);
    tm tm;
    localtime_s(&tm,&now);
    return std::to_string(tm.tm_year + 1900) 
    + "-" + std::to_string(tm.tm_mon + 1) 
    + "-" + std::to_string(tm.tm_mday)
    + " " + std::to_string(tm.tm_hour)
    + ":" + std::to_string(tm.tm_min)
    + ":" + std::to_string(tm.tm_sec);
}
int main() {
    std::cout.imbue(std::locale("",LC_CTYPE));
    ::SetConsoleCtrlHandler((PHANDLER_ROUTINE)ctrlHandler,true);
    WSAData wsaData;
    if(WSAStartup(MAKEWORD(2,1),&wsaData)!= 0) {
        std::cout<<"初始化失败"<<std::endl;
        return -1;
    }
    sockaddr_in addr;
    ZeroMemory(&addr,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8662);
    addr.sin_addr.S_un.S_addr = ADDR_ANY;
    SOCKET socket = WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,0,0,WSA_FLAG_OVERLAPPED);
    if(socket == INVALID_SOCKET) {
        goto end;
    }
    bind(socket,reinterpret_cast<sockaddr*>(&addr),sizeof(addr));
    listen(socket,5);
    SOCKET clientSocket;
    sockaddr_in clientAddr;
    int length = sizeof(sockaddr_in);
    char buffer[4096];
    // char buffer[] = "HTTP/1.1 200 OK\r\nContent-Type:text/html;charset=UTF-8\r\n\n<h1>nice to meet you</h1>";
    char rBuffer[4096];
    ZeroMemory(rBuffer,sizeof(rBuffer));
    while(true) {
        if((clientSocket  = accept(socket,reinterpret_cast<sockaddr*>((&clientAddr)),&length)) == INVALID_SOCKET) {
            std::cout<<"未知错误"<<std::endl;
            continue;
        }
        int l = recv(clientSocket,rBuffer,sizeof(rBuffer),0);
        if(l > 0) {
            rBuffer[l] = 0;
            std::cout<<rBuffer<<std::endl;
        }
        RequestParser parser(rBuffer,l);
        Request request = parser.parseRequest();
        std::cout<<"what you want is "<<request.getUrl()<<std::endl;

        Response response;

        fs::path path(static_path);
        path += request.getUrl();
        std::cout<<"file path is "<<path<<std::endl;
        if(fs::exists(path) && fs::is_regular_file(path)) {
            size_t length = fs::file_size(path);
            if(length > 0) {
                char * buffer = new char[length];
                std::ifstream is(path,std::ios_base::in | std::ios_base::binary);
                is.read(buffer,length);
                is.close();
                response.setContent(buffer,length);
                delete [] buffer;
            }
        }else {
            response.addHeader(Header("Content-Type","application/json"));
            response.setContent("{\"name\":\"hand13\",\"password\":\"123456\",\"time\":\""+now() + "\"}");
        }
        int length;
        response.toMessage(buffer,sizeof(buffer),length);
        send(clientSocket,buffer,length,0);
        closesocket(clientSocket);
        std::cout<<"客户套接字关闭"<<std::endl;
    }
    closesocket(socket);
    end:
    WSACleanup();
    return 0;
}
