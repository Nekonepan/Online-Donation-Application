# 🟦 ONLINE DONATION APPLICATION

A project for the Struktur Data course, implementing multiple classic data structures (Array, Linked List, Stack, Queue, Tree/BST/AVL) dalam satu aplikasi donasi online berbasis console.

---

## 📂 Tujuan Project

- Mengimplementasikan berbagai struktur data.
- Mengintegrasikan beberapa struktur data menjadi satu aplikasi yang bekerja secara utuh.
- Menerapkan konsep OOP dan modular programming.
- Membuat aplikasi donasi sederhana yang interaktif dan terstruktur.

---

## 👥 Collaborators

|                                   Contributors                                  |     NIM    |    Jobdesk   |
|---------------------------------------------------------------------------------|------------|--------------|
| Erfannindya Ade Noventyas [(Erfann279)](https://github.com/Erfann279)           | 2300018279 | Array        |
| Allea Zahva [(allea-prog)](https://github.com/allea-prog)                       | 2400018028 | Linked List  |
| Dheya Rosicha Ilma [(Ilm4)](https://github.com/Ilm4)                            | 2400018019 | Stack        |
| Dhiva Anindya Untsa Layalya [(dhivaanindyaa)](https://github.com/dhivaanindyaa) | 2400018001 | Queue        |
| Lutfan Alaudin Naja [(Nekonepan)](https://github.com/Nekonepan)                 | 2400018032 | Tree/BST/AVL |

---

## 🧭 Alur Utama Aplikasi

Aplikasi bekerja mengikuti alur berikut:
```
Mulai
  |
Inisialisasi Struktur Data
  |
Tampilkan Menu Utama
  |
+----------------------------------------+
| 1. Tambah Donasi                       |
| 2. Lihat Semua Donasi                  |
| 3. Urutkan Donasi                      |
| 4. Undo Donasi Terakhir (Stack)        |
| 5. Proses Antrian Donatur (Queue)      |
| 6. Cari Donatur (Tree/BST/AVL)         |
| 7. Keluar                              |
+----------------------------------------+
```

### 📝 Penjelasan Menu

1. Tambah Donasi
  Urutan pemrosesan:
  1. Data masuk ke Queue (antrian donatur)
  2. Setelah diproses → masuk ke Linked List (data utama)
  3. Data juga disimpan di:
    - Array (untuk sorting)
    - Tree / BST / AVL (untuk pencarian)
    - Stack (riwayat untuk Undo)

2. Lihat Semua Donasi
Menampilkan data dari Linked List secara berurutan.

3. Urutkan Donasi
Sorting dapat dilakukan dengan:
- Algoritma sorting dari Array
- Atau traversal Inorder dari AVL Tree

4. Undo Donasi Terakhir
- Mengambil data dari Stack
- Menghapus data terakhir dari Linked List dan Tree
- Mengembalikan sistem ke kondisi sebelumnya

5. Proses Antrian Donatur
- Mengambil data dari Queue (`dequeue`)
- Memindahkan ke Linked List & Tree

6. Cari Donatur
Pencarian cepat menggunakan:
- BST Tree
atau
- AVL Tree (lebih optimal)

7. Keluar
Aplikasi berhenti.

---

## 🧠 Integrasi Struktur Data

Setiap struktur data bekerja sama seperti ini:
```
Input Donasi
   |
Queue (pending)
   | Proses
Linked List (data utama)
   /        \
 Array       Tree (BST/AVL)
   |           |
Sorting     Searching
   |           |
  Stack ← (Undo)
```

---

## 🏗️ Struktur Folder

```
/Online-Donation-Application
|
|-- array/
|   \-- array.cpp
|
|-- linkedlist/
|   \-- linkedlist.cpp
│
|-- stack/
|   \-- stack.cpp
|
|-- queue/
|   \-- queue.cpp
|
|-- tree/
|   \-- bst.cpp
|   \-- avl.cpp
|   \-- tree.cpp
|
|--- main.cpp
```