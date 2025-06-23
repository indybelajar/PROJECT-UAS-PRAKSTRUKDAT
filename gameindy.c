#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define MAX_CHARACTERS 5
// Struct inventory
typedef struct Item
{
    char name[50];
    struct Item *next;
} Item;

// Struct karakter
typedef struct
{
    char name[50];
    char birthdate[15];
    int affinity;
    int effort;
} Character;

// Struct untuk chapter
typedef struct Chapter
{
    int chapterNumber;
    char sinopsis[1000];
    struct Chapter *next;
} Chapter;

// chapter state untuk menyimpan riwayat poin
typedef struct
{
    int affinity[MAX_CHARACTERS]; // Array untuk menyimpan afinitas tiap karakter
    int effort[MAX_CHARACTERS];   // Array untuk menyimpan effort tiap karakter
    int completed;                // 0 = belum, 1 = sudah
} ChapterState;

ChapterState chapterStates[8]; // 0 tidak digunakan, 1-7 untuk chapter 1-7

// Variabel global
Item *inventory = NULL;
Character characters[MAX_CHARACTERS] = {
    {"Thallah", "12 Oktober", 0, 0},
    {"Indy", "3 Maret", 0, 0},
    {"Luna", "20 April", 0, 0},
    {"Boby", "3 Juni", 0, 0},
    {"Rakhan", "30 Juli", 0, 0}};

Character *senpai = &characters[0]; // default karakter utama
Chapter *head = NULL;
Chapter *currentChapter = NULL;
int isPaused = 0;
int delay = 5;
int delay2 = 2;
// Deklarasi awal fungsi chapter
void playChapter1();
void playChapter2();
void playChapter3();
void playChapter4();
void playChapter5();
void playChapter6();
void playChapter7();
void playGraduationDay();

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void saveChapterState(int chapterNumber)
{
    if (chapterNumber >= 1 && chapterNumber < 8)
    {
        for (int i = 0; i < MAX_CHARACTERS; i++)
        {
            chapterStates[chapterNumber].affinity[i] = characters[i].affinity;
            chapterStates[chapterNumber].effort[i] = characters[i].effort;
        }
        chapterStates[chapterNumber].completed = 1;
    }
}
void loadStateFromPreviousChapter(int chapterNumber)
{
    if (chapterNumber == 1)
    {
        for (int i = 0; i < MAX_CHARACTERS; i++)
        {
            characters[i].affinity = 0;
            characters[i].effort = 0;
        }
        return;
    }
    if (chapterNumber >= 2 && chapterNumber < 8 && chapterStates[chapterNumber - 1].completed)
    {
        for (int i = 0; i < MAX_CHARACTERS; i++)
        {
            characters[i].affinity = chapterStates[chapterNumber - 1].affinity[i];
            characters[i].effort = chapterStates[chapterNumber - 1].effort[i];
        }
    }
}

void typewriterEffect(const char *text, int delay)
{
    int skip = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (_kbhit()) // jika ada tombol ditekan
        {
            char ch = _getch();
            if (ch == 13) // ENTER = ASCII 13
            {
                skip = 1;
            }
        }

        if (skip)
        {
            printf("%s", &text[i]); // cetak sisa teks langsung
            break;
        }
        else
        {
            printf("%c", text[i]);
            fflush(stdout);
            Sleep(delay);
        }
    }
}

void addItem(char name[])
{
    Item *newItem = (Item *)malloc(sizeof(Item));
    strcpy(newItem->name, name);
    newItem->next = inventory;
    inventory = newItem;
}

void useItem(char name[])
{
    Item *temp = inventory, *prev = NULL;
    while (temp != NULL && strcmp(temp->name, name) != 0)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("Item tidak ditemukan.\n");
        return;
    }
    if (prev == NULL)
    {
        inventory = temp->next;
    }
    else
    {
        prev->next = temp->next;
    }
    free(temp);
    printf("Item '%s' telah digunakan.\n", name);
}

void showInventory()
{
    printf("\nInventory:\n");
    Item *temp = inventory;
    while (temp != NULL)
    {
        printf("- %s\n", temp->name);
        temp = temp->next;
    }
}

void addChapter(int chapterNumber, const char *scene )
{
    Chapter *newChap = (Chapter *)malloc(sizeof(Chapter));
    newChap->chapterNumber = chapterNumber;
    strcpy(newChap->scene, scene);
    newChap->next = NULL;

    if (head == NULL)
    {
        head = newChap;
    }
    else
    {
        Chapter *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newChap;
    }
}

void listCharacters()
{
    printf("\n=== Daftar Karakter ===\n");
    for (int i = 0; i < MAX_CHARACTERS; i++)
    {
        printf("Nama: %s\n", characters[i].name);
        printf("Tanggal Lahir: %s\n", characters[i].birthdate);
        printf("Afinitas: %d\n", characters[i].affinity);
        printf("Effort: %d\n\n", characters[i].effort);
    }
}

int gameMenu()
{
    int choice;
    typewriterEffect("\n=== MENU PAUSE ===\n", delay2);
    typewriterEffect("1. Lanjutkan permainan\n", delay2);
    typewriterEffect("2. Buka inventory\n", delay2);
    typewriterEffect("3. Keluar permainan\n> ", delay2);
    scanf("%d", &choice);
    clearInputBuffer();
    switch (choice)
    {
    case 1:
        isPaused = 0;
        return 1;
    case 2:
        showInventory();
        return gameMenu();
    case 3:
        typewriterEffect("Terimakasih telah bermain:)\n", delay2);
        exit(0);
    default:
        typewriterEffect("Pilihan tidak valid.\n", delay2);
        return gameMenu();
    }
}
void jumpToChapter(int targetChapter)
{
    Chapter *current = head;
    char fullText[600];

    if (currentChapter == NULL)
    {
        printf("Chapter tidak ditemukan.\n");
        return;
    }

    while (currentChapter != NULL)
    {
        loadStateFromPreviousChapter(currentChapter->chapterNumber);
        typewriterEffect("\n=================\n", delay2);
        snprintf(fullText, sizeof(fullText), "Chapter %d:\n%s\n", currentChapter->chapterNumber, currentChapter->scene);
        typewriterEffect(fullText, delay2);
        typewriterEffect("=================\n", delay2);

        switch (currentChapter->chapterNumber)
        {
        case 1:
            playChapter1();
            break;
        case 2:
            playChapter2();
            break;
        case 3:
            playChapter3();
            break;
        case 4:
            playChapter4();
            break;
        case 5:
            playChapter5();
            break;
        case 6:
            playChapter6();
            break;
        case 7:
            playChapter7();
            break;
        case 8:
            playGraduationDay();
            return;
        default:
            break;
        }

        saveChapterState(currentChapter->chapterNumber);
        currentChapter = currentChapter->next;
    }
}

