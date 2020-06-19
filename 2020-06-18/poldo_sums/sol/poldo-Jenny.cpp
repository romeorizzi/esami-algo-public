#include<stdio.h>
#include<cstdio>
#include<iostream>
#include<stdlib.h>
#include<cassert>
#include<vector>

using namespace std;

#define MAXN 10005

struct poset{
    int peso;
    poset* prec;
    poset(int p){
        peso = p;
    }
    poset(){}
};

int N;
int p[MAXN];
int chain[MAXN];
poset lista[MAXN];
long int tmp=0;
int maxp = 0;
FILE *in, *out;

void stampa_ris(poset *nodo, int cont){
    if( nodo->prec == nullptr ){

    }else{
        stampa_ris(nodo->prec,1);
    }
    fprintf(out, "%d", nodo->peso);
    if(cont != 0)
        fprintf(out, " ");
}

int main(){
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");


    int t;
    fscanf(in,"%d", &N);
    for(int i=0; i<N; i++){
        fscanf(in,"%d", &p[i]);
        lista[i].peso = p[i];
    }

    for(int i=0; i<N; i++){
        for(int j=i+1; j<N; j++){
            if(p[i]>p[j] && chain[i] >= chain[j]){
                chain[j] = chain[i]+1;
                lista[j].prec = &lista[i];
            }
        }
    }

    for(int i=0;i<N;i++){
        if(chain[i]>= chain[maxp]){
            maxp = i;
        }
    }

    fprintf(out,"%d\n", chain[maxp]+1);
    stampa_ris(&lista[maxp],0);

    return 0;
}
