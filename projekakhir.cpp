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

    for (int i = 0; i < kiri; i++)
        cout << " ";

    cout << judul;

    for (int i = 0; i < kanan; i++)
        cout << " ";

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

            cout << "[ Sisa Kesempatan ] : "
                 << kesempatan << endl;

            if (kesempatan > 0) {
                pause();
            }
        }
    }

    return false;
}

string ubahKecil(string nama) {

    for (size_t i = 0; i < nama.length(); i++) {

        if (nama[i] >= 'A' && nama[i] <= 'Z') {
            nama[i] = nama[i] + 32;
        }
    }

    return nama;
}

bool cekKode(int kode) {

    Menu *bantu = head;

    while (bantu != NULL) {

        if (bantu->kode == kode) {
            return true;
        }

        bantu = bantu->next;
    }

    return false;
}

bool cekNama(string nama) {

    Menu *bantu = head;

    while (bantu != NULL) {

        if (ubahKecil(bantu->nama)
            == ubahKecil(nama)) {

            return true;
        }

        bantu = bantu->next;
    }

    return false;
}

void tambahMenu() {

    bersihLayar();

    Menu *baru = new Menu;

    header("TAMBAH DATA MENU");

    cout << "[ Kode Menu ] : ";
    cin >> baru->kode;

    if (cekKode(baru->kode)) {

        pesanGagal("kode menu sudah digunakan.");

        delete baru;

        return;
    }

    cin.ignore();

    cout << "[ Nama Menu ] : ";
    getline(cin, baru->nama);

    if (cekNama(baru->nama)) {

        pesanGagal("nama menu sudah ada.");

        delete baru;

        return;
    }

    cout << "[ Harga ] : Rp ";
    cin >> baru->harga;

    cout << "[ Stok ] : ";
    cin >> baru->stok;

    baru->next = NULL;

    if (head == NULL) {

        head = baru;

    } else {

        Menu *bantu = head;

        while (bantu->next != NULL) {
            bantu = bantu->next;
        }

        bantu->next = baru;
    }

    pesanBerhasil("data menu berhasil ditambahkan.");
}

void tampilMenu() {

    bersihLayar();

    if (head == NULL) {

        pesanInfo("data menu masih kosong.");

        return;
    }

    header("DATA MENU RESTORAN");

    cout << "| " << left
         << setw(8) << "KODE"
         << setw(25) << "NAMA MENU"
         << setw(18) << "HARGA"
         << setw(8) << "STOK"
         << " |\n";

    garisBiasa();

    Menu *bantu = head;

    while (bantu != NULL) {

        cout << "| " << left
             << setw(8) << bantu->kode
             << setw(25) << bantu->nama
             << "Rp " << setw(15) << bantu->harga
             << setw(8) << bantu->stok
             << " |\n";

        bantu = bantu->next;
    }

    garisBiasa();
}

void hapusMenu() {

    bersihLayar();

    if (head == NULL) {

        pesanInfo("data menu masih kosong.");

        return;
    }

    string namaCari;

    cin.ignore();

    header("HAPUS DATA MENU");

    cout << "[ Nama Menu ] : ";
    getline(cin, namaCari);

    Menu *hapus = head;
    Menu *sebelum = NULL;

    while (hapus != NULL &&
           ubahKecil(hapus->nama)
           != ubahKecil(namaCari)) {

        sebelum = hapus;
        hapus = hapus->next;
    }

    if (hapus == NULL) {

        pesanGagal("nama menu tidak ditemukan.");

        return;
    }

    if (sebelum == NULL) {

        head = head->next;

    } else {

        sebelum->next = hapus->next;
    }

    delete hapus;

    pesanBerhasil("menu berhasil dihapus.");
}

void tampilMenuUtama() {

    header("SISTEM PENGELOLAAN MENU RESTORAN");

    cout << "| [1] Tambah Menu                                             |\n";
    cout << "| [2] Tampilkan Menu                                          |\n";
    cout << "| [3] Hapus Menu                                              |\n";
    cout << "| [4] Keluar                                                  |\n";

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
            tambahMenu();
            pause();
            break;

        case 2:
            tampilMenu();
            pause();
            break;

        case 3:
            hapusMenu();
            pause();
            break;

        case 4:
            bersihLayar();
            cout << "Program selesai.\n";
            break;

        default:
            pesanGagal("pilihan tidak tersedia.");
            pause();
        }

    } while (pilihan != 4);

    return 0;
}
