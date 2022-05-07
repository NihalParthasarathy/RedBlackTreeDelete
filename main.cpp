//Nihal Parthasrathy
//5/7/2022
//This code makes a red black tree to sort numbers in a balanced form. It adds the numbers form manual adding or from a file and also displays it

//Inclusions
#include "node.h"
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>

using namespace std;

//Function Prototypes
void manualAdd(Node* &root, Node* &newptr);
void recurciveAdd(Node* &root, Node* curr, int value, Node* &newptr);
bool search(Node* curr, int num, Node* &newptr);
void display(Node* curr, int depth);
void addFile(Node* &root, Node* &newptr, int &count);
void remove(Node* root, int num, Node* newptr);
void check(Node* &root, Node* curr);

int main() {
  int count = 1;
  cout << "Red Black Tree" << endl;
  Node* root = NULL;
  bool playing = true;
  Node* newptr = NULL;
  
  while (playing == true) {//While loop
    cout << "would you like to add from a file(ADD), Manualy add(TYPE), search(SEARCH), display(DISPLAY), remove from heap(REMOVE), o\
r quit(QUIT)" << endl;
    char input[10];
    cin >> input;
    
    if (strcmp(input, "ADD") == 0) {//Calls the add function
      addFile(root, newptr, count);
    }
    else if (strcmp(input, "TYPE") == 0) {//Calls type function
      manualAdd(root, newptr);
    }
    else if (strcmp(input, "DISPLAY") == 0) {//Calls display function
      display(root, 0);
    }
    else if (strcmp(input, "SEARCH") == 0) {//Calls the search function
      cout << "What number would you like to search" << endl;
      int input2;
      cin >> input2;
      bool a = search(root, input2, newptr);
      if (a == true) {
        cout << "number in tree" << endl;
      }
      else {
        cout << "number not in tree" << endl;
      }
    }
    else if (strcmp(input, "REMOVE") == 0) {//Calls remove function
      /*cout << "what number would you like to remove" << endl;
      int input3;
      cin >> input3;
      remove(root, input3, newptr);*/
    }
    else if (strcmp(input, "QUIT") == 0) {//Returns false
      playing = false;//Exits while Loop stopping game
    }
  }
}

void manualAdd(Node* &root, Node* &newptr) {//Asks for number and adds it
  cout << "enter a number between 1-999" << endl;
  int num;
  cin >> num;
  if (root == NULL) {//If root is Null
    root = new Node(num);
    root->parent = NULL;
    check(root, root);
  }
  else if (root != NULL) {//If it is not a root
    recurciveAdd(root, root, num, newptr);
  }
}

void addFile(Node* &root, Node* &newptr, int &count) {//Adds from a file
  cout << "how many numbers to add" << endl;
  int ninput;
  cin >> ninput;

  for(int i = 0; i < ninput; i ++){//Create how many numbers the user wants
    fstream file("numberFile.txt");//Import the number file
    char input[100];
    int num = 0;
    char temp[100];
    if(count > 50){
      count = 1;
    }
    
    while (file.getline(input, 100, ' ')) {
      if (count == num) {
	strcpy(temp,input);
	num++;
      }
      num++;
    }
    int numput = atoi(temp);//Changes from string to int
    count++; 
    if (root == NULL) {//If root is Null
      root = new Node(numput);
      root->parent = NULL;
      check(root, root);
    }
    else if (root != NULL) {//If it is not a root
      recurciveAdd(root, root, numput, newptr);
    }
  }
}

void recurciveAdd(Node* &root, Node* curr, int value, Node* &newptr) {//Adds recurcivly to the tree
  if (curr->data >= value && curr->getLeft() == NULL) {
    curr->setLeft(new Node(value));
    curr->getLeft()->parent = curr;
    newptr = curr;
    check(root, curr->getLeft());//Check function
  }
  else if (curr->data < value && curr->getRight() == NULL) {
    curr->setRight(new Node(value));
    curr->getRight()->parent = curr;
    newptr = curr;
    check(root, curr->getRight());//check function
  }
  else if (curr->data >= value) {//Recurcive Call
    recurciveAdd(root, curr->getLeft(), value, newptr);
  }
  else if (curr->data < value) {//Recurcive Call
    recurciveAdd(root, curr->getRight(), value, newptr);
  }
}

