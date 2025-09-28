#ifndef AVL_H
#define AVL_H
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
    Node* insertHelper(Node* node, string& name, string& ufid, bool& duplicateID);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeftRight(Node* node);
    Node* rotateRightLeft(Node* node);
public:
    bool insert(string& name, string& ufid, bool& duplicateID);
    void remove(int id);
    void searchID(int id);
    void searchName(string name);
    void printInOrder(Node* root);
    void printPreOrder(Node* root);
    void printPostOrder(Node* root);
    void printLevelCount();
    void removeInOrderN();

    // destructor
    ~AVLTree() {
        // use a postorder traversal to delete nodes since each node will
        // only get visited once with a postorder traversal
    }

};

#endif //AVL_H
