#include <iostream>
#include <fstream>
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

struct Riwayat {
    string keterangan;
    Riwayat *prev;
    Riwayat *next;
};

Menu *head = NULL;
Riwayat *awal = NULL;
Riwayat *akhir = NULL;

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

string ubahKecil(string teks) {
    for (size_t i = 0; i < teks.length(); i++) {
        if (teks[i] >= 'A' && teks[i] <= 'Z') {
            teks[i] = teks[i] + 32;
        }
    }
    return teks;
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
            pesanBerhasil("yeyyy login berhasil, selamat datang admin cantik.");
            pause();
            return true;
        } else {
            kesempatan--;
            pesanGagal("maaff, username atau password salah! coba lagi ya.");
            cout << "[ Sisa Kesempatan ] : " << kesempatan << endl;

            if (kesempatan > 0) {
                pause();
            }
        }
    }

    pesanGagal("yahh kesempatan login habis:( coba lain waktu ya!.");
    return false;
}

void simpanFile() {
    ofstream file("data_menu.txt");

    Menu *bantu = head;

    while (bantu != NULL) {
        file << bantu->kode << "|"
             << bantu->nama << "|"
             << bantu->harga << "|"
             << bantu->stok << endl;

        bantu = bantu->next;
    }

    file.close();
}

void loadFile() {
    ifstream file("data_menu.txt");

    if (!file.is_open()) {
        return;
    }

    while (!file.eof()) {
        Menu *baru = new Menu;
        string kode, harga, stok;

        getline(file, kode, '|');
        getline(file, baru->nama, '|');
        getline(file, harga, '|');
        getline(file, stok);

        if (kode == "" || baru->nama == "") {
            delete baru;
            break;
        }

        baru->kode = stoi(kode);
        baru->harga = stoi(harga);
        baru->stok = stoi(stok);
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
    }

    file.close();
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
        if (ubahKecil(bantu->nama) == ubahKecil(nama)) {
            return true;
        }

        bantu = bantu->next;
    }

    return false;
}

void tambahRiwayat(string teks) {
    Riwayat *baru = new Riwayat;

    baru->keterangan = teks;
    baru->prev = NULL;
    baru->next = NULL;

    if (awal == NULL) {
        awal = akhir = baru;
    } else {
        akhir->next = baru;
        baru->prev = akhir;
        akhir = baru;
    }
}

void tambahMenu() {
    bersihLayar();

    Menu *baru = new Menu;

    header("TAMBAH DATA MENU");

    cout << "[ Kode Menu ] : ";
    cin >> baru->kode;

    if (cekKode(baru->kode)) {
        pesanGagal("etss kode menu sudah digunakan.");
        delete baru;
        return;
    }

    cin.ignore();

    cout << "[ Nama Menu ] : ";
    getline(cin, baru->nama);

    if (cekNama(baru->nama)) {
        pesanGagal("Nama menu sudah ada.");
        delete baru;
        return;
    }

    cout << "[ Harga     ] : Rp ";
    cin >> baru->harga;

    cout << "[ Stok      ] : ";
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

    simpanFile();
    garisBiasa();
    pesanBerhasil("okeyyy! data menu berhasil ditambahkan.");
}

