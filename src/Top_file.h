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
void error (const char *);
Node* insert(int, int, int, Node*);
void find (int);
void delete_node (int);
void print_out(int, int, Node*);







        


