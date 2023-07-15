/**
import random
from itertools import permutations
import time

characters = ["0", "1", "2", "3"]
count = 0

if not characters:
    print("エラー: 総当たりする文字列が設定されていません。")
else:
    start_time = time.time()

    for perm in permutations(characters):
        shuffled_word = ''.join(perm)
        print(shuffled_word)
        count += 1

    end_time = time.time()
    elapsed_time = end_time - start_time
    print("出力できた単語数:", count, "語", "{:.2f}秒".format(elapsed_time))

Pythonで書けば20行近くなのにね、、
GPTを使いPythonのコードをJavaに変換しました。
**/
import java.util.ArrayList;
import java.util.List;

public class PermutationExample {
    public static void main(String[] args) {
        String[] characters = {"0", "1", "2", "3"};    //ここでは0,1,2,3の組み合わせを総当たりさせる
        int count = 0;

        if (characters.length == 0) {
            System.out.println("エラー: 総当たりする文字列が設定されていません。");
        } else {
            long startTime = System.currentTimeMillis();

            List<String> permutations = generatePermutations(characters);
            for (String permutation : permutations) {
                System.out.println(permutation);
                count++;
            }

            long endTime = System.currentTimeMillis();
            double elapsedSeconds = (endTime - startTime) / 1000.0;
            System.out.println("出力できた単語数: " + count + "語 " + String.format("%.2f秒", elapsedSeconds));
        }
    }

    private static List<String> generatePermutations(String[] characters) {
        List<String> permutations = new ArrayList<>();
        permute(characters, 0, permutations);
        return permutations;
    }

    private static void permute(String[] characters, int start, List<String> permutations) {
        if (start == characters.length - 1) {
            StringBuilder sb = new StringBuilder();
            for (String ch : characters) {
                sb.append(ch);
            }
            permutations.add(sb.toString());
        } else {
            for (int i = start; i < characters.length; i++) {
                swap(characters, start, i);
                permute(characters, start + 1, permutations);
                swap(characters, start, i);
            }
        }
    }

    private static void swap(String[] characters, int i, int j) {
        String temp = characters[i];
        characters[i] = characters[j];
        characters[j] = temp;
    }
}
