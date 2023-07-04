/*
* The code responsible for the server
* and for processing client commands
*/

#include "../Top_file.h"

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
    char buffer[BUFFER_SIZE];

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

        bzero(buffer, BUFFER_SIZE);
        msg = read(newsockfd, buffer, BUFFER_SIZE);

        if (msg < 0){
            error("Error on reading.");
        }

        int i = 0;
        std::string char_stream;

        int exit = strncmp("exit", buffer, 4);

        if(exit == 0){
            break;
        }

        while(1){

            if (buffer[i] == '\0'){
                write("Incorrect Command", newsockfd);
                break;
            }
            else {

                char_stream.push_back(buffer[i]);

                if (char_stream.find("insert") != std::string::npos){
                    int data = find_data(i, buffer); 

                    if (data == INCORRECT_DATA){
                        write("Incorrect Data", newsockfd);
                    }  
                    else{
                        root = insert(data, msg, newsockfd, root);
                    }    
                    
                    break;
                }
                else if (char_stream.find("print") != std::string::npos){
                    if (root == NULL){
                        write("BST is empty", newsockfd);
                    }
                    else{
                       print_out(msg, newsockfd, root); 
                    }
                    
                    
                    break; 
                }
                else if (char_stream.find("delete") != std::string::npos){

                    int data = find_data(i, buffer); 

                    if (data == INCORRECT_DATA){

                        write("Incorrect Data", newsockfd);
                    }                        
                    else{
                        if (find(root, data) == NULL){
                            char temp[10 + sizeof(char)];
                            std::sprintf(temp, "%d", data);
		                    char msg [55] = "ERROR: ";
		                    strcat(msg, temp);
                            write(strcat(msg, " doesn't exist in BST"), newsockfd);
                        }
                        else{
                            root = delete_node(data, root);
                            write("Deleted", newsockfd); 
                        }
                        
                    }

                    break; 
                }
                else if (char_stream.find("find") != std::string::npos){
                    

                    int data = find_data(i, buffer); 

                    if (data == INCORRECT_DATA){

                        write("Incorrect Data", newsockfd);
                    } 
                    else{

                        if (find(root, data) == NULL){

                            write("This number is not in the storage", newsockfd);

                            
                        }
                        else{
                            
                            write("This number exists", newsockfd);
                        }
                     
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
