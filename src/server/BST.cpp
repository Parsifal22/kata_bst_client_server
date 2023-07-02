/*
* The file contains functions that are responsible for the functionality of BST
*/

#include "../Top_file.h"

/// @brief Creates new node 
/// @param val - number, which client sent
/// @return New node
Node *new_node(int val){
    Node *newnode = new Node();

    newnode->data = val;
    newnode->left = newnode->right = NULL;
    return newnode;
}

/// @brief Inserts new number to the tree
/// @param val
/// @param msg 
/// @param newsockfd
/// @param tree 
/// @return Three with the new number
Node * insert(int val, int msg, int newsockfd, Node * tree){

    if (tree == NULL){

        write("Insert Element", newsockfd);
        return new_node(val);
        }

    if (tree->data < val){
        tree->right = insert(val, msg, newsockfd, tree->right);
    } 

    else if (tree->data > val) {
        tree->left = insert(val, msg, newsockfd, tree->left);  
    }
    
    else {
        write("This number is already in the storage", newsockfd);
    }

    return tree;

}

/// @brief Prints tree's numbers for the client
/// @param msg 
/// @param newsockfd 
/// @param tree 
void print_out(int msg, int newsockfd, Node *tree){


        if(tree == NULL){
            return;
        }
    
        print_out(msg, newsockfd, tree->left);
        
        char temp[10 + sizeof(char)];
        std::sprintf(temp, "%d", tree->data);
        
        write(temp, newsockfd);
        write(" ", newsockfd);

        if (msg < 0){
                error("Error on Writing.");
            }

        print_out(msg, newsockfd, tree->right);

}



/// @brief Looks for the smallest number on a branch
/// @param tree 
/// @return 
Node* findMin(Node* tree)
	{
	    if(tree == NULL)
	        return NULL;
	    else if(tree->left == NULL)
	        return tree;
	    else
	        return findMin(tree->left);
	}

/// @brief Deletes number from the tree
/// @param val Number to be removed
/// @param tree 
/// @return Tree without a given number
Node* delete_node(int val, Node* tree) {

	    Node* temp;
	    if(tree == NULL)
	        return NULL;
	    else if(val < tree->data)
	        tree->left = delete_node(val, tree->left);
	    else if(val > tree->data)
	        tree->right = delete_node(val, tree->right);
	    else if(tree->left && tree->right)
	    {
	        temp = findMin(tree->right);
	        tree->data = temp->data;
	        tree->right = delete_node(tree->data, tree->right);
	    }
	    else
	    {
	        temp = tree;
	        if(tree->left == NULL)
	            tree = tree->right;
	        else if(tree->right == NULL)
	            tree = tree->left;
	        delete temp;
	    }
	
	    return tree;
	}


    /// @brief Looks for the given number in the tree
    /// @param tree 
    /// @param val 
    /// @return found node
    Node* find(Node* tree, int val){
        
        if(tree == NULL)
	        return NULL;
	    else if(val < tree->data)
	        return find(tree->left, val);
	    else if(val > tree->data)
	        return find(tree->right, val);
	    else
	        return tree;       
    }
