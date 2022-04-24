#include <iostream>
#include <netinet/in.h>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
using namespace std;
int main(int argc, char **argv)
{
    //1.1
    sockaddr_in * self_addr = new (sockaddr_in);
    self_addr->sin_family = AF_INET; // Ethernet protocol IPv4
    self_addr->sin_port = 0; // port
    self_addr->sin_addr.s_addr = 0;
    //1.2
    sockaddr_in * remote_addr = new (sockaddr_in);
    remote_addr->sin_family = AF_INET; // Ethernet protocol IPv4
    remote_addr->sin_port = htons(13); // port 13 - daytime
    remote_addr->sin_addr.s_addr = inet_addr("82.179.90.12"); //char->int
    
    char* buf = new char[256];
    strcpy(buf, "Как поживаете?\n");
    int bufLen=strlen(buf);

    //2 creation socket TCP
    int s=socket(AF_INET,SOCK_STREAM,0);
    if (s==-1) { //error handling
        cout<<"error_creation_socket"<<endl;
        exit(0);
    }

    //3 unification address with socket
    int rc = bind(s,(const sockaddr*) self_addr,sizeof(sockaddr_in));
    if (rc==-1) {//error handling
        close(s);
        cout<<"error_unification_address_with_socket"<<endl;
        exit(0);
    }
    //4 establishing_a_connection_with_the_server
    rc = connect(s,(const sockaddr*) remote_addr, sizeof(sockaddr_in));
    if (rc == -1) {//error handling
        close(s);
        cout<<"error_establishing_a_connection_with_the_server"<<endl;
        exit(0);
    }
    //5.1
    //sending a message
    rc = send(s, buf, bufLen, 0);
    if (rc == -1) {//error handling
        close(s);
        cout<<"error_sending_a_message"<<endl;
        exit(0);
    }
    cout<<"send message:"<<buf<<endl;

    //5.2
    //acceptance of the message
    rc = recv(s, buf, 256,0);
    if (rc == -1) {//error handling
        close(s);
        cout<<"error_acceptance_of_the_message"<<endl;
        exit(0);
    }
    buf[rc]='\0';
    cout<<"message received:"<<buf<<endl;
    
    //6 close socket
    close(s);

    delete self_addr;
    delete remote_addr;
    delete[] buf;
    return 0;
}
