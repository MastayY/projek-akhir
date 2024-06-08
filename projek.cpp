#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

// ---------------| Global Variable |--------------- //
string sort = "ID";

// ---------------| Struct |--------------- //
struct Barang {
    int id;
    string namaBarang;
    string kodeBarang;
    int harga;
    int stok;
    Barang *next;
};

// ---------------| Function |--------------- //
string splitString(const string &str, size_t width) {
    if (str.length() <= width) return str;
    return str.substr(0, width - 6) + "...";
}

void printBarang(Barang *barang) {
    cout << left << " " << setw(5) << "ID" 
        << setw(25) << "Nama Barang" 
        << setw(15) << "Kode Barang" 
        << setw(15) << "Harga" 
        << setw(5) << "Stok" 
        << endl;
    cout << "+----------------------------------------------------------------+" << endl;
    while(barang != NULL) {
        cout << left << " " << setw(5) << barang->id
            << setw(25) << splitString(barang->namaBarang, 25)
            << setw(15) << barang->kodeBarang
            << setw(15) << barang->harga
            << setw(5) << barang->stok
            << endl;
        barang = barang->next;
    }
    cout << "+----------------------------------------------------------------+" << endl;
    cout << "\nTekan Enter untuk kembali ke menu..." << endl;
    cin.ignore();
    cin.get();
}

void displayMenu() {
    cout << "|---------[ MENU ]---------|" << endl;
    cout << "  1. Tambah Barang" << endl;
    cout << "  2. Hapus Barang" << endl;
    cout << "  3. Edit Barang" << endl;
    cout << "  4. Lihat Barang" << endl;
    cout << "  5. Keluar" << endl;
    cout << "|--------------------------|" << endl;
}

void tambahBarang(Barang *&head, int &currentId) {
    Barang *newBarang = new Barang();
    
    newBarang->id = currentId++;
    cout << "|-------------[ Tambah Barang ]-------------|" << endl;
    cout << "|- Nama Barang\t: ";
    cin.ignore();
    getline(cin, newBarang->namaBarang);
    cout << "|- Kode Barang\t: ";
    cin >> newBarang->kodeBarang;
    cout << "|- Harga Barang\t: ";
    cin >> newBarang->harga;
    cout << "|- Stok Barang\t: ";
    cin >> newBarang->stok;
    cout << "|-------------------------------------------|" << endl;
    newBarang->next = NULL;

    if (head == NULL) {
        head = newBarang;
    } else {
        Barang *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newBarang;
    }

    cout << "\nBarang berhasil ditambahkan. Tekan enter untuk kembali" << endl;
    cin.ignore();
    cin.get();
}

void urutkanBarang(Barang *&head, int pilihan) {
    if (head == NULL) return;

    bool swapped;
    Barang *ptr1;
    Barang *lptr = NULL;

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            bool condition = false;
            switch (pilihan) {
                case 1:
                    condition = ptr1->id > ptr1->next->id;
                    sort = "ID";
                    break;
                case 2:
                    condition = ptr1->kodeBarang > ptr1->next->kodeBarang;
                    sort = "Kode Barang";
                    break;
                case 3:
                    condition = ptr1->stok > ptr1->next->stok;
                    sort = "Stok";
                    break;
                case 4:
                    condition = ptr1->namaBarang > ptr1->next->namaBarang;
                    sort = "Nama Barang";
                    break;
            }
            if (condition) {
                swap(ptr1->id, ptr1->next->id);
                swap(ptr1->namaBarang, ptr1->next->namaBarang);
                swap(ptr1->kodeBarang, ptr1->next->kodeBarang);
                swap(ptr1->harga, ptr1->next->harga);
                swap(ptr1->stok, ptr1->next->stok);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void lihatBarang(Barang *&head) {
    if (head == NULL) {
        cout << "Tidak ada barang yang tersedia." << endl << endl;
        cout << "\nTekan Enter untuk kembali ke menu..." << endl;
        cin.ignore();
        cin.get();
        return;
    }

    int pilihanUrut;
    cout << "|--------[ URUTKAN BERDASARKAN ]--------|" << endl;
    cout << "  1. ID" << endl;
    cout << "  2. Kode Barang" << endl;
    cout << "  3. Stok" << endl;
    cout << "  4. Nama Barang" << endl;
    cout << "|--------------------------------------|" << endl;
    cout << " Pilihan: ";
    cin >> pilihanUrut;

    system("cls");
    cout << "\t\t\t   DAFTAR BARANG" << endl;
    cout << "\t\t\t  ---------------" << endl << endl;
    urutkanBarang(head, pilihanUrut);
    printBarang(head);
}

// ---------------| Main Program |--------------- //
int main() {
    Barang *head = NULL;
    int currentId = 1;
    int userChoice;
    bool exit = false;

    do {
        system("cls");

        displayMenu();
        cout << "\nMasukkan pilihan: ";
        cin >> userChoice;

        system("cls");

        switch(userChoice) {
            case 1:
                tambahBarang(head, currentId);
                break;
            case 2:
                cout << "Hapus Barang" << endl;
                break;
            case 3:
                cout << "Edit Barang" << endl;
                break;
            case 4:
                lihatBarang(head);
                break;
            case 5:
                exit = true;
                break;
            default:
                cout << "Pilihan tidak valid" << endl;
                break;
        }

    } while (!exit);
    
    return 0;
}