/**
 *  Template per soluzione in c per il problema tree_split_out
 *
 *  Romeo Rizzi, per l'appello di algoritmi 2019-09-04
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000000

int n = 0, input_type;
char str[MAX_N];
int in_tree[MAX_N], out_tree[MAX_N];

void parse_array(int *v, int *len, char *str){
    char *num=strtok(str," ");
    do{
        //v[(*len)++]=strtol(num,NULL,10);
        v[(*len)++]=atoi(num);
    }while((num=strtok(NULL, " "))!=NULL);
}

int main() {
  // leggere l'input_type:
  scanf("%d",&input_type);

  // leggo il resto della riga come stringa
  //FILE *input=fopen("input.txt", "r");
  FILE *input=stdin;
  fgets(str,MAX_N,input); // se da file, impostare la variabile <input> al file desiderato. Preferiamo utilizzare fgets invece di gets per ragioni di stabilità e generalità.

  // ottengo la sequenza che codifica l'albero in input (in formato input_type):
  parse_array(in_tree,&n,str);
  

  // in questo template di soluzione mi limito a ricopiare l'input in output (non sarà mai la soluzione corretta tranne che per alberi di un solo nodo):
  printf("%d ", input_type);

  for(int i=0; i<n; i++)
    printf("%d ", in_tree[i]);
  printf("\n");
  
  return 0;
}