void playChapter1()
{
    int choice;
    typewriterEffect("\nHari 1:\n", delay);
    typewriterEffect("Hari pertama dari sisa 7 hari ini dimulai. Aku melihat Thallah sedang membereskan berkas-berkas sendirian di aula OSIS. Dia tampak sedikit lelah. Ini kesempatanku!\n", delay);
    typewriterEffect("Sementara itu, aku datang bersama Indy dan Luna, dua sahabatku yang selalu mendukungku dalam diam. Kami bertiga memang dekat sejak awal masuk sekolah", delay);
    typewriterEffect("Indy: \"Rima, kamu yakin mau nyamperin Kak Thallah?\"\n", delay);
    typewriterEffect("Luna: \"Ayo semangat, Rima! Kami di sini support kamu!\n", delay);

    typewriterEffect("Rima: (Berjalan mendekat) \"Kak Thallah, butuh bantuan?\"\n", delay);
    typewriterEffect("\nApa yang akan kamu lakukan?\n", delay);
    printf("1. Tawarkan bantuan spesifik\n");
    printf("2. Tawarkan minuman\n");
    printf("3. Hanya bertanya\n");
    printf("0. Menu\n> ", delay);
    scanf("%d", &choice);
    clearInputBuffer();

    if (choice == 0)
    {
        if (!gameMenu())
            return;
        playChapter1();
        return;
    }

    switch (choice)
    {
    case 1:
        senpai->affinity += 3;
        senpai->effort += 5;
        typewriterEffect("\nRima: \"Melihat berkas sebanyak itu pasti bikin pusing. Mau aku bantu rapikan atau kumpulkan sesuai abjad?\"\n", delay);
        typewriterEffect("Thallah: (Tersenyum lega) \"Eh, Rima. Kebetulan sekali. Bisa tolong kumpulkan berkas ini sesuai abjad? Aku sudah mau tumbang rasanya.\"\n", delay);
        typewriterEffect("(Indy dan Luna saling pandang dan ikut membantu dengan cepat.)\n", delay);
        typewriterEffect("Indy: \"Kami bantu juga ya, Kak. Lebih cepat lebih baik!\"\n", delay);
        typewriterEffect("Luna: \"Asal jangan disuruh ngitung, aku lemah di matematika!\" (tertawa ringan)\n", delay);
        typewriterEffect("Kami mulai mengobrol ringan, membicarakan persiapan kelulusan Thallah.\n", delay);
        typewriterEffect("(Poin Effort Rima: +5, Poin Kedekatan Thallah: +3)\n", delay);
        break;
    case 2:
        senpai->affinity += 2;
        senpai->effort += 4;
        typewriterEffect("\nRima: \"Kak Thallah kelihatan capek. Mau aku belikan minum? Ada teh dingin atau kopi panas?\"\n", delay);
        typewriterEffect("Thallah: (Tersenyum tipis) \"Wah, makasih banyak, Rima. Teh dingin kedengarannya enak.\"\n", delay);
        typewriterEffect("Indy langsung berlari ke kantin.\n", delay);
        typewriterEffect("Indy: \"Gue yang beliin! Kalian fokus di sini aja.\"\n", delay);
        typewriterEffect("Sementara itu Luna dan aku membantu membereskan berkas.\n", delay);
        typewriterEffect("(Poin Effort Rima: +4, Poin Kedekatan Thallah: +2)\n", delay);
        break;
    case 3:
        senpai->affinity += 1;
        senpai->effort += 2;
        typewriterEffect("\nRima: \"Kak Thallah sibuk banget ya?\"\n", delay);
        typewriterEffect("Thallah: (Menghela nafas) \"Lumayan, Ma. Berkas-berkas akhir tahun ini banyak sekali.\"\n", delay);
        typewriterEffect("Luna menepuk bahuku pelan.\n", delay);
        typewriterEffect("Luna: \"Ayo bantuin, jangan bengong aja.\"\n", delay);
        typewriterEffect("Aku ikut membantu walau tak banyak bicara.\n", delay);
        typewriterEffect("(Poin Effort Rima: +2, Poin Kedekatan Thallah: +1)\n", delay);
        break;
    default:
        printf("Pilihan tidak valid.\n", delay);
        playChapter1();
        return;
    }
    typewriterEffect("\n(Bersamaan dengan itu, Boby dan temannya Rakhan memperhatikan dari kejauhan.)\n", delay);
    typewriterEffect("Boby: \"Eh, lihat tuh, Rakhan. Si Rima lagi nyamperin Thallah lagi.\"\n", delay);
    typewriterEffect("Rakhan: \"Dia gigih juga ya. Tapi lu bukan pernah deket juga sama Rima, By?\"\n", delay);
    typewriterEffect("Boby: (tersenyum miring) \"Heh, itu cerita lama. Tapi... siapa tahu dia masih ingat gue.\"\n", delay);
    typewriterEffect("(Narasi: Aku merasa seperti ada yang memperhatikan. Tapi kuabaikan, karena fokusku sekarang hanya satu—Thallah.)\n", delay);
}

void playChapter2()
{
    int choice;
    typewriterEffect("\nHari 2:\n", delay);
    typewriterEffect("Sore ini, Rima dan Thallah sedang berada di ruang ekskul fotografi, memeriksa hasil jepretan dari acara sekolah minggu lalu. Suasana hening, hanya terdengar suara klik mouse. Thallah tiba-tiba menghela napas panjang.\n", delay);
    typewriterEffect("Thallah: (Menghela napas, melihat hasil jepretan) \"Kadang aku lelah, Rima. Banyak harapan di pundakku.\"\n", delay);

    typewriterEffect("\nApa yang akan kamu lakukan?\n", delay);
    printf("1. Beri dukungan penuh\n");
    printf("2. Beri saran praktis\n");
    printf("3. Ubah topik (menghibur)\n");
    printf("0. Menu\n> ");
    scanf("%d", &choice);
    clearInputBuffer();

    if (choice == 0)
    {
        if (!gameMenu())
            return;
        playChapter2();
        return;
    }
    switch (choice)
    {
    case 1:
        senpai->effort += 7;
        senpai->affinity += 5;
        typewriterEffect("\nRima: \"Kak Thallah juga manusia, Kak. Wajar kalau capek. Tapi aku yakin Kakak pasti bisa melewati semua ini. Kakak hebat!\"\n", delay);
        typewriterEffect("Thallah: (Menoleh, tatapannya melembut) \"Kamu benar. Aku belum pernah bilang ini ke siapa-siapa, tapi... aku takut. Takut tidak bisa membanggakan orang tuaku, takut salah memilih jalan.\"\n", delay);
        typewriterEffect("Thallah mulai terbuka, menceritakan kegelisahan terdalamnya. Dia bercerita tentang tekanan dari keluarga, tentang mimpi besarnya untuk menjadi fotografer profesional, tapi juga keraguan yang menyelimutinya. Aku mendengarkan dengan saksama, sesekali memberi semangat.\n", delay);
        typewriterEffect("Rima: \"Kak Thallah pasti bisa. Kakak punya bakat, punya semangat. Aku percaya itu. Aku akan selalu mendukung Kakak.\"\n", delay);
        typewriterEffect("Thallah: (Tersenyum tulus) \"Terima kasih, Rima. Kamu satu-satunya orang yang bisa kuajak bicara tentang ini.\"\n", delay);
        typewriterEffect("(Poin Effort Rima: +7, Poin Kedekatan Thallah: +5)\n", delay);
        break;
    case 2:
        senpai->effort += 5;
        senpai->affinity += 3;
        typewriterEffect("\nRima: \"Mungkin Kakak perlu istirahat sebentar? Atau coba cerita apa yang membuat Kakak merasa begitu?\"\n", delay);
        typewriterEffect("Thallah: (Mendesah) \"Ya, mungkin aku memang butuh istirahat. Aku... aku cuma merasa beban terlalu banyak.\"\n", delay);
        typewriterEffect("Thallah tidak langsung menceritakan detail, tapi dia mengisyaratkan tentang tekanan ujian dan harapan keluarga. Aku mencoba menghiburnya dengan bercerita tentang pengalamanku sendiri.\n", delay);
        typewriterEffect("Rima: \"Aku juga kadang meraSsa begitu, Kak. Tapi percayalah, Kakak tidak sendiri.\"\n", delay);
        typewriterEffect("Thallah: \"Terima kasih, Rima. Kamu baik sekali.\"\n", delay);
        typewriterEffect("(Poin Effort Rima: +5, Poin Kedekatan Thallah: +3)\n", delay);
        break;
    case 3:
        senpai->effort += 3;
        senpai->affinity += 1;
        typewriterEffect("\nRima: \"Fokus sama jepretan ini saja, Kak. Lihat, yang ini bagus banget! Kakak punya bakat seni yang luar biasa.\"\n", delay);
        typewriterEffect("Thallah: (Tersenyum tipis) \"Haha, kamu bisa saja. Memang menyenangkan kalau melihat hasil yang bagus.\"\n", delay);
        typewriterEffect("Thallah tidak melanjutkan keluh kesahnya. Dia memang tersenyum, tapi aku merasa dia tidak sepenuhnya terbuka. Aku mencoba membuat suasana lebih ceria dengan membahas teknik fotografi.\n", delay);
        typewriterEffect("(Poin Effort Rima: +3, Poin Kedekatan Thallah: +1)\n", delay);
        break;
    default:
        printf("Pilihan tidak valid.\n", delay);
        playChapter2();
        return;
    }
}

