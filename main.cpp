//Nihal Parthasrathy
//5/29/2022
//This code makes a red black tree to sort numbers in a balanced form. It adds the numbers form manual adding or from a file and also displays it. It also removes from the tree and you can search for something in it

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
void remove(Node* &root, Node* curr, int num, Node* newptr);
void check(Node* &root, Node* curr);
void move(Node* &root, Node* curr);
void checkDelete(Node* curr, Node* &root);

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
      cout << "what number would you like to remove" << endl;
      int input3;
      cin >> input3;
      remove(root, root, input3, newptr);
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

void move(Node* &root, Node* curr) {
  if (curr->getLeft() == NULL && curr->getRight() != NULL) {
    if (curr->color == false && curr->getRight()->color == true) {
      curr->getRight()->color = false;
    }
  }
  else if (curr->getLeft() != NULL && curr->getRight() == NULL) {
    if (curr->color == false && curr->getLeft()->color == true) {
      curr->getLeft()->color = false;
    }
  }
}

void checkDelete(Node* curr, Node* &root) {//Check delete function which has cases for double blacks
  Node* sibling = NULL;
  if (curr == root) {//CASE 1
    cout << "case 1" << endl;
    return;
  }
  else {
    //Sets up varubles
    Node* parent = curr->parent;
    if (curr == curr->parent->getRight()) {
      sibling = curr->parent->getLeft();
    }
    else if (curr == curr->parent->getLeft()) {
      sibling = curr->parent->getRight();
    }
    if (sibling != NULL) {
      //CASE 2
      if (sibling->color == true && curr == curr->parent->getLeft() && curr->color == false && parent->color == false) {//Rotates the sibling through the parent
	Node* siblingLeft = sibling->getLeft();
	display(root, 0);
	sibling->parent = parent->parent;
	if (parent != root) {
	  if (parent == parent->getLeft()) {
          parent->parent->setLeft(sibling);
	  }
	  else {
	    parent->parent->setRight(sibling);
	  }
      }
	else {
	  root = sibling;
	}
	sibling->setLeft(parent);
	parent->parent = sibling;
	parent->color = true;//changes colors
	sibling->color = false;
	parent->setRight(siblingLeft);
	if (siblingLeft != NULL) {
	  siblingLeft->parent = parent;
	}
	sibling = parent->getRight();//Resets sibling
      }
      else if (sibling->color == true && curr == curr->parent->getRight() && curr->color == false && parent->color == false) {//Rotates sibling through parent
	Node* siblingRight = sibling->getRight();
	sibling->parent = parent->parent;
	if (parent != root) {
	  if (parent == parent->getLeft()) {
	    parent->parent->setLeft(sibling);
	  }
	  else {
	    parent->parent->setRight(sibling);
	  }
	}
	else {
	  root = sibling;
	}
	sibling->setRight(parent);
	parent->parent = sibling;
	parent->color = true;//Changes colors
	sibling->color = false;
	parent->setLeft(siblingRight);
	if (siblingRight != NULL) {
	  siblingRight->parent = parent;
	}
	Node* temporary = sibling;
	sibling = parent->getLeft();//Resets sibling
      }
      
    
      //CASE 3
      if (sibling->color == false && curr->color == false && parent->color == false && (sibling->getLeft() == NULL || sibling->getLeft()->color == false) && (sibling->getRight() == NULL || sibling->getRight()->color == false)) {//Sets siblings color to red then recurcive call on parent
	sibling->color = true;
	checkDelete(parent, root);
      }
      //CASE 4
      else if (parent->color == true && sibling->color == false && (sibling->getLeft() == NULL || sibling->getLeft()->color == false) && (sibling->getRight() == NULL || sibling->getRight()->color == false)) {//Sets parent to black and sibling to red
	parent->color = false;
	sibling->color = true;
	return;
      }
      //CASE 5
      else if (parent->getLeft() == sibling && (sibling->getLeft() == NULL || sibling->getLeft()->color == false)) {//Rotates through sibling
	if (sibling->getRight() != NULL) {
	  if (sibling->getRight()->color == true) {//If siblings right is red
	    Node* siblingRight = sibling->getRight();//Rotates trhough sibling
	    parent->setLeft(siblingRight);
	    siblingRight->parent = parent;
	    Node* temp = siblingRight->getLeft();
	    siblingRight->setLeft(sibling);
	    sibling->parent = siblingRight;
	    sibling->setRight(temp);
	    temp->parent = sibling;
	    sibling->color = true;//Sets colors
	    siblingRight->color = false;
	    sibling = siblingRight;//Resets sibling
	  }
	}
      }
      else if (parent->getRight() == sibling && (sibling->getRight() == NULL || sibling->getRight()->color == false)) {
	if (sibling->getLeft() != NULL) {
	  if (sibling->getLeft()->color == true) {
	    Node* siblingLeft = sibling->getLeft();//Rotates through sibling
	    parent->setRight(siblingLeft);
	    siblingLeft->parent = parent;
	    Node* temp = siblingLeft->getRight();
	    siblingLeft->setRight(sibling);
	    sibling->parent = siblingLeft;
	    sibling->setLeft(temp);
	    temp->parent = sibling;
	    sibling->color = true;//Sets colors
	    siblingLeft->color = false;
	    sibling = siblingLeft;//Resets sibling
	  }
	}
      }
      //CASE 6
      if (sibling->color == false && parent->getLeft() == sibling && sibling->getLeft() != NULL && curr->color == false) {//Rotates through parent and switchs parent and siblings colors
	if (sibling->getLeft()->color == true) {
	  Node* temp = sibling->getRight();
	  sibling->setRight(parent);
	  if (parent->parent != NULL) {//Checks if parent is NULL
	    if (parent == parent->parent->getRight()) {
	      parent->parent->setRight(sibling);
	      sibling->parent = parent->parent;
	    }
	    else {
	      parent->parent->setLeft(sibling);
	      sibling->parent = parent->parent;
	    }
	  }
	  else {
	    sibling->parent = NULL;
	    root = sibling;
	  }
	  parent->parent = sibling;
	  parent->setLeft(temp);
	  if (temp != NULL) {
	    temp->parent = parent;
	  }
	  //Sets colors
	  sibling->getLeft()->color = false;
	  sibling->color = parent->color;
	  parent->color = false;
	  return;
	}
      }
      else if (sibling->color == false && parent->getRight() == sibling && sibling->getRight() != NULL && curr->color == false) {
	if (sibling->getRight()->color == true) {
	  Node* temp = sibling->getLeft();
	  sibling->setLeft(parent);
	  if (parent->parent != NULL) {
	    if (parent == parent->parent->getRight()) {
	      parent->parent->setRight(sibling);
	      sibling->parent = parent->parent;
	    }
	    else {
	      parent->parent->setLeft(sibling);
	      sibling->parent = parent->parent;
	    }
	  }
	  else {
	    sibling->parent = NULL;
	    root = sibling;
	  }
	  parent->parent = sibling;
	  parent->setRight(temp);
	  if (temp != NULL) {
	    temp->parent = parent;
	  }
	  //Sets colors
	  sibling->getRight()->color = false;
	  sibling->color = parent->color;
	  parent->color = false;
	  return;
	}
      }
    }
  }
}


