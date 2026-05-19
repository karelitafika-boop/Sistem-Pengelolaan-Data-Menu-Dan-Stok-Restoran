#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
using namespace std;

struct Menu {
    int kode;
    string nama;
    int harga;
    int stok;
    Menu *next;
};

Menu *head = NULL;

void bersihLayar() {
    system("cls");
}

void garisAtas() {
    cout << "+==============================================================+\n";
}

void garisBiasa() {
    cout << "+--------------------------------------------------------------+\n";
}

void header(string judul) {
    int lebar = 62;
    int panjang = (int)judul.length();
    int kiri = (lebar - panjang) / 2;
    int kanan = lebar - panjang - kiri;

    garisAtas();
    cout << "|";
    for (int i = 0; i < kiri; i++) cout << " ";
    cout << judul;
    for (int i = 0; i < kanan; i++) cout << " ";
    cout << "|\n";
    garisAtas();
}

void pesanBerhasil(string teks) {
    cout << "\n[ BERHASIL ] " << teks << endl;
}

void pesanGagal(string teks) {
    cout << "\n[ woopps gagall ] -> " << teks << endl;
}

void pesanInfo(string teks) {
    cout << "\n[ INFO     ] " << teks << endl;
}

void pause() {
    cout << "\n tekan [ enter ] untuk kembali yaa...";
    cin.ignore();
    cin.get();
}

bool login() {
    string username, password;
    int kesempatan = 3;

    while (kesempatan > 0) {
        bersihLayar();
        header("LOGIN ADMIN RESTORAN");

        cout << "[ haii username kamu apaa?     ] : ";
        cin >> username;
        cout << "[ kalau passwordnya apa hayo?  ] : ";
        cin >> password;

        garisBiasa();

        if (username == "admin" && password == "12345") {
            pesanBerhasil("yeyyy login berhasil.");
            pause();
            return true;
        } else {
            kesempatan--;
            pesanGagal("username atau password salah.");
            cout << "[ Sisa Kesempatan ] : " << kesempatan << endl;

            if (kesempatan > 0) {
                pause();
            }
        }
    }

    return false;
}

void tampilMenuUtama() {
    header("SISTEM PENGELOLAAN MENU RESTORAN");

    cout << "| [1] Tambah Menu                                             |\n";
    cout << "| [2] Tampilkan Menu                                          |\n";
    cout << "| [3] Keluar                                                  |\n";

    garisAtas();
}

int main() {

    int pilihan;

    if (!login()) {
        return 0;
    }

    do {
        bersihLayar();

        tampilMenuUtama();

        cout << "[ Pilih Menu ] : ";
        cin >> pilihan;

        switch (pilihan) {

        case 1:
            pesanInfo("fitur belum tersedia.");
            pause();
            break;

        case 2:
            pesanInfo("fitur belum tersedia.");
            pause();
            break;

        case 3:
            bersihLayar();
            cout << "Program selesai.\n";
            break;

        default:
            pesanGagal("pilihan tidak tersedia.");
            pause();
        }

    } while (pilihan != 3);

    return 0;
}
