#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

// ---------------| Global Variable |--------------- //
string sortBy = "ID";
bool firstLoad = true;

// ---------------| Struct |--------------- //
struct Barang
{
    int id;
    string namaBarang;
    string kodeBarang;
    int harga;
    int stok;
    Barang *next;
};

// ---------------| Function |--------------- //
string splitString(const string &str, size_t width)
{
    if (str.length() <= width)
        return str;
    return str.substr(0, width - 6) + "...";
}

string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

void printBarang(Barang *barang)
{
    cout << left << " " << setw(5) << "ID"
            << setw(25) << "Nama Barang"
            << setw(15) << "Kode Barang"
            << setw(15) << "Harga"
            << setw(5) << "Stok"
            << endl;
    cout << "+----------------------------------------------------------------+" << endl;
    while (barang != NULL)
    {
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

void displayMenu()
{
    if (firstLoad)
    {
        cout << "+----------------------------------------------+" << endl;
        cout << "|               SISTEM INVENTARIS              |" << endl;
        cout << "|                     BARANG                   |" << endl;
        cout << "+----------------------------------------------+" << endl;
        cout << "|  Dibuat oleh: Kelompok 3                     |" << endl;
        cout << "|                                              |" << endl;
        cout << "|  Anggota:                                    |" << endl;
        cout << "|  1. Aurelia Nur Fitria                       |" << endl;
        cout << "|  2. Daniel Dwi Putra Gunawan                 |" << endl;
        cout << "|  3. Muhammad Hilmi Rasyid                    |" << endl;
        cout << "|  4. Muhammad Naufal Yazid Akbar              |" << endl;
        cout << "|  5. Nasywan Damar Fadhila                    |" << endl;
        cout << "+----------------------------------------------+" << endl;

        cout << "\n* Tekan Enter untuk masuk ke sistem..." << endl;
        cin.get();
        system("cls");
        firstLoad = false;
    }

    cout << "|---------[ MENU ]---------|" << endl;
    cout << "  1. Tambah Barang          " << endl;
    cout << "  2. Hapus Barang           " << endl;
    cout << "  3. Edit Barang            " << endl;
    cout << "  4. Lihat Barang           " << endl;
    cout << "  5. Search Barang          " << endl;
    cout << "  6. Undo                   " << endl;
    cout << "  7. Keluar                 " << endl;
    cout << "|--------------------------|" << endl;
}

void saveState(stack<Barang *> &stack, Barang *head)
{
    Barang *current = head;
    Barang *newHead = NULL;
    Barang *newCurrent = NULL;

    while (current != NULL)
    {
        Barang *newBarang = new Barang();
        newBarang->id = current->id;
        newBarang->namaBarang = current->namaBarang;
        newBarang->kodeBarang = current->kodeBarang;
        newBarang->harga = current->harga;
        newBarang->stok = current->stok;
        newBarang->next = NULL;

        if (newHead == NULL)
        {
            newHead = newBarang;
            newCurrent = newHead;
        }
        else
        {
            newCurrent->next = newBarang;
            newCurrent = newBarang;
        }
        current = current->next;
    }

    stack.push(newHead);
}

void restoreState(stack<Barang *> &stack, Barang *&head, const string &action)
{
    if (!stack.empty())
    {
        Barang *oldHead = head;
        head = stack.top();
        stack.pop();

        while (oldHead != NULL)
        {
            Barang *temp = oldHead;
            oldHead = oldHead->next;
            delete temp;
        }

        cout << "Barang berhasil di " << action << endl;
        cout << "\nTekan Enter untuk kembali ke menu..." << endl;
        cin.ignore();
        cin.get();
    }
    else
    {
        cout << "Tidak ada aksi " << action << " yang dapat dilakukan." << endl;
        cout << "Tekan Enter untuk kembali ke menu..." << endl;
        cin.ignore();
        cin.get();
    }
}


void tambahBarang(Barang *&head, int &currentId, stack<Barang *> &undoStack)
{
    saveState(undoStack, head);

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

    if (head == NULL)
    {
        head = newBarang;
    }
    else
    {
        Barang *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newBarang;
    }

    cout << "\nBarang berhasil ditambahkan. Tekan enter untuk kembali" << endl;
    cin.ignore();
    cin.get();
}

void hapusBarang(Barang *&head, stack<Barang *> &undoStack)
{
    saveState(undoStack, head);

    if (head == NULL)
    {
        cout << "Tidak ada barang yang tersedia untuk dihapus." << endl;
        cout << "\nTekan Enter untuk kembali ke menu..." << endl;
        cin.ignore();
        cin.get();
        return;
    }

    int id;
    cout << "|-------------[ Hapus Barang ]-------------|" << endl;
    cout << "|- Masukkan ID Barang\t: ";
    cin >> id;
    cout << "|------------------------------------------|" << endl;

    Barang *current = head;
    Barang *prev = NULL;

    while (current != NULL && current->id != id)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        cout << "\n* Barang dengan ID " << id << " tidak ditemukan." << endl;
    }
    else
    {
        if (prev == NULL)
        {
            head = current->next;
        }
        else
        {
            prev->next = current->next;
        }
        delete current;
        cout << "\n* Barang berhasil dihapus." << endl;
    }

    cout << "\nTekan Enter untuk kembali ke menu..." << endl;
    cin.ignore();
    cin.get();
}

void editBarang(Barang *&head, stack<Barang *> &undoStack)
{
    saveState(undoStack, head);
    if (head == NULL)

    {
        cout << "Tidak ada barang yang tersedia untuk diedit." << endl;
        cout << "\nTekan Enter untuk kembali ke menu..." << endl;
        cin.ignore();
        cin.get();
        return;
    }

    int id;
    cout << "|-------------[ Edit Barang ]-------------|" << endl;
    cout << "|- Masukkan ID Barang\t: ";
    cin >> id;
    cout << "|-----------------------------------------|" << endl;

    Barang *current = head;

    while (current != NULL && current->id != id)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        cout << "Barang dengan ID " << id << " tidak ditemukan." << endl;
    }
    else
    {
        cout << "|- Nama (" << current->namaBarang << ")\n|-> ";
        cin.ignore();
        getline(cin, current->namaBarang);
        cout << "|\n|- Kode (" << current->kodeBarang << ")\n|-> ";
        cin >> current->kodeBarang;
        cout << "|\n|- Harga (" << current->harga << ")\n|-> ";
        cin >> current->harga;
        cout << "|\n|- Stok (" << current->stok << ")\n|-> ";
        cin >> current->stok;
        cout << "|-----------------------------------------|" << endl;
        cout << "\n* Barang berhasil diedit." << endl;
    }

    cout << "\nTekan Enter untuk kembali ke menu..." << endl;
    cin.ignore();
    cin.get();
}

