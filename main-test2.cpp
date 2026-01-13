#include <iostream>
using namespace std;

/* ===================== STRUCT DONASI ===================== */
struct Donasi {
    int id;
    string nama;
    int nominal;
};

/* ===================== ARRAY DONASI ===================== */
Donasi data_donasi[100];
int total_donasi = 0;

/* ===================== STACK (UNDO) ===================== */
Donasi stack_undo[100];
int top = -1;

void push_undo(Donasi d) {
    stack_undo[++top] = d;
}

void undo_donasi() {
    if (top < 0) {
        cout << "Tidak ada donasi untuk di-undo\n";
        return;
    }
    total_donasi--;
    top--;
    cout << "Donasi terakhir berhasil di-undo\n";
}

/* ===================== QUEUE (ANTRIAN DONATUR) ===================== */
string queue_donatur[100];
int front_q = 0, rear_q = -1;

void enqueue(string nama) {
    queue_donatur[++rear_q] = nama;
}

void dequeue() {
    if (front_q > rear_q) {
        cout << "Antrian donatur kosong\n";
        return;
    }
    cout << "Memproses donatur: " << queue_donatur[front_q++] << endl;
}

/* ===================== TREE (BST CARI DONATUR) ===================== */
struct Node {
    string nama;
    Node* left;
    Node* right;
    Node(string n, Node* l, Node* r) : nama(n), left(l), right(r) {}
};

Node* root = NULL;

Node* insert_bst(Node* current, string nama) {
    if (current == NULL)
        return new Node{nama, NULL, NULL};

    if (nama < current->nama)
        current->left = insert_bst(current->left, nama);
    else
        current->right = insert_bst(current->right, nama);

    return current;
}

bool search_bst(Node* current, string nama) {
    if (current == NULL) return false;
    if (current->nama == nama) return true;

    if (nama < current->nama)
        return search_bst(current->left, nama);
    return search_bst(current->right, nama);
}

/* ===================== SORTING DONASI ===================== */
void sort_donasi() {
    for (int i = 0; i < total_donasi - 1; i++) {
        for (int j = 0; j < total_donasi - i - 1; j++) {
            if (data_donasi[j].nominal > data_donasi[j + 1].nominal) {
                Donasi temp = data_donasi[j];
                data_donasi[j] = data_donasi[j + 1];
                data_donasi[j + 1] = temp;
            }
        }
    }
    cout << "Donasi berhasil diurutkan berdasarkan nominal\n";
}

/* ===================== DISPLAY DONASI ===================== */
void tampil_donasi() {
    if (total_donasi == 0) {
        cout << "Belum ada donasi\n";
        return;
    }
    for (int i = 0; i < total_donasi; i++) {
        cout << data_donasi[i].id << ". " << data_donasi[i].nama << " - Rp" << data_donasi[i].nominal << endl;
    }
}

/* ===================== MENU ===================== */
void show_menu() {
    cout << "\n=== ONLINE DONATION APPLICATION ===\n";
    cout << "1. Tambah Donasi\n";
    cout << "2. Lihat Semua Donasi\n";
    cout << "3. Urutkan Donasi\n";
    cout << "4. Undo Donasi Terakhir\n";
    cout << "5. Proses Antrian Donatur\n";
    cout << "6. Cari Donatur\n";
    cout << "7. Keluar\n";
}

/* ===================== MAIN ===================== */
int main() {
    int pilih;

    do {
        show_menu();
        cout << "Pilih menu: ";
        cin >> pilih;

        switch (pilih) {
        case 1: {
            Donasi d;
            d.id = total_donasi + 1;

            cout << "Nama Donatur : ";
            cin >> d.nama;
            cout << "Nominal Donasi : ";
            cin >> d.nominal;

            data_donasi[total_donasi++] = d;
            push_undo(d);
            enqueue(d.nama);
            root = insert_bst(root, d.nama);

            cout << "Donasi berhasil ditambahkan\n";
            break;
        }
        case 2: {
            tampil_donasi();
            break;
        }

        case 3: {
            sort_donasi();
            break;
        }

        case 4: {
            undo_donasi();
            break;
        }

        case 5: {
            dequeue();
            break;
        }

        case 6: {
            string cari;
            cout << "Masukkan nama donatur: ";
            cin >> cari;

            if (search_bst(root, cari))
                cout << "Donatur ditemukan\n";
            else
                cout << "Donatur tidak ditemukan\n";
            break;
        }
        case 7: {
            cout << "Terima kasih telah menggunakan aplikasi\n";
            break;
        }

        default: {
            cout << "Menu tidak valid\n";
        }
        }

    } while (pilih != 7);

    return 0;
}
