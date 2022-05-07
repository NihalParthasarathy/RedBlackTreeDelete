//Nihal Parthasrathy
//5/7/2022
//This code makes a red black tree to sort numbers in a balanced form. It adds the numbers form manual adding or from a file and also displays i\
t
#ifndef NODE_H
#define NODE_H
#include <iostream>

class Node {//Node Class
 public:
  //Varubles and pointers
  Node* left;
  Node* right;
  Node* parent;
  bool color; //True is Red, False is black
  int data;
  //Prototypes
  Node(int newdata);
  void setLeft(Node* newleft);
  void setRight(Node* newright);
  Node* getLeft();
  Node* getRight();
  Node* getParent();
  int getData();
  void setParent(Node* newparent);
  bool getColor();

};




#endif
