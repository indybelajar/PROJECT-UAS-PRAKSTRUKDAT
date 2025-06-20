#include <stdio.h>
#include <string.h>
// FaatihKorkmaz
// Rakha Atha Muhammad
// Struct class Kurnia
typedef struct {
    char name[20];
    int healthBonus;
    int strengthBonus;
    int agilityBonus;
} Class;

// Struct gender
typedef struct {
    char name[10];
    int healthBonus;
    int strengthBonus;
    int agilityBonus;
} Gender;

// Struct karakter
typedef struct {
    char name[50];
    Gender gender;
    Class class;
    int health;
    int strength;
    int agility;
} Character;

// Tampilkan status karakter
void tampilkanStatus(Character player) {
    printf("\n=== Status Karakter ===\n");
    printf("Nama     : %s\n", player.name);
    printf("Gender   : %s\n", player.gender.name);
    printf("Class    : %s\n", player.class.name);
    printf("Health   : %d\n", player.health);
    printf("Strength : %d\n", player.strength);
    printf("Agility  : %d\n", player.agility);
}

// Tampilkan daftar item
void tampilkanItem() {
    printf("\n=== Daftar Item ===\n");
    printf("- Sword\n");
    printf("- Shield\n");
    printf("- Armor\n");
    printf("- Dagger\n");
    printf("- Spear\n");
}

// Buat karakter
Character createCharacter(Class classList[], int classCount, Gender genderList[], int genderCount) {
    Character player;
    player.health = 100;
    player.strength = 10;
    player.agility = 10;

    printf("\n=== Create Your Character ===\n");
    printf("Nama: ");
    scanf(" %[^\n]%*c", player.name);

    // Pilih gender
    printf("\nPilih Gender:\n");
    for (int i = 0; i < genderCount; i++) {
        printf("%d. %s (Strength +%d, Agility +%d)\n",
               i + 1,
               genderList[i].name,
               genderList[i].strengthBonus,
               genderList[i].agilityBonus);
    }
    printf("Pilihan Anda: ");
    int genderChoice;
    scanf("%d", &genderChoice);

    if (genderChoice < 1 || genderChoice > genderCount) {
        printf("Pilihan tidak valid. Default Male.\n");
        player.gender = genderList[0];
    } else {
        player.gender = genderList[genderChoice - 1];
    }

    player.strength += player.gender.strengthBonus;
    player.agility += player.gender.agilityBonus;

    // Pilih class
    printf("\nPilih Class:\n");
    for (int i = 0; i < classCount; i++) {
        printf("%d. %s (Health +%d, Strength +%d, Agility +%d)\n",
               i + 1,
               classList[i].name,
               classList[i].healthBonus,
               classList[i].strengthBonus,
               classList[i].agilityBonus);
    }
    printf("Pilihan Anda: ");
    int classChoice;
    scanf("%d", &classChoice);

    if (classChoice < 1 || classChoice > classCount) {
        printf("Pilihan tidak valid. Default Barbarian.\n");
        player.class = classList[0];
    } else {
        player.class = classList[classChoice - 1];
    }

    player.health += player.class.healthBonus;
    player.strength += player.class.strengthBonus;
    player.agility += player.class.agilityBonus;

    return player;
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
    printf("\nMulai Permainan? (Y/N): ");
    scanf(" %c", &mulai);

    if (mulai == 'Y' || mulai == 'y') {
        // Daftar class
        Class classList[] = {
            {"Barbarian", 10, 5, 0},
            {"Thief", 0, 0, 15},
            {"Knight", 20, 3, 0},
            {"Archer", 0, 2, 10}
        };
        int classCount = sizeof(classList) / sizeof(classList[0]);

        // Daftar gender
        Gender genderList[] = {
            {"Male", 5, 0},
            {"Female", 0, 5}
        };
        int genderCount = sizeof(genderList) / sizeof(genderList[0]);

        Character player = createCharacter(classList, classCount, genderList, genderCount);
        tampilkanStatus(player);
        tampilkanItem();
        printf("\nPetualangan dimulai!\n");
    } else {
        printf("\nPermainan dibatalkan.\n");
    }

    return 0;
}