void urutkanBarang(Barang *&head, int pilihan)
{
    if (head == NULL)
        return;

    bool swapped;
    Barang *ptr1;
    Barang *lptr = NULL;

    do
    {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            bool condition = false;
            switch (pilihan)
            {
            case 1:
                condition = ptr1->id > ptr1->next->id;
                break;
            case 2:
                condition = ptr1->kodeBarang > ptr1->next->kodeBarang;
                break;
            case 3:
                condition = ptr1->stok > ptr1->next->stok;
                break;
            case 4:
                condition = ptr1->namaBarang > ptr1->next->namaBarang;
                break;
            }
            if (condition)
            {
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

void lihatBarang(Barang *&head)
{
    if (head == NULL)
    {
        cout << "Tidak ada barang yang tersedia." << endl;
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

    switch(pilihanUrut) {
        case 1:
            sortBy = "ID";
            break;
        case 2:
            sortBy = "Kode Barang";
            break;
        case 3:
            sortBy = "Stok";
            break;
        case 4:
            sortBy = "Nama Barang";
            break;
        default:
            cout << "Pilihan tidak valid" << endl;
            cin.ignore();
            cin.get();
    }

    system("cls");
    cout << "\t\t\t   DAFTAR BARANG" << endl;
    cout << "\t\t\t  ---------------" << endl
        << endl;
    cout << "* Diurutkan berdasarkan: " << sortBy << endl
        << endl;
    urutkanBarang(head, pilihanUrut);
    printBarang(head);
}

void searchBarang(Barang *&head)
{
    if (head == NULL)
    {
        cout << "Tidak ada barang yang tersedia." << endl;
        cout << "\nTekan Enter untuk kembali ke menu..." << endl;
        cin.ignore();
        cin.get();
        return;
    }

    string keyword;
    cout << "|-------------[ Search Barang ]-------------|" << endl;
    cout << "|- Search Keyword\t: ";
    cin.ignore();
    getline(cin, keyword);
    cout << "|-------------------------------------------|" << endl;

    keyword = toLower(keyword);

    Barang *current = head;
    bool found = false;

    system("cls");

    cout << "\t\t\t    HASIL CARI   " << endl;
    cout << "\t\t\t  ---------------" << endl
        << endl;
    cout << "* Keyword: " << keyword << endl
        << endl;
    cout << left << " " << setw(5) << "ID"
            << setw(25) << "Nama Barang"
            << setw(15) << "Kode Barang"
            << setw(15) << "Harga"
            << setw(5) << "Stok"
            << endl;
    cout << "+----------------------------------------------------------------+" << endl;
    while (current != NULL)
    {
        if (toLower(current->namaBarang).find(keyword) != string::npos || toLower(current->kodeBarang).find(keyword) != string::npos)
        {
            cout << left << " " << setw(5) << current->id
                << setw(25) << splitString(current->namaBarang, 25)
                << setw(15) << current->kodeBarang
                << setw(15) << current->harga
                << setw(5) << current->stok
                << endl;
            found = true;
        }
        current = current->next;
    }

    if (!found)
    {
        cout << "\tBarang dengan keyword " << keyword << " tidak ditemukan." << endl;
    }
    cout << "+----------------------------------------------------------------+" << endl;

    cout << "\nTekan Enter untuk kembali ke menu..." << endl;
    cin.ignore();
    cin.get();
}

// ---------------| Main Program |--------------- //
int main()
{
    Barang *head = NULL;
    int currentId = 1;
    int userChoice;
    bool exit = false;
    stack<Barang *> undoStack;

    Barang *barang1 = new Barang();
    Barang *barang2 = new Barang();
    Barang *barang3 = new Barang();
    Barang *barang4 = new Barang();
    Barang *barang5 = new Barang();

    do
    {
        system("cls");

        displayMenu();
        cout << " Masukkan pilihan: ";
        cin >> userChoice;

        system("cls");

        switch (userChoice)
        {
        case 1:
            tambahBarang(head, currentId, undoStack);
            break;
        case 2:
            hapusBarang(head, undoStack);
            break;
        case 3:
            editBarang(head, undoStack);
            break;
        case 4:
            lihatBarang(head);
            break;
        case 5:
            searchBarang(head);
            break;
        case 6:
            restoreState(undoStack, head, "Undo");
            break;
        case 7:
            exit = true;
            break;
        case 69: // Dummy data untuk testing
            saveState(undoStack, head);
            
            barang1->id = 1;
            barang1->namaBarang = "Beras Sungut Lele";
            barang1->kodeBarang = "SMBK001";
            barang1->harga = 20000;
            barang1->stok = 10;
            barang1->next = barang2;

            barang2->id = 2;
            barang2->namaBarang = "Minyak Bimoli 1L";
            barang2->kodeBarang = "SMBK003";
            barang2->harga = 15000;
            barang2->stok = 20;
            barang2->next = barang3;

            barang3->id = 3;
            barang3->namaBarang = "Gula Pasir";
            barang3->kodeBarang = "SMBK002";
            barang3->harga = 12000;
            barang3->stok = 15;
            barang3->next = barang4;

            barang4->id = 4;
            barang4->namaBarang = "Tepung Terigu";
            barang4->kodeBarang = "SMBK004";
            barang4->harga = 5000;
            barang4->stok = 25;
            barang4->next = barang5;

            barang5->id = 5;
            barang5->namaBarang = "Susu Bendera 1L";
            barang5->kodeBarang = "SMBK005";
            barang5->harga = 15000;
            barang5->stok = 30;
            barang5->next = NULL;

            head = barang1;
            currentId = 6;

            break;
        default:
            cout << "Pilihan tidak valid" << endl;
            break;
        }

    } while (!exit);

    return 0;
}
