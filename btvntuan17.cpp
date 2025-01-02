#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

// So dinh cua do thi
const int so_dinh = 7;

// Ma tran ke (7x7)
int do_thi[so_dinh][so_dinh] = {
    {0, 1, 0, 1, 1, 0, 1},
    {0, 0, 1, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 1, 1},
    {1, 0, 1, 0, 0, 1, 1},
    {0, 1, 0, 1, 0, 1, 1},
    {1, 1, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 1, 0, 0}
};

// Duyet BFS
void duyet_BFS(int bat_dau) {
    vector<bool> dinh_da_duyet(so_dinh, false);
    queue<int> hang_doi;
    hang_doi.push(bat_dau);
    dinh_da_duyet[bat_dau] = true;

    cout << "Duyet BFS: ";
    while (!hang_doi.empty()) {
        int dinh = hang_doi.front();
        hang_doi.pop();
        cout << char('a' + dinh) << " "; // Hien thi dinh duoi dang chu cai

        for (int i = 0; i < so_dinh; i++) {
            if (do_thi[dinh][i] && !dinh_da_duyet[i]) {
                hang_doi.push(i);
                dinh_da_duyet[i] = true;
            }
        }
    }
    cout << endl;
}

// Duyet DFS
void duyet_DFS(int bat_dau) {
    vector<bool> dinh_da_duyet(so_dinh, false);
    stack<int> ngan_xep;
    ngan_xep.push(bat_dau);

    cout << "Duyet DFS: ";
    while (!ngan_xep.empty()) {
        int dinh = ngan_xep.top();
        ngan_xep.pop();

        if (!dinh_da_duyet[dinh]) {
            dinh_da_duyet[dinh] = true;
            cout << char('a' + dinh) << " "; // Hien thi dinh duoi dang chu cai
        }

        for (int i = so_dinh - 1; i >= 0; i--) {
            if (do_thi[dinh][i] && !dinh_da_duyet[i]) {
                ngan_xep.push(i);
            }
        }
    }
    cout << endl;
}

int main() {
    // Nhap dinh bat dau duyet
    char bat_dau;
    cout << "Nhap dinh bat dau (a-g): ";
    cin >> bat_dau;

    // Duyet BFS va DFS
    duyet_BFS(bat_dau - 'a');
    duyet_DFS(bat_dau - 'a');

    return 0;
}
