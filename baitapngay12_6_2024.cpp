#include <iostream>

using namespace std;

//dn cau truc nut trong cay
struct Node {
    char value[10];       
    Node* left;           //con trai
    Node* right;          //con phai

    //ham tao
    Node(const char* val) {
        copyString(value, val); //copy gtri
        left = nullptr;
        right = nullptr;
    }

    //ham copystring
    static void copyString(char* dest, const char* src) {
        while (*src) {
            *dest++ = *src++;
        }
        *dest = '\0'; 
    }
};

//ham duyet tien to
void preOrder(Node* root) {
    if (root) {
        char* val = root->value;
        while (*val) {
            cout.put(*val++);
        }
        cout.put(' ');
        preOrder(root->left);
        preOrder(root->right);
    }
}

//ham duyet trung to
void inOrder(Node* root) {
    if (root) {
        inOrder(root->left);
        char* val = root->value;
        while (*val) {
            cout.put(*val++);
        }
        cout.put(' ');
        inOrder(root->right);
    }
}

//ham duyet hau to
void postOrder(Node* root) {
    if (root) {
        postOrder(root->left);
        postOrder(root->right);
        char* val = root->value;
        while (*val) {
            cout.put(*val++);
        }
        cout.put(' ');
    }
}

int main() {
    Node* root = new Node("+");

    //xay dung cay con trai
    root->left = new Node("-");
    root->left->left = new Node("+");
    root->left->left->left = new Node("a");
    root->left->left->right = new Node("/");
    root->left->left->right->left = new Node("*");
    root->left->left->right->left->left = new Node("5");
    root->left->left->right->left->right = new Node("b");
    root->left->left->right->right = new Node("c");
    root->left->right = new Node("^");
    root->left->right->left = new Node("c");
    root->left->right->right = new Node("8");

    //xay dung cay con phai
    root->right = new Node("*");
    root->right->left = new Node("d");
    root->right->right = new Node("^");
    root->right->right->left = new Node("e");
    root->right->right->right = new Node("0.5");

    cout << "Duyet tien to: ";
    preOrder(root);
    cout << "\n";

    cout << "Duyet trung to: ";
    inOrder(root);
    cout << "\n";

    cout << "Duyet hau to: ";
    postOrder(root);
    cout << "\n";

    return 0;
}
