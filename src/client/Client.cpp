/*
* The code responsible for connecting the client to the server
* and sending commands to the server
*/

#include "../Top_file.h"

int main(int argc, char *argv[]){
    
    int sockfd;
    int newsockfd;
    int portno;
    int msg;
    char buffer[BUFFER_SIZE];

    struct sockaddr_in serv_addr;
    struct hostent *server;

    if (argc < 3){
        std::cout << stderr << " usage " << argv[0] << " hostname port" << std::endl;
        exit(1);
    }

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0){
        error("Error, opening socket");
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
        bzero(buffer, BUFFER_SIZE);
        fgets(buffer, BUFFER_SIZE, stdin);

        int i = strncmp("exit", buffer, 4);

        if(i == 0){
            break;
        }
        
        msg = write(sockfd, buffer, strlen(buffer));

        if (msg < 0){
                error("Error on Writing.");
            }

        bzero(buffer, BUFFER_SIZE);

        msg = read(sockfd, buffer, BUFFER_SIZE);

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