#include <stdio.h>

int main()
{
    // Program dummy sederhana

    printf("=== Selamat Datang di Program Dummy ===\n");

    char nama[50];
    int umur;

    printf("Masukkan nama Anda: ");
    scanf("%s", nama);

    printf("Masukkan umur Anda: ");
    scanf("%d", &umur);

    printf("\nHalo %s, umur Anda %d tahun.\n", nama, umur);
    printf("Program ini hanya dummy untuk latihan input/output.\n");

    return 0;
}
