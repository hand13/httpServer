﻿#include <chrono>
#include <WinSock2.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include "Response.h"
using namespace std::chrono;
int main() {
    std::cout.imbue(std::locale("",LC_CTYPE));
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
    char buffer[2048];
    // char buffer[] = "HTTP/1.1 200 OK\r\nContent-Type:text/html;charset=UTF-8\r\n\n<h1>nice to meet you</h1>";
    char rBuffer[2048];
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
        Response response;
        response.addHeader(Header("Content-Type","application/json"));
        response.setContent("{\"name\":\"hand13\",\"password\":\"123456\"}");
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