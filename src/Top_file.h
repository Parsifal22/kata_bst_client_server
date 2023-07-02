#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <queue>


///MACROS///
#define BUFFER_SIZE 255
#define INCORRECT_DATA -1

///Node struct///
struct Node {
        int data;
        Node* left;
        Node* right;
};


///FUNCTIONS///
Node* insert(int, int, int, Node*);
Node* delete_node (int, Node*);
Node* find (Node*, int);

void error (const char *);
void print_out(int, int, Node*);
void write(const char *, int);

int find_data(int, char []);





        


