#include <stdio.h>
#include <stdlib.h>

typedef  ui;

int main()
{
    ui N;
    scanf("%u",&N);
    ui* array = malloc(N*sizeof(ui));
    for(ui* index = array; index < array+N; index++){
        scanf("%u",index);
    }
    ui L = 0, M = 0, R = 0, honey = 0;
    ui* Lm = calloc((N-1),sizeof(ui));
    ui* arena = malloc((N-1)*sizeof(ui));
    ui* Rm = arena - 1;

    for(int m = 0; m < N-1; m++){
        Lm[0] += array[m];
        for(int l = 1; l < m+1; l++){
            Lm[l]=Lm[l-1]-array[l-1];
        }

        Rm[m+1]=array[m+1];
        for(int r = m+2; r < N; r++){
            Rm[r] = Rm[r-1] + array[r];
        }
        ui RmI = N-1;
        for(int l = 0; l < m+1; l++){
            while(RmI>m){
                if(Rm[RmI] == Lm[l]){
                    if(Rm[RmI]>honey){
                        L = l; M = m; R = RmI; honey = Rm[RmI];
                    }
                    else if(Rm[RmI] == honey && l < L){
                        L = l; M = m; R = RmI;
                    }
                    break;
                }
                if(Rm[RmI-1] < Lm[l]){
                    break;
                }
                RmI--;
            }
        }
    }
    if(honey == 0){
        printf("-1");
        return 0;
    }
    printf("%d %d %d",L+1,M+1,R+1);
}