void check(Node* &root, Node* curr) {
  Node* parent = NULL;
  Node* grandparent = NULL;
  Node* uncle = NULL;

  //Makes the Node pointers if they exit in the tree
  if (curr->parent != NULL) {
    parent = curr->parent;
    if (parent->parent != NULL) {
      grandparent = parent->parent;   
      if (grandparent->getLeft() == parent) {
	uncle = grandparent->getRight();
      }
      else if (grandparent->getRight() == parent) {
	uncle = grandparent->getLeft();
      }
    } 
  }
  if (curr->color == true && curr == root) {//Case 1
    root->color = false;
    return;
  }
  else if (curr->parent != NULL && curr->parent->color == false) {//Case 2
    return;
  }
  else if (uncle != NULL && parent->color == true && uncle->color == true) {//Case 3
    parent->color = false;
    uncle->color = false;
    grandparent->color = true;
    check(root, grandparent);//Recurcive Call on Grandparent
  }
  else if (uncle == NULL || uncle->color == false) {//If the uncle is black
    if (parent == grandparent->getRight() && curr == parent->getLeft()) {//Case 4
      grandparent->setRight(curr);
      curr->parent = grandparent;
      Node* temp = curr->getRight();
      curr->setRight(parent);
      parent->parent = curr;
      if (temp != NULL) {
	temp->parent = parent;
      }
      parent->setLeft(temp);
      parent = curr;
      curr = parent->getRight();
    }
    else if (parent == grandparent->getLeft() && curr == parent->getRight()) {//Case 4
      grandparent->setLeft(curr);
      curr->parent = grandparent;
      Node* temp = curr->getLeft();
      curr->setLeft(parent);
      parent->parent = curr;
      if (temp != NULL) {
        temp->parent = parent;
      }
      parent->setRight(temp);
      parent = curr;
      curr = parent->getLeft();
    }
    if (parent->color == true && curr->color == true) {//Case 5
      Node* greatgrandparent = NULL;
      if (grandparent->getLeft() == parent && parent->getLeft() == curr) {//If parent is a left child and curr is a left child
	Node* temp = parent->getRight();
	parent->setRight(grandparent);
	if (grandparent != root) {
	  greatgrandparent = grandparent->parent;
	  parent->parent = greatgrandparent;
	  if (grandparent == greatgrandparent->getLeft()) {
	    greatgrandparent->setLeft(parent);
	  }
	  else {
	    greatgrandparent->setRight(parent);
	  }
	}
	else {
	  parent->parent = NULL;
	  root = parent;
	}
	grandparent->parent = parent;
	if (temp != NULL) {
	  temp->parent = grandparent;
	}
	grandparent->setLeft(temp);
	parent->color = false;
	grandparent->color = true;
      }
      else if (grandparent->getRight() == parent && parent->getRight() == curr) {//If parent is a right child and curr is a right child
	Node* temp = parent->getLeft();
        parent->setLeft(grandparent);
        if (grandparent != root) {
          greatgrandparent = grandparent->parent;
          parent->parent = greatgrandparent;
	  if (grandparent == greatgrandparent->getLeft()) {
            greatgrandparent->setLeft(parent);
          }
          else {
            greatgrandparent->setRight(parent);
          }
        }
        else {
          parent->parent = NULL;
          root = parent;
        }
        grandparent->parent = parent;
	if (temp != NULL) {
          temp->parent = grandparent;
        }
        grandparent->setRight(temp);
	parent->color = false;
        grandparent->color = true;
      }
    }
  }
}

bool search(Node* curr, int num, Node* &newptr) {//Search Function
  bool b = false;
  if (curr->data == num) {
    newptr = curr;
    return true;
  }
  else {
    if (curr->data > num && curr->getLeft() != NULL) {
      b = search(curr->getLeft(), num, newptr);
    }
    else if (curr->data < num && curr->getRight() != NULL) {
      b = search(curr->getRight(), num, newptr);
    }
    if(b) {
      return true;
    }
  }
  return false;
}

void display(Node* curr, int depth) {//Displays the heap using tabs
  if (curr->right != NULL) {
    display(curr->right, depth + 1);//Recurcive call
  }
  for (int i = 0; i < depth; i++) {//Prints out the amount of tabs based on the depth
    cout << "\t";
  }
  if (curr->color == true) {
    if (curr->parent != NULL) {
      cout << curr->data << "  RED" << " Parent: " << curr->parent->data << endl;
    }
    else {
      cout << curr->data << "  RED" << " Parent: NULL" << endl;
    }
  }
  else if (curr->color == false) {
    if (curr->parent != NULL) {
      cout << curr->data << "  BLACK" << " Parent: " << curr->parent->data << endl;
    }
    else {
      cout << curr->data << "  BLACK" << " Parent: NULL" << endl;
    }
  }
  if (curr->left != NULL) {
    display(curr->left, depth + 1);//Recurcive call
  }
}

//Remove function from binary tree
/*void remove(Node* curr, int num, Node* newptr) {
  if (search(curr, num, newptr) == true) {
    Node* temp = newptr;
    cout << temp->data << endl;
    if (temp->getLeft() == NULL && temp->getRight() == NULL) {
      if (temp->parent->getLeft() == temp) {
        temp->parent->left = NULL;
        delete temp;
        cout << "here" << endl;
      }
      else {
        temp->parent->right = NULL;
        delete temp;
      }
      newptr = NULL;
    }
    else if (temp->getLeft() != NULL && temp->getRight() == NULL) {
      //MAKE THE PARENTS POINTER POINT TO THE CHILD (EASIER)
      cout << "where" << endl;
      Node* tempParent = temp->parent;
      while (temp->getLeft() != NULL) {
        Node* temptemp = temp;
        temp = temp->getLeft();
        delete temptemp;
      }
      tempParent->left = temp;
      newptr = NULL;
    }
    else if (temp->getLeft() == NULL && temp->getRight() != NULL) {
      cout << "there" << endl;
      Node* tempParent = temp->parent;
      while (temp->getRight() != NULL) {
        Node* temptemp = temp;
        temp = temp->getRight();
        delete temptemp;
      }
      tempParent->right = temp;
      newptr = NULL;
    }

  }
  }*/
