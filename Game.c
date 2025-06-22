#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

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
Character senpai = {"Thallah", "12 Oktober", 0};
Chapter* head = NULL;
Chapter* currentChapter = NULL;
int isPaused = 0;
int delay = 5;

// Deklarasi awal fungsi chapter
void playChapter1();
void playChapter2();
void playChapter3();
void playChapter5();
void playChapter7();

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//efek typewiter
void typewriterEffect(const char *text, int delay) {
    for (int i = 0; text[i] != '\0'; i++) {
        printf("%c", text[i]);
        fflush(stdout);
        Sleep(delay); // delay dalam milidetik
    }
}


void addItem(char name[]) {
    Item* newItem = (Item*)malloc(sizeof(Item));
    strcpy(newItem->name, name);
    newItem->next = inventory;
    inventory = newItem;
}

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

void showInventory() {
    printf("\nInventory:\n");
    Item* temp = inventory;
    while (temp != NULL) {
        printf("- %s\n", temp->name);
        temp = temp->next;
    }
}

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

void listCharacters() {
    printf("\n=== Daftar Karakter ===\n");
    printf("Nama: %s\n", senpai.name);
    printf("Tanggal Lahir: %s\n", senpai.birthdate);
    printf("Afinitas: %d\n", senpai.affinity);
}

int gameMenu() {
    int choice;
    printf("\n=== MENU PAUSE ===\n");
    printf("1. Lanjutkan permainan\n");
    printf("2. Buka inventory\n");
    printf("3. Keluar permainan\n> ");
    scanf("%d", &choice);
    clearInputBuffer();
    switch (choice) {
        case 1:
            isPaused = 0;
            return 1;
        case 2:
            showInventory();
            return gameMenu();
        case 3:
            exit(0);
        default:
            printf("Pilihan tidak valid.\n");
            return gameMenu();
    }
}

void jumpToChapter(int targetChapter) {
    Chapter* current = head;
    while (current != NULL) {
        if (current->chapterNumber == targetChapter) {
            currentChapter = current;
            break;
        }
        current = current->next;
    }
    if (currentChapter == NULL) {
        printf("Chapter tidak ditemukan.\n");
        return;
    }

    while (currentChapter != NULL) {
        printf("\n=================\n");
        printf("Chapter %d:\n%s\n", currentChapter->chapterNumber, currentChapter->scene);
        printf("=================\n");

        switch (currentChapter->chapterNumber) {
            case 1: playChapter1(); break;
            case 2: playChapter2(); break;
            case 3: playChapter3(); break;
            case 5: playChapter5(); break;
            case 7: playChapter7(); return;
            default: break;
        }
        currentChapter = currentChapter->next;
    }
}

void playChapter1() {
    int choice;
    printf("MC: Ah, indahnya hari ini.\n(Kakak kelas datang)\nMC: (Apa yang harus aku lakukan?)\n");
    printf("1. Ucapkan salam\n2. Abaikan saja\n0. Menu\n> ");
    scanf("%d", &choice);
    clearInputBuffer();
    if (choice == 0) {
        if (!gameMenu()) return;
        playChapter1();
        return;
    }
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
    printf("Senpai: Hai, kamu siswa baru ya?\nMC: (Bagaimana ya jawabnya?)\n");
    printf("1. Jawab dengan semangat\n2. Jawab singkat saja\n0. Menu\n> ");
    scanf("%d", &choice);
    clearInputBuffer();
    if (choice == 0) {
        if (!gameMenu()) return;
        playChapter2();
        return;
    }
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
    printf("MC: (Apa reaksimu?)\n1. Marah\n2. Sedih\n3. Dengarkan sampai habis\n0. Menu\n> ");
    scanf("%d", &choice);
    clearInputBuffer();
    if (choice == 0) {
        if (!gameMenu()) return;
        playChapter3();
        return;
    }
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
    printf("\nGunakan item untuk menarik perhatian senpai?\n1. Cokelat\n2. Tidak\n0. Menu\n> ");
    scanf("%d", &choice);
    clearInputBuffer();
    if (choice == 0) {
        if (!gameMenu()) return;
        playChapter5();
        return;
    }
    if (choice == 1) {
        useItem("Cokelat");
        senpai.affinity += 2;
        printf("Senpai tersenyum menerima cokelatmu. Afinitas meningkat!\n");
    }
}

