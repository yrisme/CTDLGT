#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct NodeMucLuc {
    string tieude;           
    int sotrang;             
    vector<NodeMucLuc*> muccon; 

    NodeMucLuc(const string& td, int st) : tieude(td), sotrang(st) {}
};

class CayMucLuc {
private:
    NodeMucLuc* goc;

    //De quy dem so chuong
    int demSoChuong(NodeMucLuc* node) {
        if (!node) return 0;
        int dem = (node->tieude.find("Chuong") == 0) ? 1 : 0;
        for (auto muc : node->muccon) {
            dem += demSoChuong(muc);
        }
        return dem;
    }

    //De quy tim chuong dai nhat
    NodeMucLuc* timChuongDaiNhat(NodeMucLuc* node, NodeMucLuc*& dainhat) {
        if (!node) return nullptr;

        if (node->tieude.find("Chuong") == 0 && (!dainhat || node->sotrang > dainhat->sotrang)) {
            dainhat = node;
        }
        for (auto muc : node->muccon) {
            timChuongDaiNhat(muc, dainhat);
        }
        return dainhat;
    }

    //Tim va xoa muc
    bool timVaXoa(NodeMucLuc*& node, const string& tieudeCanXoa) {
        if (!node) return false;

        if (node->tieude == tieudeCanXoa) {
            xoaNode(node);
            return true;
        }

        //Duyet cac muc con
        for (auto it = node->muccon.begin(); it != node->muccon.end(); ++it) {
            if ((*it)->tieude == tieudeCanXoa) {
                xoaNode(*it);
                node->muccon.erase(it); //Xoa khoi ds muc con
                return true;
            }
            if (timVaXoa(*it, tieudeCanXoa)) return true;
        }
        return false;
    }

    //Xoa node va cac muc con
    void xoaNode(NodeMucLuc*& node) {
        if (!node) return;
        for (auto muc : node->muccon) {
            xoaNode(muc);
        }
        delete node;
        node = nullptr;
    }

    //Hien thi cay
    void hienThi(NodeMucLuc* node, int capdo) {
        if (!node) return;
        cout << string(capdo * 4, ' ') << "- " << node->tieude << " (" << node->sotrang << " trang)\n";
        for (auto muc : node->muccon) {
            hienThi(muc, capdo + 1);
        }
    }

public:
    CayMucLuc() : goc(nullptr) {}

    //Thiet lap goc cay
    void taoGoc(const string& tieude, int sotrang) {
        goc = new NodeMucLuc(tieude, sotrang);
    }

    //Them muc con
    void themMucCon(NodeMucLuc* muccha, const string& tieude, int sotrang) {
        if (muccha) {
            muccha->muccon.push_back(new NodeMucLuc(tieude, sotrang));
        }
    }

    //Dem so chuong
    int soLuongChuong() {
        return demSoChuong(goc);
    }

    //Tim chuong dai nhat
    NodeMucLuc* chuongDaiNhat() {
        NodeMucLuc* chuongdai = nullptr;
        timChuongDaiNhat(goc, chuongdai);
        return chuongdai;
    }

    //Tim va xoa 1 muc
    bool xoaMuc(const string& tieude) {
        return timVaXoa(goc, tieude);
    }

    //Hien thi cay muc luc
    void inCay() {
        hienThi(goc, 0);
    }

    //Lay goc cay
    NodeMucLuc* layGoc() {
        return goc;
    }

    ~CayMucLuc() {
        xoaNode(goc);
    }
};

int main() {
    CayMucLuc sach;

    //Tao cay muc luc
    sach.taoGoc("Tieu de sach", 0);

    //Them cac chuong
    sach.themMucCon(sach.layGoc(), "Chuong 1: Tro choi tu than", 30);
    sach.themMucCon(sach.layGoc(), "Chuong 2: Khach tro & xac song", 50);
    sach.themMucCon(sach.layGoc(), "Chuong 3: Loi canh bao", 40);
    sach.themMucCon(sach.layGoc(), "Chuong 4: Nguoi thua thu 14", 60);
    sach.themMucCon(sach.layGoc(), "Chuong 5: 14 ngay kinh hoang", 40);

    //Them cac muc nho trong chuong 2
    NodeMucLuc* chuong2 = sach.layGoc()->muccon[1];
    sach.themMucCon(chuong2, "Muc 2.1: Khach tro", 20);
    sach.themMucCon(chuong2, "Muc 2.2: Xac song", 30);

    //Hien thi cay muc luc
    cout << "Muc luc ban dau:\n";
    sach.inCay();

    //Dem so chuong
    cout << "\nSo chuong: " << sach.soLuongChuong() << "\n";

    //Tim chuong dai nhat
    NodeMucLuc* chuongdai = sach.chuongDaiNhat();
    if (chuongdai) {
        cout << "Chuong dai nhat: " << chuongdai->tieude << " (" << chuongdai->sotrang << " trang)\n";
    }

    //Xoa 1 muc
    cout << "\nXoa muc 'Muc 2.1: Khach tro'...\n";
    if (sach.xoaMuc("Muc 2.1: Khach tro")) {
        cout << "Xoa thanh cong!\n";
    } else {
        cout << "Khong tim thay muc can xoa!\n";
    }

    //Hien thi cay muc luc sau khi xoa
    cout << "\nMuc luc sau khi xoa:\n";
    sach.inCay();

    return 0;
}
