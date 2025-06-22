#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
// test
//  Struct inventory
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
void playChapter5();
void playChapter7();

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// efek typewiter
void typewriterEffect(const char *text, int delay)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        printf("%c", text[i]);
        fflush(stdout);
        Sleep(delay); // delay dalam milidetik
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

    while (currentChapter != NULL)
    {
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
        case 5:
            playChapter5();
            break;
        case 7:
            playChapter7();
            return;
        default:
            break;
        }
        currentChapter = currentChapter->next;
    }
}

void playChapter1()
{
    int choice;
    typewriterEffect("\nHari 1: Pendekatan Awal\n", delay);
    typewriterEffect("(Latar: Aula OSIS, siang hari)\n", delay);
    typewriterEffect("(Narasi Rima): Hari pertama dari sisa 7 hari ini dimulai. Aku melihat Thallah sedang membereskan berkas-berkas sendirian di aula OSIS. Dia tampak sedikit lelah. Ini kesempatanku!\n", delay);
    typewriterEffect("Rima: (Berjalan mendekat) \"Kak Thallah, butuh bantuan?\"\n", delay);

    typewriterEffect("\nApa yang akan kamu lakukan?\n", delay);
    typewriterEffect("1. Tawarkan bantuan spesifik\n", delay);
    typewriterEffect("2. Tawarkan minuman\n", delay);
    typewriterEffect("3. Hanya bertanya\n", delay);
    typewriterEffect("0. Menu\n> ", delay);
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
        typewriterEffect("\nRima: \"Melihat berkas sebanyak itu pasti bikin pusing. Mau aku bantu rapikan atau kumpulkan sesuai abjad?\"\n", delay);
        typewriterEffect("Thallah: (Tersenyum lega) \"Eh, Rima. Kebetulan sekali. Bisa tolong kumpulkan berkas ini sesuai abjad? Aku sudah mau tumbang rasanya.\"\n", delay);
        typewriterEffect("(Narasi Rima): Aku mengerjakan tugas itu dengan semangat, sesekali melirik Thallah yang tampak kelelahan.\n", delay);
        typewriterEffect("Kami mulai mengobrol ringan, membicarakan persiapan kelulusannya, tentang ujian-ujiannya yang melelahkan.\n", delay);
        typewriterEffect("Aku berusaha menciptakan suasana nyaman, melontarkan candaan kecil yang membuatnya tersenyum.\n", delay);
        typewriterEffect("Rasanya, jarak di antara kami mulai memudar lagi.\n", delay);
        typewriterEffect("(Poin Effort Rima: +5, Poin Kedekatan Thallah: +3)\n", delay);
        break;
    case 2:
        senpai.affinity += 2;
        typewriterEffect("\nRima: \"Kak Thallah kelihatan capek. Mau aku belikan minum? Ada teh dingin atau kopi panas?\"\n", delay);
        typewriterEffect("Thallah: (Tersenyum tipis) \"Wah, makasih banyak, Rima. Teh dingin kedengarannya enak. Aku cuma perlu rapikan berkas ini sedikit lagi.\"\n", delay);
        typewriterEffect("(Narasi Rima): Setelah membawakannya teh dingin, aku menawarkan diri untuk membantunya merapikan berkas.\n", delay);
        typewriterEffect("Kami mengobrol santai tentang kegiatannya setelah ujian, dan aku sesekali melontarkan candaan ringan yang membuatnya tersenyum.\n", delay);
        typewriterEffect("(Poin Effort Rima: +4, Poin Kedekatan Thallah: +2)\n", delay);
        break;
    case 3:
        senpai.affinity += 1;
        typewriterEffect("\nRima: \"Kak Thallah sibuk banget ya?\"\n", delay);
        typewriterEffect("Thallah: (Mendesah pelan) \"Lumayan, Rima. Berkas-berkas akhir tahun ini banyak sekali.\"\n", delay);
        typewriterEffect("(Narasi Rima): Aku hanya berdiri di sana sebentar, merasa canggung untuk menawarkan bantuan lebih jauh.\n", delay);
        typewriterEffect("Thallah kembali sibuk dengan berkasnya. Aku memutuskan untuk membantu membereskan beberapa map yang tercecer di meja.\n", delay);
        typewriterEffect("(Poin Effort Rima: +2, Poin Kedekatan Thallah: +1)\n", delay);
        break;
    default:
        typewriterEffect("Pilihan tidak valid.\n", delay);
        playChapter1();
        return;
    }
}