void playChapter7() {
    int choice;
    printf("Senpai terlihat bingung kamu tidak mengobrol lagi...\n");
    printf("Apakah kamu ingin menyatakan cinta saat kelulusan?\n1. Ya\n2. Tidak\n0. Menu\n> ");
    scanf("%d", &choice);
    clearInputBuffer();
    if (choice == 0) {
        if (!gameMenu()) return;
        playChapter7();
        return;
    }
    if (choice == 1) {
        if (senpai.affinity >= 5) {
            printf("\nSenpai menerima cintamu! ❤️ Ending Bahagia!\n");
        } else {
            printf("\nSenpai menolakmu dengan halus... Ending Sedih 😢\n");
        }
    } else {
        printf("\nKamu menyimpan perasaanmu sendiri... Ending Netral.\n");
    }
}

void playGameFromStart() {
    currentChapter = head;
    jumpToChapter(1);
}

int wait() {
    char input[10];
    fgets(input, sizeof(input), stdin);

    // Menghapus newline '\n' dari input
    input[strcspn(input, "\n")] = 0;

    if (strcmp(input, "1") == 0) {
        return 1; // Skip
    }
    return 0; // Lanjut
}

void showProlog() {
    typewriterEffect("\n=== PROLOG ===\t\t\t\t\t(Enter = Lanjut, 1 = Skip prolog)\n", delay);
    // Hari ke-1 MPLS
    typewriterEffect("(Latar: Pagi hari, Lapangan SMA, Masa Pengenalan Lingkungan Sekolah (MPLS) Hari 1)\n", delay);
    typewriterEffect("Langit biru cerah menyambut hari pertama Masa Pengenalan Lingkungan Sekolah.\n", delay);
    typewriterEffect("Aku, Rima, si adik kelas yang masih kosong tentang seluk-beluk SMA ini, berjalan mengikuti barisan,\n", delay);
    typewriterEffect("berusaha tidak tersesat di antara ratusan siswa baru. Di tengah riuhnya suara, para siswa baru yang\n", delay);
    typewriterEffect("gugup, dan anggota OSIS yang berteriak memberi arahan, pandanganku terhenti pada satu sosok.\n", delay);
    if (wait()) return;

    typewriterEffect("Seorang kakak kelas dengan name tag \"Thallah\". Rambutnya klimis, tertata rapi, dan matanya berbinar\n", delay);
    typewriterEffect("di balik lensa kamera DSLR yang ia gunakan untuk memfoto jalannya MPLS. Senyumnya... ah, senyumnya\n", delay);
    typewriterEffect("seolah menerangi seluruh lapangan, bahkan di bawah terik matahari yang menyengat.\n", delay);
    if (wait()) return;

    typewriterEffect("Ia berdiri di sekitar lapangan sembari memfoto temannya yang sedang menjelaskan jadwal hari ini.\n", delay);
    typewriterEffect("Setelah selesai menjelaskan, ia mendatangi temannya dan mengajaknya bicara. Suaranya tenang tapi tegas,\n", delay);
    typewriterEffect("namun entah kenapa terdengar begitu menenangkan bagiku. Beberapa kali matanya bersitatap denganku\n", delay);
    typewriterEffect("saat ia melintas, dan setiap kali itu terjadi, jantungku berdegup lebih kencang. Hari itu, interaksi kami\n", delay);
    typewriterEffect("hanya sebatas sapaan singkat dan anggukan kepala.\n", delay);
    typewriterEffect("=======================\n", delay);
    if (wait()) return;

    // Hari ke-2 MPLS
    typewriterEffect("(Latar: Lapangan SMA, MPLS Hari 2)\n", delay);
    typewriterEffect("Pada hari kedua MPLS, aku melihatnya kembali! Namun, kali ini ia tidak berseragam OSIS,\n", delay);
    typewriterEffect("melainkan berdiri di tengah lapangan, memimpin sebuah demo ekskul. Suaranya masih tenang tapi tegas saat\n", delay);
    typewriterEffect("ia menjelaskan tentang Ekskul Fotografi yang ia pimpin. Matanya tampak berbinar saat ia menjelaskan fungsi\n", delay);
    typewriterEffect("lensa, komposisi, dan cahaya.\n", delay);
    if (wait()) return;

    typewriterEffect("Kemudian, ia menawari para murid baru untuk mencoba kamera yang ia pegang. Aku yang melihat kesempatan emas ini,\n", delay);
    typewriterEffect("tanpa ragu langsung mengangkat tangan. Ia menghampiriku perlahan, dan dalam bayanganku, ia seperti seorang\n", delay);
    typewriterEffect("kesatria yang menghampiri putri. Dia menjelaskan cara menggunakan kamera dengan lembut, dengan sabar membimbing\n", delay);
    typewriterEffect("tanganku menekan tombol shutter dan mengatur focus. Itu adalah pengalaman pertama dan paling berkesan bagiku\n", delay);
    typewriterEffect("selama MPLS.\n", delay);
    if (wait()) return;

    typewriterEffect("Sejak momen itu, di benakku, ini bukan hanya sekadar MPLS. Ini adalah misi PDKT, misi untuk\n", delay);
    typewriterEffect("mendekati Thallah! Aku mulai berusaha mencari tahu lebih banyak tentangnya. Hal pertama yang kutahu,\n", delay);
    typewriterEffect("Thallah adalah anggota OSIS dan ketua Ekskul Fotografi. Tanpa pikir panjang, aku memutuskan untuk berniat\n", delay);
    typewriterEffect("menjadi anggota OSIS dan mendaftar ke Ekskul Fotografi.\n", delay);
    if (wait()) return;

    typewriterEffect("Tentu saja, alasan utamaku masuk ke kedua organisasi itu adalah untuk selalu berada di dekatnya. Supaya aku\n", delay);
    typewriterEffect("bisa menanyakan hal-hal sepele, atau sekadar menawarkan bantuan kecil. Singkat cerita, dengan sedikit\n", delay);
    typewriterEffect("keberuntungan dan usaha keras, aku berhasil masuk ke dalam dua organisasi tersebut!\n", delay);
    if (wait()) return;

    typewriterEffect("Sedikit yang Rima tahu, Thallah ternyata siswa Kelas 12, yang berarti akan lulus sebentar lagi.\n", delay);
    typewriterEffect("Aku menjalani hari-hari sibukku sebagai anggota OSIS dan Ekskul Fotografi bersama Thallah selama semester satu.\n", delay);
    typewriterEffect("Aku selalu mencari cara untuk berinteraksi dengannya, membantunya dalam tugas OSIS, atau sekadar menemaninya\n", delay);
    typewriterEffect("di ruang fotografi. Kami banyak tertawa, banyak berbagi cerita. Perasaanku padanya semakin dalam setiap harinya.\n", delay);
    if (wait()) return;

    typewriterEffect("Namun, setelah masuk ke Semester 2, Thallah mulai fokus penuh untuk mempersiapkan diri mengikuti berbagai\n", delay);
    typewriterEffect("ujian akhir dan UTBK. Proses PDKT-ku kembali dari nol. Aku berusaha keras untuk tidak mengganggunya.\n", delay);
    typewriterEffect("Aku tidak lagi sering mengajaknya bicara, tidak lagi menawarkan bantuan sepele. Aku tahu ia butuh fokus,\n", delay);
    typewriterEffect("dan aku tidak ingin menjadi pengganggu.\n", delay);
    if (wait()) return;

    typewriterEffect("Sampai pada saat di mana seluruh ujian itu sudah selesai dan perjalanannya menuju kelulusan semakin dekat.\n", delay);
    typewriterEffect("Hanya tersisa 7 hari lagi sampai kelulusan Thallah. Aku bertekad untuk kembali mendekatinya, tidak peduli\n", delay);
    typewriterEffect("seberapa singkat waktu yang tersisa. Ini adalah kesempatanku.\n", delay);
    if (wait()) return;
}

