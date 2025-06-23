#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

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
    char scene[500];
    struct Chapter *next;
} Chapter;

// chapter state untuk menyimpan riwayat poin
typedef struct
{
    int affinity;
    int effort;
    int completed; // 0 = belum, 1 = sudah
} ChapterState;

ChapterState chapterStates[8]; // 0 tidak digunakan, 1-7 untuk chapter 1-7

// Variabel global
Item *inventory = NULL;
Character senpai = {"Thallah", "12 Oktober", 0};
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

void showChapterPoints();
void sortAndShowChapterPoints(int sortByAffinity);

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
        chapterStates[chapterNumber].affinity = senpai.affinity;
        chapterStates[chapterNumber].effort = senpai.effort;
        chapterStates[chapterNumber].completed = 1;
    }
}

void loadStateFromPreviousChapter(int chapterNumber)
{
    if (chapterNumber == 1)
    {
        senpai.affinity = 0;
        senpai.effort = 0;
        return;
    }
    if (chapterNumber >= 2 && chapterNumber < 8 && chapterStates[chapterNumber - 1].completed)
    {
        senpai.affinity = chapterStates[chapterNumber - 1].affinity;
        senpai.effort = chapterStates[chapterNumber - 1].effort;
    }
}

// efek typewiter
// void typewriterEffect(const char *text, int delay)
// {
//     for (int i = 0; text[i] != '\0'; i++)
//     {
//         printf("%c", text[i]);
//         fflush(stdout);
//         Sleep(delay); // delay dalam milidetik
//     }
// }
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

