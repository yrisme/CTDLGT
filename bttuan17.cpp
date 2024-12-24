#include <iostream>
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
            int chieu_cao_trai = lay_chieu_cao(nut->trai);
            int chieu_cao_phai = lay_chieu_cao(nut->phai);
            nut->chieu_cao = 1 + (chieu_cao_trai > chieu_cao_phai ? chieu_cao_trai : chieu_cao_phai);
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

        if (do_lech > 1) {
            if (lay_do_lech(nut->trai) < 0) {
                nut->trai = xoay_trai(nut->trai);
            }
            return xoay_phai(nut);
        }

        if (do_lech < -1) {
            if (lay_do_lech(nut->phai) > 0) {
                nut->phai = xoay_phai(nut->phai);
            }
            return xoay_trai(nut);
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
            return nut;
        }

        cap_nhat_chieu_cao(nut);
        return can_bang_nut(nut);
    }

    void duyet_trung_tu(NutAVL* nut) {
        if (nut) {
            duyet_trung_tu(nut->trai);
            cout << nut->gia_tri << " ";
            duyet_trung_tu(nut->phai);
        }
    }

    void duyet_tien_tu(NutAVL* nut) {
        if (nut) {
            cout << nut->gia_tri << " ";
            duyet_tien_tu(nut->trai);
            duyet_tien_tu(nut->phai);
        }
    }

public:
    CayAVL() : goc(nullptr) {}

    void them(int gia_tri) {
        goc = chen(goc, gia_tri);
    }

    void in_cac_buoc(int danh_sach[], int kich_thuoc) {
        for (int i = 0; i < kich_thuoc; ++i) {
            cout << "Bước " << i + 1 << ": Thêm " << danh_sach[i] << endl;
            them(danh_sach[i]);

            cout << "Duyệt trung tự: ";
            duyet_trung_tu(goc);
            cout << endl;

            cout << "Duyệt tiên tự: ";
            duyet_tien_tu(goc);
            cout << endl;

            cout << "-------------------------------------" << endl;
        }
    }
};

int main() {
    int danh_sach[] = {240, 73, 101, 21, 13, 25, 11, 37, 89, 30, 15, 51};
    int kich_thuoc = sizeof(danh_sach) / sizeof(danh_sach[0]);

    CayAVL cay;
    cay.in_cac_buoc(danh_sach, kich_thuoc);

    return 0;
}
