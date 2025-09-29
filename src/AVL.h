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
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeftRight(Node* node);
    Node* rotateRightLeft(Node* node);
    Node* insertHelper(Node* node, string& name, string& ufid, bool& success);
    Node* removeHelper(Node* node, string& ufid, bool& success);
    void searchNameHelper(Node* node, string& name, vector<string>& idFound);
    Node* searchIDHelper(Node* node, string& ufid);
    void printInOrderHelper(Node* root, vector<string>& nameList);
    void printPreOrderHelper(Node* root, vector<string>& nameList);
    void printPostOrderHelper(Node* root, vector<string>& nameList);
    void getInOrderUFID(Node* root, vector<string>& ufidList);
public:
    void insert(string name, string ufid);
    void remove(string ufid);
    void searchID(string ufid);
    void searchName(string name);
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
