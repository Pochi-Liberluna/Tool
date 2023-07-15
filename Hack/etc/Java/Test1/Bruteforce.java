/**
import random
from itertools import permutations

characters = [ "", "", "",  "", "", "", "", ""]
count = 0

for perm in permutations(characters):
    shuffled_word = ''.join(perm)
    print(shuffled_word)
    count += 1

print("出力できた単語数:", count, "語")
input("終了するには Enter キーを押してください...")

Pythonで書けば10行近くなのにね、、
GPTを使いPythonのコードをJavaに変換しました。
**/
import java.util.ArrayList;
import java.util.List;

public class PermutationExample {
    public static void main(String[] args) {
        String[] characters = {"", "", "", "", "", "", "", ""};
        int count = 0;

        List<String> permutations = generatePermutations(characters);
        for (String permutation : permutations) {
            System.out.println(permutation);
            count++;
        }

        System.out.println("出力できた単語数: " + count + "語");
        System.out.println("終了するには Enter キーを押してください...");
        try {
            System.in.read();
        } catch (Exception e) {
            e.printStackTrace();
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
