#ifndef AVL_H
#define AVL_H
#include <vector>
#include <iostream>
#include <string>
using namespace std;

struct Node {
    // Node attributes
    string name;
    string ufid;
    int height;
    Node* left;
    Node* right;

    // Node constructor
    Node(string name, string ufid) {
        this->name = name;
        this->ufid = ufid;
        this->height = 1;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class AVLTree {
private:
    Node* root = nullptr;
    int getHeight(Node* node);
    int getBalanceFactor(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeftRight(Node* node);
    Node* rotateRightLeft(Node* node);
    Node* insertHelper(Node* node, const string& name, const string& ufid, bool& success);
    Node* removeHelper(Node* node, const string& ufid, bool& success);
    void searchNameHelper(Node* node, const string& name, vector<string>& idFound);
    Node* searchIDHelper(Node* node, const string& ufid);
    void printInOrderHelper(Node* root, vector<string>& nameList);
    void printPreOrderHelper(Node* root, vector<string>& nameList);
    void printPostOrderHelper(Node* root, vector<string>& nameList);
    void getInOrderUFID(Node* root, vector<string>& ufidList);
public:
    void insert(const string& name, const string& ufid);
    void remove(const string& ufid);
    void searchID(const string&ufid);
    void searchName(const string& name);
    void printInOrder();
    void printPreOrder();
    void printPostOrder();
    void printLevelCount();
    void removeInOrderN(int n);

    // destructor
    ~AVLTree() {
        // use a postorder traversal to delete nodes since each node will
        // only get visited once with a postorder traversal
    }
};

#endif //AVL_H
