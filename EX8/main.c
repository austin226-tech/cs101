#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 256


int is_winning_ticket(int winning_nums[], int numbers[]) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 3; j++) {
            if (numbers[i] == winning_nums[j]) {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    int winning_nums[3];
    char line[MAX_LINE_LEN];
    char current_date[MAX_LINE_LEN] = "Unknown Date"; 
    FILE *fp;
    
    printf("請輸入中獎號碼三個: ");
    if (scanf("%d %d %d", &winning_nums[0], &winning_nums[1], &winning_nums[2]) != 3) {
        printf("輸入格式錯誤，請輸入三個整數。\n");
        return 1;
    }

    printf("輸入中獎號碼為: %02d %02d %02d\n", winning_nums[0], winning_nums[1], winning_nums[2]);
    printf("以下為中獎彩卷:\n");
    fp = fopen("lotto.txt", "r");
    if (fp == NULL) {
        printf("錯誤：無法開啟 lotto.txt (請確認檔案是否存在)\n");
        return 1;
    }
    while (fgets(line, MAX_LINE_LEN, fp) != NULL) {
        line[strcspn(line, "\r\n")] = 0;
        if (strstr(line, "= ") != NULL && strstr(line, "lotto649") == NULL && strstr(line, "csie") == NULL) {
            strcpy(current_date, line); 
        }
        if (line[0] == '[') {
            int id, n[7];
            if (sscanf(line, "[%d]: %d %d %d %d %d %d %d", 
                       &id, &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6]) == 8) {
                
                if (is_winning_ticket(winning_nums, n)) {
                    printf("售出時間: %s\n", current_date); 
                    printf("%s\n", line);
                }
            }
        }
    }

    fclose(fp);
    return 0;
}
