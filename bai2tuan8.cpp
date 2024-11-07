#include <iostream>
using namespace std;

struct Term {
    int coefficient; //Hệ số
    int exponent;    //Bậc
    Term* next;     
};

//Hàm tạo node 
Term* createTerm(int coeff, int exp) {
    Term* newTerm = new Term();
    newTerm->coefficient = coeff;
    newTerm->exponent = exp;
    newTerm->next = nullptr;
    return newTerm;
}

//Hàm nhập đa thức 
Term* inputPolynomial() {
    Term* head = nullptr;
    Term* tail = nullptr;
    int n;
    cout << "Nhập số lượng hạng tử của đa thức: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        int coeff, exp;
        cout << "Nhập hệ số và bậc của hạng tử thứ " << i+1 << ": ";
        cin >> coeff >> exp;
        
        Term* newTerm = createTerm(coeff, exp);
        if (head == nullptr) {
            head = newTerm;
            tail = newTerm;
        } else {
            tail->next = newTerm;
            tail = newTerm;
        }
    }
    return head;
}

//Hàm in đa thức
void printPolynomial(Term* poly) {
    Term* temp = poly;
    if (temp == nullptr) {
        cout << "Đa thức rỗng!" << endl;
        return;
    }

    while (temp != nullptr) {
        if (temp->coefficient > 0 && temp != poly) {
            cout << "+";
        }
        cout << temp->coefficient << ".x^" << temp->exponent << " ";
        temp = temp->next;
    }
    cout << endl;
}

//Hàm cộng hai đa thức
Term* addPolynomials(Term* poly1, Term* poly2) {
    Term* result = nullptr;
    Term* tail = nullptr;

    while (poly1 != nullptr || poly2 != nullptr) {
        int coeff = 0;
        int exp;

        if (poly1 != nullptr && (poly2 == nullptr || poly1->exponent > poly2->exponent)) {
            coeff = poly1->coefficient;
            exp = poly1->exponent;
            poly1 = poly1->next;
        } else if (poly2 != nullptr && (poly1 == nullptr || poly2->exponent > poly1->exponent)) {
            coeff = poly2->coefficient;
            exp = poly2->exponent;
            poly2 = poly2->next;
        } else {
            coeff = poly1->coefficient + poly2->coefficient;
            exp = poly1->exponent;
            poly1 = poly1->next;
            poly2 = poly2->next;
        }

        if (coeff != 0) {
            Term* newTerm = createTerm(coeff, exp);
            if (result == nullptr) {
                result = newTerm;
                tail = newTerm;
            } else {
                tail->next = newTerm;
                tail = newTerm;
            }
        }
    }
    return result;
}

int main() {

    cout << "Nhập đa thức f(x): " << endl;
    Term* poly1 = inputPolynomial();
    cout << "Nhập đa thức g(x): " << endl;
    Term* poly2 = inputPolynomial();

    cout << "f(x) = ";
    printPolynomial(poly1);

    cout << "g(x) = ";
    printPolynomial(poly2);

    Term* result = addPolynomials(poly1, poly2);

    cout << "h(x) = ";
    printPolynomial(result);

    return 0;
}