void tampilMenu() {
    bersihLayar();

    if (head == NULL) {
        pesanInfo("Data menu masih kosong.");
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

void sortingASC() {
    if (head == NULL) {
        return;
    }

    bool tukar;
    Menu *i;
    Menu *batas = NULL;

    do {
        tukar = false;
        i = head;

        while (i->next != batas) {
            if (ubahKecil(i->nama) > ubahKecil(i->next->nama)) {
                swap(i->kode, i->next->kode);
                swap(i->nama, i->next->nama);
                swap(i->harga, i->next->harga);
                swap(i->stok, i->next->stok);

                tukar = true;
            }

            i = i->next;
        }

        batas = i;

    } while (tukar);

    simpanFile();
}

void menuSorting() {
    bersihLayar();

    if (head == NULL) {
        pesanInfo("wehh data menu masih kosong, isi dulu yaa!");
        return;
    }

    sortingASC();
    pesanBerhasil("okeyy, data berhasil diurutkan dari A-Z.");

    tampilMenu();
}

void binarySearch() {
    bersihLayar();

    if (head == NULL) {
        pesanInfo("Data menu masih kosong.");
        return;
    }

    sortingASC();

    int jumlah = 0;
    Menu *bantu = head;

    while (bantu != NULL) {
        jumlah++;
        bantu = bantu->next;
    }

    Menu data[100];

    bantu = head;
    int i = 0;

    while (bantu != NULL) {
        data[i].kode = bantu->kode;
        data[i].nama = bantu->nama;
        data[i].harga = bantu->harga;
        data[i].stok = bantu->stok;
        data[i].next = NULL;

        i++;
        bantu = bantu->next;
    }

    string cari;
    cin.ignore();

    header("CARI MENU");

    cout << "[ Cari Menu ] : ";
    getline(cin, cari);

    string cariKecil = ubahKecil(cari);

    int kiri = 0;
    int kanan = jumlah - 1;
    int tengah;
    bool ketemu = false;

    while (kiri <= kanan) {
        tengah = (kiri + kanan) / 2;

        string namaTengah = ubahKecil(data[tengah].nama);

        if (namaTengah == cariKecil) {
            pesanBerhasil("yashhhyashh menu ditemukan!.");
            garisBiasa();

            cout << "[ Kode  ] : " << data[tengah].kode << endl;
            cout << "[ Nama  ] : " << data[tengah].nama << endl;
            cout << "[ Harga ] : Rp " << data[tengah].harga << endl;
            cout << "[ Stok  ] : " << data[tengah].stok << endl;

            garisBiasa();
            ketemu = true;
            break;
        } else if (namaTengah < cariKecil) {
            kiri = tengah + 1;
        } else {
            kanan = tengah - 1;
        }
    }

    if (!ketemu) {
        pesanGagal("aduhh menu tidak ditemukan.");
    }
}

void updateStok() {
    bersihLayar();

    if (head == NULL) {
        pesanInfo("Data menu masih kosong.");
        return;
    }

    string namaCari;
    int stokBaru;

    cin.ignore();

    header("UPDATE STOK MENU");

    cout << "[ Nama Menu ] : ";
    getline(cin, namaCari);

    Menu *bantu = head;

    while (bantu != NULL) {
        if (ubahKecil(bantu->nama) == ubahKecil(namaCari)) {
            garisBiasa();

            cout << "[ Kode Menu ] : " << bantu->kode << endl;
            cout << "[ Nama Menu ] : " << bantu->nama << endl;
            cout << "[ Stok Lama ] : " << bantu->stok << endl;
            cout << "[ Stok Baru ] : ";
            cin >> stokBaru;

            string catatan = "Stok " + bantu->nama + " diubah dari " +
                             to_string(bantu->stok) + " menjadi " +
                             to_string(stokBaru);

            bantu->stok = stokBaru;

            tambahRiwayat(catatan);
            simpanFile();

            garisBiasa();
            pesanBerhasil("stok menu berhasil diupdate yaa!.");
            return;
        }

        bantu = bantu->next;
    }

    pesanGagal("Nama menu tidak ditemukan.");
}

void hapusMenu() {
    bersihLayar();

    if (head == NULL) {
        pesanInfo("Data menu masih kosong.");
        return;
    }

    string namaCari;

    cin.ignore();

    header("HAPUS DATA MENU");

    cout << "[ Nama Menu ] : ";
    getline(cin, namaCari);

    Menu *hapus = head;
    Menu *sebelum = NULL;

    while (hapus != NULL && ubahKecil(hapus->nama) != ubahKecil(namaCari)) {
        sebelum = hapus;
        hapus = hapus->next;
    }

    if (hapus == NULL) {
        pesanGagal("yahh nama menu tidak ditemukan.");
        return;
    }

    if (sebelum == NULL) {
        head = head->next;
    } else {
        sebelum->next = hapus->next;
    }

    delete hapus;
    simpanFile();

    pesanBerhasil("menu berhasil dihapus yaaa.");
}

void tampilRiwayat() {
    bersihLayar();

    if (awal == NULL) {
        pesanInfo("riwayat stok masih kosong, update stok dulu yaa!");
        return;
    }

    header("RIWAYAT PERUBAHAN STOK");

    Riwayat *bantu = awal;
    int no = 1;

    while (bantu != NULL) {
        cout << "[ " << setw(2) << no++ << " ] "
             << bantu->keterangan << endl;

        bantu = bantu->next;
    }

    garisBiasa();
}

void tampilMenuUtama() {
    header("SISTEM PENGELOLAAN MENU RESTORAN");

    cout << "| [1] Tambah Menu                                             |\n";
    cout << "| [2] Tampilkan Menu                                          |\n";
    cout << "| [3] Urutkan Menu A-Z                                        |\n";
    cout << "| [4] Cari Menu                                               |\n";
    cout << "| [5] Update Stok                                             |\n";
    cout << "| [6] Hapus Menu                                              |\n";
    cout << "| [7] Riwayat Stok                                            |\n";
    cout << "| [8] Keluar                                                  |\n";

    garisAtas();
}

int main() {
	
    int pilihan;

    if (!login()) {
        return 0;
    }

    loadFile();

    do {
        bersihLayar();

        tampilMenuUtama();

        cout << "[ Pilih Menu (1-8)] : ";
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
            menuSorting();
            pause();
            break;

        case 4:
            binarySearch();
            pause();
            break;

        case 5:
            updateStok();
            pause();
            break;

        case 6:
            hapusMenu();
            pause();
            break;

        case 7:
            tampilRiwayat();
            pause();
            break;

        case 8:
            bersihLayar();
            header("PROGRAM SELESAI");
            cout << "TERIMAKASIHHH YAAAA, program ditutup! -by carelita and arsya.\n";
            garisBiasa();
            break;

        default:
            pesanGagal("yahhh pilihan tidak tersedia.");
            pause();
        }

    } while (pilihan != 8);

    return 0;
}
