#include <iostream>
using namespace std;

/* ===================== STRUCT DONASI ===================== */
struct Donasi {
    int id;
    string nama;
    int nominal;
};

/* ===================== AUTO ID ===================== */
int autoID = 1;

/* ===================== LINKED LIST (DATA UTAMA) ===================== */
struct NodeLL {
    Donasi data;
    NodeLL* next;
};

NodeLL* head = NULL;

void insertLinkedList(Donasi d) {
    NodeLL* newNode = new NodeLL{d, NULL};
    if (head == NULL) {
        head = newNode;
    }
    else {
        NodeLL* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void hapusTerakhirLL() {
    if (head == NULL) {
        return;
    }

    if (head->next == NULL) {
        delete head;
        head = NULL;
    } else {
        NodeLL* temp = head;
        while (temp->next->next != NULL) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = NULL;
    }
}

void tampilLinkedList() {
    if (head == NULL) {
        cout << "Belum ada donasi" << endl;
        return;
    }
    cout << endl << "=== DATA DONASI ===" << endl;
    NodeLL* temp = head;
    while (temp != NULL) {
        cout << "(" << temp->data.id << ") " << temp->data.nama << " - Rp" << temp->data.nominal << endl;
        temp = temp->next;
    }
}

/* ===================== ARRAY (VIEW SORTING SAJA) ===================== */
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

void sortAsc() {
    for (int i = 0; i < totalDonasi - 1; i++) {
        for (int j = 0; j < totalDonasi - i - 1; j++) {
            if (dataDonasi[j].nominal > dataDonasi[j + 1].nominal) {
                // Manual swap
                Donasi temp = dataDonasi[j];
                dataDonasi[j] = dataDonasi[j + 1];
                dataDonasi[j + 1] = temp;
            }
        }
    }
}

void sortDesc() {
    for (int i = 0; i < totalDonasi - 1; i++) {
        for (int j = 0; j < totalDonasi - i - 1; j++) {
            if (dataDonasi[j].nominal < dataDonasi[j + 1].nominal) {
                // Manual swap
                Donasi temp = dataDonasi[j];
                dataDonasi[j] = dataDonasi[j + 1];
                dataDonasi[j + 1] = temp;
            }
        }
    }
}

void tampilArray() {
    cout << endl << "=== TAMPILAN DONASI TERURUT (JUMLAH DONASI) ===" << endl;
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
        cout << "Tidak ada donasi untuk di-undo" << endl;
        return;
    }

    Donasi last = stackUndo[top--];
    hapusTerakhirLL();

    cout << "Undo donasi: " << last.nama << " (Rp" << last.nominal << ")" << endl;
}

/* ===================== QUEUE (ANTRIAN DONATUR) ===================== */
string queueDonatur[100];
int frontQ = 0, rearQ = -1;

void enqueue(string nama) {
    queueDonatur[++rearQ] = nama;
}

void dequeue() {
    if (frontQ > rearQ) {
        cout << "Antrian donatur kosong" << endl;
        return;
    }
    cout << "Memproses donatur: " << queueDonatur[frontQ++] << endl;
}

/* ===================== TREE (BST HISTORIS PENCARIAN) ===================== */
struct Node {
    string nama;
    Node* left;
    Node* right;
};

Node* root = NULL;

Node* insertBST(Node* node, string nama) {
    if (node == NULL) {
        return new Node{nama, NULL, NULL};
    }
    if (nama < node->nama) {
        node->left = insertBST(node->left, nama);
    }
    else {
        node->right = insertBST(node->right, nama);
    }
    return node;
}

bool searchBST(Node* node, string nama) {
    if (node == NULL) {
        return false;
    }
    if (node->nama == nama) {
        return true;
    }
    if (nama < node->nama) {
        return searchBST(node->left, nama);
    }
    return searchBST(node->right, nama);
}

/* ===================== MENU ===================== */
void showMenu() {
    cout << endl << "=== ONLINE DONATION APPLICATION ===" << endl;
    cout << "1. Tambah Donasi" << endl;
    cout << "2. Lihat Semua Donasi" << endl;
    cout << "3. Urutkan Donasi (View)" << endl;
    cout << "4. Undo Donasi Terakhir" << endl;
    cout << "5. Proses Antrian Donatur" << endl;
    cout << "6. Cari Donatur" << endl;
    cout << "7. Keluar" << endl;
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
                d.id = autoID++;

                cin.ignore();
                cout << "Nama Donatur : ";
                getline(cin, d.nama);
                cout << "Nominal Donasi : ";
                cin >> d.nominal;

                insertLinkedList(d);     // Linked List
                pushUndo(d);             // Stack
                enqueue(d.nama);         // Queue
                root = insertBST(root, d.nama); // BST

                cout << "Donasi berhasil ditambahkan" << endl;
                break;
            }
            case 2: {
                tampilLinkedList();      // DATA ASLI
                break;
            }

            case 3: {
                int p;
                cout << endl << "1. Ascending" << endl << "2. Descending" << endl << "Pilih: ";
                cin >> p;

                copyLLtoArray();         // COPY SAJA
                if (p == 2) {
                    sortDesc();
                } else {
                    sortAsc();
                }

                tampilArray();           // VIEW SAJA
                break;
            }
            case 4: {
                undoDonasi();
                break;
            }

            case 5: {
                dequeue();
                break;
            }

            case 6: {
                string cari;
                cin.ignore();
                cout << "Cari nama donatur: ";
                getline(cin, cari);

                if (searchBST(root, cari)) {
                    // Cari di linked list untuk detail donasi
                    NodeLL* temp = head;
                    bool found = false;
                    while (temp != NULL) {
                        if (temp->data.nama == cari) {
                            cout << "Donatur ditemukan!" << endl;
                            cout << "Nama Donatur: " << temp->data.nama << endl;
                            cout << "Jumlah Donasi: Rp" << temp->data.nominal << endl;
                            found = true;
                            break;
                        }
                        temp = temp->next;
                    }
                    if (!found) {
                        cout << "Donatur tidak ditemukan" << endl;
                    }
                } else {
                    cout << "Donatur tidak ditemukan" << endl;
                }
                break;
            }
            case 7: {
                cout << "Terima kasih telah menggunakan aplikasi" << endl;
                break;
            }

            default: {
                cout << "Menu tidak valid" << endl;
            }
        }
    } while (pilih != 7);

    return 0;
}
