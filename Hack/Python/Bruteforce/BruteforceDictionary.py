import random
from itertools import permutations

characters = ["", "", "", "", "", "", "", "", "", "", ""]   #これは11文字に対応してますが自分で文字数を指定できます。
count = 0

for perm in permutations(characters):
    shuffled_word = ''.join(perm)
    print(shuffled_word)
    count += 1

print("出力できた単語数:", count, "語")
input("終了するには Enter キーを押してください...")
