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
#define BUFFER_SIZE 10

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

int find_data(int, char []);





        