void playChapter3()
{
    int choice;
    typewriterEffect("\nHari 3:\n", delay);
    typewriterEffect("Rima dan Thallah sedang mencari referensi buku untuk proyek fotografi terakhir kami. Suasana perpustakaan yang sepi membuat kami bisa mengobrol lebih santai.\n", delay);
    typewriterEffect("Di meja sebelah, Indy dan Luna sedang mengerjakan laporan ospek, sesekali mencuri pandang ke arah kami sambil senyum-senyum kecil.\n", delay);
    typewriterEffect("Jauh di ujung rak, Boby dan Rakhan terlihat sedang memilih buku musik. Suara tawa kecil Rakhan sempat membuatku menoleh.\n", delay);
    typewriterEffect("Tiba-tiba, Thallah menghentikan langkahnya, menatapku dengan ekspresi ragu.\n", delay);
    typewriterEffect("Thallah: \"Rima, aku mau cerita sesuatu padamu...\"\n", delay);
    typewriterEffect("Rima: \"(Dalam hati: Deg-degan, semoga ini yang kuharapkan... Jantungku berdetak tak karuan.)\"\n", delay);
    typewriterEffect("Thallah: (Menghela napas) \"Aku... aku sebenarnya suka sama seseorang. Tapi aku bingung harus bagaimana. Aku tidak tahu apakah dia juga suka padaku atau tidak.\"\n", delay);
    typewriterEffect("Dunia seolah berhenti berputar. Kata-katanya menghantamku telak, lebih keras dari bentakan mana pun.\n", delay);
    typewriterEffect("Thallah: \"Dia itu teman SMP-ku dulu. Kami sudah dekat sebulan ini sebelum kelulusan SMA. Gimana ya Ma?\"\n", delay);

    // Pilihan untuk Rima
    typewriterEffect("\nApa yang akan kamu lakukan?\n", delay);
    printf("1. Marah\n");
    printf("2. Sedih\n");
    printf("3. Dengarkan sampai habis\n");
    printf("0. Menu\n>");
    scanf("%d", &choice);
    clearInputBuffer();

    if (choice == 0)
    {
        if (!gameMenu())
            return;
        playChapter3();
        return;
    }
    switch (choice)
    {
    case 1:
        senpai->affinity -= 7;
        senpai->effort -= 10;
        typewriterEffect("\n(Rima menunjukkan kekesalan, ekspresi terkejut dan kesal)\n", delay);
        typewriterEffect("Rima: \"(Suara sedikit tinggi, menahan amarah) Kak Thallah, kenapa baru cerita sekarang?! Kenapa harus padaku?\"\n", delay);
        typewriterEffect("Thallah: \"(Terkejut, ekspresi bingung dan sedikit kecewa) Eh? Ada apa, Rima? Maaf kalau mendadak... aku kira kamu akan mengerti.\"\n", delay);
        typewriterEffect("Indy dari meja sebelah terlihat ikut melirik, tampak khawatir, sementara Luna menggenggam tanganku diam-diam untuk menenangkan.\n", delay);
        typewriterEffect("Suasana menjadi canggung dan dingin. Aku merasa menyesal telah bereaksi seperti itu.\n", delay);
        typewriterEffect("Rima: \"(Dalam hati: Aku tidak seharusnya marah seperti itu. Tapi hatiku terasa hancur mendengar dia suka pada orang lain.)\"\n", delay);
        typewriterEffect("(Poin Effort Rima: -10, Poin Kedekatan Thallah: -7)\n", delay);
        break;
    case 2:
        senpai->affinity -= 3;
        senpai->effort -= 5;
        typewriterEffect("\n(Rima menunjukkan kesedihan, ekspresi mata berkaca-kaca.)\n", delay);
        typewriterEffect("Rima: \"(Suara pelan, mencoba menahan tangis) Oh... begitu ya, Kak. Aku... aku turut senang untuk Kakak.\"\n", delay);
        typewriterEffect("Thallah: \"(Khawatir, ekspresi cemas) Rima? Kamu kenapa? Kamu sakit? Wajahmu pucat.\"\n", delay);
        typewriterEffect("Boby melirik ke arah kami sejenak, mungkin merasa suasana tak nyaman. Rakhan menyikutnya dan berbisik pelan, lalu mereka berlalu.\n", delay);
        typewriterEffect("Aku tak bisa menyembunyikan kesedihanku. Thallah pun tampak bingung dan menghentikan ceritanya.\n", delay);
        typewriterEffect("(Poin Effort Rima: -5, Poin Kedekatan Thallah: -3)\n", delay);
        break;
    case 3:
        senpai->affinity += 7;
        senpai->effort += 10;
        typewriterEffect("\n(Rima menunjukkan ekspresi tenang, mencoba tersenyum.)\n", delay);
        typewriterEffect("Rima: \"(Mencoba tersenyum tulus meski hatiku sakit) Oh ya? Wah, Kak Thallah bisa suka juga ya. Ceritain dong, Kak. Seperti apa dia?\"\n", delay);
        typewriterEffect("Thallah: \"(Ekspresi nyaman dan bersemangat) Ah, Rima. Dia...\"\n", delay);
        typewriterEffect("Thallah mulai bercerita panjang lebar, sementara aku menatap ke arah Indy dan Luna. Mereka tersenyum menyemangatiku dari kejauhan.\n", delay);
        typewriterEffect("Di sisi lain perpustakaan, Boby tampak menatap kami sesaat sebelum kembali membaca. Aku bertanya-tanya... apakah dia tahu isi cerita Thallah?\n", delay);
        typewriterEffect("(Poin Effort Rima: +10, Poin Kedekatan Thallah: +7)\n", delay);
        break;
    default:
        printf("Pilihan tidak valid.\n");
        playChapter3();
        return;
    }
}

