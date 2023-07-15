#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>

void permute(std::vector<char>& characters, int start, int end, int& count) {
    if (start == end) {
        for (const char& ch : characters) {
            std::cout << ch;
        }
        std::cout << std::endl;
        count++;
    } else {
        for (int i = start; i <= end; i++) {
            std::swap(characters[start], characters[i]);
            permute(characters, start + 1, end, count);
            std::swap(characters[start], characters[i]); // バックトラック
        }
    }
}

int main() {
    std::vector<char> characters = {'0', '1', '2', '3'};  //ここでは0,1,2,3を総当たりする
    int count = 0;

    if (characters.empty()) {
        std::cout << "エラー: 総当たりする文字列が設定されていません。\n";
    } else {
        clock_t start_time = clock();

        permute(characters, 0, characters.size() - 1, count);

        clock_t end_time = clock();
        double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
        std::cout << "出力できた単語数: " << count << "語 " << elapsed_time << "秒\n";
    }

    return 0;
}
