#include "../Top_file.h"


void error(const char *msg)
{

    perror(msg);
    exit(1);
}



int find_data(int i, char data[]){

    std::string data_colector;

    while(data[i] != '\0'){
        if (isdigit(data[i])){
            data_colector.push_back(data[i]);
        }
        
        i++;
    }

    
    if (!data_colector.empty()){
        return std::stoi(data_colector);
    }

    return INCORRECT_DATA;
}


void write(const char * msg, int newsockfd){

        int i = write(newsockfd, msg, strlen(msg));

        if (i < 0){
                error("Error on Writing.");
            }

}