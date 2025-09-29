#include <iostream>
#include <algorithm>
#include <regex>
#include "AVL.h"
using namespace std;

// helper functions
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

Node* AVLTree::insertHelper(Node* node, const string& name, const string& ufid, bool& success) {
  if (node == nullptr) {
    success = true;
    return new Node(name, ufid);
  }
  else if (ufid < node->ufid) {
    node->left = insertHelper(node->left,name, ufid, success);
  }
  else if (ufid > node->ufid) {
    node->right = insertHelper(node->right, name, ufid, success);
  }
  // checks if there are duplicate IDs
  else {
    success = false;
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

void AVLTree::printPreOrderHelper(Node* root, vector<string>& nameList) {
  if (root != nullptr) {
    nameList.push_back(root->name);
    printPreOrderHelper(root->left, nameList);
    printPreOrderHelper(root->right, nameList);
  }
}

void AVLTree::printInOrderHelper(Node* root, vector<string>& nameList) {
  if (root != nullptr) {
    printInOrderHelper(root->left, nameList);
    nameList.push_back(root->name);
    printInOrderHelper(root->right, nameList);
  }
}

void AVLTree::printPostOrderHelper(Node* root, vector<string>& nameList) {
  if (root != nullptr) {
    printPostOrderHelper(root->left, nameList);
    printPostOrderHelper(root->right, nameList);
    nameList.push_back(root->name);
  }
}

void AVLTree::getInOrderUFID(Node *root, vector<string> &ufidList) {
  if (root != nullptr) {
    getInOrderUFID(root->left, ufidList);
    ufidList.push_back(root->ufid);
    getInOrderUFID(root->right, ufidList);
  }
}

void AVLTree::searchNameHelper(Node *node, const string& name, vector<string> &idFound) {
  if (node == nullptr) {
    return;
  }

  //uses pre-order traversal to match name and ufid
  if (node->name == name) {
    idFound.push_back(node->ufid);
  }
  searchNameHelper(node->left, name, idFound);
  searchNameHelper(node->right, name, idFound);
}

Node* AVLTree::searchIDHelper(Node* node, const string& ufid) {
  if (node == nullptr) {
    return nullptr;
  }

  if (ufid == node->ufid) {
    return node;
  }

  if (ufid < node->ufid) {
    return searchIDHelper(node->left, ufid);
  }
  else {
    return searchIDHelper(node->right, ufid);
  }
}

Node* AVLTree:: removeHelper(Node* node, const string& ufid, bool& success){
  if (node == nullptr) {
    success = false;
    return nullptr;
  }

  if (ufid < node->ufid) {
    node->left = removeHelper(node->left, ufid, success);
  }
  else if (ufid > node->ufid) {
    node->right = removeHelper(node->right, ufid, success);
  }
  else {
    success = true;
    Node* temp;

    // 0 or 1 child case
    if (node->left == nullptr || node->right == nullptr) {
      temp = node->left ? node->left : node->right;
      Node* temp = node->left ? node->left : node->right;
      delete node; // Delete the current node
      return temp; // Return its child (or nullptr) to be re-linked

      // // 0 child case
      // if (temp == nullptr) {
      //   temp = node;
      //   node = nullptr;
      // }
      // // 1 child case
      // else {
      //   Node* nodeDelete = node;
      //   node = temp;
      //   delete nodeDelete;
      //   return node;
      // }
      // delete temp;

    }
    // 2 child case
    else {
      temp = node->right;
      while (temp->left != nullptr) {
        temp = temp->left;
      }
      node->name = temp->name;
      node->ufid = temp->ufid;
      node->right = removeHelper(node->right, temp->ufid, success);
    }
  }
  if (node == nullptr) {
    return node;
  }

  return node;
}

// public functions
void AVLTree::insert(const string& name, const string& ufid){
  // checks if UFId is exactly 8 characters and if all chars are digits
  if (ufid.length() != 8 ) {
    cout << "unsuccessful" << endl;
    return;
  }

  // checks if all chars are digits
  for (char c: ufid) {
    if (!isdigit(c)) {
      cout << "unsuccessful" << endl;
      return;
    }
  }

  // check for valid characters
  const regex validName("^[a-zA-Z ]+$");
  if (!regex_match(name, validName)) {
    cout << "unsuccessful" << endl;
    return;
  }

  bool success = true;
  // calls recursive helper
  root = insertHelper(this->root, name, ufid, success);

  if (success == true) {
    cout << "successful" << endl;
    return;
  }
  else {
    cout << "unsuccessful" << endl;
    return;
  }
}

void AVLTree::remove(const string& ufid){
  bool success = false;
  root = removeHelper(root, ufid, success);
  if (success) {
    cout << "successful" << endl;
  }
  else {
    cout << "unsuccessful" << endl;
  }
}

void AVLTree::searchID(const string& ufid){
  Node* node = searchIDHelper(this->root, ufid);

  if (node != nullptr) {
    cout << node->name << endl;
  }
  else {
    cout << "unsuccessful" << endl;
  }

}

void AVLTree::searchName(const string& name){
  vector<string> idFound;
  searchNameHelper(root, name, idFound);

  if (idFound.empty()) {
    cout << "unsuccessful" << endl;
  }
  else {
    for (auto& id : idFound) {
      cout << id << endl;
    }
  }
}

void AVLTree::printPreOrder(){
  vector<string> nameList;
  printPreOrderHelper(this->root, nameList);
  for (size_t i = 0; i < nameList.size(); i++) {
    cout << nameList[i];
    if (i < nameList.size() - 1) {
      cout << ", ";
    }
  }
  cout << endl;
}

void AVLTree::printInOrder(){
  vector<string> nameList;
  printInOrderHelper(this->root, nameList);
  for (size_t i = 0; i < nameList.size(); i++) {
    cout << nameList[i];
    if (i < nameList.size() - 1) {
      cout << ", ";
    }
  }
  cout << endl;
}

void AVLTree::printPostOrder(){
  vector<string> nameList;
  printPostOrderHelper(this->root, nameList);
  for (size_t i = 0; i < nameList.size(); i++) {
    cout << nameList[i];
    if (i < nameList.size() - 1) {
      cout << ", ";
    }
  }
  cout << endl;
}

void AVLTree::printLevelCount(){
  cout << getHeight(this->root) << endl;
}

void AVLTree::removeInOrderN(int n){
  vector<string> ufidList;
  getInOrderUFID(root, ufidList);

  if (n >= 0 && static_cast<size_t>(n) < ufidList.size()) {
    remove(ufidList[n]);
  }
  else {
    cout << "unsuccessful" << endl;
  }
}