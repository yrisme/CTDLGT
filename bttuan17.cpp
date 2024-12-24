#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct NutAVL {
    int gia_tri;
    int chieu_cao;
    NutAVL* trai;
    NutAVL* phai;

    NutAVL(int gt) : gia_tri(gt), chieu_cao(1), trai(nullptr), phai(nullptr) {}
};

class CayAVL {
private:
    NutAVL* goc;

    int lay_chieu_cao(NutAVL* nut) {
        return nut ? nut->chieu_cao : 0;
    }

    void cap_nhat_chieu_cao(NutAVL* nut) {
        if (nut) {
            nut->chieu_cao = 1 + max(lay_chieu_cao(nut->trai), lay_chieu_cao(nut->phai));
        }
    }

    int lay_do_lech(NutAVL* nut) {
        return nut ? lay_chieu_cao(nut->trai) - lay_chieu_cao(nut->phai) : 0;
    }

    NutAVL* xoay_phai(NutAVL* y) {
        NutAVL* x = y->trai;
        NutAVL* T2 = x->phai;

        x->phai = y;
        y->trai = T2;

        cap_nhat_chieu_cao(y);
        cap_nhat_chieu_cao(x);

        return x;
    }

    NutAVL* xoay_trai(NutAVL* x) {
        NutAVL* y = x->phai;
        NutAVL* T2 = y->trai;

        y->trai = x;
        x->phai = T2;

        cap_nhat_chieu_cao(x);
        cap_nhat_chieu_cao(y);

        return y;
    }

    NutAVL* can_bang_nut(NutAVL* nut) {
        int do_lech = lay_do_lech(nut);

        // Mất cân bằng bên trái
        if (do_lech > 1) {
            if (lay_do_lech(nut->trai) < 0) { // Trường hợp trái-phải
                nut->trai = xoay_trai(nut->trai);
            }
            return xoay_phai(nut); // Trường hợp trái-trái
        }

        // Mất cân bằng bên phải
        if (do_lech < -1) {
            if (lay_do_lech(nut->phai) > 0) { // Trường hợp phải-trái
                nut->phai = xoay_phai(nut->phai);
            }
            return xoay_trai(nut); // Trường hợp phải-phải
        }

        return nut;
    }

    NutAVL* chen(NutAVL* nut, int gia_tri) {
        if (!nut) {
            return new NutAVL(gia_tri);
        }

        if (gia_tri < nut->gia_tri) {
            nut->trai = chen(nut->trai, gia_tri);
        } else if (gia_tri > nut->gia_tri) {
            nut->phai = chen(nut->phai, gia_tri);
        } else {
            return nut; // Không cho phép giá trị trùng lặp
        }

        cap_nhat_chieu_cao(nut);
        return can_bang_nut(nut);
    }

    void duyet_trung_tu(NutAVL* nut, vector<int>& ket_qua) {
        if (nut) {
            duyet_trung_tu(nut->trai, ket_qua);
            ket_qua.push_back(nut->gia_tri);
            duyet_trung_tu(nut->phai, ket_qua);
        }
    }

    void duyet_tien_tu(NutAVL* nut, vector<int>& ket_qua) {
        if (nut) {
            ket_qua.push_back(nut->gia_tri);
            duyet_tien_tu(nut->trai, ket_qua);
            duyet_tien_tu(nut->phai, ket_qua);
        }
    }

public:
    CayAVL() : goc(nullptr) {}

    void them(int gia_tri) {
        goc = chen(goc, gia_tri);
    }

    void in_cac_buoc(const vector<int>& danh_sach) {
        for (size_t i = 0; i < danh_sach.size(); ++i) {
            cout << "Bước " << i + 1 << ": Thêm " << danh_sach[i] << endl;
            them(danh_sach[i]);

            vector<int> trung_tu, tien_tu;
            duyet_trung_tu(goc, trung_tu);
            duyet_tien_tu(goc, tien_tu);

            cout << "Duyệt trung tự: ";
            for (int val : trung_tu) {
                cout << val << " ";
            }
            cout << endl;

            cout << "Duyệt tiên tự: ";
            for (int val : tien_tu) {
                cout << val << " ";
            }
            cout << endl;

            cout << "-------------------------------------" << endl;
        }
    }
};

int main() {
    vector<int> danh_sach = {240, 73, 101, 21, 13, 25, 11, 37, 89, 30, 15, 51};
    CayAVL cay;
    cay.in_cac_buoc(danh_sach);
    return 0;
}
