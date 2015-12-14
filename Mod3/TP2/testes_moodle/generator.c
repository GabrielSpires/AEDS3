#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main() {
  int t = 1;
  printf("%d\n", t);
  while (t--) {
    //int n = rand()%500 + 1;
    int n = 500;
    //int maior = (n > 251) ? 251 : n;
    //int k = rand()%maior;
    int k = 3; //bom para FB
    //k = 200;
    scanf("%d", &k);
    //k = (n < 251) ? n : 250;
    k = (n < 100) ? n : 5000;
    /*
     if (n < 251) k = n
     else k = 250;
    */
    int max = 1000000;
    printf("%d %d\n", n, k);
    for (int i = 0; i <= n; ++i)
      //printf("1000000\n");
      printf("10000\n");
      //printf("%d\n", 900000 + rand()%100000);
  }
  return 0;
}
