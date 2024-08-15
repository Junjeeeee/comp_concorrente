#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>

int *entrada; //array de entrada

typedef struct{
    int indice_inicial;
    int indice_apos_o_final;
} atributos_muda_entrada;

void *muda_entrada(void* indices_p)
{
    atributos_muda_entrada *indices = (atributos_muda_entrada *) indices_p;

    for(int i=indices->indice_inicial;i<indices->indice_apos_o_final;i++)
    {
        entrada[i]++;
    }

    free(indices_p);
}


int main(int argc, char * argv[]) {
    int nthreads; //qtde de threads que serao criadas (recebida na linha de comando)
    int nelementos;//qtde de elementos do array (recebida na linha de comando)
    atributos_muda_entrada *atributos;

    if(argc<2) {
       printf("--ERRO: informe a qtde de threads <%s> <nthreads>\n", argv[0]);
       return 1;
    }
    nthreads = atoi(argv[1]);

    if(argc<3) {
        printf("--ERRO: informe a qtde de numeros do array <%s> <nelementos>\n", argv[0]);
        return 1;
    }
    nelementos = atoi(argv[2]);

    entrada = (int*)malloc(nelementos*sizeof(int)); // dá malloc no vetor
    for(int i=0;i<nelementos;i++) entrada[i] = 0; //preenche o vetor com 0s.

    int quant_cada_thread = nelementos/nthreads;
    int p_inicial = 0;
    int p_final = quant_cada_thread;
    p_final += (nelementos%nthreads); // primeira thread pegará o resto da divisão como trabalho para si
   
    pthread_t tid_sistema[nthreads];

    for(int i=1; i<=nthreads; i++) 
    {
        printf("--Aloca e preenche argumentos para thread %d\n", i);
        atributos = malloc(sizeof(atributos_muda_entrada));
        if (atributos == NULL) 
        {
            printf("--ERRO: malloc()\n"); 
            return 1;
        }
        atributos->indice_inicial = p_inicial; 
        atributos->indice_apos_o_final = p_final;
        p_inicial = p_final;
        p_final+=quant_cada_thread; 

        printf("--Cria a thread %d\n", i);
        if (pthread_create(&tid_sistema[i-1], NULL, muda_entrada, (void*) atributos)) 
        {
            printf("--ERRO: pthread_create()\n"); 
            return 2;
        }
    }

    //espera todas as threads terminarem
    for (int i=0; i<nthreads; i++) {
        if (pthread_join(tid_sistema[i], NULL)) 
        {
            printf("--ERRO: pthread_join() da thread %d\n", i); 
        } 
    }

    for(int i=0;i<nelementos;i++)
    {
        printf("%i ",entrada[i]);
    }
    printf("\n");
    return 0;
}