void playChapter4()
{
    int choice;
    typewriterEffect("\nHari 4: Dunia yang Kelabu\n", delay);
    typewriterEffect("(Latar: Kantin Sekolah, siang hari)\n", delay);
    typewriterEffect("(Narasi Rima): Aku terpuruk. Sepanjang hari keempat ini, aku seperti zombie yang berjalan tanpa jiwa.\n", delay);
    typewriterEffect("Setiap langkah terasa berat, dan setiap sudut sekolah seolah mengingatkanku pada Thallah dan ceritanya.\n", delay);
    typewriterEffect("Aku duduk sendirian di kantin, menyendok nasi tanpa rasa. Di meja lain, Indy dan Luna sedang ngobrol dengan heboh, tapi mereka sesekali melirik ke arahku dengan cemas.\n", delay);
    typewriterEffect("Boby sedang bermain gitar kecil sambil duduk bersama Rakhan di pojok ruangan, menyanyikan lagu mellow yang entah kenapa terasa menohok perasaanku.\n", delay);
    typewriterEffect("Thallah: (Mendekati meja Rima di kantin) \"Rima, kamu kenapa? Kelihatannya lesu sekali. Mau makan siang denganku dan teman-teman OSIS?\"\n", delay);

    typewriterEffect("\nApa yang akan kamu lakukan?\n", delay);
    printf("1. Tolak dengan alasan jujur\n");
    printf("2. Tolak dengan alasan umum\n");
    printf("3. Terima tawarannya (meski berat)\n");
    printf("0. Menu\n> ");
    scanf("%d", &choice);
    clearInputBuffer();
    if (choice == 0)
    {
        if (!gameMenu())
            return;
        playChapter4();
        return;
    }

    switch (choice)
    {
    case 1:
        senpai->affinity -= 1;
        senpai->effort -= 3;
        typewriterEffect("\nRima: (Suara pelan, menghindari kontak mata) \"Maaf, Kak Thallah. Aku... aku kurang enak badan hari ini. Mungkin aku butuh sendiri sebentar.\"\n", delay);
        typewriterEffect("Thallah: (Ekspresi khawatir) \"Oh, begitu. Baiklah, kalau ada apa-apa, jangan sungkan cerita ya.\"\n", delay);
        typewriterEffect("Indy langsung datang menghampiriku setelah Thallah pergi, duduk di sampingku tanpa bicara apa-apa. Kehadirannya saja sudah menenangkan.\n", delay);
        typewriterEffect("(Narasi Rima): Aku tahu Thallah peduli, tapi aku tidak bisa menahan kesedihanku. Hari ini rasanya makin gelap.\n", delay);
        typewriterEffect("(Poin Effort Rima: -3, Poin Kedekatan Thallah: -1)\n", delay);
        break;
    case 2:
        senpai->affinity -= 1;
        senpai->effort -= 2;
        typewriterEffect("\nRima: (Memaksakan senyum) \"Ah, maaf Kak. Aku sudah bawa bekal. Aku juga masih ada tugas yang harus diselesaikan.\"\n", delay);
        typewriterEffect("Thallah: (Mengangguk, sedikit kecewa) \"Oh, begitu. Baiklah. Jangan terlalu diporsir ya tugasnya.\"\n", delay);
        typewriterEffect("Luna mengirimiku chat pendek: *'Kami tunggu di taman belakang kalau kamu butuh angin segar.'*\n", delay);
        typewriterEffect("(Narasi Rima): Aku tahu mereka semua berusaha menghiburku, tapi aku tidak bisa berpura-pura baik-baik saja. Aku hanya ingin menghilang.\n", delay);
        typewriterEffect("(Poin Effort Rima: -2, Poin Kedekatan Thallah: -1)\n", delay);
        break;
    case 3:
        senpai->affinity += 2;
        senpai->effort += 5;
        typewriterEffect("\nRima: (Mengambil napas dalam, memaksakan diri) \"Baiklah, Kak. Aku ikut.\"\n", delay);
        typewriterEffect("Thallah: (Tersenyum lega) \"Nah, begitu dong! Ayo, kita gabung.\"\n", delay);
        typewriterEffect("(Narasi Rima): Aku mengikuti Thallah ke meja teman-teman OSIS. Di sana sudah ada Luna yang memberiku senyum lembut, dan Indy yang meletakkan botol air di depanku tanpa berkata apa-apa.\n", delay);
        typewriterEffect("Boby menyambut dengan petikan gitar lembut, sementara Rakhan menyodorkan keripik sambil berkata, \"Biar gak terlalu pahit harinya.\"\n", delay);
        typewriterEffect("Aku ikut tertawa, meski dalam hati rasanya perih. Tapi kehadiran mereka... sedikit menyembuhkan.\n", delay);
        typewriterEffect("(Poin Effort Rima: +5, Poin Kedekatan Thallah: +2)\n", delay);
        break;
    default:
        printf("Pilihan tidak valid.\n");
        playChapter4();
        return;
    }
}

void playChapter5()
{
    int choice;
    typewriterEffect("\nHari 5: Bangkit dan Bertekad\n", delay);
    typewriterEffect("(Latar: Kamar Rima, pagi hari)\n", delay);
    typewriterEffect("(Narasi Rima): Setelah semalaman merenung, menatap langit-langit kamar yang gelap, aku memutuskan. Cukup sudah!\n", delay);
    typewriterEffect("Aku tidak bisa terus-menerus larut dalam kesedihan dan penyesalan. Cinta itu butuh perjuangan, bukan hanya harapan yang pupus.\n", delay);
    typewriterEffect("Aku harus merebut Thallah. Lagipula, mereka baru dekat seminggu. Masih ada harapan, kan? Aku tidak akan menyerah begitu saja pada takdir ini.\n", delay);
    typewriterEffect("Pagi itu, aku kembali bersemangat. Senyumku kembali mengembang, langkahku lebih ringan, dan tatapanku kembali tajam, penuh tekad.\n", delay);
    typewriterEffect("Aku akan berjuang untuk perasaanku, tidak peduli seberapa kecil kemungkinannya.\n", delay);
    typewriterEffect("Indy bahkan memberiku semangat lewat pesan: *'Hari ini kamu harus bersinar, Ri. Biar dia lihat siapa kamu sebenarnya.'*\n", delay);
    typewriterEffect("Aku menatap kaca. Ini aku, Rima. Dan aku akan memperjuangkan cintaku.\n", delay);

    typewriterEffect("\nApa yang akan kamu lakukan?\n", delay);
    printf("1. Dekati dengan perhatian/bantuan\n");
    printf("2. Dekati dengan ajakan khusus\n");
    printf("3. Dekati dengan pamer bakat/prestasi\n");
    printf("0. Menu\n> ");
    scanf("%d", &choice);
    clearInputBuffer();

    if (choice == 0)
    {
        if (!gameMenu())
            return;
        playChapter5();
        return;
    }

    switch (choice)
    {
    case 1:
        senpai->affinity += 4;
        senpai->effort += 7;
        typewriterEffect("\n(Narasi Rima): Aku akan kembali bersikap ceria di depan Thallah, bahkan lebih dari biasanya.\n", delay);
        typewriterEffect("Aku menemani dia menyusun laporan OSIS, sesekali membawakan camilan yang dibuat Luna semalam.\n", delay);
        typewriterEffect("Aku juga membantunya mengatur file foto lomba. \"Wah, Rima kamu detail banget ya,\" katanya sambil tersenyum.\n", delay);
        typewriterEffect("Aku merasa ada harapan. Sedikit demi sedikit, aku ingin jadi bagian yang penting di hidupnya.\n", delay);
        typewriterEffect("(Poin Effort Rima: +7, Poin Kedekatan Thallah: +4)\n", delay);
        break;
    case 2:
        senpai->affinity += 5;
        senpai->effort += 8;
        typewriterEffect("\n(Narasi Rima): Aku mengajaknya bicara di lorong usai pelajaran selesai.\n", delay);
        typewriterEffect("Rima: \"Kak, minggu ini kita belum sempat ngobrol banyak ya. Gimana kalau kita brainstorming proyek foto sore ini? Aku tahu tempat yang sepi dan bagus.\"\n", delay);
        typewriterEffect("Thallah tampak kaget, lalu tersenyum kecil. \"Boleh juga. Kamu serius banget ya sama proyek ini. Aku suka.\"\n", delay);
        typewriterEffect("Di kejauhan, Rakhan melihat kami, lalu mengedip iseng padaku. Entah kenapa, aku merasa didukung, meski tak diucapkan langsung.\n", delay);
        typewriterEffect("(Poin Effort Rima: +8, Poin Kedekatan Thallah: +5)\n", delay);
        break;
    case 3:
        senpai->affinity += 3;
        senpai->effort += 6;
        typewriterEffect("\n(Narasi Rima): Hari ini ada sesi latihan publikasi OSIS. Aku tahu Thallah akan hadir sebagai pengarah dokumentasi.\n", delay);
        typewriterEffect("Aku menampilkan hasil editanku dengan percaya diri, dibantu sedikit masukan dari Boby kemarin malam.\n", delay);
        typewriterEffect("Saat presentasiku selesai, Thallah bertepuk tangan pertama kali. \"Bagus banget, Rima. Kamu berkembang cepat.\"\n", delay);
        typewriterEffect("Aku tersenyum puas, walau jantungku berdetak kencang. Hari ini, dia melihatku lebih dari biasanya.\n", delay);
        typewriterEffect("(Poin Effort Rima: +6, Poin Kedekatan Thallah: +3)\n", delay);
        break;
    default:
        printf("Pilihan tidak valid.\n");
        playChapter5();
        return;
    }
}

