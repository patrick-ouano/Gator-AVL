#include <iostream>
#include <algorithm>
#include <regex>
#include "AVL.h"
using namespace std;

int AVLTree::getHeight(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->height;
}

int AVLTree::getBalanceFactor(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return getHeight(node->left) - getHeight(node->right);
}

bool AVLTree::insert(string& name, string& ufid, bool& duplicateID){
  // checks if UFId is exactly 8 characters and if all chars are digits
  if (ufid.length() != 8 ) { // || !all_of(ufid.begin(), ufid.end(), ::isdigit)
    // cout << "unsuccessful" << endl;
    return false;
  }

  // checks if all chars are digits
  for (char c: ufid) {
    if (!isdigit(c)) {
      // cout << "unsuccessful" << endl;
      return false;
    }
  }

  // check for valid characters
  const regex validName("^[a-zA-Z ]+$");
  if (!regex_match(name, validName)) {
    // cout << "unsuccessful" << endl;
    return false;
  }

  // calls recursive helper
  root = insertHelper(this->root, name, ufid, duplicateID);

  if (duplicateID == false) {
    // cout << "successful" << endl;
    return true;
  }
  else {
    // cout << "unsuccessful" << endl;
    return false;
  }
}

Node* AVLTree::insertHelper(Node* node, string& name, string& ufid, bool& duplicateID) {
  if (node == nullptr) {
    duplicateID = false;
    return new Node(name, ufid);
  }
  else if (ufid < node->ufid) {
    node->left = insertHelper(node->left,name, ufid, duplicateID);
  }
  else if (ufid > node->ufid) {
    node->right = insertHelper(node->right, name, ufid, duplicateID);
  }
  // checks if there are duplicate IDs
  else {
    duplicateID = true;
    return node;
  }

  // update height - taken from lecture video
  node->height = 1 + max(getHeight(node->left), getHeight(node->right));

  // if tree is right heavy
  if (getBalanceFactor(node) < -1) {
    // if tree's right subtree is left heavy
    if (getBalanceFactor(node->right) > 1) {
      node = rotateRightLeft(node);
      node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
    else {
      node = rotateLeft(node);
      node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
  }
  // if tree is left heavy
  else if (getBalanceFactor(node) > 1) {
    // if tree's left subtree is right heavy
    if (getBalanceFactor(node->left) < -1) {
      node = rotateLeftRight(node);
      node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
    else {
      node = rotateRight(node);
      node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
  }
  return node;
}

Node* AVLTree::rotateLeft(Node* node) {
  Node* grandchild = node->right->left;
  Node* newParent = node->right;
  newParent->left = node;
  node->right = grandchild;
  return newParent;
}

Node* AVLTree::rotateRight(Node* node) {
  Node* grandchild = node->left->right;
  Node* newParent = node->left;
  newParent->right = node;
  node->left = grandchild;
  return newParent;
}

Node* AVLTree::rotateLeftRight(Node* node) {
  node->left = rotateLeft(node->left);
  return rotateRight(node);
}

Node* AVLTree::rotateRightLeft(Node* node) {
  node->right = rotateRight(node->right);
  return rotateLeft(node);
}

void AVLTree::remove(int id){
  return;
}

void AVLTree::searchID(int id){
  return;
}

void AVLTree::searchName(string name){
  return;
}

void AVLTree::printInOrder(Node* root){
  if (root != nullptr) {
    printInOrder(root->left);
    cout << root->name << ", ";
    printInOrder(root->right);
  }
}

void AVLTree::printPreOrder(Node* root){
  if (root != nullptr) {
    cout << root->name << ", ";
    printPreOrder(root->left);
    printPreOrder(root->right);
  }
}

void AVLTree::printPostOrder(Node* root){
  if (root != nullptr) {
    printPostOrder(root->left);
    printPostOrder(root->right);
    cout << root->name << ", ";
  }
}

void AVLTree::printLevelCount(){
  return;
}

void AVLTree::removeInOrderN(){
  return;
}