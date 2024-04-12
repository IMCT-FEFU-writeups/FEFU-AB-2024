#include <stdio.h>
#include <stdlib.h>

#define max(a,b)((a)>(b)?(a):(b))
#define min(a,b)((a)>(b)?(a):(b))

typedef int ui;


typedef struct
{
    int value;
    int dec;
    int inc;
    int point;
} DATA,*HDATA;

int cmp(const void* a, const void* b)
{
    return ((HDATA)a)->value>((HDATA)b)->value? 1:-1;
}

typedef struct
{
    HDATA array;
    int minp;
    int size;
    int gap;
} VECTOR,*HVECTOR;

long long calculateBattels(HVECTOR PTeam, HVECTOR OTeam)
{
    long long diff = 0;
    int lseen = 0;
    if(PTeam->size == 0 || OTeam->size == 0) return 0;
    for(int i = 0; i < OTeam->size; i++)
    {
        for(int j = lseen; j <= PTeam->size; j++)
        {
            if(j == 0 && PTeam->array[j].value > OTeam->array[i].value)
            {
                PTeam->array[j].inc++;
                diff+=PTeam->size;
                break;
            }
            if(j == PTeam->size)
            {
                PTeam->array[j-1].dec++;
                diff-=PTeam->size;
                break;
            }
            if(PTeam->array[j].value > OTeam->array[i].value)
            {
                PTeam->array[j].inc++;
                PTeam->array[j-1].dec++;
                diff+=PTeam->size-2*j;
                lseen = j;
                break;
            }
        }
    }
    return diff;
}

int calculateBattelsR(HVECTOR PTeam, HVECTOR OTeam)
{
    long long diff = -1000;
    int lseen = 0;
    if(OTeam->size == 0) return 0;
    if(PTeam->size == 0)
    {
        for(int i = 0; i < OTeam->size; i++)
        {
            diff = max(diff,-OTeam->array[i].point);
        }
        return diff;
    }
    for(int i = 0; i < OTeam->size; i++)
    {
        for(int j = lseen; j <= PTeam->size; j++)
        {
            if(j == 0 && PTeam->array[j].value > OTeam->array[i].value)
            {
                diff = max(diff,-PTeam->size - OTeam->array[i].point);
                break;
            }
            if(j == PTeam->size)
            {
                diff = max(diff, PTeam->size - OTeam->array[i].point);
                break;
            }
            if(PTeam->array[j].value > OTeam->array[i].value)
            {
                diff = max(diff,-PTeam->size+2*j - OTeam->array[i].point);
                lseen = j;
                break;
            }
        }
    }
    return diff;
}

void calculatePoints(HVECTOR vector)
{
    int inc = 0;
    for(int i = 0; i < vector->size; i++)
    {
        inc+=vector->array[i].inc;
        vector->array[i].point=inc;
    }
    int dec = 0;
    for(int i = vector->size-1; i >= 0; i--)
    {
        dec+=vector->array[i].dec;
        vector->array[i].point-=dec;
        vector->minp = min(vector->array[i].point,vector->minp);
    }
}


void push(HVECTOR vector, ui value)
{
    if(!vector->array)
    {
        vector->array=malloc(4*sizeof(DATA));
        vector->gap=4;
        vector->minp = 0;
    }
    if(vector->size>=vector->gap)
    {
        vector->gap<<=1;
        vector->array=realloc(vector->array,vector->gap*sizeof(DATA));
    }
    vector->array[vector->size++]=(DATA)
    {
        value,0
    };

}

void sort(HVECTOR vector)
{
    qsort(vector->array,vector->size,sizeof(DATA),cmp);
}

int main()
{
    FILE *fIn, *fOut;
    fIn = fopen("input.txt","r");
    fOut = fopen("output.txt","w");
    int N, M;
    //fIn = stdin;
    //fOut = stdout;

    fscanf(fIn,"%d %d", &N, &M);
    HVECTOR Pweigths = calloc(M,sizeof(VECTOR));// Pahom team's weigth
    HVECTOR Oweigths = calloc(M,sizeof(VECTOR));//Opponent team's weigth

    ui weigth, mastery;
    for(int i = 0; i < N; i++)
    {
        fscanf(fIn,"%d %d",&mastery, &weigth);
        push(Pweigths+weigth-1,mastery);
    }

    for(HVECTOR category = Pweigths; category < Pweigths + M; category++)
    {
        sort(category);
    }

    for(int i = 0; i < N; i++)
    {
        fscanf(fIn,"%d %d",&mastery, &weigth);
        push(Oweigths+weigth-1,mastery);
    }

    for(HVECTOR category = Oweigths; category < Oweigths + M; category++)
    {
        sort(category);
    }
    int points = 0;
    for(int i = 0; i < M; i++)
    {
        points+=calculateBattels(Pweigths+i,Oweigths+i);
        calculatePoints(Pweigths+i);
    }
    int max_diff = 0;
    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < M; j++)
        {
            if(j==i) continue;
            if(Pweigths[i].minp+Oweigths[j].size<=max_diff)
            {
                continue;
            }
            max_diff = max(max_diff, calculateBattelsR(Oweigths+j,Pweigths+i));

        }
    }
    fprintf(fOut,"%d",points+max_diff);
    return 0;
}
