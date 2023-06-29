#include "Top_file.h"
//struct hostent *server;

int main(int argc, char *argv[]){


    if(argc < 2)
    {
        std::cout << "Port is not provided" << std::endl;
        exit(1);
    }

    int sockfd;
    int newsockfd;
    int portno;

    char buffer[255];

    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    socklen_t clilen;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd < 0){
        error("Error opening Socket.");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));

    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        error("Binding Failed.");
    }
    

    return 0;
}


void error(const char *msg)
{

    perror(msg);
    exit(1);
}