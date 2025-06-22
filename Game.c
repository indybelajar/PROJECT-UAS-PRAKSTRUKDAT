#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct untuk item inventory
typedef struct Item {
    char name[50];
    struct Item* next;
} Item;

// Struct karakter
typedef struct {
    char name[50];
    char birthdate[15];
    int affinity;
} Character;

// Struct untuk chapter
typedef struct Chapter {
    int chapterNumber;
    char scene[500];
    struct Chapter* next;
} Chapter;

// Variabel global
Item* inventory = NULL;
Character senpai = {"Raka", "20 April", 0};
Chapter* head = NULL;

// Fungsi tambah item
void addItem(char name[]) {
    Item* newItem = (Item*)malloc(sizeof(Item));
    strcpy(newItem->name, name);
    newItem->next = inventory;
    inventory = newItem;
}

// Fungsi pakai item
void useItem(char name[]) {
    Item *temp = inventory, *prev = NULL;
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Item tidak ditemukan.\n");
        return;
    }
    if (prev == NULL) {
        inventory = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
    printf("Item '%s' telah digunakan.\n", name);
}

// Tampilkan inventory
void showInventory() {
    printf("\nInventory:\n");
    Item* temp = inventory;
    while (temp != NULL) {
        printf("- %s\n", temp->name);
        temp = temp->next;
    }
}

// Tambah chapter
void addChapter(int chapterNumber, char* scene) {
    Chapter* newChap = (Chapter*)malloc(sizeof(Chapter));
    newChap->chapterNumber = chapterNumber;
    strcpy(newChap->scene, scene);
    newChap->next = NULL;

    if (head == NULL) {
        head = newChap;
    } else {
        Chapter* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newChap;
    }
}

// Tampilkan karakter
void listCharacters() {
    printf("\n=== Daftar Karakter ===\n");
    printf("Nama: %s\n", senpai.name);
    printf("Tanggal Lahir: %s\n", senpai.birthdate);
    printf("Afinitas: %d\n", senpai.affinity);
}

// Lompat ke chapter tertentu
void jumpToChapter(int targetChapter) {
    Chapter* current = head;
    while (current != NULL) {
        if (current->chapterNumber == targetChapter) {
            printf("\nChapter %d:\n%s\n", current->chapterNumber, current->scene);
            return;
        }
        current = current->next;
    }
    printf("Chapter tidak ditemukan.\n");
}

// Modul per chapter
void playChapter1() {
    int choice;
    printf("MC: Ah, indahnya hari ini.\n(Kakak kelas datang)\nMC: (Apa yang harus aku lakukan?)\n");
    printf("1. Ucapkan salam\n2. Abaikan saja\n> ");
    scanf("%d", &choice);
    if (choice == 1) {
        senpai.affinity += 1;
        printf("Senpai membalas dengan senyuman. Afinitas meningkat!\n");
    } else {
        senpai.affinity -= 1;
        printf("Senpai terlihat bingung dan lewat begitu saja... Afinitas menurun.\n");
    }
}

void playChapter2() {
    int choice;
    printf("Senpai: Hai, kamu mahasiswa baru ya?\nMC: (Bagaimana ya jawabnya?)\n");
    printf("1. Jawab dengan semangat\n2. Jawab singkat saja\n> ");
    scanf("%d", &choice);
    if (choice == 1) {
        senpai.affinity += 2;
        printf("Senpai terkesan dengan semangatmu!\n");
    } else {
        printf("Senpai tetap ramah, tapi tampak kecewa sedikit.\n");
    }
}

void playChapter3() {
    int choice;
    printf("Senpai cerita bahwa dia sedang dekat dengan seseorang.\n");
    printf("MC: (Apa reaksimu?)\n1. Marah\n2. Sedih\n3. Dengarkan sampai habis\n> ");
    scanf("%d", &choice);
    if (choice == 1) {
        senpai.affinity -= 2;
        printf("Kamu marah... afinitas menurun!\n");
    } else if (choice == 2) {
        senpai.affinity += 1;
        printf("Kamu sedih... afinitas naik sedikit.\n");
    } else if (choice == 3) {
        senpai.affinity += 2;
        printf("Kamu mendengarkan dengan sabar... afinitas meningkat!\n");
    }
}

void playChapter5() {
    int choice;
    printf("\nGunakan item untuk menarik perhatian senpai?\n1. Cokelat\n2. Tidak\n> ");
    scanf("%d", &choice);
    if (choice == 1) {
        useItem("Cokelat");
        senpai.affinity += 2;
        printf("Senpai tersenyum menerima cokelatmu. Afinitas meningkat!\n");
    }
}

void playChapter7() {
    int choice;
    printf("Senpai terlihat bingung kamu tidak mengobrol lagi...\n");
    printf("Apakah kamu ingin menyatakan cinta saat kelulusan?\n1. Ya\n2. Tidak\n> ");
    scanf("%d", &choice);
    if (choice == 1) {
        if (senpai.affinity >= 5) {
            printf("\nSenpai menerima cintamu! \u2764\ufe0f Ending Bahagia!\n");
        } else {
            printf("\nSenpai menolakmu dengan halus... Ending Sedih \U0001f622\n");
        }
    } else {
        printf("\nKamu menyimpan perasaanmu sendiri... Ending Netral.\n");
    }
}

void playGameFromStart() {
    Chapter* current = head;
    while (current != NULL) {
        printf("\nChapter %d:\n%s\n", current->chapterNumber, current->scene);
        switch (current->chapterNumber) {
            case 1: playChapter1(); break;
            case 2: playChapter2(); break;
            case 3: playChapter3(); break;
            case 5: playChapter5(); break;
            case 7: playChapter7(); return;
            default: break;
        }
        current = current->next;
    }
}

// Menu utama
void showMenu() {
    int pilihan, targetChapter;
    do {
        printf("\n=== Menu Utama ===\n");
        printf("1. Mulai permainan\n");
        printf("2. Lompat ke chapter tertentu\n");
        printf("3. List character\n");
        printf("4. Keluar game\n> ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                playGameFromStart();
                break;
            case 2:
                printf("Masukkan nomor chapter (1-7): ");
                scanf("%d", &targetChapter);
                jumpToChapter(targetChapter);
                break;
            case 3:
                listCharacters();
                break;
            case 4:
                printf("Terima kasih telah bermain!\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 4);
}

int main() {
    printf("=========================");
    printf("\nGame Otome Berbasis Teks\n");
    printf("Creator:\n- Indy Agustin\n- Grace Larisma Jaya\n- Rakha Atha Muhammad\n- Muhammad Mumtaaz Raihaan Thaariq\n- Muhammad Faatih Yusron\n");
    printf("=========================\n");

    addChapter(1, "Kamu melihat senpai dari kejauhan di pagi hari.");
    addChapter(2, "Senpai mulai menyapamu di koridor kampus.");
    addChapter(3, "Senpai bercerita tentang seseorang yang dia sukai.");
    addChapter(4, "Kamu merasa tidak semangat dan mulai menjauh.");
    addChapter(5, "Kamu mulai bangkit dan ingin bicara lagi.");
    addChapter(6, "Senpai mengajakmu ngobrol tentang masa depan.");
    addChapter(7, "Kelulusan datang. Saatnya menyatakan perasaan atau tidak.");

    addItem("Surat cinta");
    addItem("Cokelat");

    showInventory();
    showMenu();

    return 0;
}
