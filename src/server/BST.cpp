#include "../Top_file.h"

Node *new_node(int val){
    Node *newnode = new Node();

    newnode->data = val;
    newnode->left = newnode->right = NULL;
    return newnode;
}


Node * insert(int val, int msg, int newsockfd, Node * tree){

    if (tree == NULL){

        msg = write(newsockfd, "Insert Element", strlen("Insert Element"));

        if (msg < 0){
                error("Error on Writing.");
            }

        return new_node(val);
        }

    if (tree->data < val){
        tree->right = insert(val, msg, newsockfd, tree->right);
    } 

    else if (tree->data > val) {
        tree->left = insert(val, msg, newsockfd, tree->left);  
    }
    
    else {
        msg = write(newsockfd, "There is the same element", strlen("There is the same element"));

        if (msg < 0){
                error("Error on Writing.");
            }
    }

    return tree;

}


void print_out(int msg, int newsockfd, Node *tree){


        if(tree == NULL){
            return;
        }
    
        print_out(msg, newsockfd, tree->left);
        char temp[10 + sizeof(char)];
        std::sprintf(temp, "%d", tree->data);
        
        msg = write(newsockfd, temp, strlen(temp));
        msg = write(newsockfd, " ", strlen(" "));

        if (msg < 0){
                error("Error on Writing.");
            }

        print_out(msg, newsockfd, tree->right);

}