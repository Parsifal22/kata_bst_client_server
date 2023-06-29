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
    int msg;
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
    
    listen(sockfd, 2);
    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    if(newsockfd < 0){
        error("Error on Accept");
    }

    while(1){

        bzero(buffer, 255);
        msg = read(newsockfd, buffer, 255);
        if (msg < 0){
            error("Error on reading.");
        }

        std::cout << "Client : " << buffer << std::endl;

        bzero(buffer, 255);
        fgets(buffer, 255, stdin);

        msg = write(newsockfd, buffer, strlen(buffer));

        if(msg < 0){
            error("Error on Writing.");
        }

        int i = strncmp("Bye", buffer, 3);

        if(i == 0){
            break;
        }

    }

    close(newsockfd);
    close(sockfd);
    return 0;
}


void error(const char *msg)
{

    perror(msg);
    exit(1);
}