void playChapter6()
{
    int choice;
    typewriterEffect("\nHari 6: Pukulan Kedua\n", delay);
    typewriterEffect("(Latar: Area Pengumuman UTBK/SNBT di Sekolah)\n", delay);
    typewriterEffect("(Narasi Rima): Hari itu adalah pengumuman UTBK. Suasana kampus sangat ramai,\n", delay);
    typewriterEffect("dipenuhi teriakan kebahagiaan dari mereka yang diterima dan isak tangis kekecewaan dari yang belum berhasil.\n", delay);
    typewriterEffect("Aku melihat Indy dan Luna berdiri tak jauh dariku, saling menggenggam tangan, menahan degup jantung.\n", delay);
    typewriterEffect("Boby berdiri di sisi papan pengumuman, membantu guru membagikan cetakan hasil, sedangkan Rakhan sedang duduk santai di tangga, memainkan gitarnya sambil menghibur siswa yang menunggu.\n", delay);
    typewriterEffect("Lalu... aku melihat Thallah berlari ke arahku, wajahnya berseri-seri, senyumnya paling lebar yang pernah kulihat.\n", delay);
    typewriterEffect("Thallah: \"Rima! Aku diterima! Aku diterima di jurusan impianku, Teknik Industri!\"\n", delay);
    typewriterEffect("Dia memelukku dengan spontan, membuat Luna dan Indy saling bertukar pandang dari jauh.\n", delay);
    typewriterEffect("(Narasi Rima): Pelukannya terasa hangat, tapi kata-kata selanjutnya langsung menusuk jantungku.\n", delay);
    typewriterEffect("Thallah: \"Dan... dan dia juga satu kampus denganku! Dia di jurusan Sastra Indonesia!\"\n", delay);
    typewriterEffect("Aku melihat senyum itu. Senyum yang... bukan untukku.\n", delay);

    typewriterEffect("\nApa yang akan kamu lakukan?\n", delay);
    printf("1. Berikan selamat dengan tulus\n");
    printf("2. Ubah topik/alihkan perhatian\n");
    printf("3. Pergi dengan alasan mendesak\n");
    printf("0. Menu\n> ");
    scanf("%d", &choice);
    clearInputBuffer();

    if (choice == 0)
    {
        if (!gameMenu())
            return;
        playChapter6();
        return;
    }

    switch (choice)
    {
    case 1:
        senpai->affinity += 4;
        senpai->effort += 8;
        typewriterEffect("\nRima: (Memaksakan senyum selebar mungkin) \"Wah, selamat ya, Kak Thallah! Aku turut senang sekali untuk Kakak! Semoga sukses di kampus impian!\"\n", delay);
        typewriterEffect("Thallah: (Tersenyum cerah) \"Makasih banyak, Rima! Kamu memang teman baikku!\"\n", delay);
        typewriterEffect("(Narasi Rima): Kata 'teman' itu... seperti palu godam.\n", delay);
        typewriterEffect("Aku menoleh ke arah Luna dan Indy. Mereka tersenyum lembut, seolah tahu hatiku hancur tapi memilih diam.\n", delay);
        typewriterEffect("(Poin Effort Rima: +8, Poin Kedekatan Thallah: +4)\n", delay);
        break;
    case 2:
        senpai->affinity += 0;
        senpai->effort += 2;
        typewriterEffect("\nRima: (Mengganti ekspresi, sedikit panik) \"Wah, itu bagus sekali, Kak! Ngomong-ngomong, Kakak udah lihat daftar anak-anak baru OSIS tahun depan? Banyak wajah baru lho.\"\n", delay);
        typewriterEffect("Thallah: (Sedikit mengernyit) \"Oh, ya? Belum sempat lihat. Tapi... kamu kenapa, Rima? Kok ganti topik gitu?\"\n", delay);
        typewriterEffect("Rakhan yang duduk di tangga mengangkat alis ke arahku, seolah membaca kegugupanku.\n", delay);
        typewriterEffect("(Narasi Rima): Aku tahu ekspresi Thallah berubah. Tapi aku tidak siap membicarakan rasa sakitku.\n", delay);
        typewriterEffect("(Poin Effort Rima: +2, Poin Kedekatan Thallah: +0)\n", delay);
        break;
    case 3:
        senpai->affinity -= 3;
        senpai->effort -= 5;
        typewriterEffect("\nRima: (Ekspresi menahan sakit, buru-buru) \"Selamat, Kak! Maaf, aku harus pergi sekarang. Ada urusan mendadak!\"\n", delay);
        typewriterEffect("Aku berbalik, nyaris berlari. Suara Thallah memanggilku samar-samar dari belakang.\n", delay);
        typewriterEffect("Thallah: \"Eh, Rima? Ada apa? Hati-hati!\"\n", delay);
        typewriterEffect("(Narasi Rima): Aku tak menjawab. Air mataku mulai jatuh bahkan sebelum aku melewati gerbang sekolah.\n", delay);
        typewriterEffect("Di lorong, aku hampir menabrak Boby. Dia tampak ingin bertanya, tapi melihat wajahku, dia hanya diam dan menepuk bahuku perlahan.\n", delay);
        typewriterEffect("(Poin Effort Rima: -5, Poin Kedekatan Thallah: -3)\n", delay);
        break;
    default:
        printf("Pilihan tidak valid.\n");
        playChapter6();
        return;
    }
}

