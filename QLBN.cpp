#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct BenhNhan {
    long long SDT;
    string ho;
    string ten;
    int tuoi;
    string nhomMau;
    string gioiTinh;
    BenhNhan* tiep;
};

class HangDoiKetNoi {
    BenhNhan* dau;
    BenhNhan* cuoi;

public:
    HangDoiKetNoi() {
        dau = nullptr;
        cuoi = nullptr;
    }

    BenhNhan NhapThongTin();
    void ThemVaoCuoi();
    void ThemVaoDau();
    void XuatThongTinBenhNhan();
    bool TimKiem(long long);
    void SuaThongTinBenhNhan(long long);
    void XoaBenhNhan(long long);
    void DuaBenhNhanDenBacSi();
    void LuuDanhSachBenhNhanVaoTepTin();
    string tenPhongKham;
};

// Kiểm tra xem bệnh nhân có tồn tại trong danh sách không
bool HangDoiKetNoi::TimKiem(long long item) {
    BenhNhan* p = dau;

    while (p != nullptr) {
        if (p->SDT == item) {
            return true;
        }
        p = p->tiep;
    }
    return false;
}

// Nhập thông tin của bệnh nhân
BenhNhan HangDoiKetNoi::NhapThongTin() {
    BenhNhan p;
    system("cls");
    cout << "\n\tVui long nhap thong tin benh nhan\n\n";
    cout << "\tHo: ";
    cin >> p.ho;
    cout << "\tTen: ";
    cin >> p.ten;

    bool nhapLaiNhomMau = true;
    while (nhapLaiNhomMau) {
        cout << "\tNhom mau (A+, A-, B+, B-, O+, O-): ";
        cin >> p.nhomMau;
        p.nhomMau[0] = toupper(p.nhomMau[0]);
        p.nhomMau[1] = toupper(p.nhomMau[1]);
        if (p.nhomMau == "A+" || p.nhomMau == "A-" || p.nhomMau == "B+" || p.nhomMau == "B-" ||
            p.nhomMau == "O+" || p.nhomMau == "O-") {
            nhapLaiNhomMau = false;
        } else {
            cout << "\tNhom mau khong hop le. Vui long nhap lai.\n";
        }
    }

    // Nhập giới tính 
    do {
        cout << "\tGioi tinh (1: Nam / 2: Nu): ";
        int luaChon;
        cin >> luaChon;
        if (luaChon == 1) {
            p.gioiTinh = "Nam";
            break;
        } else if (luaChon == 2) {
            p.gioiTinh = "Nu";
            break;
        } else {
            cout << "\tLua chon khong hop le. Vui long nhap lai.\n";
        }
    } while (true);

    // Nhập tuổi 
    do {
        cout << "\tTuoi: ";
        cin >> p.tuoi;
        if (p.tuoi <= 1) {
            cout << "\tTuoi phai la mot so nguyen lon hon 1. Vui long nhap lai.\n";
        }
    } while (p.tuoi <= 1);

    // Nhập số điện thoại 
    do {
        cout << "\tSo dien thoai: ";
        cin >> p.SDT;
        if (p.SDT <= 0) {
            cout << "\tSo dien thoai phai la mot so nguyen duong. Vui long nhap lai.\n";
        } else if (TimKiem(p.SDT)) {
            cout << "\tSo dien thoai da ton tai trong danh sach. Vui long nhap lai.\n";
        } else {
            break;
        }
    } while (true);

    return p;
}

// Hiển thị thông tin của bệnh nhân
void HangDoiKetNoi::XuatThongTinBenhNhan() {
    if (dau == nullptr) {
        cout << "\n\tKhong co benh nhan de hien thi";
        return;
    }

    BenhNhan* p = dau;
    while (p != nullptr) {
        cout << "\n\t**********************************";
        cout << "\n\tThong tin cua benh nhan";
        cout << "\n\tHo            : " << p->ho;
        cout << "\n\tTen           : " << p->ten;
        cout << "\n\tGioi tinh     : " << p->gioiTinh;
        cout << "\n\tTuoi          : " << p->tuoi;
        cout << "\n\tNhom mau      : " << p->nhomMau;
        cout << "\n\tSo dien thoai : " << p->SDT;
        cout << "\n\t**********************************";
        p = p->tiep;
    }
}

// Thêm bệnh nhân vào đầu danh sách
void HangDoiKetNoi::ThemVaoDau() {
    BenhNhan p = NhapThongTin();
    if (p.SDT == 0) {
    	cout << "\n\tKhong co benh nhan de hien thi";
        return;
    }

    if (dau == nullptr) {
        dau = cuoi = new BenhNhan(p);
        cuoi->tiep = nullptr;
    } else {
        p.tiep = dau;
        dau = new BenhNhan(p);
    }

    cout << "\n\tDa them benh nhan";
}

// Thêm bệnh nhân vào cuối danh sách
void HangDoiKetNoi::ThemVaoCuoi() {
    BenhNhan p = NhapThongTin();
    if (p.SDT == 0) {
        return;
    }

    if (dau == nullptr) {
        dau = cuoi = new BenhNhan(p);
        cuoi->tiep = nullptr;
    } else {
        cuoi->tiep = new BenhNhan(p);
        cuoi = cuoi->tiep;
        cuoi->tiep = nullptr;
    }

    cout << "\n\tDa them benh nhan";
}

