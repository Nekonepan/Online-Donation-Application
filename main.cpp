#include <iostream>
#include <string>
using namespace std;

/* ========= STRUCT BERSAMA ========= */
struct Donation {
    int id;
    string nama;
    int jumlah;
};

/* ========= ARRAY ========= */
void array_add(Donation d);
void array_sort();
void array_display();
void array_remove(int id);

/* ========= LINKED LIST ========= */
void list_insert(Donation d);
void list_display();
void list_remove(int id);

/* ========= STACK ========= */
void stack_push(Donation d);
Donation stack_pop();

/* ========= QUEUE ========= */
void queue_enqueue(Donation d);
Donation queue_dequeue();

/* ========= TREE / BST / AVL ========= */
void bst_insert(Donation d);
Donation* bst_search(int id);
void bst_remove(int id);

void showMenu() {
    cout << "=== ONLINE DONATION APPLICATION ===" << endl;
    cout << "1. Tambah Donasi" << endl;
    cout << "2. Lihat Semua Donasi" << endl;
    cout << "3. Urutkan Donasi" << endl;
    cout << "4. Undo Donasi Terakhir" << endl;
    cout << "5. Proses Antrian Donatur"  << endl;
    cout << "6. Cari Donatur" << endl;
    cout << "7. Keluar" << endl;
}

/* ========= MENU FUNCTION ========= */
void showMenu();
void addDonation();
void showAllDonations();
void sortDonations();
void undoDonation();
void processQueue();
void searchDonation();

/* ========= MAIN ========= */
int main() {
    int pilihan;

    do {
        showMenu();
        cout << "Pilih menu : ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                addDonation();
                break;
            }
            
            case 2: {
                showAllDonations();
                break;
            }

            case 3: {
                sortDonations();
                break;
            }

            case 4: {
                undoDonation();
                break;
            }

            case 5: {
                processQueue();
                break;
            }

            case 6: {
                searchDonation();
                break;
            }

            case 7: {
                cout << "Program selesai" << endl;
                break;
            }

            default: {
                cout << "Pilihan tidak valid" << endl;
            }
        }
    } while (pilihan != 7);

    return 0;
}