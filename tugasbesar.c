#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// "\x1b[35m" //warna
typedef struct tgerak {
    int x;
    int y;
} tgerak;

typedef struct thadiah {
    int x;
    int y;
    char nama[5];
    int poin;
} thadiah;

void tampilTgerak() {
    tgerak temp;
    FILE *tgerak = fopen("tgerak.txt", "r");
    if (tgerak == NULL) {
        printf("File tidak terbuka\n");
        return;
    }

    printf("------------------\n");
    printf("|x\t|y\t|\n");
    printf("------------------\n");
    while ((fscanf(tgerak, "%d %d ", &temp.x, &temp.y)) == 2) {
        printf("|%d\t|%d\t|\n", temp.x, temp.y);
    }
    printf("------------------\n\n");

    fclose(tgerak);
}

void tambahTgerak() {
    tampilTgerak();
    tgerak temp;

    printf("Masukan nilai x:");
    scanf("%d", &temp.x);
    printf("Masukan nilai y:");
    scanf("%d", &temp.y);

    FILE *tgerak = fopen("tgerak.txt", "a");
    if (tgerak == NULL) {
        printf("File tidak terbuka\n");
        return;
    }

    fprintf(tgerak, "%d %d\n", temp.x, temp.y);
    fclose(tgerak);
}
int cekBrpLine(int fileMana) {
    int counter = 0;

    if (fileMana == 2) {
        tgerak temp_gerak;
        FILE *tgerak = fopen("tgerak.txt", "r");
        if (tgerak == NULL) {
            printf("File tidak terbuka\n");
            return 0;
        }

        while ((fscanf(tgerak, "%d %d ", &temp_gerak.x, &temp_gerak.y)) == 2) {
            counter++;
        }
        fclose(tgerak);

    } else {
        thadiah temp_hadiah;
        FILE *thadiah = fopen("thadiah.txt", "r");
        if (thadiah == NULL) {
            printf("File tidak terbuka\n");
            return 0;
        }

        while ((fscanf(thadiah, "%d %d %s %d", &temp_hadiah.x, &temp_hadiah.y, temp_hadiah.nama, &temp_hadiah.poin)) == fileMana) {
            counter++;
        }
        fclose(thadiah);
    }
    return counter;
}

void sorting(){
    //membuka file dalam mode membaca
    FILE *fileHadiah = fopen("thadiah.txt", "r");
    if(fileHadiah == NULL){
        printf("File tidak terbuka sorting\n");
        return;
    }

    int jml_hadiah = cekBrpLine(4);

    thadiah hadiah[jml_hadiah];
    for (int i = 0; i < jml_hadiah; i++) {
        fscanf(fileHadiah, "%d %d %s %d", &hadiah[i].x, &hadiah[i].y, hadiah[i].nama, &hadiah[i].poin);
    }
    fclose(fileHadiah);

    //selection sort
    for(int i=0; i< jml_hadiah-1; i++){
        int minIndex = i;
        for(int j=i+1; j<jml_hadiah; j++){
            if(hadiah[minIndex].y > hadiah[j].y){
                minIndex=j;
            }
        }
        if(minIndex != i){
            thadiah temp;
            temp.x = hadiah[i].x;
            temp.y = hadiah[i].y;
            temp.poin = hadiah[i].poin;
            strcpy(temp.nama, hadiah[i].nama);

            // Lakukan pertukaran
            hadiah[i].x = hadiah[minIndex].x;
            hadiah[i].y = hadiah[minIndex].y;
            hadiah[i].poin = hadiah[minIndex].poin;
            strcpy(hadiah[i].nama, hadiah[minIndex].nama);

            hadiah[minIndex].x = temp.x;
            hadiah[minIndex].y = temp.y;
            hadiah[minIndex].poin = temp.poin;
            strcpy(hadiah[minIndex].nama, temp.nama);
        }
    }

    FILE *fileHadiahTulis = fopen("thadiah.txt", "w");

    for(int i=0; i<jml_hadiah; i++){
        fprintf(fileHadiahTulis, "%d %d %s %d\n", hadiah[i].x, hadiah[i].y, hadiah[i].nama, hadiah[i].poin);
    }
    fclose(fileHadiahTulis);

}

void tampilThadiah() {
    sorting(); //melakukan sorting dulu

    thadiah temp;
    FILE *thadiah = fopen("thadiah.txt", "r");
    if (thadiah == NULL) {
        printf("File tidak terbuka\n");
        return;
    }

    printf("---------------------------------\n");
    printf("|x\t|y\t|nama\t|skor\t|\n");
    printf("---------------------------------\n");
    while ((fscanf(thadiah, "%d %d %s %d", &temp.x, &temp.y, temp.nama, &temp.poin)) == 4) {
        printf("|%d\t|%d\t|%s\t|%d\t|\n", temp.x, temp.y, temp.nama, temp.poin);
    }
    printf("---------------------------------\n\n");

    fclose(thadiah);
}