void showMenu() {
    int pilihan, targetChapter;
    do {
        printf("\n=== Menu Utama ===\n");
        printf("1. Mulai permainan\n");
        printf("2. Lompat ke chapter tertentu\n");
        printf("3. List character\n");
        printf("4. Keluar game\n> ");
        scanf("%d", &pilihan);
        clearInputBuffer();

        switch (pilihan) {
            case 1:
                showProlog();
                playGameFromStart();
                break;
            case 2:
                printf("Masukkan nomor chapter (1-7): ");
                scanf("%d", &targetChapter);
                clearInputBuffer();
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
    printf("\nGame Otome: A Week Before Graduate I Try to Ask My Senpai to be My Boyfriend\n");
    printf("Creator:\n- Indy Agustin\n- Grace Larisma Jaya\n- Rakha Atha Muhammad\n- Muhammad Mumtaaz Raihaan Thaariq\n- Muhammad Faatih Yusron\n");
    printf("=========================");

    addChapter(1, "Kamu melihat Thallah dari kejauhan di pagi hari.");
    addChapter(2, "Thallah mulai menyapamu di koridor sekolah.");
    addChapter(3, "Thallah bercerita tentang seseorang yang dia sukai.");
    addChapter(4, "Kamu merasa tidak semangat dan mulai menjauh.");
    addChapter(5, "Kamu mulai bangkit dan ingin bicara lagi.");
    addChapter(6, "Thallah mengajakmu ngobrol tentang masa depan.");
    addChapter(7, "Kelulusan datang. Saatnya menyatakan perasaan atau tidak.");

    addItem("Surat cinta");
    addItem("Cokelat");

    showInventory();
    showMenu();

    return 0;
}
