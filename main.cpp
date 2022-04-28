#include "node.h"
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>

using namespace std;

void manualAdd(Node* &root);
void recurciveAdd(Node* &root, Node* curr, int value);
bool search(Node* curr, int num, Node* &newptr);
void display(Node* curr, int depth);
void addFile(Node* &root);
void remove(Node* root, int num, Node* newptr);
void check(Node* &root, Node* curr, int value);

int main() {
  srand(time(0));
  cout << "Binary Search Tree" << endl;
  Node* root = NULL;
  bool playing = true;
  Node* newptr = NULL;
  while (playing == true) {//While loop
    cout << "would you like to add from a file(ADD), Manualy add(TYPE), search(SEARCH), display(DISPLAY), remove from heap(REMOVE), o\
r quit(QUIT)" << endl;
    char input[10];
    cin >> input;
    if (strcmp(input, "ADD") == 0) {//Calls the add function
      addFile(root);
    }
    else if (strcmp(input, "TYPE") == 0) {//Calls type function
      manualAdd(root);
    }
    else if (strcmp(input, "DISPLAY") == 0) {//Calls display function
      display(root, 0);
    }
    else if (strcmp(input, "SEARCH") == 0) {//Calls the print function
      cout << "What number would you liek to search" << endl;
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
      cout << "what number would you like to remove" << endl;
      int input3;
      cin >> input3;
      remove(root, input3, newptr);
    }
    else if (strcmp(input, "QUIT") == 0) {//Returns false
      playing = false;//Exits while Loop stopping game
    }
  }
}

void manualAdd(Node* &root) {
  cout << "enter a number between 1-999" << endl;
  int num;
  cin >> num;
  if (root == NULL) {
    root = new Node(num);
    root->parent = NULL;
    check(root, root, num);
    if (root->color == false) {
      cout << "black" << endl;
    }
  }
  else if (root != NULL) {
    recurciveAdd(root, root, num);
    check(root, root->left, num);
  }
}

void addFile(Node* &root) {//Adds from a file
  cout << "how many numbers to add" << endl;
  int input;
  cin >> input;

  for (int i = 0; i < input; i++) {
    char input[10];
    char tempString[10];
    int count = 1;
    int numput;
    int randomnum = (rand() % 50) + 1;
    fstream myfile("numberFile.txt");//Opens file

    while (myfile.getline(input,10, ' ')) {
      if (count == randomnum) {
        strcpy(tempString, input);
        count++;
      }
      count++;
    }
    numput = atoi(tempString);//Changes from string to int
    if (root == NULL) {
      root = new Node(numput);
      root->parent = NULL;
    }
    else if (root != NULL) {
      recurciveAdd(root, root, numput);
    }
  }
}

void recurciveAdd(Node* &root, Node* curr, int value) {
  if (curr->data >= value && curr->getLeft() == NULL) {
    curr->setLeft(new Node(value));
    curr->getLeft()->parent = curr;
    //check(root, curr->getLeft(), value);
  }
  else if (curr->data < value && curr->getRight() == NULL) {
    curr->setRight(new Node(value));
    curr->getRight()->parent = curr;
    //check(root, curr->getRight(), value);
  }
  else if (curr->data >= value) {
    recurciveAdd(root, curr->getLeft(), value);
  }
  else if (curr->data < value) {
    recurciveAdd(root, curr->getRight(), value);
  }
}

void check(Node* &root, Node* curr, int value) {
  Node* parent;
  Node* grandparent;
  Node* uncle;
  if (curr->parent != NULL) {
    parent = curr->parent;
    if (parent->parent != NULL) {
      grandparent = parent->parent;
    }
    if (parent->getLeft() == curr) {
    uncle = grandparent->getRight();
    }
    else if (parent->getRight() == curr) {
      uncle = grandparent->getLeft();
    } 
  }
  
  
  if (curr->color == true && curr == root) {
    root->color = false;
  }
  else if (curr->parent != NULL && curr->parent->color == false) {
    return;
  }
  else if (parent->color == true && uncle->color == true) {
    parent->color = false;
    uncle->color = false;
    grandparent->color = true;
    check(root, grandparent, value);
  }
  else if (uncle->color == false && parent == grandparent->getRight()) {

  }
  else if (uncle->color == false && parent == grandparent->getLeft()) {
    
  }
}

bool search(Node* curr, int num, Node* &newptr) {
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
    cout << curr->data << "  RED" << endl;
  }
  else if (curr->color == false) {
    cout << curr->data << "  BLACK" << endl;
  }
  //cout << curr->data << endl;//Prints out the number
  if (curr->left != NULL) {
    display(curr->left, depth + 1);//Recurcive call
  }
}

void remove(Node* curr, int num, Node* newptr) {
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
}