// Lấy bệnh nhân ra khỏi danh sách
void HangDoiKetNoi::DuaBenhNhanDenBacSi() {
    if (dau == nullptr) {
        cout << "\n\tKhong co benh nhan de dua den bac si";
    } else {
        BenhNhan* p = dau;
        dau = dau->tiep;
        cout << "\n\tDa dua benh nhan den bac si";
    }
}

// Sửa thông tin bệnh nhân theo SDT
void HangDoiKetNoi::SuaThongTinBenhNhan(long long sdtBenhNhan) {
    BenhNhan* p = dau;
    while (p != nullptr) {
        if (p->SDT == sdtBenhNhan) {
            system("cls");
            cout << "\n\tNhap thong tin moi cho benh nhan co so dien thoai " << sdtBenhNhan << ":\n\n";
            
            // Chỉ cho phép sửa họ, tên, nhóm máu, tuổi và giới tính
            cout << "\tHo: ";
            cin >> p->ho;
            cout << "\tTen: ";
            cin >> p->ten;
            cout << "\tNhom mau (A+, A-, B+, B-, O+, O-): ";
            cin >> p->nhomMau;
            p->nhomMau[0] = toupper(p->nhomMau[0]);
            p->nhomMau[1] = toupper(p->nhomMau[1]);
            
            // Nhập giới tính
            do {
                cout << "\tGioi tinh (1: Nam / 2: Nu): ";
                int luaChon;
                cin >> luaChon;
                if (luaChon == 1) {
                    p->gioiTinh = "Nam";
                    break;
                } else if (luaChon == 2) {
                    p->gioiTinh = "Nu";
                    break;
                } else {
                    cout << "\tLua chon khong hop le. Vui long nhap lai.\n";
                }
            } while (true);

            // Nhập tuổi
            do {
                cout << "\tTuoi: ";
                cin >> p->tuoi;
                if (p->tuoi <= 1) {
                    cout << "\tTuoi phai la mot so nguyen lon hon 1. Vui long nhap lai.\n";
                }
            } while (p->tuoi <= 1);

            cout << "\n\tDa sua thong tin benh nhan co so dien thoai " << sdtBenhNhan << endl;
            return;
        }
        p = p->tiep;
    }
    cout << "\n\tKhong tim thay benh nhan co so dien thoai " << sdtBenhNhan << endl;
}

// Xóa bệnh nhân theo SDT
void HangDoiKetNoi::XoaBenhNhan(long long sdtBenhNhan) {
    if (dau == nullptr) {
        cout << "\n\tKhong co benh nhan de xoa" << endl;
        return;
    }

    if (dau->SDT == sdtBenhNhan) {
        BenhNhan* p = dau;
        dau = dau->tiep;
        delete p;
        cout << "\n\tDa xoa benh nhan co so dien thoai " << sdtBenhNhan << endl;
        return;
    }

    BenhNhan* hienTai = dau;
    while (hienTai->tiep != nullptr) {
        if (hienTai->tiep->SDT == sdtBenhNhan) {
            BenhNhan* p = hienTai->tiep;
            hienTai->tiep = p->tiep;
            delete p;
            cout << "\n\tDa xoa benh nhan co so dien thoai " << sdtBenhNhan << endl;
            return;
        }
        hienTai = hienTai->tiep;
    }
    cout << "\n\tKhong tim thay benh nhan co so dien thoai " << sdtBenhNhan << endl;
}

// Hàm lưu danh sách bệnh nhân vào tệp tin .txt
void HangDoiKetNoi::LuuDanhSachBenhNhanVaoTepTin() {
    string tenTepTin = tenPhongKham + ".txt"; // Sử dụng tên phòng khám làm tên tệp tin
    ofstream file(tenTepTin);

    if (file.is_open()) {
        BenhNhan* p = dau;
        while (p != nullptr) {
            file << p->ho << " " << p->ten << " " << p->tuoi << " " << p->nhomMau << " " << p->gioiTinh << " " << p->SDT << "\n";
            p = p->tiep;
        }
        file.close();
        cout << "\n\tDanh sach benh nhan da duoc luu vao tep tin " << tenTepTin << endl;
    } else {
        cout << "\n\tKhong the mo tep tin de ghi." << endl;
    }
}

