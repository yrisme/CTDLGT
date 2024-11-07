#include <iostream>

struct Node {
    int data; 
    Node* next; //Trỏ đến node tiếp theo
};

//Hàm tạo một node 
Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

//Hàm chèn một node vào sau node T
void insertAfter(Node* T, int newData) {
    if (T == nullptr) {
        std::cout << "Node T không hợp lệ." << std::endl;
        return;
    }
    
    // Tạo một node mới
    Node* newNode = new Node();
    newNode->data = newData;
    newNode->next = T->next;  //Kết nối con trỏ của node mới với node tiếp theo của T
    T->next = newNode;        //Kết nối node T với node mới
}

//Hàm xóa node cuối 
void deleteTail(Node*& head) {
    if (head == nullptr) {
        std::cout << "Danh sách rỗng." << std::endl;
        return;
    }
    
    if (head->next == nullptr) {  //Nếu danh sách chỉ có 1 node
        delete head;
        head = nullptr;
        return;
    }
    
    Node* temp = head;
    //Duyệt đến node trước node cuối
    while (temp->next && temp->next->next) {
        temp = temp->next;
    }
    
    //Xóa node cuối
    Node* lastNode = temp->next;
    temp->next = nullptr;
    delete lastNode;
}

//Hàm xóa một node được trỏ bởi con trỏ T
void deleteNode(Node*& head, Node* T) {
    if (T == nullptr || head == nullptr) {
        std::cout << "Node không hợp lệ hoặc danh sách rỗng." << std::endl;
        return;
    }

    //Node T là node đầu 
    if (T == head) {
        head = head->next;
        delete T;
        return;
    }

    //Tìm node trước node T
    Node* temp = head;
    while (temp != nullptr && temp->next != T) {
        temp = temp->next;
    }

    //Tìm thấy node trước T
    if (temp != nullptr) {
        temp->next = T->next;  //Bỏ qua T
        delete T;  //Xóa node T
    } else {
        std::cout << "Node không tồn tại trong danh sách." << std::endl;
    }
}

//Hàm in dslk
void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        std::cout << temp->data << " -> ";
        temp = temp->next;
    }
    std::cout << "nullptr" << std::endl;
}

int main() {

    Node* head = nullptr;

    Node* first = createNode(10);
    head = first;

    Node* second = createNode(20);
    first->next = second;

    Node* third = createNode(30);
    second->next = third;

    std::cout << "Danh sách ban đầu: ";
    printList(head);

    //Chèn node 
    insertAfter(second, 25);
    std::cout << "Danh sách sau khi chèn node 25 sau node 20: ";
    printList(head);

    deleteTail(head);
    std::cout << "Danh sách sau khi xóa node đuôi: ";
    printList(head);

    //Xóa node 25
    deleteNode(head, second->next);  
    std::cout << "Danh sách sau khi xóa node có giá trị 25: ";
    printList(head);

    return 0;
}
