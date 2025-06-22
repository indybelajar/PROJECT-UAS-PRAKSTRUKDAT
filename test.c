#include <stdio.h>
#include <string.h>
#include <windows.h> // Untuk Sleep()

int delay = 30;

// Fungsi: Typewriter effect
void typewriterEffect(const char *text, int delay) {
    for (int i = 0; text[i] != '\0'; i++) {
        printf("%c", text[i]);
        fflush(stdout);
        Sleep(delay); // delay dalam milidetik
    }
}

// Fungsi: Menampilkan array paragraf satu per satu
void typewriterParagraphs(const char* paragraphs[], int count, int delay) {
    char input[10];
    for (int i = 0; i < count; i++) {
        typewriterEffect(paragraphs[i], delay);

        if (i < count - 1) {
            printf("\n(Enter : lanjut, 1 skip) ");
            fgets(input, sizeof(input), stdin);

            if (input[0] == '1') {
                printf("\n(Melewati sisa prolog...)\n");
                break;
            }
        }
    }
}

// Fungsi modular untuk input lanjut atau skip
int wait() {
    char input[10];
    printf("(1 : skip; Enter : Lanjut) > ");
    fgets(input, sizeof(input), stdin);

    // Menghapus newline '\n' dari input
    input[strcspn(input, "\n")] = 0;

    if (strcmp(input, "1") == 0) {
        return 1; // Skip
    }
    return 0; // Lanjut
}

