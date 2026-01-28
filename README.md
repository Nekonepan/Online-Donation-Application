# 🟦 ONLINE DONATION APPLICATION

Online Donation Application adalah aplikasi berbasis C++ (console) yang dirancang untuk mensimulasikan sistem pengelolaan donasi secara sederhana namun terstruktur. Aplikasi ini dibuat sebagai proyek pembelajaran Struktur Data, dengan tujuan menerapkan beberapa struktur data utama dalam satu studi kasus yang saling terintegrasi.

Aplikasi memungkinkan pengguna untuk menambahkan donasi, melihat data donasi aktif, mengurutkan donasi, memproses donasi berdasarkan antrian, melakukan undo input terakhir, serta mencari donatur.

---

## 📂 Tujuan Project

- Mengimplementasikan berbagai struktur data.
- Mengintegrasikan beberapa struktur data menjadi satu aplikasi yang bekerja secara utuh.
- Menerapkan konsep OOP dan modular programming.
- Membuat aplikasi donasi sederhana yang interaktif dan terstruktur.

---

## 🧩 Struktur Data yang Digunakan

| Struktur Data            | Peran dalam Aplikasi                            |
| ------------------------ | ----------------------------------------------- |
| Linked List              | Menyimpan data donasi aktif (urutan asli input) |
| Array                    | Menampilkan data donasi terurut (view only)     |
| Stack                    | Undo donasi terakhir yang diinput               |
| Queue                    | Antrian donatur untuk diproses                  |
| Binary Search Tree (BST) | Pencarian data donatur                          |

---

## ⚙️ Requierements

- g++ (MinGW / MSYS2 / GCC)

---

## 🏃Cara Run Aplikasi

1. Clone repository

```
git clone https://github.com/Nekonepan/Online-Donation-Application.git
```

2. Navigasi ke folder project

```
cd Online-Donation-Application
```

3. Run file

- CMD / Git Bash / MSYS2 / MinGW:

```
g++ main.cpp -o main.exe
./main.exe
```

- PowerShell:

```
g++ main.cpp -o main.exe
.\main.exe
```

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
| 2. Lihat Semua Donasi (Linked-List)    |
| 3. Urutkan Donasi (Array)              |
| 4. Undo Donasi Terakhir (Stack)        |
| 5. Proses Antrian Donatur (Queue)      |
| 6. Cari Donatur (BST)                  |
| 7. Keluar                              |
+----------------------------------------+
```

### 📝 Penjelasan Menu

**1. Tambah Donasi**

Urutan pemrosesan:

- Data masuk ke Queue (antrian donatur)
- Setelah diproses → masuk ke Linked List (data utama)
- Data juga disimpan di:
  - Array (untuk sorting)
  - Tree / BST / AVL (untuk pencarian)
  - Stack (riwayat untuk Undo)

**2. Lihat Semua Donasi**

Menampilkan data dari Linked List secara berurutan.

**3. Urutkan Donasi**

Sorting dapat dilakukan dengan:

- Algoritma sorting dari Array
- Atau traversal Inorder dari AVL Tree

**4. Undo Donasi Terakhir**

- Mengambil data dari Stack
- Menghapus data terakhir dari Linked List dan Tree
- Mengembalikan sistem ke kondisi sebelumnya

**5. Proses Antrian Donatur**

- Mengambil data dari Queue (`dequeue`)
- Memindahkan ke Linked List & Tree

**6. Cari Donatur**

Pencarian cepat menggunakan:

- BST Tree
  atau
- AVL Tree (lebih optimal)

**7. Keluar**

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

## 🤝 Credits

Institusi : Universitas Ahmad Dahlan Daerah Istimewa Yogyakarta

Mata Kuliah : Struktur Data

Dosen : Dr. Ardiansyah, S.T., M.Cs.

Tujuan Pengembangan : Proyek Akademi

| Contributors                                                                    | NIM        | Jobdesk      | Github Profile |
| ------------------------------------------------------------------------------- | ---------- | ------------ |----------------|
| Erfannindya Ade Noventyas                                                       | 2300018279 | Array        | [(Erfann279)](https://github.com/Erfann279) |
| Allea Zahva                                                                     | 2400018028 | Linked List  | [(allea-prog)](https://github.com/allea-prog) |
| Dheya Rosicha Ilma                                                              | 2400018019 | Stack        | [(Ilm4)](https://github.com/Ilm4) |
| Dhiva Anindya Untsa Layalya                                                     | 2400018001 | Queue        | [(dhivaanindyaa)](https://github.com/dhivaanindyaa) |
| Lutfan Alaudin Naja                                                             | 2400018032 | Tree/BST/AVL | [(Nekonepan)](https://github.com/Nekonepan) |