void playChapter2()
{
    int choice;
    typewriterEffect("\nHari 2: Saling Terbuka\n", delay);
    typewriterEffect("(Latar: Ruang Ekskul Fotografi, sore hari)\n", delay);
    typewriterEffect("(Narasi Rima): Sore ini, aku dan Thallah sedang berada di ruang ekskul fotografi, memeriksa hasil jepretan dari acara sekolah minggu lalu. Suasana hening, hanya terdengar suara klik mouse. Thallah tiba-tiba menghela napas panjang.\n", delay);
    typewriterEffect("Thallah: (Menghela napas, melihat hasil jepretan) \"Kadang aku lelah, Rima. Banyak harapan di pundakku.\"\n", delay);

    typewriterEffect("\nApa yang akan kamu lakukan?\n", delay);
    typewriterEffect("1. Beri dukungan penuh\n", delay);
    typewriterEffect("2. Beri saran praktis\n", delay);
    typewriterEffect("3. Ubah topik (menghibur)\n", delay);
    typewriterEffect("0. Menu\n> ", delay);
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
        typewriterEffect("(Narasi Rima): Thallah mulai terbuka, menceritakan kegelisahan terdalamnya. Dia bercerita tentang tekanan dari keluarga, tentang mimpi besarnya untuk menjadi fotografer profesional, tapi juga keraguan yang menyelimutinya. Aku mendengarkan dengan saksama, sesekali memberi semangat.\n", delay);
        typewriterEffect("Rima: \"Kak Thallah pasti bisa. Kakak punya bakat, punya semangat. Aku percaya itu. Aku akan selalu mendukung Kakak.\"\n", delay);
        typewriterEffect("Thallah: (Tersenyum tulus) \"Terima kasih, Rima. Kamu satu-satunya orang yang bisa kuajak bicara tentang ini.\"\n", delay);
        typewriterEffect("(Poin Effort Rima: +7, Poin Kedekatan Thallah: +5)\n", delay);
        break;
    case 2:
        senpai.effort += 5;
        senpai.affinity += 3;
        typewriterEffect("\nRima: \"Mungkin Kakak perlu istirahat sebentar? Atau coba cerita apa yang membuat Kakak merasa begitu?\"\n", delay);
        typewriterEffect("Thallah: (Mendesah) \"Ya, mungkin aku memang butuh istirahat. Aku... aku cuma merasa beban terlalu banyak.\"\n", delay);
        typewriterEffect("(Narasi Rima): Thallah tidak langsung menceritakan detail, tapi dia mengisyaratkan tentang tekanan ujian dan harapan keluarga. Aku mencoba menghiburnya dengan bercerita tentang pengalamanku sendiri.\n", delay);
        typewriterEffect("Rima: \"Aku juga kadang meraSsa begitu, Kak. Tapi percayalah, Kakak tidak sendiri.\"\n", delay);
        typewriterEffect("Thallah: \"Terima kasih, Rima. Kamu baik sekali.\"\n", delay);
        typewriterEffect("(Poin Effort Rima: +5, Poin Kedekatan Thallah: +3)\n", delay);
        break;
    case 3:
        senpai.effort += 3;
        senpai.affinity += 1;
        typewriterEffect("\nRima: \"Fokus sama jepretan ini saja, Kak. Lihat, yang ini bagus banget! Kakak punya bakat seni yang luar biasa.\"\n", delay);
        typewriterEffect("Thallah: (Tersenyum tipis) \"Haha, kamu bisa saja. Memang menyenangkan kalau melihat hasil yang bagus.\"\n", delay);
        typewriterEffect("(Narasi Rima): Thallah tidak melanjutkan keluh kesahnya. Dia memang tersenyum, tapi aku merasa dia tidak sepenuhnya terbuka. Aku mencoba membuat suasana lebih ceria dengan membahas teknik fotografi.\n", delay);
        typewriterEffect("(Poin Effort Rima: +3, Poin Kedekatan Thallah: +1)\n", delay);
        break;
    default:
        typewriterEffect("Pilihan tidak valid.\n", delay);
        playChapter2();
        return;
    }
}

void playChapter3()
{
    int choice;
    printf("Senpai cerita bahwa dia sedang dekat dengan seseorang.\n");
    printf("MC: (Apa reaksimu?)\n1. Marah\n2. Sedih\n3. Dengarkan sampai habis\n0. Menu\n> ");
    scanf("%d", &choice);
    clearInputBuffer();
    if (choice == 0)
    {
        if (!gameMenu())
            return;
        playChapter3();
        return;
    }
    if (choice == 1)
    {
        senpai.affinity -= 2;
        printf("Kamu marah... afinitas menurun!\n");
    }
    else if (choice == 2)
    {
        senpai.affinity += 1;
        printf("Kamu sedih... afinitas naik sedikit.\n");
    }
    else if (choice == 3)
    {
        senpai.affinity += 2;
        printf("Kamu mendengarkan dengan sabar... afinitas meningkat!\n");
    }
}

void playChapter5()
{
    int choice;
    printf("\nGunakan item untuk menarik perhatian senpai?\n1. Cokelat\n2. Tidak\n0. Menu\n> ");
    scanf("%d", &choice);
    clearInputBuffer();
    if (choice == 0)
    {
        if (!gameMenu())
            return;
        playChapter5();
        return;
    }
    if (choice == 1)
    {
        useItem("Cokelat");
        senpai.affinity += 2;
        printf("Senpai tersenyum menerima cokelatmu. Afinitas meningkat!\n");
    }
}

void playChapter7()
{
    int choice;
    printf("Senpai terlihat bingung kamu tidak mengobrol lagi...\n");
    printf("Apakah kamu ingin menyatakan cinta saat kelulusan?\n1. Ya\n2. Tidak\n0. Menu\n> ");
    scanf("%d", &choice);
    clearInputBuffer();
    if (choice == 0)
    {
        if (!gameMenu())
            return;
        playChapter7();
        return;
    }
    if (choice == 1)
    {
        if (senpai.affinity >= 5)
        {
            printf("\nSenpai menerima cintamu! ❤️ Ending Bahagia!\n");
        }
        else
        {
            printf("\nSenpai menolakmu dengan halus... Ending Sedih 😢\n");
        }
    }
    else
    {
        printf("\nKamu menyimpan perasaanmu sendiri... Ending Netral.\n");
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
    typewriterEffect("=========================", delay2);
    typewriterEffect("\nGame Otome: A Week Before Graduate I Try to Ask My Senpai to be My Boyfriend\n", delay2);
    typewriterEffect("Creator:\n- Indy Agustin\n- Grace Larisma Jaya\n- Rakha Atha Muhammad\n- Muhammad Mumtaaz Raihaan Thaariq\n- Muhammad Faatih Yusron\n", delay2);
    typewriterEffect("=========================", delay2);

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
