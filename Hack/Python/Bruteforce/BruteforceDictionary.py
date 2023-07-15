import random
from itertools import permutations
import time

characters = ["0", "1", "2", "3"]    #0,1,2,3を総当たり
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