void showProlog() {
    typewriterEffect("\n=== PROLOG ===\n", delay);
    // Hari ke-1 MPLS
    typewriterEffect("(Latar: Pagi hari, Lapangan SMA, Masa Pengenalan Lingkungan Sekolah (MPLS) Hari 1)\n", delay);
    if (wait()) return;

    typewriterEffect("(Narasi Rima): Langit biru cerah menyambut hari pertama Masa Pengenalan Lingkungan Sekolah.\n", delay);
    if (wait()) return;
    
    typewriterEffect("Aku, Rima, si adik kelas yang masih kosong tentang seluk-beluk SMA ini, berjalan mengikuti barisan,\n", delay);
    typewriterEffect("berusaha tidak tersesat di antara ratusan siswa baru. Di tengah riuhnya suara, para siswa baru yang\n", delay);
    typewriterEffect("gugup, dan anggota OSIS yang berteriak memberi arahan, pandanganku terhenti pada satu sosok.\n", delay);
    typewriterEffect("Seorang kakak kelas dengan name tag \"Thallah\". Rambutnya klimis, tertata rapi, dan matanya berbinar\n", delay);
    typewriterEffect("di balik lensa kamera DSLR yang ia gunakan untuk memfoto jalannya MPLS. Senyumnya... ah, senyumnya\n", delay);
    typewriterEffect("seolah menerangi seluruh lapangan, bahkan di bawah terik matahari yang menyengat.\n", delay);
    typewriterEffect("Ia berdiri di sekitar lapangan sembari memfoto temannya yang sedang menjelaskan jadwal hari ini.\n", delay);
    typewriterEffect("Setelah selesai menjelaskan, ia mendatangi temannya dan mengajaknya bicara. Suaranya tenang tapi tegas,\n", delay);
    typewriterEffect("namun entah kenapa terdengar begitu menenangkan bagiku. Beberapa kali matanya bersitatap denganku\n", delay);
    typewriterEffect("saat ia melintas, dan setiap kali itu terjadi, jantungku berdegup lebih kencang. Hari itu, interaksi kami\n", delay);
    typewriterEffect("hanya sebatas sapaan singkat dan anggukan kepala.\n", delay);
    typewriterEffect("=======================\n", delay);

    // Hari ke-2 MPLS
    typewriterEffect("(Latar: Lapangan SMA, MPLS Hari 2)\n", delay);
    typewriterEffect("(Narasi Rima): Pada hari kedua MPLS, aku melihatnya kembali! Namun, kali ini ia tidak berseragam OSIS,\n", delay);
    typewriterEffect("melainkan berdiri di tengah lapangan, memimpin sebuah demo ekskul. Suaranya masih tenang tapi tegas saat\n", delay);
    typewriterEffect("ia menjelaskan tentang Ekskul Fotografi yang ia pimpin. Matanya tampak berbinar saat ia menjelaskan fungsi\n", delay);
    typewriterEffect("lensa, komposisi, dan cahaya.\n", delay);
    typewriterEffect("Kemudian, ia menawari para murid baru untuk mencoba kamera yang ia pegang. Aku yang melihat kesempatan emas ini,\n", delay);
    typewriterEffect("tanpa ragu langsung mengangkat tangan. Ia menghampiriku perlahan, dan dalam bayanganku, ia seperti seorang\n", delay);
    typewriterEffect("kesatria yang menghampiri putri. Dia menjelaskan cara menggunakan kamera dengan lembut, dengan sabar membimbing\n", delay);
    typewriterEffect("tanganku menekan tombol shutter dan mengatur focus. Itu adalah pengalaman pertama dan paling berkesan bagiku\n", delay);
    typewriterEffect("selama MPLS.\n", delay);

    typewriterEffect("(Narasi Rima): Sejak momen itu, di benakku, ini bukan hanya sekadar MPLS. Ini adalah misi PDKT, misi untuk\n", delay);
    typewriterEffect("mendekati Thallah! Aku mulai berusaha mencari tahu lebih banyak tentangnya. Hal pertama yang kutahu,\n", delay);
    typewriterEffect("Thallah adalah anggota OSIS dan ketua Ekskul Fotografi. Tanpa pikir panjang, aku memutuskan untuk berniat\n", delay);
    typewriterEffect("menjadi anggota OSIS dan mendaftar ke Ekskul Fotografi.\n", delay);

    typewriterEffect("Tentu saja, alasan utamaku masuk ke kedua organisasi itu adalah untuk selalu berada di dekatnya. Supaya aku\n", delay);
    typewriterEffect("bisa menanyakan hal-hal sepele, atau sekadar menawarkan bantuan kecil. Singkat cerita, dengan sedikit\n", delay);
    typewriterEffect("keberuntungan dan usaha keras, aku berhasil masuk ke dalam dua organisasi tersebut!\n", delay);

    typewriterEffect("(Narasi Rima): Sedikit yang Rima tahu, Thallah ternyata siswa Kelas 12, yang berarti akan lulus sebentar lagi.\n", delay);
    typewriterEffect("Aku menjalani hari-hari sibukku sebagai anggota OSIS dan Ekskul Fotografi bersama Thallah selama semester satu.\n", delay);
    typewriterEffect("Aku selalu mencari cara untuk berinteraksi dengannya, membantunya dalam tugas OSIS, atau sekadar menemaninya\n", delay);
    typewriterEffect("di ruang fotografi. Kami banyak tertawa, banyak berbagi cerita. Perasaanku padanya semakin dalam setiap harinya.\n", delay);

    typewriterEffect("Namun, setelah masuk ke Semester 2, Thallah mulai fokus penuh untuk mempersiapkan diri mengikuti berbagai\n", delay);
    typewriterEffect("ujian akhir dan UTBK. Proses PDKT-ku kembali dari nol. Aku berusaha keras untuk tidak mengganggunya.\n", delay);
    typewriterEffect("Aku tidak lagi sering mengajaknya bicara, tidak lagi menawarkan bantuan sepele. Aku tahu ia butuh fokus,\n", delay);
    typewriterEffect("dan aku tidak ingin menjadi pengganggu.\n", delay);

    typewriterEffect("Sampai pada saat di mana seluruh ujian itu sudah selesai dan perjalanannya menuju kelulusan semakin dekat.\n", delay);
    typewriterEffect("Hanya tersisa 7 hari lagi sampai kelulusan Thallah. Aku bertekad untuk kembali mendekatinya, tidak peduli\n", delay);
    typewriterEffect("seberapa singkat waktu yang tersisa. Ini adalah kesempatanku.\n", delay);
}

/*
*  .----------------.  .----------------.  .----------------.  .----------------.  .----------------. *
* | .--------------. || .--------------. || .--------------. || .--------------. || .--------------. | *
* | | ____    ____ | || | _____  _____ | || |   _____      | || |      __      | || |     _____    | | *
* | ||_   \  /   _|| || ||_   _||_   _|| || |  |_   _|     | || |     /  \     | || |    |_   _|   | | *
* | |  |   \/   |  | || |  | |    | |  | || |    | |       | || |    / /\ \    | || |      | |     | | *
* | |  | |\  /| |  | || |  | '    ' |  | || |    | |   _   | || |   / ____ \   | || |      | |     | | *
* | | _| |_\/_| |_ | || |   \ `--' /   | || |   _| |__/ |  | || | _/ /    \ \_ | || |     _| |_    | | *
* | ||_____||_____|| || |    `.__.'    | || |  |________|  | || ||____|  |____|| || |    |_____|   | | *
* | |              | || |              | || |              | || |              | || |              | | *
* | '--------------' || '--------------' || '--------------' || '--------------' || '--------------' | *
*  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' *
*/

// Fungsi utama
int main() {
    showProlog();
    // Tambahkan menu / gameplay selanjutnya di sini
    return 0;
}
