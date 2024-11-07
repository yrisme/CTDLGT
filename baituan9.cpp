#include <iostream>

struct Node {
    int coeff;  //Hệ số
    int exp;    //Số mũ
    Node* next; //Trỏ đến node tiếp theo
};

//Hàm tạo node 
Node* createNode(int coeff, int exp) {
    Node* newNode = new Node();
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = nullptr;
    return newNode;
}

//Hàm thêm node vào cuối dslk
void appendNode(Node*& poly, int coeff, int exp) {
    Node* newNode = createNode(coeff, exp);
    if (!poly) {
        poly = newNode;
    } else {
        Node* temp = poly;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
}

//Hàm nhập đa thức
void inputPolynomial(Node*& poly) {
    int degree;
    std::cout << "Nhập bậc của đa thức: ";
    std::cin >> degree; // Nhập bậc của đa thức
    for (int i = degree; i >= 0; --i) {
        int coeff;
        std::cout << "Nhập hệ số cho x^" << i << ": ";
        std::cin >> coeff; // Nhập hệ số cho từng x^i
        if (coeff != 0) {
            appendNode(poly, coeff, i); //Thêm node vào đa thức nếu hệ số # 0
        }
    }
}

//Hàm cộng đa thức
Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = nullptr;
    while (poly1 || poly2) {
        if (poly1 && (!poly2 || poly1->exp > poly2->exp)) {
            appendNode(result, poly1->coeff, poly1->exp);
            poly1 = poly1->next;
        } else if (poly2 && (!poly1 || poly2->exp > poly1->exp)) {
            appendNode(result, poly2->coeff, poly2->exp);
            poly2 = poly2->next;
        } else {
            int sumCoeff = poly1->coeff + poly2->coeff;
            if (sumCoeff != 0) {
                appendNode(result, sumCoeff, poly1->exp);
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }
    return result;
}

//Hàm in đa thức kèm theo địa chỉ của các phần tử (debug)
void printPolynomialWithDebug(Node* poly) {
    while (poly) {
        std::cout << "Node tại địa chỉ " << poly << ": " << poly->coeff << "x^" << poly->exp;
        if (poly->next) std::cout << " -> ";
        poly = poly->next;
    }
    std::cout << std::endl;
}

int main() {
    Node* poly1 = nullptr;
    Node* poly2 = nullptr;

    std::cout << "Nhập đa thức thứ nhất:\n";
    inputPolynomial(poly1);  

    std::cout << "\nNhập đa thức thứ hai:\n";
    inputPolynomial(poly2);  

    Node* result = addPolynomials(poly1, poly2);

    std::cout << "\nĐa thức thứ nhất (kèm địa chỉ từng node):\n";
    printPolynomialWithDebug(poly1);

    std::cout << "\nĐa thức thứ hai (kèm địa chỉ từng node):\n";
    printPolynomialWithDebug(poly2);

    std::cout << "\nĐa thức tổng (kèm địa chỉ từng node):\n";
    printPolynomialWithDebug(result);

    return 0;
}
