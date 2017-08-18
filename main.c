#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int score(char x, char y,int a, int b, int c){
    int skor;
    if(x==y){
        skor = a;
    }
    else if(x=='-'){
        skor = b;
    }
    else{
        skor = c;
    }
    return skor;
    }

int maximum(int x,int y,int z){

    if( x>=y && x>=z)
        return x;

    else if (y>=x && y>=z)
        return y;

    else
        return z;
}

int main()
{
    int match, mismatch, gap, lowRoad, highRoad;
    char dna1[20];
    char dna2[20];
    int a;
    for(a=0;a<20;a++){
        dna1[a]=' ';
       }

    for(a=0;a<20;a++){
        dna2[a]=' ';
       }
    int i,j;
    int dna1elemansayisi=0;
    int dna2elemansayisi=0;

    FILE *inputs;
    inputs = fopen("inputs.txt ", "r");
    FILE *outputDNA;
    outputDNA = fopen("output.txt", "w");

    if (inputs == NULL)
    {
        printf("input bulunamadi.\n");
    }
    else{
        fscanf(inputs,"%d %d %d %d %d %s %s\n\n",&match, &mismatch, &gap, &lowRoad, &highRoad, &dna1, &dna2);
                //inputtan degisken alinmasi
        printf("%d,%d,%d,%d,%d\n%s\n%s\n",match,mismatch,gap,lowRoad,highRoad,dna1,dna2);
                //matris buyuklugu icin string uzunlugu alimi
        dna1elemansayisi = strlen(dna1);
        dna2elemansayisi = strlen(dna2);
        int aligmentTable[dna1elemansayisi+2][dna2elemansayisi+2];
        aligmentTable[0][0] = 0;

        //kavramsal boşluk
        aligmentTable[1][1] = 0;

        //kavramsal boşluk sonrası ilk satır ve sütun elemanları ataması
        for(i=0;i<=dna1elemansayisi+1;i++){
                aligmentTable[1][i+1] = i*gap;
            }

        for(j=0;j<=dna2elemansayisi+1;j++){
                aligmentTable[j+1][1] = j*gap;
                }

        for(i=2;i<dna1elemansayisi+2;i++){
           for(j=2;j<dna2elemansayisi+2;j++){
                aligmentTable[i][j] = maximum((aligmentTable[i][j-1]+score('-',dna1[j-2],match,mismatch,gap) ),
                                              (aligmentTable[i-1][j]+score(dna2[i-2],'-',match,mismatch,gap)),
                                              (aligmentTable[i-1][j-1]+score(dna2[i-2],dna1[j-2],match,mismatch,gap)) );
                     }
        }

       for(i=0;i<=dna1elemansayisi;i++){
            for(j=0;j<=dna2elemansayisi;j++){
                printf("%d \t", aligmentTable[i+1][j+1]);
            }
            printf("\n");
       }
        for(i=0;i<=dna1elemansayisi;i++){
            for(j=0;j<=dna2elemansayisi;j++){
                fprintf(outputDNA,"%d \t", aligmentTable[i+1][j+1]);
            }
            fputs("\n",outputDNA);
       }
        printf("\n");
        printf("\n");
       for(i=0;i<20;i++){
        printf("%c",dna1[i]);
       }
       printf("\n");
       for(i=0;i<20;i++){
        printf("%c",dna2[i]);
       }

    }
    fclose(inputs);
    fclose(outputDNA);
}
