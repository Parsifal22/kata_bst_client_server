#include "../Top_file.h"

int main(int argc, char *argv[]){
    
    int sockfd;
    int newsockfd;
    int portno;
    int msg;
    char buffer[255];

    struct sockaddr_in serv_addr;
    struct hostent *server;

    if (argc < 3){
        std::cout << stderr << " usage " << argv[0] << " hostname port" << std::endl;
        exit(1);
    }

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0){
        error("ERROR opening socket");
    }

    server = gethostbyname(argv[1]);
    
    if(server == NULL){
        std::cout << stderr << "Error, no such host" << std::endl;
        }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        error("Connection Failed");
    }

    std::cout << "Successful Connection to Server" << std::endl;

    while(1)
    {
        bzero(buffer, 255);
        fgets(buffer, 255, stdin);

        int i = strncmp("Exit", buffer, 4);

        if(i == 0){
            break;
        }
        
        msg = write(sockfd, buffer, strlen(buffer));

        if(msg = 0){
            error("Error on writing");
        }

        bzero(buffer, 255);
        msg = read(sockfd, buffer, 255);

        if(msg < 0){
            error("Error on reading.");
        }

        std::cout << "Server: " << buffer << std::endl;


    }

    close(sockfd);

    return 0;
}


void error(const char *msg)
{

    perror(msg);
    exit(1);
}