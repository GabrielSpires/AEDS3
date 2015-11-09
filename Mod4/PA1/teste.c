#include <stdio.h>

int main()
{
    long int i,j,c[100000],s[100000];
    int n,v,fail=0;
    while(1){
        scanf("%d %d",&n,&v);
        if(n==0 || v==0)
            return 0;
        fail = 0;
        for(i=0;i<n;i++){
            scanf("%ld %ld",&c[i],&s[i]);
            if(i>0){
                if(c[i]<s[i-1]&&v==0)
                    fail++;
                if(c[i]>=s[i-1]){
                    v++;
                }
                for(j=i-1;j>=0;j--)
                    if(s[i]>s[j]&&c[i]<s[j])
                        fail++;
            }
        }
        if(fail>0)
            printf("Nao\n");
        else
            printf("Sim\n");
    }
    return 0;
}