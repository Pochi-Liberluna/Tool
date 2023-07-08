#include<stdio.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

int main(void){
  float sahen,uhen,answer;
  char enzan;

  std::cout << "¥n________  _________ ___    __ ___________ ___________ ___  __ __       __\n" << std::endl;
  std::cout << "|   ___  \|   ______|   \  |  |____   ____|  _______  |  | / /|  |     |  |\n" << std::endl;
  std::cout << "|  |   |  |  |______|  | \ |  |   |  |    |  |     |  |  |/ / |  |     |  |\n" << std::endl;
  std::cout << "|  |   |  |   ______|  |\ \|  |   |  |    |  |_____|  |    /  |  |     |  |\n" << std::endl;
  std::cout << "|  |___|  |  |______|  | \    |   |  |    |  |     |  |  |\ \ |  |_____|  |\n" << std::endl;
  std::cout << "|________/|_________|__|  \___|   |__|    |__|     |__|__| \_\|___________|\n" << std::endl;

  printf("これはコマンドプロンプト上で計算を行う簡易電子計算機です。¥nソースコードはGitHubに貼ってあります。->'https://github.com/Pochi-Liberluna/Tool/Windows/C-C++/Dentaku/'¥n");

  printf("数値1を入力してください。=>");
  scanf("%f",&sahen);

  getchar()
    
  printf("¥n演算子を入力してください。=>");
  scanf("%c",&enzan);

  printf("¥n数値2を入力してください。=>");
  scanf("%f",&uhen);

  if(enzan == '+'){
    answer = sahen + uhen;
  } else if(enzan == '-'){
    answer = sahen - uhen;
  } else if(enzan == '*'){
    answer = sahen * uhen;
  } else if(enzan == '/'){
    if(uhen != 0){
    answer = sahen / uhen;
  } else{
      printf("0では割り算ができません。¥n");
      return 0;
  }
} else{
    printf("無効な演算子です。¥n");
    return 0;
}

  printf("計算結果:%.2f¥n",answer); //少数第二位まで表示

  return 0;
}
//AA描くのめんどい

/**
 ________  _________ ___    __ ___________ ___________ ___  __ __       __
|   ___  ¥|   ______|   ¥  |  |____   ____|  _______  |  | / /|  |     |  |
|  |   |  |  |______|  | ¥ |  |   |  |    |  |     |  |  |/ / |  |     |  |
|  |   |  |   ______|  |¥ ¥|  |   |  |    |  |_____|  |    /  |  |     |  |
|  |___|  |  |______|  | ¥ ¥  |   |  |    |  |     |  |  |¥ ¥ |  |_____|  |
|________/|_________|__|  ¥___|   |__|    |__|     |__|__| ¥_¥|___________|

**/
