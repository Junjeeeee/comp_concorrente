
#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 3

#define MAX_SIZE 1000

// Variaveis globais
sem_t ler_arquivo,ler_buffer1, ler_buffer2;      //semaforos para coordenar a ordem de execucao das threads
char buffer1[MAX_SIZE];
char buffer2[MAX_SIZE];


//funcao executada pela thread 1
void *t1 (void *arg) {
    FILE* arquivo = (FILE*)arg;
    int count = 0;
    char c;
    while ((c = fgetc(arquivo)) != EOF) {
        sem_wait(&ler_arquivo);
        buffer1[count] = c;
        count++;
        if(count == MAX_SIZE) count = 0;
        sem_post(&ler_buffer1);
    }
    sem_wait(&ler_arquivo);
    buffer1[count] = '\0';
    sem_post(&ler_buffer1);
   pthread_exit(NULL);
}

//funcao executada pela thread 2
void *t2 (void *arg) {
   int count_buffer1 = 0;
   int count_buffer2 = 0;
   int quant = 0;
    int n= 0;
    // 2n+1 sequencia = 3 5 7 9 11 13 15 17 19 10
   while(1)
   {
        sem_wait(&ler_buffer1);
        if(buffer1[count_buffer1] == '\0') break;
        if((quant == 10 && n == 10) || (n<10 && quant == (2*n)+1))
        {
            
            if(n<10) n++;
            quant = 0;
            buffer2[count_buffer2] = '\n';
            count_buffer2++;
            if(count_buffer2 == MAX_SIZE) count_buffer2 = 0;
            sem_post(&ler_buffer2);

        }
        buffer2[count_buffer2] = buffer1[count_buffer1];
        count_buffer1++;
        count_buffer2++;
        if(count_buffer2 == MAX_SIZE) count_buffer2 = 0;
        if(count_buffer1 == MAX_SIZE) count_buffer1 = 0;
        quant++;
        sem_post(&ler_buffer2);
        sem_post(&ler_arquivo);
   }
   sem_post(&ler_buffer2);
   pthread_exit(NULL);
}

//funcao executada pela thread 3
void *t3 (void *arg) {
   int count_buffer2 = 0;
   while(1)
   {
        sem_wait(&ler_buffer2);
        if(buffer2[count_buffer2] == '\0') break;
        printf("%c",buffer2[count_buffer2]);
        count_buffer2++;
        if(count_buffer2 == MAX_SIZE) count_buffer2 = 0;
   }
   pthread_exit(NULL);
}

//funcao principal
int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Uso: %s <nome_do_arquivo>\n", argv[0]);
        return 1;
    }

    FILE* arquivo = fopen(argv[1], "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

  pthread_t tid[NTHREADS];

  //inicia os semaforos
  sem_init(&ler_arquivo, 0, MAX_SIZE-1);
  sem_init(&ler_buffer1, 0, 0);
  sem_init(&ler_buffer2, 0, 0);

  //cria as tres threads
  if (pthread_create(&tid[2], NULL, t3, NULL)) { 
	  printf("--ERRO: pthread_create()\n"); exit(-1); }
  if (pthread_create(&tid[1], NULL, t2, NULL)) { 
	  printf("--ERRO: pthread_create()\n"); exit(-1); }
  if (pthread_create(&tid[0], NULL, t1, arquivo)) { 
	  printf("--ERRO: pthread_create()\n"); exit(-1); }

  //--espera todas as threads terminarem
  for (int t=0; t<NTHREADS; t++) {
    if (pthread_join(tid[t], NULL)) {
         printf("--ERRO: pthread_join() \n"); exit(-1); 
    } 
  } 

  return 0;
}