void playChapter7()
{
    int choice;
    typewriterEffect("\nHari 7: Dilema dan Melodi Sedih\n", delay);
    typewriterEffect("(Latar: Lingkungan Sekolah, Menjelang Akhir Hari Sekolah)\n", delay);
    typewriterEffect("(Narasi Rima): Sejak pengumuman UTBK, aku dan Thallah tidak lagi berkomunikasi seintensif sebelumnya.\n", delay);
    typewriterEffect("Aku menjaga jarak, hatiku terlalu sakit untuk sekadar bercanda dengannya seperti biasa.\n", delay);
    typewriterEffect("Aku tidak lagi mencari-cari alasan untuk menemuinya, tidak lagi mengirim pesan-pesan iseng.\n", delay);
    typewriterEffect("Ini adalah hari terakhir kami di sekolah sebelum kelulusannya. Setelah ini, semuanya akan berubah.\n", delay);
    typewriterEffect("Aku merasa hari ini berlalu begitu lambat, sekaligus begitu cepat.\n", delay);
    typewriterEffect("Indy sempat menepuk pundakku di koridor, matanya seolah tahu isi hatiku.\n", delay);
    typewriterEffect("Luna mengajak duduk sebentar di taman belakang, hanya untuk diam bersamaku, tanpa kata-kata.\n", delay);

    typewriterEffect("\n(Latar: Malam Hari, Kamar Rima)\n", delay);
    typewriterEffect("(Narasi Rima): Suara gitar akustik Rakhan yang ia unggah di story malam ini menemani kesendirianku.\n", delay);
    typewriterEffect("Lagu sedih itu... pas sekali dengan suasana hatiku.\n", delay);
    typewriterEffect("Aku memandang langit-langit kamarku yang gelap. Malam ini adalah penentuan.\n", delay);
    typewriterEffect("Boby bahkan mengirim chat singkat tadi: 'Rima, apapun pilihanmu besok, pastikan kamu nggak nyesel ya.'\n", delay);

    typewriterEffect("\n(POV Thallah)\n", delay);
    typewriterEffect("(Narasi Thallah): Aku agak bingung. Tumben sekali Rima, si adik kelas yang selalu cerewet dan kocak itu, tidak lagi mendekatiku.\n", delay);
    typewriterEffect("Biasanya dia selalu punya bahan obrolan, selalu ada di sekitarku, bahkan di saat aku senang maupun sedih.\n", delay);
    typewriterEffect("Aku bahkan sempat terkejut dia memelukku kemarin saat pengumuman, rasanya aneh, tapi nyaman.\n", delay);
    typewriterEffect("Apakah dia sibuk dengan persiapan kuliahnya? Atau aku membuat kesalahan saat bercerita tentang dia...\n", delay);
    typewriterEffect("tentang cowok yang aku suka? Aku jadi sedikit merindukan kehadirannya yang selalu ceria dan caranya membuatku tertawa lepas.\n", delay);
    typewriterEffect("Hari-hari terakhir di sekolah ini terasa lebih sepi tanpanya, dan entah kenapa, ada perasaan aneh yang mengganjal di dadaku. Ini seperti ada yang kurang.\n", delay);

    typewriterEffect("\n(Kembali ke POV Rima)\n", delay);
    typewriterEffect("(Narasi Rima): Aku harus memutuskan. Haruskah aku menyatakan perasaanku sekarang?\n", delay);
    typewriterEffect("Di hari kelulusan besok, di tengah perpisahan dan euforia kelulusan?\n", delay);
    typewriterEffect("Atau aku harus menunggu lain kali, saat semuanya sudah lebih tenang, dan aku punya strategi yang lebih matang...\n", delay);
    typewriterEffect("mungkin setelah dia dan seniornya itu... ah, entahlah.\n", delay);

    typewriterEffect("\nMalam Sebelum Kelulusan: Pilihan Penentu\n", delay);
    printf("1. TEMBAK BESOK SAAT KELULUSAN\n");
    printf("2. JANGAN TEMBAK BESOK\n");
    printf("0. Menu\n> ");
    scanf("%d", &choice);
    clearInputBuffer();

    if (choice == 0)
    {
        if (!gameMenu())
            return;
        playChapter7();
        return;
    }

    switch (choice)
    {
    case 1:
        senpai->effort += 10;
        typewriterEffect("\n(Narasi Rima): Setelah pergolakan batin yang panjang, mengingat semua 'effort' yang sudah kukerahkan,\n", delay);
        typewriterEffect("semua kesabaran dan dukungan yang kuberikan padanya, aku memutuskan untuk...\n", delay);
        typewriterEffect("menembak besok di hari kelulusan. Ini adalah pertaruhan terakhirku.\n", delay);
        typewriterEffect("Indy dan Luna mengangguk saat kuceritakan niatku. Boby membalas chat dengan emoji acungan jempol.\n", delay);
        typewriterEffect("Dan lagu Rakhan yang masih terputar... seolah jadi soundtrack keputusanku malam ini.\n", delay);
        typewriterEffect("(Poin Effort Rima: +10)\n", delay);
        break;
    case 2:
        typewriterEffect("\n(Narasi Rima): Mungkin terlalu riskan. Ada kemungkinan aku akan ditolak mentah-mentah,\n", delay);
        typewriterEffect("dan itu akan merusak momen kelulusan kami berdua, dan mungkin persahabatan yang sudah terjalin.\n", delay);
        typewriterEffect("Lebih baik biarkan waktu yang menjawab. Biarkan dia tahu perasaanku dengan caraku sendiri, tanpa perlu kata-kata.\n", delay);
        typewriterEffect("Indy memelukku lama saat aku bilang aku mundur. Luna tampak lega, meski matanya berkaca-kaca.\n", delay);
        typewriterEffect("Boby hanya mengetik: 'Itu juga keputusan berani. Kamu tahu apa yang terbaik.'\n", delay);
        typewriterEffect("Dan gitar Rakhan masih bernyanyi... tentang rasa yang tak harus diungkapkan secara langsung.\n", delay);
        typewriterEffect("(Poin Effort Rima: +0)\n", delay);
        break;
    default:
        printf("Pilihan tidak valid.\n");
        playChapter7();
        return;
    }
}

