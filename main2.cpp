#include <iostream>
using namespace std;

/* ===================== STRUCT DONASI ===================== */
struct Donasi {
    int id;
    string nama;
    int nominal;
};

/* ===================== LINKED LIST (DATA UTAMA) ===================== */
struct NodeLL {
    Donasi data;
    NodeLL* next;
};

NodeLL* head = NULL;

void insertLinkedList(Donasi d) {
    NodeLL* newNode = new NodeLL{d, NULL};
    if (head == NULL)
        head = newNode;
    else {
        NodeLL* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}

void tampilLinkedList() {
    if (head == NULL) {
        cout << "Belum ada donasi\n";
        return;
    }
    NodeLL* temp = head;
    while (temp != NULL) {
        cout << temp->data.id << ". "
             << temp->data.nama
             << " - Rp" << temp->data.nominal << endl;
        temp = temp->next;
    }
}

/* ===================== ARRAY (UNTUK SORTING) ===================== */
Donasi dataDonasi[100];
int totalDonasi = 0;

void copyLLtoArray() {
    totalDonasi = 0;
    NodeLL* temp = head;
    while (temp != NULL) {
        dataDonasi[totalDonasi++] = temp->data;
        temp = temp->next;
    }
}

void sortDonasi() {
    for (int i = 0; i < totalDonasi - 1; i++) {
        for (int j = 0; j < totalDonasi - i - 1; j++) {
            if (dataDonasi[j].nominal > dataDonasi[j + 1].nominal) {
                Donasi tmp = dataDonasi[j];
                dataDonasi[j] = dataDonasi[j + 1];
                dataDonasi[j + 1] = tmp;
            }
        }
    }
}

void tampilArray() {
    for (int i = 0; i < totalDonasi; i++) {
        cout << dataDonasi[i].id << ". " << dataDonasi[i].nama << " - Rp" << dataDonasi[i].nominal << endl;
    }
}

/* ===================== STACK (UNDO) ===================== */
Donasi stackUndo[100];
int top = -1;

void pushUndo(Donasi d) {
    stackUndo[++top] = d;
}

void undoDonasi() {
    if (top < 0 || head == NULL) {
        cout << "Tidak ada donasi untuk di-undo\n";
        return;
    }

    // hapus node terakhir linked list
    if (head->next == NULL) {
        delete head;
        head = NULL;
    } else {
        NodeLL* temp = head;
        while (temp->next->next != NULL)
            temp = temp->next;
        delete temp->next;
        temp->next = NULL;
    }

    top--;
    cout << "Donasi terakhir berhasil di-undo\n";
}

/* ===================== QUEUE (ANTRIAN DONATUR) ===================== */
string queueDonatur[100];
int frontQ = 0, rearQ = -1;

void enqueue(string nama) {
    queueDonatur[++rearQ] = nama;
}

void dequeue() {
    if (frontQ > rearQ) {
        cout << "Antrian donatur kosong\n";
        return;
    }
    cout << "Memproses donatur: " << queueDonatur[frontQ++] << endl;
}

/* ===================== TREE (BST PENCARIAN) ===================== */
struct Node {
    string nama;
    Node* left;
    Node* right;
};

Node* root = NULL;

Node* insertBST(Node* node, string nama) {
    if (node == NULL)
        return new Node{nama, NULL, NULL};
    if (nama < node->nama)
        node->left = insertBST(node->left, nama);
    else
        node->right = insertBST(node->right, nama);
    return node;
}

bool searchBST(Node* node, string nama) {
    if (node == NULL) return false;
    if (node->nama == nama) return true;
    if (nama < node->nama)
        return searchBST(node->left, nama);
    return searchBST(node->right, nama);
}

/* ===================== MENU ===================== */
void showMenu() {
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
        showMenu();
        cout << "Pilih menu: ";
        cin >> pilih;

        switch (pilih) {
        case 1: {
            Donasi d;
            d.id = (head == NULL) ? 1 : (head->data.id + 1);
            
            cin.ignore();
            cout << "Nama Donatur : ";
            getline(cin, d.nama);
            cout << "Nominal Donasi : ";
            cin >> d.nominal;

            insertLinkedList(d);        // LINKED LIST
            pushUndo(d);                // STACK
            enqueue(d.nama);            // QUEUE
            root = insertBST(root, d.nama); // TREE

            cout << "Donasi berhasil ditambahkan\n";
            break;
        }
        case 2:
            tampilLinkedList(); // LINKED LIST
            break;

        case 3:
            copyLLtoArray();    // LINKED LIST → ARRAY
            sortDonasi();       // ARRAY
            tampilArray();
            break;

        case 4:
            undoDonasi();       // STACK + LINKED LIST
            break;

        case 5:
            dequeue();          // QUEUE
            break;

        case 6: {
            string cari;
            cout << "Masukkan nama donatur: ";
            cin >> cari;
            if (searchBST(root, cari))
                cout << "Donatur ditemukan\n";
            else
                cout << "Donatur tidak ditemukan\n";
            break;
        }
        case 7:
            cout << "Terima kasih telah menggunakan aplikasi\n";
            break;

        default:
            cout << "Menu tidak valid\n";
        }
    } while (pilih != 7);

    return 0;
}