void tambahHadiah() {
    tampilThadiah();

    thadiah temp;

    printf("Masukan Posisi hadiah x:");
    scanf("%d", &temp.x);
    printf("Masukan Posisi hadiah y:");
    scanf("%d", &temp.y);
    printf("Masukan nama hadiah: ");
    scanf("%s", temp.nama);
    printf("Masukan poin hadiah: ");
    scanf("%d", &temp.poin);

    FILE *thadiah = fopen("thadiah.txt", "a"); //w
    if (thadiah == NULL) {
        printf("File tidak terbuka\n");
        return;
    }

    fprintf(thadiah, "%d %d %s %d\n", temp.x, temp.y, temp.nama, temp.poin);
    fclose(thadiah);
}

void jeda(float x) {
    time_t start, current;
    time(&start);
    do {
        time(&current);
    } while (difftime(current, start) < x);
}

void simulasi(int papan_x, int papan_y) {
    sorting();//sorting dulu
    
    int jml_gerak = cekBrpLine(2); //2 untuk cek tgerak 4 untuk cek thadiah
    int jml_hadiah = cekBrpLine(4);


    tgerak gerak[jml_gerak];
    thadiah hadiah[jml_hadiah];

    FILE *tgerak = fopen("tgerak.txt", "r");
    FILE *thadiah = fopen("thadiah.txt", "r");

    //memasukan dari txt ke struct
    for (int i = 0; i < jml_gerak; i++) {
        fscanf(tgerak, "%d %d", &gerak[i].x, &gerak[i].y);
    }
    for (int i = 0; i < jml_hadiah; i++) {
        fscanf(thadiah, "%d %d %s %d", &hadiah[i].x, &hadiah[i].y, hadiah[i].nama, &hadiah[i].poin);
    }
    fclose(tgerak);
    fclose(thadiah);

    //memasukan default papan = -1;
    int papan[papan_y][papan_x];
    for (int i = 0; i < papan_y; i++) {
        for (int j = 0; j < papan_x; j++) {
            papan[i][j] = -1;
        }
    }

    //memasukan index hadiah ke papan
    for (int i = 0; i < jml_hadiah; i++) {
        if(hadiah[i].y <= papan_y && hadiah[i].x <= papan_x){
            papan[hadiah[i].y][hadiah[i].x] = i;
        }
    }

    int skor = 0;   //inisialisasi skor dengan 0
    for (int g = 0; g < jml_gerak; g++) {           //memulai pergerakan tgerak

        system("clear");
        
        //jika koordinat gerak menginjak koordinat yang terdapat hadiah
        if(papan[gerak[g].y][gerak[g].x] >= 0){
            int index=papan[gerak[g].y][gerak[g].x];
            skor+=hadiah[index].poin;       //skor bertambah sesuai poin dari hadiah
        }
        papan[gerak[g].y][gerak[g].x]=-2;       //koordinat papan yang ada geraknya diinisialisasi dengan -2

        //bagian atas
        for (int i = 0; i < papan_x * 1.1; i++) {
            printf("-");
        }
        printf("\n");

        //utama
        for (int i = 0; i < papan_y; i++) {
            
            for (int j = 0; j < papan_x; j++) {
                //print pembatas
                if (j == 0) {
                    printf("|");
                } else if (j == papan_x - 1) {
                    printf("\t|");
                }

                //print isi papan
                if(papan[i][j] >= 0){
                    printf("\x1b[35m%s\x1b[30m%d\x1b[0m", hadiah[papan[i][j]].nama, hadiah[papan[i][j]].poin);
                }else if(papan[i][j] == -2){
                    printf("O");
                    papan[i][j] = -1;
                }else{
                    printf(" ");
                }


            }
            printf("\n");
        }

        //bagian bawah
        for (int i = 0; i < papan_x * 1.1; i++) {
            printf("-");
        }
        printf("\n");
        //print skor
        printf("Skor: %d\n", skor);

        jeda(0.5);
    }
}
void liteo(){
    //warna biru
    printf("\x1b[34m");

    char* judul[] = {
        "##       ##   ######   ######            ######     By:",
        "##       ##     ##     ##                ##  ##     Kelompok 5",
        "##       ##     ##     ######   ######   ##  ##     B-S1 Informatika",
        "##       ##     ##     ##                ##  ##     2024",
        "######   ##     ##     ######            ######",
    };

    for(int i = 0; i < 5; i++){
        printf("%s\n", judul[i]);
    }

    //balikin lagi warnanya jadi default
    printf("\x1b[0m");
}

int main() {
    int papan_x, papan_y;
    printf("Lebar Papan: ");
    scanf("%d", &papan_x);
    printf("Panjang Papan: ");
    scanf("%d", &papan_y);

    system("clear");
    liteo();
    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Tambah hadiah\n");
        printf("2. Tambah gerak O\n");
        printf("3. Simulasi Lite-o\n");
        printf("4. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            tambahHadiah();
            break;
        case 2:
            tambahTgerak();
            break;
        case 3:
            simulasi(papan_x, papan_y);
            break;
        case 4:
            exit(0);
            break;
        default:
            printf("Pilihan tidak valid!\n");
            break;
        }
    }

    return 0;
}