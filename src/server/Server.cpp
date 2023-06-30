#include "../Top_file.h"
#include <string>

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

    Node *root = NULL;
    
    while(1){

        bzero(buffer, 255);
        msg = read(newsockfd, buffer, 255);

        if (msg < 0){
            error("Error on reading.");
        }

        int i = 0;
        std::string char_stream;

        int exit = strncmp("Exit", buffer, 4);

        if(exit == 0){
            break;
        }

        while(1){

            if (buffer[i] == '\0'){

                msg = write(newsockfd, "Incorrect Command", strlen("Incorrect Command"));

                if(msg < 0){
                    error("Error on Writing.");
                }
                break;
            }
            else if (buffer[i] != ' '){

                char_stream.push_back(buffer[i]);

            }
            else {
                
                std::cout << char_stream << std::endl;

                if (char_stream.find("insert") != std::string::npos){
                    root = insert(buffer[i+1] - '0', msg, newsockfd, root);
                    break;
                }
                else if (char_stream.find("print") != std::string::npos){
 
                    print_out(msg, newsockfd, root);
                    
                    break; 
                }
                else if (char_stream.find("find") != std::string::npos){

                    msg = write(newsockfd, "Find", strlen("Find"));

                    if (msg < 0){
                        error("Error on Writing.");
                    }

                    break; 
                }
                else {

                    msg = write(newsockfd, "Incorrect Command", strlen("Incorrect Command"));

                    if (msg < 0){
                        error("Error on Writing.");
                    }

                    break; 
                }
                        

           }

            i++;
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