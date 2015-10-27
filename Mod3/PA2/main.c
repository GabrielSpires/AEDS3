#include <stdio.h>

int fibnc(int, int*);

int main(int argc, char const *argv[]){
	int n, f, x, c = 0;

	scanf("%d", &n);
	while(n--){
		scanf("%d", &x);
		f = fibnc(x, &c);
		printf("fib(%d) = %d calls = %d\n", x, c, f);
		c=0;
	}
	return 0;
}

int fibnc(int x, int *c){
	if(x==0){
		return 0;
	}else if(x==1){
		return 1;
	}
	*c = *c + 2;
	return fibnc(x-1, c)+fibnc(x-2, c);
}