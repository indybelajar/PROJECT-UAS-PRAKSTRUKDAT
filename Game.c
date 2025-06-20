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

// Struct untuk chapter/hari
typedef struct Chapter {
    int day;
    char scene[200];
    struct Chapter* next;
} Chapter;

// Variabel global
Item* inventory = NULL;
Character senpai = {"Raka", "20 April", 0};
Chapter* head = NULL;

// Tambah item ke inventory
void addItem(char name[]) {
    Item* newItem = (Item*)malloc(sizeof(Item));
    strcpy(newItem->name, name);
    newItem->next = inventory;
    inventory = newItem;
    printf("Item '%s' ditambahkan ke inventory.\n", name);
}

// Hapus item dari inventory (pakai item)
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

// Tambah chapter ke linked list
void addChapter(int day, char* scene) {
    Chapter* newChap = (Chapter*)malloc(sizeof(Chapter));
    newChap->day = day;
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

// Cari karakter
void searchCharacter(char* keyword) {
    if (strstr(senpai.name, keyword) || strstr(senpai.birthdate, keyword)) {
        printf("Karakter ditemukan:\nNama: %s\nLahir: %s\nAfinitas: %d\n", senpai.name, senpai.birthdate, senpai.affinity);
    } else {
        printf("Karakter tidak ditemukan.\n");
    }
}

// Main game logic
void playGame() {
    Chapter* current = head;
    int choice;
    while (current != NULL) {
        printf("\nHari %d:\n%s\n", current->day, current->scene);

        if (current->day == 3) {
            printf("Pilihanmu saat senpai cerita tentang cewek lain:\n");
            printf("1. Marah\n2. Sedih\n3. Dengerin sampe habis\n> ");
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

        if (current->day == 5) {
            printf("\nGunakan item untuk menarik perhatian senpai?\n1. Cokelat\n2. Tidak\n> ");
            scanf("%d", &choice);
            if (choice == 1) {
                useItem("Cokelat");
                senpai.affinity += 2;
                printf("Senpai tersenyum menerima cokelatmu. Afinitas meningkat!\n");
            }
        }

        if (current->day == 7) {
            printf("Senpai terlihat heran kamu tidak ngobrol lagi...\n");
            printf("Apakah kamu ingin menyatakan cinta saat kelulusan?\n1. Ya\n2. Tidak\n> ");
            scanf("%d", &choice);
            if (choice == 1) {
                if (senpai.affinity >= 5) {
                    printf("\nSenpai menerima cintamu! ❤️ Ending Bahagia!\n");
                } else {
                    printf("\nSenpai menolakmu dengan halus... Ending Sedih 😢\n");
                }
                return;
            } else {
                printf("\nKamu menyimpan perasaanmu sendiri... Ending Netral.\n");
                return;
            }
        }

        current = current->next;
    }
}

int main() {
    char mulai;

    printf("=========================\n");
    printf("Game Sederhana Berbasis Teks\n");
    printf("Creator:\n");
    printf("- Indy Agustin\n");
    printf("- Grace Larisma Jaya\n");
    printf("- Rakha Atha Muhammad\n");
    printf("- Muhammad Mumtaaz Raihaan Thaariq\n");
    printf("- Muhammad Faatih Yusron\n");
    printf("=========================\n");
    printf("\nMulai Permainan? (Y/N): ");
    scanf(" %c", &mulai);

    if (mulai != 'Y' && mulai != 'y') {
        printf("Permainan dibatalkan. Terima kasih!\n");
        return 0;
    }

    // Tambah cerita
    addChapter(1, "Kamu bertemu senpai di ospek. Kesan pertama baik.");
    addChapter(2, "Kalian mulai terbuka satu sama lain.");
    addChapter(3, "Senpai cerita dia suka orang lain. Kamu merasa aneh...");
    addChapter(4, "Kamu ngedown dan menghindari senpai.");
    addChapter(5, "Kamu bangkit dan ingin perjuangkan senpai.");
    addChapter(6, "Senpai cerita bahwa orang yang dia suka kuliah di kampus yang sama.");
    addChapter(7, "Hari terakhir ospek. Apakah kamu akan menyatakan cinta?");

    // Tambah item ke inventory
    addItem("Surat cinta");
    addItem("Cokelat");
    showInventory();

    // Main game
    playGame();

    // Fitur pencarian karakter
    printf("\n\nCari karakter berdasarkan nama/tanggal lahir:\nKetik keyword: ");
    char keyword[50];
    scanf("%s", keyword);
    searchCharacter(keyword);

    return 0;
}