void menuPhongKham(HangDoiKetNoi* q) {
    int luaChon = 0;

    while (luaChon != 8) {
        system("cls");
        cout << "\n\n\tChao mung ban den voi: " << q->tenPhongKham;
        cout << "\n\t\t[1] Them benh nhan binh thuong";
        cout << "\n\t\t[2] Them benh nhan nguy kich";
        cout << "\n\t\t[3] Dua benh nhan den bac si";
        cout << "\n\t\t[4] Danh sach benh nhan";
        cout << "\n\t\t[5] Sua thong tin benh nhan";
        cout << "\n\t\t[6] Xoa benh nhan";
        cout << "\n\t\t[7] Luu danh sach benh nhan";
        cout << "\n\t\t[8] Quay lai";
        cout << "\n\tVui long nhap lua chon cua ban: ";
        cin >> luaChon;

        switch (luaChon) {
            case 1:
                q->ThemVaoCuoi();
                cout << "\n\tNhan phim bat ky de thoat";
                cin.ignore();
                cin.get();
                break;

            case 2:
                q->ThemVaoDau();
                cout << "\n\tNhan phim bat ky de thoat";
                cin.ignore();
                cin.get();
                break;

            case 3:
                q->DuaBenhNhanDenBacSi();
                cout << "\n\tNhan phim bat ky de thoat";
                cin.ignore();
                cin.get();
                break;

            case 4:
                system("cls");
                q->XuatThongTinBenhNhan();
                cout << "\n\tNhan phim bat ky de thoat";
                cin.ignore();
                cin.get();
                break;

            case 5:
                long long soDienThoaiBenhNhan;
                cout << "\n\tNhap so dien thoai cua benh nhan can sua: ";
                cin >> soDienThoaiBenhNhan;
                q->SuaThongTinBenhNhan(soDienThoaiBenhNhan);
                cout << "\n\tNhan phim bat ky de thoat";
                cin.ignore();
                cin.get();
                break;

            case 6:
                long long soDienThoaiCanXoa;
                cout << "\n\tNhap so dien thoai cua benh nhan can xoa: ";
                cin >> soDienThoaiCanXoa;
                q->XoaBenhNhan(soDienThoaiCanXoa);
                cout << "\n\tNhan phim bat ky de thoat";
                cin.ignore();
                cin.get();
                break;

            case 7:
                q->LuuDanhSachBenhNhanVaoTepTin();
                cout << "\n\tNhan phim bat ky de thoat";
                cin.ignore();
                cin.get();
                break;
        }
    }
}

// Hàm kiểm tra xem tên người dùng và mật khẩu cung cấp có đúng không
bool KiemTraDangNhap(const string& tenDangNhap, const string& matKhau) {
    string dong;
    ifstream accountsFile("account.txt");

    if (accountsFile.is_open()) {
        while (getline(accountsFile, dong)) {
            size_t viTriPhanTach = dong.find(':');
            if (viTriPhanTach != string::npos) {
                string tenDangNhapLuu = dong.substr(0, viTriPhanTach);
                string matKhauLuu = dong.substr(viTriPhanTach + 1);

                if (tenDangNhapLuu == tenDangNhap && matKhauLuu == matKhau) {
                    accountsFile.close();
                    return true;
                }
            }
        }
        accountsFile.close();
    }

    return false;
}

int main() {
    string tenDangNhap, matKhau;
    int soLanDangNhap = 3;
    bool daDangNhap = false;

    while (soLanDangNhap > 0) {
        cout << "\n\t>>>>>>>>>>>>>>>>>>>>>>>>>>";
        cout << "\n\tHE THONG QUAN LY BENH NHAN";
        cout << "\n\t<<<<<<<<<<<<<<<<<<<<<<<<<<\n";
        cout << "\n\tDang nhap de truy cap he thong\n";
        cout << "\n\tTen dang nhap: ";
        cin >> tenDangNhap;
        cout << "\tMat khau: ";
        cin >> matKhau;

        if (KiemTraDangNhap(tenDangNhap, matKhau)) {
            daDangNhap = true;
            break;
        } else {
            system("cls");
            cout << "\n\tDang nhap khong thanh cong. Vui long thu lai. So lan con lai: " << soLanDangNhap - 1 << "\n";
            soLanDangNhap--;
        }
    }

    if (!daDangNhap) {
        system("cls");
        cout << "\n\tBan da vuot qua so lan thu dang nhap toi da. Thoat...\n";
        return 1;
    }

    int luaChon = 0;
    HangDoiKetNoi phongKham[4];

    while (luaChon != 5) {
        phongKham[0].tenPhongKham = "Phong kham da khoa";
        phongKham[1].tenPhongKham = "Phong kham tim";
        phongKham[2].tenPhongKham = "Phong kham phoi";
        phongKham[3].tenPhongKham = "Phau thuat tham my";

        system("cls");
        cout << "\n\t>>>>>>>>>>>>>>>>>>>>>>>>>>";
        cout << "\n\tHE THONG QUAN LY BENH NHAN";
        cout << "\n\t<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";

        for (int i = 0; i < 4; i++) 
		{
            cout << "\t" << (i + 1) << ": " << phongKham[i].tenPhongKham << "\n";
        }

        cout << "\t5: Thoat\n";
        cout << "\tVui long nhap lua chon cua ban: ";
        cin >> luaChon;
        

        if (luaChon >= 1 && luaChon <= 4) {
            menuPhongKham(&phongKham[luaChon - 1]);
        }
       
    }

    if (luaChon == 5) {
        system("cls");
        cout << "\n\tCHuong trinh duoc thuc hien boi nhom SV";
        cout << "\n\tVu Tuan Nam: 1851070250";
        cout << "\n\tHa Văn Loi: 1851070358";
    }
    return 0;
}