void playGraduationDay()
{
    int choice;
    typewriterEffect("\nHari Kelulusan: Detik-detik Penentu\n", delay);
    typewriterEffect("(Latar: Aula Sekolah, Acara Kelulusan)\n", delay);
    typewriterEffect("(Narasi Rima): Pagi harinya, aku merasakan jantungku berdegup kencang, lebih kencang dari lari maraton yang pernah kulakukan.\n", delay);
    typewriterEffect("Setelah acara kelulusan selesai, di tengah keramaian siswa yang berfoto dan berpamitan, aku mencari Thallah.\n", delay);
    typewriterEffect("Aku melihatnya sedang tertawa bersama teman-temannya. Ia tampak begitu gagah, bahkan dalam seragam yang sudah sedikit kusut.\n", delay);
    typewriterEffect("Aku menarik napas dalam, memantapkan hati, dan berjalan mendekatinya.\n", delay);
    typewriterEffect("Rima: \"Kak Thallah,\" panggilku, suaraku sedikit tercekat.\n", delay);
    typewriterEffect("Thallah: (Menoleh, senyumnya sedikit memudar melihat ekspresi seriusku) \"Eh, Rima. Ada apa? Tumben serius begitu.\"\n", delay);

    typewriterEffect("\nApa yang ingin kamu lakukan?\n", delay);
    printf("1. Nyatakan perasaan dengan surat\n");
    printf("2. Ungkapkan langsung secara lisan\n");
    printf("0. Jangan nyatakan perasaan (pilihan dari Chapter 7)\n> ");
    scanf("%d", &choice);
    clearInputBuffer();

    if (choice == 0)
    {
        typewriterEffect("Kelulusan pun tiba, dan Thallah lulus tanpa mengetahui perasaanku yang sesungguhnya.\n", delay);
        typewriterEffect("Aku hanya bisa menatap punggungnya yang semakin menjauh, membawa serta sebagian hatiku.\n", delay);
        typewriterEffect("Namun aku tahu, rasa tidak harus selalu diucapkan untuk menjadi nyata.\n", delay);
        typewriterEffect("Aku, Indy, Luna, dan Boby berfoto bersama di halaman sekolah. Meskipun hatiku sedikit kosong, aku tahu aku tidak sendiri.\n", delay);
        typewriterEffect("Rakhan bahkan memainkan lagu perpisahan, seolah menjadi latar dari kisah yang tak sempat diselesaikan.\n", delay);
        typewriterEffect("\n=== ENDING: Tidak Pernah Diungkapkan ===\n", delay);

        return;
    }

    // Jika pemain memilih 1 atau 2, tampilkan adegan awal yang sama
    if (choice == 1)
    {
        typewriterEffect("\nRima: \"Aku... aku mau ngomong sesuatu,\" kataku, suaraku sedikit bergetar.\n", delay);
        typewriterEffect("Aku mengeluarkan sebuah surat yang sudah kubuat semalaman, mencurahkan semua perasaanku di sana.\n", delay);
        typewriterEffect("\"Aku tahu ini mungkin mendadak, dan mungkin kamu akan terkejut. Tapi aku... aku suka sama kamu, Kak Thallah.\"\n", delay);
        typewriterEffect("\"Aku tahu kamu suka orang lain, tapi aku hanya ingin kamu tahu perasaanku.\"\n", delay);
    }
    else if (choice == 2)
    {
        typewriterEffect("\nRima: \"Kak Thallah, ini mungkin berat buat Kakak dengar. Tapi selama ini...\"\n", delay);
        typewriterEffect("\"Aku punya perasaan lebih dari sekadar junior ke senior. Aku suka sama Kakak.\"\n", delay);
    }

    // Evaluasi ending berdasarkan skor
    if (senpai->effort > 30 && senpai->affinity > 15)
    {
        // ENDING DITERIMA
        typewriterEffect("\n(Narasi Rima): Thallah terdiam, matanya melebar. Wajahnya menunjukkan ekspresi terkejut, sedikit bingung,\n", delay);
        typewriterEffect("lalu perlahan sebuah senyum tipis, namun tulus, mengembang di bibirnya.\n", delay);
        if (choice == 1)
        {
            typewriterEffect("Dia mengambil surat itu dari tanganku.\n", delay);
        }
        else
        {
            typewriterEffect("Dia menatapku dalam-dalam, pandangannya penuh pengertian.\n", delay);
        }
        typewriterEffect("Thallah: \"Rima... aku tidak menyangka kamu akan mengatakan ini. Jujur, aku terkejut.\n", delay);
        typewriterEffect("Tapi... aku juga merasakan sesuatu yang aneh selama seminggu ini.\n", delay);
        typewriterEffect("Sejak kamu mendengarkan ceritaku dengan sabar, sejak kamu tetap di sisiku meskipun aku banyak cerita tentang dia...\n", delay);
        typewriterEffect("Aku mulai menyadari ada perasaan lain yang tumbuh. Kamu selalu ada, dan kamu membuatku nyaman. Rasanya berbeda dengan yang lain.\"\n", delay);
        typewriterEffect("Dia menarik napas. \"Mungkin ini gila, tapi... beri aku waktu, ya? Tapi... ya, aku mau mencoba bersamamu.\"\n", delay);
        typewriterEffect("(Narasi Rima): Senyumnya semakin lebar, dan kali ini, hatiku benar-benar lega.\n", delay);
        typewriterEffect("Kami pun tersenyum satu sama lain, di tengah riuhnya suasana kelulusan, seolah hanya ada kami berdua di sana.\n", delay);
        typewriterEffect("\n=== TRUE ENDING: Bersama ===\n", delay);
    }
    else
    {
        // ENDING DITOLAK
        typewriterEffect("\n(Narasi Rima): Thallah terdiam, matanya melebar. Wajahnya menunjukkan ekspresi terkejut, sedikit bingung,\n", delay);
        typewriterEffect("lalu perlahan sebuah senyum tipis dan sendu mengembang di bibirnya.\n", delay);
        if (choice == 1)
        {
            typewriterEffect("Dia menggenggam tanganku lembut, menolak surat yang kupegang.\n", delay);
        }
        else
        {
            typewriterEffect("Dia menatapku dengan tatapan kasihan.\n", delay);
        }
        typewriterEffect("Thallah: \"Rima... aku hargai keberanian dan kejujuranmu. Aku... aku minta maaf.\"\n", delay);
        typewriterEffect("\"Aku sudah menganggapmu seperti adik sendiri, dan kamu adalah teman terbaik selama di sekolah ini.\n", delay);
        typewriterEffect("Tapi... perasaanku sudah ada untuk orang lain, dan itu tidak bisa aku paksakan. Aku harap kamu mengerti.\"\n", delay);
        typewriterEffect("\"Aku harap kita tetap bisa jadi teman baik, ya? Jangan jadi canggung gara-gara ini.\"\n", delay);
        typewriterEffect("(Narasi Rima): Meskipun sakit, aku mengangguk pelan, berusaha tersenyum. Air mataku hampir jatuh, tapi aku menahannya.\n", delay);
        typewriterEffect("Mungkin ini adalah akhir dari kisahku dengannya sebagai lebih dari teman, tapi setidaknya, aku sudah jujur pada perasaanku.\n", delay);
        typewriterEffect("Kelulusan Thallah yang seharusnya menjadi momen bahagia, kini terasa begitu getir.\n", delay);
        typewriterEffect("\n=== BAD ENDING: Tidak Terbalas ===\n", delay);
    }
}

void playGameFromStart()
{
    currentChapter = head;
    jumpToChapter(1);
}

int wait()
{
    char input[10];
    fgets(input, sizeof(input), stdin);

    // Menghapus newline '\n' dari input
    input[strcspn(input, "\n")] = 0;

    if (strcmp(input, "1") == 0)
    {
        return 1; // Skip
    }
    return 0; // Lanjut
}

