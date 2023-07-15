#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(char *x, char *y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}

void permute(char *characters, int start, int end, int *count) {
    if (start == end) {
        printf("%s\n", characters);
        (*count)++;
    } else {
        for (int i = start; i <= end; i++) {
            swap(&characters[start], &characters[i]);
            permute(characters, start + 1, end, count);
            swap(&characters[start], &characters[i]); // バックトラック
        }
    }
}

int main() {
    char characters[] = {'0', '1', '2', '3'};  //ここでは0,1,2,3を総当たりする
    int count = 0;
    int length = sizeof(characters) / sizeof(characters[0]) - 1;

    if (length == 0) {
        printf("エラー: 総当たりする文字列が設定されていません。\n");
    } else {
        clock_t start_time = clock();

        permute(characters, 0, length - 1, &count);

        clock_t end_time = clock();
        double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("出力できた単語数: %d語 %.5f秒\n", count, elapsed_time);
    }

    return 0;
}
