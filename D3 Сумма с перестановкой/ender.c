#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define int_len 9
#define alphabet_power 10

#define swap(a, b) ({ char tmp = a; a = b; b = tmp; })


char hash[alphabet_power];

void fill_hash(char* b){
    while(*b != '\0')hash[*(b++)-'0']++;
}

int check_hash(char* hash){
    for(int i = 0; i < alphabet_power; i++){
        if(hash[i]) return 0;
    }
    return 1;
}

int check_b(int b){
    if (b < 0) return 0;
    char* temp_hash = alloca(alphabet_power);
    memcpy(temp_hash,hash,alphabet_power);
    for(char* index = itoa(b,alloca(int_len+1),10); *index != '\0'; index++){
        temp_hash[*index-'0']--;
    }
    return check_hash(temp_hash);
}

int permute(char *a, int l, int r,int c)
{
    if (l == r) return (a[1] == '\0' || a[0] != '0') && check_b(c-atoi(a));

    for (int i = l; i <= r; i++)
    {
        swap(a[l], a[i]);
        if(permute(a, l + 1, r, c)){
            return 1;
        }
        swap(a[l], a[i]);
    }
    return 0;
}

int main()
{
    FILE *fIn, *fOut;
    fIn = fopen("input.txt", "r");
    fOut = fopen("output.txt", "w");
    //fIn = stdin;
    //fOut = stdout;
    memset(hash,0,alphabet_power);
    char *a = malloc(int_len+1), *b = malloc(int_len+1);
    int c;
    fscanf(fIn,"%s %s %d", a, b, &c);
    fill_hash(b);
    if(permute(a,0,strlen(a)-1,c)){
        fprintf(fOut,"YES\n%s %d", a, c-atoi(a));
    }
    else{
        fprintf(fOut,"NO");
    }
    return 0;
}