void addChapter(int chapterNumber, char *scene)
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
    printf("Nama: %s\n", senpai.name);
    printf("Tanggal Lahir: %s\n", senpai.birthdate);
    printf("Afinitas: %d\n", senpai.affinity);
    printf("Effort: %d\n", senpai.effort); // Asumsi Effort = Affinity / 2
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

    while (current != NULL)
    {
        if (current->chapterNumber == targetChapter)
        {
            currentChapter = current;
            break;
        }
        current = current->next;
    }

    if (currentChapter == NULL)
    {
        printf("Chapter tidak ditemukan.\n");
        return;
    }

    // Mulai dari chapter yang dituju, lanjutkan sampai habis
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
            break;
        default:
            printf("Chapter belum tersedia.\n");
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
        senpai.affinity += 3;
        senpai.effort += 5;
        typewriterEffect("\nRima: \"Melihat berkas sebanyak itu pasti bikin pusing. Mau aku bantu rapikan atau kumpulkan sesuai abjad?\"\n", delay);
        typewriterEffect("Thallah: (Tersenyum lega) \"Eh, Rima. Kebetulan sekali. Bisa tolong kumpulkan berkas ini sesuai abjad? Aku sudah mau tumbang rasanya.\"\n", delay);
        typewriterEffect("Aku mengerjakan tugas itu dengan semangat, sesekali melirik Thallah yang tampak kelelahan.\n", delay);
        typewriterEffect("Kami mulai mengobrol ringan, membicarakan persiapan kelulusannya, tentang ujian-ujiannya yang melelahkan.\n", delay);
        typewriterEffect("Aku berusaha menciptakan suasana nyaman, melontarkan candaan kecil yang membuatnya tersenyum.\n", delay);
        typewriterEffect("Rasanya, jarak di antara kami mulai memudar lagi.\n", delay);
        typewriterEffect("(Poin Effort Rima: +5, Poin Kedekatan Thallah: +3)\n", delay);
        break;
    case 2:
        senpai.affinity += 2;
        senpai.effort += 4;
        typewriterEffect("\nRima: \"Kak Thallah kelihatan capek. Mau aku belikan minum? Ada teh dingin atau kopi panas?\"\n", delay);
        typewriterEffect("Thallah: (Tersenyum tipis) \"Wah, makasih banyak, Rima. Teh dingin kedengarannya enak. Aku cuma perlu rapikan berkas ini sedikit lagi.\"\n", delay);
        typewriterEffect("Setelah membawakannya teh dingin, aku menawarkan diri untuk membantunya merapikan berkas.\n", delay);
        typewriterEffect("Kami mengobrol santai tentang kegiatannya setelah ujian, dan aku sesekali melontarkan candaan ringan yang membuatnya tersenyum.\n", delay);
        typewriterEffect("(Poin Effort Rima: +4, Poin Kedekatan Thallah: +2)\n", delay);
        break;
    case 3:
        senpai.affinity += 1;
        senpai.effort += 2;
        typewriterEffect("\nRima: \"Kak Thallah sibuk banget ya?\"\n", delay);
        typewriterEffect("Thallah: (Menghela nafas) \"Lumayan, ma. Berkas-berkas akhir tahun ini banyak sekali.\"\n", delay);
        typewriterEffect("Aku hanya berdiri di sana sebentar, merasa canggung untuk menawarkan bantuan lebih jauh.\n", delay);
        typewriterEffect("Thallah kembali sibuk dengan berkasnya. Aku memutuskan untuk membantu membereskan beberapa map yang tercecer di meja.\n", delay);
        typewriterEffect("(Poin Effort Rima: +2, Poin Kedekatan Thallah: +1)\n", delay);
        break;
    default:
        printf("Pilihan tidak valid.\n", delay);
        playChapter1();
        return;
    }
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
        senpai.effort += 7;
        senpai.affinity += 5;
        typewriterEffect("\nRima: \"Kak Thallah juga manusia, Kak. Wajar kalau capek. Tapi aku yakin Kakak pasti bisa melewati semua ini. Kakak hebat!\"\n", delay);
        typewriterEffect("Thallah: (Menoleh, tatapannya melembut) \"Kamu benar. Aku belum pernah bilang ini ke siapa-siapa, tapi... aku takut. Takut tidak bisa membanggakan orang tuaku, takut salah memilih jalan.\"\n", delay);
        typewriterEffect("Thallah mulai terbuka, menceritakan kegelisahan terdalamnya. Dia bercerita tentang tekanan dari keluarga, tentang mimpi besarnya untuk menjadi fotografer profesional, tapi juga keraguan yang menyelimutinya. Aku mendengarkan dengan saksama, sesekali memberi semangat.\n", delay);
        typewriterEffect("Rima: \"Kak Thallah pasti bisa. Kakak punya bakat, punya semangat. Aku percaya itu. Aku akan selalu mendukung Kakak.\"\n", delay);
        typewriterEffect("Thallah: (Tersenyum tulus) \"Terima kasih, Rima. Kamu satu-satunya orang yang bisa kuajak bicara tentang ini.\"\n", delay);
        typewriterEffect("(Poin Effort Rima: +7, Poin Kedekatan Thallah: +5)\n", delay);
        break;
    case 2:
        senpai.effort += 5;
        senpai.affinity += 3;
        typewriterEffect("\nRima: \"Mungkin Kakak perlu istirahat sebentar? Atau coba cerita apa yang membuat Kakak merasa begitu?\"\n", delay);
        typewriterEffect("Thallah: (Mendesah) \"Ya, mungkin aku memang butuh istirahat. Aku... aku cuma merasa beban terlalu banyak.\"\n", delay);
        typewriterEffect("Thallah tidak langsung menceritakan detail, tapi dia mengisyaratkan tentang tekanan ujian dan harapan keluarga. Aku mencoba menghiburnya dengan bercerita tentang pengalamanku sendiri.\n", delay);
        typewriterEffect("Rima: \"Aku juga kadang meraSsa begitu, Kak. Tapi percayalah, Kakak tidak sendiri.\"\n", delay);
        typewriterEffect("Thallah: \"Terima kasih, Rima. Kamu baik sekali.\"\n", delay);
        typewriterEffect("(Poin Effort Rima: +5, Poin Kedekatan Thallah: +3)\n", delay);
        break;
    case 3:
        senpai.effort += 3;
        senpai.affinity += 1;
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
    typewriterEffect("Rima dan Thallah sedang mencari referensi buku untuk proyek fotografi terakhir kami. Suasana perpustakaan yang sepi membuat kami bisa mengobrol lebih santai. Tiba-tiba, Thallah menghentikan langkahnya, menatapku dengan ekspresi ragu.\n", delay);
    typewriterEffect("Thallah:\" Rima, aku mau cerita sesuatu padamu...\"\n", delay);
    typewriterEffect("Rima: \"(Dalam hati: Deg-degan, semoga ini yang kuharapkan... Jantungku berdetak tak karuan.\")\n", delay);
    typewriterEffect("Thallah: (Menghela napas) \"Aku... aku sebenarnya suka sama seseorang. Tapi aku bingung harus bagaimana. Aku tidak tahu apakah dia juga suka padaku atau tidak.\"\n", delay);
    typewriterEffect("Dunia seolah berhenti berputar. Kata-katanya menghantamku telak, lebih keras dari bentakan mana pun.\n", delay);
    typewriterEffect("Thallah: \"Dia itu teman SMP-ku dulu. Kami sudah dekat sebulan ini sebelum kelulusan SMA. Gimana ya Ma?\n", delay);
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
    {
        senpai.affinity -= 7;
        senpai.effort -= 10;
        typewriterEffect("\n(Rima menunjukkan kekesalan, ekspresi terkejut dan kesal)\n", delay);
        typewriterEffect("Rima: \"(Suara sedikit tinggi, menahan amarah) Kak Thallah, kenapa baru cerita sekarang?! Kenapa harus padaku?\"\n", delay);
        typewriterEffect("Thallah: \"(Terkejut, ekspresi bingung dan sedikit kecewa) Eh? Ada apa, Rima? Maaf kalau mendadak... aku kira kamu akan mengerti.\"\n", delay);
        typewriterEffect("Thallah tampak kaget dan sedikit kecewa. Ia tidak melanjutkan ceritanya, hanya terdiam dengan ekspresi bingung. \nSuasana menjadi canggung dan dingin. Aku merasa menyesal telah bereaksi seperti itu.\n", delay);
        typewriterEffect("Rima: \"(Dalam hati: Aku tidak seharusnya marah seperti itu. Tapi hatiku terasa hancur mendengar dia suka pada orang lain.)\"\n", delay);
        typewriterEffect("(Poin Effort Rima: -10, Poin Kedekatan Thallah: -7)\n", delay);
        break;
    }
    case 2:
    {
        senpai.affinity -= 3;
        senpai.effort -= 5;
        typewriterEffect("\n(Rima menunjukkan kesedihan, ekspresi mata berkaca-kaca.)\n", delay);
        typewriterEffect("Rima: \"(Suara pelan, mencoba menahan tangis) Oh... begitu ya, Kak. Aku... aku turut senang untuk Kakak.\n", delay);
        typewriterEffect("Thallah: \"(Khawatir, ekspresi cemas) Rima? Kamu kenapa? Kamu sakit? Wajahmu pucat.\n", delay);
        typewriterEffect("Thallah tampak khawatir, tapi juga bingung dengan reaksi Rima. Rima tidak bisa menyembunyikan kesedihan, dan Thallah tidak melanjutkan ceritanya tentang orang yang ia suka. Ia malah sibuk bertanya keadaanku, dan suasana terasa sangat canggung.\n", delay);
        typewriterEffect("(Poin Effort Rima: -5, Poin Kedekatan Thallah: -3)\n", delay);
        break;
    }
    case 3:
    {
        senpai.affinity += 7;
        senpai.effort += 10;
        typewriterEffect("\n(Rima menunjukkan ekspresi tenang, mencoba tersenyum.)\n", delay);
        typewriterEffect("Rima: \"(Mencoba tersenyum tulus meski hatiku sakit) Oh ya? Wah, Kak Thallah bisa suka juga ya. Ceritain dong, Kak. Seperti apa dia?", delay);
        typewriterEffect("Thallah: \"(Ekspresi nyaman dan bersemangat) Ah, Rima. Dia...\"\n", delay);
        typewriterEffect(" Thallah tersenyum tipis, seolah lega, dan mulai bercerita detail tentang temannya itu—bagaimana mereka bertemu, bagaimana teman itu selalu membantunya, dan betapa ia berharap bisa satu kampus dengannya. Setiap kata yang keluar dari mulutnya terasa seperti sayatan tipis di hatiku. Tapi aku tahu, ini adalah bagian dari usahaku. Aku harus kuat.\n", delay);
        typewriterEffect("poin Effort Rima: +10, Poin Kedekatan Thallah: +7\n", delay);
        break;
    }
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
        senpai.affinity -= 1;
        senpai.effort -= 3;
        typewriterEffect("\nRima: (Suara pelan, menghindari kontak mata) \"Maaf, Kak Thallah. Aku... aku kurang enak badan hari ini. Mungkin aku butuh sendiri sebentar.\"\n", delay);
        typewriterEffect("Thallah: (Ekspresi khawatir) \"Oh, begitu. Baiklah, kalau ada apa-apa, jangan sungkan cerita ya.\"\n", delay);
        typewriterEffect("(Narasi Rima): Thallah pergi dengan ekspresi khawatir. Aku tahu dia peduli, tapi aku tidak bisa menahan kesedihanku.\n", delay);
        typewriterEffect("Aku menghabiskan waktu makan siangku sendirian, merasa semakin hampa.\n", delay);
        typewriterEffect("(Poin Effort Rima: -3, Poin Kedekatan Thallah: -1)\n", delay);
        break;
    case 2:
        senpai.affinity -= 1;
        senpai.effort -= 2;
        typewriterEffect("\nRima: (Memaksakan senyum) \"Ah, maaf Kak. Aku sudah bawa bekal. Aku juga masih ada tugas yang harus diselesaikan.\"\n", delay);
        typewriterEffect("Thallah: (Mengangguk, sedikit kecewa) \"Oh, begitu. Baiklah. Jangan terlalu diporsir ya tugasnya.\"\n", delay);
        typewriterEffect("(Narasi Rima): Thallah pergi, meninggalkan aku dengan rasa bersalah.\n", delay);
        typewriterEffect("Aku tahu dia ingin menghiburku, tapi aku tidak bisa berpura-pura baik-baik saja. Aku hanya ingin menghilang.\n", delay);
        typewriterEffect("(Poin Effort Rima: -2, Poin Kedekatan Thallah: -1)\n", delay);
        break;
    case 3:
        senpai.affinity += 2;
        senpai.effort += 5;
        typewriterEffect("\nRima: (Mengambil napas dalam, memaksakan diri) \"Baiklah, Kak. Aku ikut.\"\n", delay);
        typewriterEffect("Thallah: (Tersenyum lega) \"Nah, begitu dong! Ayo, kita gabung.\"\n", delay);
        typewriterEffect("(Narasi Rima): Aku mengikuti Thallah ke meja teman-teman OSIS.\n", delay);
        typewriterEffect("Sepanjang makan siang, aku berusaha terlihat ceria, meski di dalam hati rasanya perih.\n", delay);
        typewriterEffect("Aku ikut tertawa, sesekali menimpali obrolan, tapi setiap tawa Thallah terasa seperti tusukan.\n", delay);
        typewriterEffect("Ini terasa sangat berat, tapi aku tahu aku harus tetap berada di dekatnya.\n", delay);
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
        senpai.affinity += 4;
        senpai.effort += 7;
        typewriterEffect("\n(Narasi Rima): Aku akan kembali bersikap ceria di depan Thallah, bahkan lebih dari biasanya.\n", delay);
        typewriterEffect("Aku akan mencari cara untuk membantunya dalam tugas OSIS atau fotografi, mendengarkan ceritanya,\n", delay);
        typewriterEffect("dan sesekali melontarkan candaan yang membuatnya tertawa lepas.\n", delay);
        typewriterEffect("Aku akan membuatnya melihatku, bukan hanya sebagai adik kelas, tapi sebagai seseorang yang penting baginya.\n", delay);
        typewriterEffect("(Poin Effort Rima: +7, Poin Kedekatan Thallah: +4)\n", delay);
        break;
    case 2:
        senpai.affinity += 5;
        senpai.effort += 8;
        typewriterEffect("\n(Narasi Rima): Aku akan mencoba mengajaknya melakukan sesuatu berdua, seperti mendiskusikan ide proyek fotografi\n", delay);
        typewriterEffect("atau bahkan mengundang dia untuk makan siang hanya berdua. Aku harus lebih berani menunjukkan bahwa aku ingin lebih dekat dengannya.\n", delay);
        typewriterEffect("(Poin Effort Rima: +8, Poin Kedekatan Thallah: +5)\n", delay);
        break;
    case 3:
        senpai.affinity += 3;
        senpai.effort += 6;
        typewriterEffect("\n(Narasi Rima): Aku akan mencoba menonjolkan diriku di depan Thallah dengan menunjukkan bakat atau prestasiku\n", delay);
        typewriterEffect("di OSIS atau ekskul fotografi. Mungkin jika dia melihatku lebih dari sekadar adik kelas, dia akan mulai melihatku secara berbeda.\n", delay);
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
    typewriterEffect("Aku melihat Thallah berlari ke arahku, wajahnya berseri-seri, senyumnya paling lebar yang pernah kulihat.\n", delay);
    typewriterEffect("Thallah: \"Rima! Aku diterima! Aku diterima di jurusan impianku, Teknik Industri!\"\n", delay);
    typewriterEffect("Thallah bahkan memelukku saking senangnya, saking tak pedulinya dengan tatapan orang-orang.\n", delay);
    typewriterEffect("(Narasi Rima): Pelukannya terasa hangat, tapi kata-kata selanjutnya langsung menusuk jantungku.\n", delay);
    typewriterEffect("Thallah: \"Dan... dan dia juga satu kampus denganku! Dia di jurusan Sastra Indonesia!\"\n", delay);

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
        senpai.affinity += 4;
        senpai.effort += 8;
        typewriterEffect("\nRima: (Memaksakan senyum selebar mungkin) \"Wah, selamat ya, Kak Thallah! Aku turut senang sekali untuk Kakak! Semoga sukses di kampus impian!\"\n", delay);
        typewriterEffect("Thallah: (Tersenyum cerah) \"Makasih banyak, Rima! Kamu memang teman baikku!\"\n", delay);
        typewriterEffect("(Narasi Rima): Thallah tidak sadar betapa kata-katanya mengoyak hatiku untuk kedua kalinya.\n", delay);
        typewriterEffect("Dia menganggapku sebagai teman baik, tempat dia mencurahkan kebahagiaannya.\n", delay);
        typewriterEffect("Dan kebahagiaannya adalah karena dia satu kampus dengan cowok yang dia suka.\n", delay);
        typewriterEffect("(Poin Effort Rima: +8, Poin Kedekatan Thallah: +4)\n", delay);
        break;
    case 2:
        senpai.affinity += 0;
        senpai.effort += 2;
        typewriterEffect("\nRima: (Mengganti ekspresi, sedikit panik) \"Wah, itu bagus sekali, Kak! Ngomong-ngomong,\n", delay);
        typewriterEffect("Kakak sudah lihat daftar mahasiswa baru yang masuk OSIS tahun depan? Banyak wajah baru lho.\"\n", delay);
        typewriterEffect("Thallah: (Sedikit mengerutkan kening) \"Oh, ya? Belum sempat lihat. Tapi... kamu kenapa, Rima? Kok tiba-tiba ganti topik?\"\n", delay);
        typewriterEffect("(Narasi Rima): Thallah tampak menyadari usahaku untuk mengalihkan pembicaraan.\n", delay);
        typewriterEffect("Aku merasa canggung, dan dia tidak terlalu melanjutkan euforianya. Suasana terasa sedikit aneh.\n", delay);
        typewriterEffect("(Poin Effort Rima: +2, Poin Kedekatan Thallah: +0)\n", delay);
        break;
    case 3:
        senpai.affinity -= 3;
        senpai.effort -= 5;
        typewriterEffect("\nRima: (Ekspresi menahan sakit, buru-buru) \"Selamat, Kak! Maaf, aku harus pergi sekarang. Ada urusan mendadak!\"\n", delay);
        typewriterEffect("(Langsung lari)\n", delay);
        typewriterEffect("Thallah: (Berteriak) \"Eh, Rima? Ada apa? Hati-hati!\"\n", delay);
        typewriterEffect("(Narasi Rima): Aku melarikan diri, tidak sanggup menahan rasa sakit.\n", delay);
        typewriterEffect("Thallah mungkin bingung, tapi aku tidak peduli saat itu. Yang penting aku bisa menjauh dari situasi ini.\n", delay);
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

    typewriterEffect("\n(Latar: Malam Hari, Kamar Rima)\n", delay);
    typewriterEffect("(Narasi Rima): Suara lagu sedih mengalun pelan dari ponselku, menemani kesendirianku di malam terakhir sebelum kelulusan Thallah.\n", delay);
    typewriterEffect("Aku memandang langit-langit kamarku yang gelap. Malam ini adalah penentuan.\n", delay);

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
        senpai.effort += 10;
        typewriterEffect("\n(Narasi Rima): Setelah pergolakan batin yang panjang, mengingat semua 'effort' yang sudah kukerahkan,\n", delay);
        typewriterEffect("semua kesabaran dan dukungan yang kuberikan padanya, aku memutuskan untuk...\n", delay);
        typewriterEffect("menembak besok di hari kelulusan. Ini adalah pertaruhan terakhirku.\n", delay);
        typewriterEffect("Akan kukerahkan semua isi hatiku dalam surat ini.\n", delay);
        typewriterEffect("(Poin Effort Rima: +10)\n", delay);
        typewriterEffect("(Item diperoleh: Surat cinta)\n", delay);
        addItem("Surat cinta");
        break;
    case 2:
        typewriterEffect("\n(Narasi Rima): Mungkin terlalu riskan. Ada kemungkinan aku akan ditolak mentah-mentah,\n", delay);
        typewriterEffect("dan itu akan merusak momen kelulusan kami berdua, dan mungkin persahabatan yang sudah terjalin.\n", delay);
        typewriterEffect("Lebih baik biarkan waktu yang menjawab. Biarkan dia tahu perasaanku dengan caraku sendiri, tanpa perlu kata-kata.\n", delay);
        typewriterEffect("Besok aku cukup memberikan hadiah perpisahan saja, seperti coklat misalnya.\n", delay);
        typewriterEffect("Aku akan memberikannya sebagai tanda terima kasih atas semua kenangan indah yang telah kami lalui bersama.\n", delay);
        typewriterEffect("(Rima membeli coklat di supermarket)\n", delay);
        typewriterEffect("(Item diperoleh: Coklat Perpisahan)\n", delay);
        typewriterEffect("(Poin Effort Rima: +0)\n", delay);
        addItem("Cokelat Perpisahan");
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
    typewriterEffect("1. Nyatakan perasaan dengan Surat cinta\n", delay);
    typewriterEffect("2. Ungkapkan langsung secara lisan\n", delay);
    typewriterEffect("3. Berikan Cokelat Perpisahan saja\n", delay);
    typewriterEffect("0. Jangan nyatakan perasaan (diam)\n> ", delay);
    scanf("%d", &choice);
    clearInputBuffer();

    if (choice == 0)
    {
        typewriterEffect("\n(Narasi Rima): Setelah pergolakan batin yang panjang, aku memutuskan untuk tidak menembaknya.\n", delay);
        typewriterEffect("Mungkin ini bukan waktu yang tepat. Aku akan terus berjuang dengan caraku sendiri, menunjukkan perasaanku lewat tindakan dan perhatian.\n", delay);
        typewriterEffect("Sampai suatu hari nanti dia menyadari perasaanku. Mungkin... suatu hari nanti.\n", delay);
        typewriterEffect("Kelulusan pun tiba, dan Thallah lulus tanpa mengetahui perasaanku yang sesungguhnya.\n", delay);
        typewriterEffect("Aku hanya bisa menatap punggungnya yang semakin menjauh, membawa serta sebagian hatiku.\n", delay);
        typewriterEffect("\n=== ENDING: Tidak Pernah Diungkapkan ===\n", delay);
        return;
    }

    if (choice == 1)
    {
        // Cek item Surat cinta
        Item *temp = inventory;
        int found = 0;
        while (temp != NULL)
        {
            if (strcmp(temp->name, "Surat cinta") == 0)
            {
                found = 1;
                break;
            }
            temp = temp->next;
        }

        if (!found)
        {
            typewriterEffect("\nKamu tidak punya Surat cinta untuk diberikan...\n", delay);
            typewriterEffect("Akhirnya kamu hanya terdiam dan tidak menyatakan apa pun.\n", delay);
            typewriterEffect("=== ENDING: Tidak Pernah Diungkapkan ===\n", delay);
            return;
        }

        useItem("Surat cinta");
        senpai.affinity += 2;

        typewriterEffect("\nRima: \"Aku... aku mau ngomong sesuatu,\" kataku, suaraku sedikit bergetar.\n", delay);
        typewriterEffect("Aku mengeluarkan sebuah surat yang sudah kubuat semalaman, mencurahkan semua perasaanku di sana.\n", delay);
        typewriterEffect("\"Tapi... jangan dibaca sekarang ya, Kak. Bacanya nanti, saat Kakak sudah mulai kuliah.\"\n", delay);
        typewriterEffect("Thallah menatapku dalam diam, lalu tersenyum, menerima surat itu dengan hati-hati.\n", delay);
        typewriterEffect("Thallah: \"Terima kasih, Rima. Aku akan membacanya nanti.\"\n", delay);
        typewriterEffect("(Item digunakan: Surat Cinta).\n", delay);
    }
    else if (choice == 2)
    {
        typewriterEffect("\nRima: \"Kak Thallah, ini mungkin berat buat Kakak dengar...\"\n", delay);
        typewriterEffect("\"Tapi selama ini... aku punya perasaan lebih dari sekadar junior ke senior.\"\n", delay);
        typewriterEffect("\"Aku suka sama Kakak.\"\n", delay);
    }
    else if (choice == 3)
    {
        // Cek item Cokelat Perpisahan
        Item *temp = inventory;
        int found = 0;
        while (temp != NULL)
        {
            if (strcmp(temp->name, "Cokelat Perpisahan") == 0)
            {
                found = 1;
                break;
            }
            temp = temp->next;
        }

        if (!found)
        {
            typewriterEffect("Kamu tidak punya Cokelat Perpisahan...\n", delay);
            typewriterEffect("Akhirnya kamu hanya tersenyum dan pergi tanpa mengucapkan apa-apa.\n", delay);
            typewriterEffect("=== ENDING: Tidak Pernah Diungkapkan ===\n", delay);
            return;
        }

        useItem("Cokelat Perpisahan");

        typewriterEffect("\n(Narasi Rima): Aku tidak mengatakan apa pun. Hanya tersenyum dan menyerahkan Cokelat Perpisahan padanya.\n", delay);
        typewriterEffect("Ia menerimanya dan tersenyum hangat, sedikit heran, tapi menghargainya.\n", delay);
        typewriterEffect("Thallah: \"Terima kasih, Rima. Ini... manis sekali.\"\n", delay);
        typewriterEffect("(Narasi Rima): Aku menahan air mata dan tersenyum. Kadang yang tak terucap, lebih berarti dari yang dibicarakan.\n", delay);
        typewriterEffect("(Item digunakan: Coklat Perpisahan).\n", delay);
        typewriterEffect("\n=== ENDING: Kenangan Manis ===\n", delay);
        return;
    }
    else
    {
        typewriterEffect("Pilihan tidak valid.\n", delay);
        playGraduationDay();
        return;
    }

    // Evaluasi akhir untuk pilihan 1 dan 2
    if (senpai.effort > 30 && senpai.affinity > 15)
    {
        if (choice == 1)
        {
            typewriterEffect("\n(Narasi Rima): Aku hanya tersenyum, lalu berbalik. Aku tidak tahu bagaimana reaksinya nanti.\n", delay);
            typewriterEffect("Tapi aku tahu, hatiku sudah lebih ringan karena sudah jujur.\n", delay);
            typewriterEffect("\n=== WAKTU BERLALU... ===\n", delay);
            typewriterEffect("Beberapa bulan kemudian...\n", delay);
            typewriterEffect("Di sebuah kamar kos kecil, Thallah duduk lelah sepulang kelas.\n", delay);
            typewriterEffect("Ia membuka laci meja dan menemukan suratku.\n", delay);
            typewriterEffect("Ia membacanya perlahan...\n", delay);
            typewriterEffect("Matanya melembut. Air matanya menggenang, namun senyumnya tulus.\n", delay);
            typewriterEffect("Thallah: \"Rima... kenapa kamu selalu tahu cara menyentuh hatiku?\"\n", delay);
            typewriterEffect("Malam itu, di kota baru yang sepi, suratku menjadi cahaya kecil di hatinya.\n\n\n", delay);
            typewriterEffect("\nBeberapa saat setelah membaca surat itu, ia mengambil ponselnya dan memanggil kontak Rima yang sudah lama tak ia panggil...\n", delay);
            typewriterEffect("Bunyi nada sambung terdengar... lalu tersambung.\n", delay);
            typewriterEffect("Thallah: \"Halo, Rima... apa kabar?...\"\n", delay);
            typewriterEffect("\n=== ENDING SURAT CINTA: Dibaca Saat Kuliah ===\n", delay);
        }
        else
        {
            typewriterEffect("\n(Narasi Rima): Thallah terdiam, lalu tersenyum.\n", delay);
            typewriterEffect("Thallah: \"Kamu selalu ada di saat aku butuh. Aku ingin mencobanya bersamamu.\"\n", delay);
            typewriterEffect("Di tengah riuhnya acara kelulusan, hanya kami yang merasa waktu berhenti.\n", delay);
            typewriterEffect("\n=== TRUE ENDING: Bersama ===\n", delay);
        }
    }
    else
    {
        if (choice == 1)
        {
            typewriterEffect("\n(Narasi Rima): Aku hanya tersenyum, lalu berbalik. Aku tidak tahu bagaimana reaksinya nanti.\n", delay);
            typewriterEffect("Tapi aku tahu, hatiku sudah lebih ringan karena sudah jujur.\n", delay);

            typewriterEffect("\n=== WAKTU BERLALU... ===\n", delay);
            typewriterEffect("Beberapa bulan kemudian...\n", delay);
            typewriterEffect("Di sebuah kamar kos yang senyap, Thallah membuka laci meja dan mengambil surat dari Rima.\n", delay);
            typewriterEffect("Ia memandangi amplop itu lama, lalu menghela napas... dan menyimpannya kembali tanpa membukanya.\n", delay);
            typewriterEffect("Thallah: \"Maaf, Rima... aku tidak bisa...\"\n", delay);

            typewriterEffect("(Narasi): Entah karena takut, bingung, atau tak ingin memberi harapan palsu,\n", delay);
            typewriterEffect("ia memilih untuk membiarkan surat itu tetap tersegel, diam di dalam laci, seperti perasaan Rima yang tak pernah terjawab.\n", delay);

            typewriterEffect("\nDi tempat lain, Rima duduk menatap layar ponsel.\n", delay);
            typewriterEffect("Tak ada notifikasi. Tak ada balasan. Tak ada panggilan. Hanya sepi.\n", delay);
            typewriterEffect("Namun ia tetap tersenyum kecil, menatap langit malam yang sama dengan Thallah di kejauhan.\n", delay);
            typewriterEffect("Rima: \"Setidaknya... dia tahu.\"\n", delay);

            typewriterEffect("\n=== ENDING: Surat yang Tak Pernah Dibalas ===\n", delay);
        }
        else if (choice == 2)
        {
            typewriterEffect("\n(Narasi Rima): Thallah menatapku pelan, lalu menggeleng dengan senyum sedih.\n", delay);
            typewriterEffect("Thallah: \"Aku minta maaf, Rima. Kamu gadis yang luar biasa, tapi... perasaanku belum ke arah itu.\"\n", delay);
            typewriterEffect("Aku menunduk, mencoba tegar. Tapi hatiku pecah perlahan.\n", delay);
            typewriterEffect("\n=== BAD ENDING: Tidak Terbalas ===\n", delay);
        }
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
        typewriterEffect("3. Lihat rekap poin tiap chapter\n", delay);
        typewriterEffect("4. List character\n", delay);
        typewriterEffect("5. Keluar game\n> ", delay);
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
            showChapterPoints();
            printf("\nUrutkan berdasarkan:\n");
            printf("1. Affinity Tertinggi\n");
            printf("2. Effort Tertinggi\n");
            printf("3. Kembali\n> ");
            scanf("%d", &pilihan);
            clearInputBuffer();

            if (pilihan == 1)
            {
                sortAndShowChapterPoints(1);
            }
            else if (pilihan == 2)
            {
                sortAndShowChapterPoints(0);
            }
            else if (pilihan == 3)
            {
                break; // kembali ke menu utama
            }
            else
            {
                printf("Pilihan tidak valid.\n");
            }
            break;
        case 4:
            listCharacters();
            break;
        case 5:
            typewriterEffect("Terima kasih telah bermain!\n", delay2);
            break;
        default:
            typewriterEffect("Pilihan tidak valid.\n", delay2);
        }
    } while (pilihan != 5);
}

