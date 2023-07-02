/*
* The file contains functions that are not related to BST
*/

#include "../Top_file.h"

/// @brief Prints out error message 
/// @param msg - error message content
void error(const char *msg)
{

    perror(msg);
    exit(1);
}


/// @brief Finds the number in the sent command
/// @param i Index pointing to char
/// @param data String with the number
/// @return Found number
int find_data(int i, char data[]){

    std::string data_colector;

    while(data[i] != '\0'){
        if (isdigit(data[i])){
            data_colector.push_back(data[i]);
        }
        
        i++;
    }

    
    if (!data_colector.empty()){

        return std::stoi(data_colector); /// Convert string to int
    }

    return INCORRECT_DATA;
}

/// @brief Writes message to client
/// @param msg - Message
/// @param newsockfd - Descriptor for communication
void write(const char * msg, int newsockfd){

        int i = write(newsockfd, msg, strlen(msg));

        if (i < 0){
                error("Error on Writing.");
            }

}