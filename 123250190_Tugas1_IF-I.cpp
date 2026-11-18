#include <iostream>
using namespace std;

struct Car {
    char plat[20];
    char nama[50];
    int jenis;
    int durasi;
};

struct Node {
    Car mobil;
    Node* next;
};

struct Employee {
    char nama[30];
};

//Pegawai
Employee pegawai[3] = {
    {"Radja"},
    {"IlhamGod"},
    {"Windah"}
};

int giliranPegawai = 0;

//Bagian Jenis Mobil
void tampilJenis(int jenis) {
    if (jenis == 1) {
        cout << "Sedan";
    }
    else if (jenis == 2) {
        cout << "SUV";
    }
    else if (jenis == 3) {
        cout << "MPV";
    }
}

//Tentu durasi
int tentukanDurasi(int jenis) {
    if (jenis == 1) {
        return 15;
    }
    else if (jenis == 2) {
        return 20;
    }
    else if (jenis == 3) {
        return 25;
    }

    return 0;
}

// Bagian Add
void tambahMobil(Node*& head, Car mobil) {
    Node* baru = new Node;
    baru->mobil = mobil;
    baru->next = nullptr;

    if (head == nullptr) {
        head = baru;
        return;
    }
    Node* terakhir = head;

    while (terakhir->next != nullptr) {
        terakhir = terakhir->next;
    }
    terakhir->next = baru;
}

// Bagian Serve

void serveCar(Node*& head, Car& previousCar, bool& adaPrevious) {
    if (head == nullptr) {
        cout << "\nAntrian kosong. Tidak ada mobil yang dapat dilayani.\n";
        return;
    }
    Node* dilayani = head;

    previousCar = dilayani->mobil;
    adaPrevious = true;
    cout << "\n========================================\n";
    cout << "           SERVE CAR\n";
    cout << "========================================\n";
    cout << "Mobil " << dilayani->mobil.plat << " sedang dicuci oleh : " << pegawai[giliranPegawai].nama << endl;

    head = dilayani->next;

    delete dilayani;

    giliranPegawai++;
    if (giliranPegawai == 3) {
        giliranPegawai = 0;
    }
    cout << "\nMobil berhasil dilayani.\n";

    if (head == nullptr) {
        cout << "Antrian sudah selesai.\n";
    }
    else {
        cout << "Mobil berikutnya adalah "
             << head->mobil.plat << ".\n";
    }
}

// Bagian Check
void checkQueue(Node* head, Car previousCar, bool adaPrevious) {
    cout << "\n";
    cout << "=========== CHECK QUEUE ===========\n";
    cout << "|   prev   |  current  |   next   |\n";
    cout << "====================================\n";

    if (head != nullptr) {
        cout << "| ";
        if (!adaPrevious) {
            cout << "tidak ada";
        }
        else {
            cout << previousCar.plat;
        }
        cout << " | ";
        cout << head->mobil.plat;

        cout << " | ";

        if (head->next == nullptr) {
            cout << "tidak ada";
        }
        else {
            cout << head->next->mobil.plat;
        }
        cout << " |\n";
        cout << "====================================\n";
    }
    else {
        if (adaPrevious) {
            cout << "\n";
            cout << "semua antrean sudah selesai\n";
            cout << "====================================\n";
        }
        else {
            cout << "| tidak ada | tidak ada | tidak ada |\n";
            cout << "====================================\n";
        }
    }
}

//Bagian tampilin antrian
void tampilkanAntrian(Node* head) {
    if (head == nullptr) {
        cout << "\nAntrian kosong.\n";
        return;
    }

    cout << "\n========================================\n";
    cout << "             DAFTAR ANTRIAN\n";
    cout << "========================================\n";

    Node* p = head;
    int nomor = 1;

    while (p != nullptr) {
        cout << nomor << ". ";
        cout << p->mobil.plat << " | ";
        cout << p->mobil.nama << " | ";

        tampilJenis(p->mobil.jenis);

        cout << " | ";
        cout << p->mobil.durasi << " menit\n";

        p = p->next;
        nomor++;
    }
}

// Bagian Hapus 
void clear(Node*& head) {
    while (head != nullptr) {
        Node* hapus = head->next;
        delete head;
        head = hapus;
    }
}

//Main
int main() {
    Node* head = nullptr;
    Car previousCar;
    bool adaPrevious = false;

    int pilihan;

    do {
        cout << "\n========================================\n";
        cout << "        WASH UP! CAR WASH\n";
        cout << "========================================\n";
        cout << "1. Add Car\n";
        cout << "2. Serve Car\n";
        cout << "3. Check Queue\n";
        cout << "4. Exit\n";
        cout << "========================================\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        if (pilihan == 1) {
            Car mobil;

            cout << "\n========================================\n";
            cout << "              ADD CAR\n";
            cout << "========================================\n";

            cout << "Plat nomor   : ";
            cin >> mobil.plat;

            cout << "Nama pemilik : ";
            cin >> mobil.nama;

            do {
                cout << "\nJenis mobil:\n";
                cout << "1. Sedan (15 menit)\n";
                cout << "2. SUV   (20 menit)\n";
                cout << "3. MPV   (25 menit)\n";
                cout << "Pilih jenis: ";
                cin >> mobil.jenis;

                if (mobil.jenis < 1 || mobil.jenis > 3) {
                    cout << "Jenis mobil tidak valid.\n";
                }

            } while (mobil.jenis < 1 || mobil.jenis > 3);

            mobil.durasi = tentukanDurasi(mobil.jenis);

            tambahMobil(head, mobil);
            cout << "\nMobil berhasil ditambahkan ke antrian.\n";
            cout << "Plat       : " << mobil.plat << endl;
            cout << "Pemilik    : " << mobil.nama << endl;
            cout << "Jenis      : ";
            tampilJenis(mobil.jenis);
            cout << endl;
            cout << "Durasi     : " << mobil.durasi << " menit\n";

        } else if (pilihan == 2) {
            serveCar(head, previousCar, adaPrevious);
        } else if (pilihan == 3) {
            checkQueue(head, previousCar, adaPrevious);
        } else if (pilihan == 4) {
            cout << "\n========================================\n";
            cout << "Terima kasih telah menggunakan\n";
            cout << "sistem antrian Wash Up!\n";
            cout << "========================================\n";
        } else {

            cout << "\nPilihan menu tidak valid.\n";
            cout << "Silakan pilih menu 1 - 4.\n";
        }

    } while (pilihan != 4);

    clear(head);
    
    return 0;
}