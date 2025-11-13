#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
int main() {
    FILE *fp_txt, *fp_bin;
    int counter = 0;
    int i, j, k, repeat;
    int lotto[5][7];
    time_t now;
    struct tm *t;
 
    srand((unsigned)time(NULL));  
 
    fp_bin = fopen("counter.bin", "r");
    if (fp_bin == NULL) {
        fp_bin = fopen("counter.bin", "w");
        fwrite(&counter, sizeof(int), 1, fp_bin);
        fclose(fp_bin);
        fp_bin = fopen("counter.bin", "r");
    }
 
    fread(&counter, sizeof(int), 1, fp_bin);
    fclose(fp_bin);
 
    counter++;
 
    fp_bin = fopen("counter.bin", "w");
    fwrite(&counter, sizeof(int), 1, fp_bin);
    fclose(fp_bin);
 
    char filename[64];
    sprintf(filename, "lotto[%05d].txt", counter);
 
    fp_txt = fopen(filename, "w");
 
    time(&now);
    t = localtime(&now);
 
    fprintf(fp_txt, "========= lotto649 =========\n");
    fprintf(fp_txt, "======= %04d/%02d/%02d %02d:%02d:%02d =======\n",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec);
 
    for (i = 0; i < 5; i++) {
        fprintf(fp_txt, "[%d]: ", i + 1);
        for (j = 0; j < 7; j++) lotto[i][j] = 0;
 
        for (j = 0; j < 7; j++) {
            do {
                lotto[i][j] = rand() % 69 + 1;
                repeat = 0;
                for (k = 0; k < j; k++) {
                    if (lotto[i][j] == lotto[i][k]) repeat = 1;
                }
            } while (repeat);
        }
 
        for (j = 0; j < 6; j++) {
            for (k = j + 1; k < 7; k++) {
                if (lotto[i][j] > lotto[i][k]) {
                    int temp = lotto[i][j];
                    lotto[i][j] = lotto[i][k];
                    lotto[i][k] = temp;
                }
            }
        }
 
        for (j = 0; j < 7; j++) fprintf(fp_txt, "%02d ", lotto[i][j]);
        fprintf(fp_txt, "\n");
    }
 
    fprintf(fp_txt, "========= csie@CGU =========\n");
    fclose(fp_txt);
 
    printf("已產生 %s\n", filename);
    return 0;
}
