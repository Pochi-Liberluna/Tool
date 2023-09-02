## About
このディレクトリにある<a href="https://github.com/Pochi-Liberluna/Tool/tree/main/header file(c-cpp)/MersennePrime/Mersenne(Lucas-Lehmer法未実装)/Mersenne.hpp">ヘッダーファイル</a>は外部のライブラリである、
</br>
GMPを使用します。GMPは大きな整数計算をサポートするライブラリなので選びました。
# 使用方法
まずGMPをインストールし、GMPラッパーとして利用可能な「gmpxx(.h)」をインクルードします。
# アルゴリズム
mpz_ui_pow_ui関数で非常に大きな指数のべき乗計算を効率的に行います。また、mpz_probab_prime_p関数使用して
</br>
メルセンヌ数の2^p-1が素数かどうかを判別します。