void showProlog()
{
    typewriterEffect("\n=== PROLOG ===\t\t\t\t\t(Enter = Lanjut, 1 = Skip prolog)\n", delay);
    // Hari ke-1 MPLS
    typewriterEffect("(Latar: Pagi hari, Lapangan SMA, Masa Pengenalan Lingkungan Sekolah (MPLS) Hari 1)\n", delay);
    typewriterEffect("Langit biru cerah menyambut hari pertama Masa Pengenalan Lingkungan Sekolah.\n", delay);
    typewriterEffect("Aku, Rima, si adik kelas yang masih kosong tentang seluk-beluk SMA ini, berjalan mengikuti barisan,\n", delay);
    typewriterEffect("berusaha tidak tersesat di antara ratusan siswa baru. Di tengah riuhnya suara, para siswa baru yang\n", delay);
    typewriterEffect("gugup, dan anggota OSIS yang berteriak memberi arahan, pandanganku terhenti pada satu sosok.\n", delay);
    if (wait())
        return;

    typewriterEffect("Seorang kakak kelas dengan name tag \"Thallah\". Rambutnya klimis, tertata rapi, dan matanya berbinar\n", delay);
    typewriterEffect("di balik lensa kamera DSLR yang ia gunakan untuk memfoto jalannya MPLS. Senyumnya... ah, senyumnya\n", delay);
    typewriterEffect("seolah menerangi seluruh lapangan, bahkan di bawah terik matahari yang menyengat.\n", delay);
    if (wait())
        return;

    typewriterEffect("Ia berdiri di sekitar lapangan sembari memfoto temannya yang sedang menjelaskan jadwal hari ini.\n", delay);
    typewriterEffect("Setelah selesai menjelaskan, ia mendatangi temannya dan mengajaknya bicara. Suaranya tenang tapi tegas,\n", delay);
    typewriterEffect("namun entah kenapa terdengar begitu menenangkan bagiku. Beberapa kali matanya bersitatap denganku\n", delay);
    typewriterEffect("saat ia melintas, dan setiap kali itu terjadi, jantungku berdegup lebih kencang. Hari itu, interaksi kami\n", delay);
    typewriterEffect("hanya sebatas sapaan singkat dan anggukan kepala.\n", delay);
    if (wait())
        return;

    // Hari ke-2 MPLS
    typewriterEffect("(Latar: Lapangan SMA, MPLS Hari 2)\n", delay);
    typewriterEffect("Pada hari kedua MPLS, aku melihatnya kembali! Namun, kali ini ia tidak berseragam OSIS,\n", delay);
    typewriterEffect("melainkan berdiri di tengah lapangan, memimpin sebuah demo ekskul. Suaranya masih tenang tapi tegas saat\n", delay);
    typewriterEffect("ia menjelaskan tentang Ekskul Fotografi yang ia pimpin. Matanya tampak berbinar saat ia menjelaskan fungsi\n", delay);
    typewriterEffect("lensa, komposisi, dan cahaya.\n", delay);
    if (wait())
        return;

    typewriterEffect("Kemudian, ia menawari para murid baru untuk mencoba kamera yang ia pegang. Aku yang melihat kesempatan emas ini,\n", delay);
    typewriterEffect("tanpa ragu langsung mengangkat tangan. Ia menghampiriku perlahan, dan dalam bayanganku, ia seperti seorang\n", delay);
    typewriterEffect("kesatria yang menghampiri putri. Dia menjelaskan cara menggunakan kamera dengan lembut, dengan sabar membimbing\n", delay);
    typewriterEffect("tanganku menekan tombol shutter dan mengatur focus. Itu adalah pengalaman pertama dan paling berkesan bagiku\n", delay);
    typewriterEffect("selama MPLS.\n", delay);
    if (wait())
        return;

    typewriterEffect("Sejak momen itu, di benakku, ini bukan hanya sekadar MPLS. Ini adalah misi PDKT, misi untuk\n", delay);
    typewriterEffect("mendekati Thallah! Aku mulai berusaha mencari tahu lebih banyak tentangnya. Hal pertama yang kutahu,\n", delay);
    typewriterEffect("Thallah adalah anggota OSIS dan ketua Ekskul Fotografi. Tanpa pikir panjang, aku memutuskan untuk berniat\n", delay);
    typewriterEffect("menjadi anggota OSIS dan mendaftar ke Ekskul Fotografi.\n", delay);
    if (wait())
        return;

    typewriterEffect("Tentu saja, alasan utamaku masuk ke kedua organisasi itu adalah untuk selalu berada di dekatnya. Supaya aku\n", delay);
    typewriterEffect("bisa menanyakan hal-hal sepele, atau sekadar menawarkan bantuan kecil. Singkat cerita, dengan sedikit\n", delay);
    typewriterEffect("keberuntungan dan usaha keras, aku berhasil masuk ke dalam dua organisasi tersebut!\n", delay);
    if (wait())
        return;

    typewriterEffect("Sedikit yang Rima tahu, Thallah ternyata siswa Kelas 12, yang berarti akan lulus sebentar lagi.\n", delay);
    typewriterEffect("Aku menjalani hari-hari sibukku sebagai anggota OSIS dan Ekskul Fotografi bersama Thallah selama semester satu.\n", delay);
    typewriterEffect("Aku selalu mencari cara untuk berinteraksi dengannya, membantunya dalam tugas OSIS, atau sekadar menemaninya\n", delay);
    typewriterEffect("di ruang fotografi. Kami banyak tertawa, banyak berbagi cerita. Perasaanku padanya semakin dalam setiap harinya.\n", delay);
    if (wait())
        return;

    typewriterEffect("Namun, setelah masuk ke Semester 2, Thallah mulai fokus penuh untuk mempersiapkan diri mengikuti berbagai\n", delay);
    typewriterEffect("ujian akhir dan UTBK. Proses PDKT-ku kembali dari nol. Aku berusaha keras untuk tidak mengganggunya.\n", delay);
    typewriterEffect("Aku tidak lagi sering mengajaknya bicara, tidak lagi menawarkan bantuan sepele. Aku tahu ia butuh fokus,\n", delay);
    typewriterEffect("dan aku tidak ingin menjadi pengganggu.\n", delay);
    if (wait())
        return;

    typewriterEffect("Sampai pada saat di mana seluruh ujian itu sudah selesai dan perjalanannya menuju kelulusan semakin dekat.\n", delay);
    typewriterEffect("Hanya tersisa 7 hari lagi sampai kelulusan Thallah. Aku bertekad untuk kembali mendekatinya, tidak peduli\n", delay);
    typewriterEffect("seberapa singkat waktu yang tersisa. Ini adalah kesempatanku.\n", delay);
    if (wait())
        return;
}

void showMenu()
{
    int pilihan, targetChapter;
    do
    {
        typewriterEffect("\n=== Menu Utama ===\n", delay);
        typewriterEffect("1. Mulai permainan\n", delay);
        typewriterEffect("2. Lompat ke chapter tertentu\n", delay);
        typewriterEffect("3. List character\n", delay);
        typewriterEffect("4. Keluar game\n> ", delay);
        scanf("%d", &pilihan);
        clearInputBuffer();

        switch (pilihan)
        {
        case 1:
            showProlog();
            playGameFromStart();
            break;
        case 2:
            typewriterEffect("Masukkan nomor chapter (1-7): ", delay2);
            scanf("%d", &targetChapter);
            clearInputBuffer();
            jumpToChapter(targetChapter);
            break;
        case 3:
            listCharacters();
            break;
        case 4:
            typewriterEffect("Terima kasih telah bermain!\n", delay2);
            break;
        default:
            typewriterEffect("Pilihan tidak valid.\n", delay2);
        }
    } while (pilihan != 4);
}

int main()
{
    typewriterEffect("(Info: Tekan ENTER kapan saja untuk skip tulisan lambat.)\n", delay2);
    typewriterEffect("Tekan ENTER untuk mulai...)\n\n", delay2);
    typewriterEffect("=========================", delay2);
    typewriterEffect("\nGame Otome: A Week Before Graduate I Try to Ask My Senpai to be My Boyfriend\n", delay2);
    typewriterEffect("Creator:\n- Indy Agustin\n- Grace Larisma Jaya\n- Rakha Atha Muhammad\n- Muhammad Mumtaaz Raihaan Thaariq\n- Muhammad Faatih Yusron\n", delay2);
    typewriterEffect("=========================", delay2);

    addChapter(1, "Pendekatan Awal");
    addChapter(2, "Saling Terbuka");
    addChapter(3, "Pukulan Tak Terduga");
    addChapter(4, "Dunia yang Kelabu");
    addChapter(5, "Bangkit dan Bertekad");
    addChapter(6, "Pukulan Kedua");
    addChapter(7, "Dilema dan Melodi Sedih");
    addChapter(8, "Detik-detik Penentu");

    addItem("Surat cinta");
    addItem("Cokelat");

    showInventory();
    showMenu();

    return 0;
}