void showChapterPoints()
{
    typewriterEffect("\n=== Rekap Tambahan Poin per Chapter ===\n", delay2);
    typewriterEffect("| Chapter | +Affinity  | +Effort |\n", delay2);
    typewriterEffect("|---------|------------|---------|\n", delay2);

    for (int i = 1; i < 8; i++)
    {
        if (chapterStates[i].completed)
        {
            int prevAffinity = (i > 1 && chapterStates[i - 1].completed) ? chapterStates[i - 1].affinity : 0;
            int prevEffort = (i > 1 && chapterStates[i - 1].completed) ? chapterStates[i - 1].effort : 0;

            int deltaAffinity = chapterStates[i].affinity - prevAffinity;
            int deltaEffort = chapterStates[i].effort - prevEffort;

            printf("|   %2d    |    %+4d    |   %+4d  |\n", i, deltaAffinity, deltaEffort);
        }
        else
        {
            printf("|   %2d    |     --     |    --   |\n", i);
        }
    }
}

void sortAndShowChapterPoints(int sortByAffinity)
{
    int indices[8];
    for (int i = 1; i < 8; i++)
    {
        indices[i] = i;
    }

    // Bubble sort berdasarkan delta (penambahan)
    for (int i = 1; i < 8 - 1; i++)
    {
        for (int j = i + 1; j < 8; j++)
        {
            int a = indices[i], b = indices[j];

            int prevAffinityA = (a > 1 && chapterStates[a - 1].completed) ? chapterStates[a - 1].affinity : 0;
            int prevEffortA = (a > 1 && chapterStates[a - 1].completed) ? chapterStates[a - 1].effort : 0;
            int deltaA = sortByAffinity
                             ? (chapterStates[a].affinity - prevAffinityA)
                             : (chapterStates[a].effort - prevEffortA);

            int prevAffinityB = (b > 1 && chapterStates[b - 1].completed) ? chapterStates[b - 1].affinity : 0;
            int prevEffortB = (b > 1 && chapterStates[b - 1].completed) ? chapterStates[b - 1].effort : 0;
            int deltaB = sortByAffinity
                             ? (chapterStates[b].affinity - prevAffinityB)
                             : (chapterStates[b].effort - prevEffortB);

            if (deltaA < deltaB)
            {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    // Tampilkan dengan efek typewriter
    char buffer[200];
    snprintf(buffer, sizeof(buffer), "\n=== Hasil Sorting Chapter Berdasarkan %s ===\n",
             sortByAffinity ? "Affinity Δ" : "Effort Δ");
    typewriterEffect(buffer, delay2);

    typewriterEffect("| Chapter | +Affinity | +Effort |\n", delay2);
    typewriterEffect("|---------|-----------|---------|\n", delay2);

    for (int i = 1; i < 8; i++)
    {
        int idx = indices[i];
        if (chapterStates[idx].completed)
        {
            int prevAffinity = (idx > 1 && chapterStates[idx - 1].completed) ? chapterStates[idx - 1].affinity : 0;
            int prevEffort = (idx > 1 && chapterStates[idx - 1].completed) ? chapterStates[idx - 1].effort : 0;

            int deltaAffinity = chapterStates[idx].affinity - prevAffinity;
            int deltaEffort = chapterStates[idx].effort - prevEffort;

            snprintf(buffer, sizeof(buffer), "|   %2d    |   %+5d    |  %+5d  |\n",
                     idx, deltaAffinity, deltaEffort);
            typewriterEffect(buffer, delay2);
        }
    }
}

int main()
{
    typewriterEffect("(Info: Tekan ENTER kapan saja untuk skip tulisan lambat.)\n", delay2);
    typewriterEffect("(Tekan ENTER untuk mulai...)\n\n", delay2);
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

    showInventory();
    showMenu();

    return 0;
}