void remove(Node* &root, Node* curr, int num, Node* newptr) {//Removes the number from the binary search tree
  if (search(curr, num, newptr) == true) {//If the number is in the tree
    Node* temp = newptr;
    Node* newPos = NULL;
    Node* x = NULL;
    if (temp == root) {//If thr root is the number to be deleted
      if (temp->getLeft() == NULL && temp->getRight() == NULL) {//If it is a leaf
	root = NULL;
	newptr = NULL;
      }
      else if (temp->getLeft() != NULL && temp->getRight() == NULL) {//If it only has a left child
	root = root->getLeft();
	root->parent = NULL;
	newptr = NULL;
	newPos = root;
      }
      else if (temp->getLeft() == NULL && temp->getRight() != NULL) {//If it only has a right child
	root = root->getRight();
	root->parent = NULL;
	newptr = NULL;
	newPos = root;
      }
      else {//If it has two children
	Node* newNode = temp->right;
        while (newNode->left != NULL) {//Goes to inorder sucser
          newNode = newNode->left;
        }
        temp->data = newNode->data;
	checkDelete(newNode, root);//Calls check delete
        if (newNode == temp->getRight()) {
          temp->right = temp->right->right;
        }
	else if(newNode->getRight() != NULL){
	  newNode->parent->left = newNode->right;
	  newNode->right->parent = newNode->parent;
	  if(newNode->parent->color){
	    newNode->right->color = false;
	  }
	}
	if (newNode->parent->left == newNode) {
	  newNode->parent->left = NULL;
	}
	newptr = NULL;
	newPos = root;
      }
    }
    else {
      if (temp->getLeft() == NULL && temp->getRight() == NULL) {//If it is a leaf
	if (temp->color == true) {
	  if (temp->parent->getLeft() == temp) {
	    temp->parent->setLeft(NULL);
	    delete temp;
	  }
	  else {
	    temp->parent->setRight(NULL);
	    delete temp;
	  }
	  return;
	}
	if (temp->parent->getLeft() == temp) {//Calls check delete then deletes
	  checkDelete(temp, root);
	  temp->parent->setLeft(NULL);
	}
	else {//Calls check delete then delets
	  checkDelete(temp, root);
	  temp->parent->setRight(NULL);
	}
	newptr = NULL;
      }
      else if (temp->getLeft() != NULL && temp->getRight() == NULL) {//If temp only has a left child
	//MAKEs THE PARENTS POINTER POINT TO THE CHILD (EASIER)
	Node* tempParent = temp->parent;
	if (tempParent->getLeft() == temp) {
	  if (temp->left->color == !temp->color) {//If colors are diffrent
	    tempParent->setLeft(temp->left);
	    temp->left->parent = tempParent;
	    if (temp->left->color) {//Sets temps left new color based on what the color variations are
	      temp->left->color = false;
	    }
	    else {
	      temp->left->color = true;
	    }
	    delete temp;
	    return;
	  }
	  //Deletes temp
	  tempParent->setLeft(temp->left);
	  temp->left->parent = tempParent;
	  delete temp;
	}
	else {
	  if (temp->left->color == !temp->color) {//If the colors are diffrent
	    tempParent->setRight(temp->left);
	    temp->left->parent = tempParent;
	    if (temp->left->color) {//Sets temps left new color based on the diffre color variations
	      temp->left->color = false;
	    }
	    else {
	      temp->left->color = true;
	    }
	    delete temp;
	    return;
	  }
	  //Deletes temp
	  tempParent->setRight(temp->left);
	  temp->left->parent = tempParent;
	  checkDelete(temp, root);
	}
	newptr = NULL;
      }
      else if (temp->getLeft() == NULL && temp->getRight() != NULL) {//If temp only has a right child
	Node* tempParent = temp->parent;
	if (tempParent->getRight() == temp) {
          if (temp->right->color == !temp->color) {//If colors are diffrent
            tempParent->setRight(temp->right);
	    temp->right->parent = tempParent;
            if (temp->right->color) {//Sets temp left based off color varients
              temp->right->color = false;
            }
	    else {
	      temp->right->color = true;
	    }
	    delete temp;
            return;
          }
	  //deletes temp then runs check delete
          tempParent->setRight(temp->right);
	  temp->right->parent = tempParent;
	  delete temp;
          checkDelete(temp, root);
	}
	else {
	  if (temp->right->color == !temp->color) {
	    tempParent->setLeft(temp->right);
	    temp->right->parent = tempParent;
            if (temp->right->color) {
              temp->right->color = false;
            }
	    else {
	      temp->right->color = true;
	    }
	    delete temp;
            return;
	  }
	  tempParent->setLeft(temp->right);
	  temp->right->parent = tempParent;
	  delete temp;
	  checkDelete(temp, root);
	}
	newptr = NULL;
      }
      else {//If it has two children
	Node* newNode = temp->right;
	while (newNode->left != NULL) {//Finds in order sucser
	  newNode = newNode->left;
	}
	temp->data = newNode->data;
	checkDelete(newNode, root);//Checks
	if (newNode == temp->getRight()) {
	  temp->right = temp->right->right;
	}
	if (newNode->parent->getLeft() == newNode) {
	  newNode->parent->setLeft(NULL);
	}
      }
    }
  }
}


