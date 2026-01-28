#include <iostream>
#include <string>
using namespace std;

// Forward declarations
struct Node;
struct QueueNode;
struct UndoNode;

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

/* ===================== QUEUE (ANTRIAN DONATUR) ===================== */
struct QueueNode {
    Donasi data;
    QueueNode* next;
};

QueueNode* frontQueue = NULL;
QueueNode* rearQueue  = NULL;

void enqueue(QueueNode*& front, QueueNode*& rear, Donasi d) {
    QueueNode* newNode = new QueueNode;
    newNode->data = d;
    newNode->next = NULL;

    if (front == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

QueueNode* peekQueue(QueueNode* front) {
    return front; // NULL kalau kosong
}

void dequeue(QueueNode*& front, QueueNode*& rear) {
    if (front == NULL) {
        return;
    }

    QueueNode* temp = front;
    front = front->next;

    if (front == NULL) {
        rear = NULL;
    }

    delete temp;
}

void prosesAntrianQueue(QueueNode*& front, QueueNode*& rear) {
    char pilih;

    if (front == NULL) {
        cout << "Tidak ada antrian donasi.\n";
        return;
    }

    while (front != NULL) {
        QueueNode* current = peekQueue(front);

        cout << "\n=== DATA ANTRIAN SAAT INI ===" << endl;
        cout << "Nama Donatur  : " << current->data.nama << endl;
        cout << "Jumlah Donasi : " << current->data.nominal << endl;

        cout << "\nProses antrian (" << current->data.nama << " - "  << current->data.nominal << ")? [Y/N]: ";
        cin >> pilih;

        if (pilih == 'Y' || pilih == 'y') {
            dequeue(front, rear);
            cout << "Antrian berhasil diproses." << endl;

        } else if (pilih == 'N' || pilih == 'n') {
            cout << "Proses antrian dihentikan." << endl;
            break;

        } else {
            cout << "Pilihan tidak valid!" << endl;
            break;
        }
    }

    if (front == NULL) {
        cout << "\nSemua antrian donasi sudah diproses.\n";
    }
}
/* ===================== STACK (UNDO) ===================== */

struct UndoNode {
    Donasi data;
    UndoNode* next;
};

UndoNode* undoTop = NULL;

void pushUndo(UndoNode*& top, Donasi d) {
    UndoNode* newNode = new UndoNode;
    newNode->data = d;
    newNode->next = top;
    top = newNode;
}

Donasi popUndo(UndoNode*& top) {
    if (top == NULL) {
        return {-1, "", 0}; // Invalid Donasi
    }

    UndoNode* temp = top;
    Donasi d = temp->data;
    top = top->next;
    delete temp;

    return d;
}

void undoQueue(QueueNode*& front, QueueNode*& rear, int id) {
    QueueNode* tempFront = NULL;
    QueueNode* tempRear = NULL;

    while (front != NULL) {
        QueueNode* curr = front;
        front = front->next;

        if (curr->data.id != id) {
            enqueue(tempFront, tempRear, curr->data);
        }

        delete curr;
    }

    front = tempFront;
    rear = tempRear;
}

void undoLastAction(
    UndoNode*& undoTop,
    QueueNode*& frontQueue,
    QueueNode*& rearQueue
) {
    Donasi d = popUndo(undoTop);

    if (d.id == -1) {
        cout << "Tidak ada aksi untuk di-undo.\n";
        return;
    }

    hapusTerakhirLL();
    undoQueue(frontQueue, rearQueue, d.id);

    cout << "Undo berhasil untuk donatur: " << d.nama << " (" << d.nominal << ")\n";
}

/* ===================== TREE (BST HISTORIS PENCARIAN) ===================== */
struct Node {
    Donasi data;
    Node* left;
    Node* right;
};

Node* root = NULL;

Node* insertBST(Node* node, Donasi d) {
    if (node == NULL) {
        return new Node{d, NULL, NULL};
    }
    if (d.nama < node->data.nama) {
        node->left = insertBST(node->left, d);
    } else {
        node->right = insertBST(node->right, d);
    }
    return node;
}

void searchBST(Node* node, string key, bool &found) {
    if (node == NULL) {
        return;
    } 

    if (node->data.nama == key) {
        cout << "\nDonatur ditemukan!" << endl;
        cout << "ID            : " << node->data.id << endl;
        cout << "Nama Donatur  : " << node->data.nama << endl;
        cout << "Jumlah Donasi : Rp" << node->data.nominal << endl;
        found = true;
    }

    // tetap telusuri dua sisi
    searchBST(node->left, key, found);
    searchBST(node->right, key, found);
}


void cariDonaturBST(Node* root) {
    string cari;
    cin.ignore();
    cout << "Cari nama donatur: ";
    getline(cin, cari);

    bool found = false;
    searchBST(root, cari, found);

    if (!found) {
        cout << "Donatur tidak ditemukan" << endl;
    }
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
                cin.ignore();

                insertLinkedList(d);     // Linked List
                pushUndo(undoTop, d); //Stack
                enqueue(frontQueue, rearQueue, d); // Queue
                root = insertBST(root, d); // BST

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
                undoLastAction(undoTop, frontQueue, rearQueue);
                break;
            }

            case 5: {
                prosesAntrianQueue(frontQueue, rearQueue);
                break;
            }

            case 6: {
                cariDonaturBST(root);
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
