#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enum untuk jenis barang
// Enum ini digunakan untuk mengkategorikan barang ke dalam tiga jenis: Elektronik, Furnitur, dan Alat Tulis.
typedef enum {
    ELEKTRONIK,
    FURNITUR,
    ALAT_TULIS
} JenisBarang;

// Struct untuk data barang
// Struct ini digunakan untuk menyimpan informasi tentang barang seperti nama, jumlah, dan jenis barang.
typedef struct {
    char nama[50];
    int jumlah;
    JenisBarang jenis;
} Barang;

// Union untuk informasi tambahan barang
// Union ini dirancang untuk menyimpan informasi tambahan tentang barang, misalnya nomor seri atau catatan.
typedef union {
    char nomorSeri[20];
    char catatan[100];
} InfoTambahan;

// Fungsi untuk menambah barang baru
// Fungsi ini memungkinkan pengguna menambahkan satu atau beberapa barang ke inventaris.
void tambahBarang(Barang **inventaris, int *jumlahBarang) {
    int jumlahBaru;
    printf("\nBerapa banyak barang yang ingin ditambahkan? ");
    scanf("%d", &jumlahBaru);

    // Jika inventaris kosong, gunakan malloc
    if (*inventaris == NULL) {
        *inventaris = (Barang *)malloc(jumlahBaru * sizeof(Barang));
    } else {
        // Jika inventaris sudah ada, gunakan realloc
        *inventaris = (Barang *)realloc(*inventaris, (*jumlahBarang + jumlahBaru) * sizeof(Barang));
    }

    // Pastikan memori berhasil dialokasikan
    if (*inventaris == NULL) {
        printf("Alokasi memori gagal!\n");
        return;
    }

    // Loop untuk memasukkan data barang baru
    for (int i = 0; i < jumlahBaru; i++) {
        printf("\nBarang #%d\n", *jumlahBarang + i + 1);
        printf("Masukkan nama barang: ");
        scanf("%s", (*inventaris)[*jumlahBarang + i].nama);

        printf("Masukkan jumlah barang: ");
        scanf("%d", &(*inventaris)[*jumlahBarang + i].jumlah);

        printf("Pilih jenis barang (0: Elektronik, 1: Furnitur, 2: Alat Tulis): ");
        int jenis;
        scanf("%d", &jenis);
        (*inventaris)[*jumlahBarang + i].jenis = (JenisBarang)jenis;
    }

    // Update jumlah barang total setelah penambahan
    *jumlahBarang += jumlahBaru;
    printf("%d barang berhasil ditambahkan!\n", jumlahBaru);
}

// Fungsi untuk menampilkan semua barang
// Fungsi ini menampilkan daftar semua barang dalam inventaris.
void tampilkanBarang(Barang *inventaris, int jumlahBarang) {
    printf("\n=== Daftar Barang ===\n");
    for (int i = 0; i < jumlahBarang; i++) {
        printf("\nBarang #%d\n", i + 1);
        printf("Nama: %s\n", inventaris[i].nama);
        printf("Jumlah: %d\n", inventaris[i].jumlah);
        printf("Jenis: ");
        switch (inventaris[i].jenis) {
            case ELEKTRONIK: printf("Elektronik\n"); break;
            case FURNITUR: printf("Furnitur\n"); break;
            case ALAT_TULIS: printf("Alat Tulis\n"); break;
        }
    }
}

// Fungsi untuk menghapus barang
// Fungsi ini menghapus barang tertentu dari inventaris berdasarkan nama barang.
void hapusBarang(Barang **inventaris, int *jumlahBarang) {
    if (*jumlahBarang == 0) {
        printf("\nInventaris kosong, tidak ada barang yang dapat dihapus.\n");
        return;
    }

    char namaBarang[50];
    printf("\nMasukkan nama barang yang ingin dihapus: ");
    scanf("%s", namaBarang);

    int index = -1;
    for (int i = 0; i < *jumlahBarang; i++) {
        if (strcmp((*inventaris)[i].nama, namaBarang) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("\nBarang dengan nama \"%s\" tidak ditemukan.\n", namaBarang);
        return;
    }

    // Geser semua barang setelah indeks yang dihapus ke posisi sebelumnya
    for (int i = index; i < *jumlahBarang - 1; i++) {
        (*inventaris)[i] = (*inventaris)[i + 1];
    }

    // Kurangi jumlah barang total
    *jumlahBarang -= 1;
    *inventaris = (Barang *)realloc(*inventaris, (*jumlahBarang) * sizeof(Barang));
    if (*inventaris == NULL && *jumlahBarang > 0) {
        printf("\nTerjadi kesalahan saat menghapus barang.\n");
        return;
    }

    printf("\nBarang \"%s\" berhasil dihapus.\n", namaBarang);
}

// Fungsi utama
// Fungsi ini adalah titik masuk program, menyediakan menu untuk mengelola inventaris.
int main() {
    Barang *inventaris = NULL;
    int jumlahBarang = 0;

    int pilihan; // Variabel untuk menyimpan pilihan menu

    
    printf("\nSelamat datang di Program Manajemen Inventaris Kantor!\n");
    printf("Silakan pilih menu untuk mulai mengelola inventaris.\n");

    do {
        printf("\n=== Menu Manajemen Inventaris ===\n");
        printf("1. Tambah Barang\n");
        printf("2. Tampilkan Barang\n");
        printf("3. Hapus Barang\n");
        printf("4. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &pilihan);

        // Eksekusi berdasarkan pilihan pengguna
        switch (pilihan) {
            case 1:
                tambahBarang(&inventaris, &jumlahBarang);
                break;
            case 2:
                tampilkanBarang(inventaris, jumlahBarang);
                break;
            case 3:
                hapusBarang(&inventaris, &jumlahBarang);
                break;
            case 4:
                printf("\nTerima kasih telah menggunakan Program Manajemen Inventaris Kantor. Sampai jumpa!\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 4);

    // Bebaskan memori sebelum keluar
    free(inventaris);
    return 0;
}
