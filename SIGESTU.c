#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int matricula;
    char nome[100];
    float nota;
} Estudante;

Estudante estudantes[MAX];
int total = 0;

/* Mostrar estudantes */

void mostrarEstudantes() {

    if(total == 0) {
        printf("\n[×] Nenhum estudante carregado!\n");
        return;
    }

    printf("\n%-12s %-30s %-10s\n",
           "Matricula","Nome","Nota");

    for(int i=0; i<total; i++) {
        printf("%-12d %-30s %.2f\n",
               estudantes[i].matricula,
               estudantes[i].nome,
               estudantes[i].nota);
    }
}

/* Ler ficheiro */

void lerFicheiro() {

    FILE *fp = fopen("estudantes.txt","r");

    if(fp == NULL) {
        printf("\n[×] Erro ao abrir estudantes.txt\n");
        return;
    }

    total = 0;

    while(fscanf(fp,"%d;%99[^;];%f",
                 &estudantes[total].matricula,
                 estudantes[total].nome,
                 &estudantes[total].nota) == 3)
    {
        total++;
    }

    fclose(fp);

    printf("\n[V] %d estudantes carregados com sucesso!\n",
           total);
}

/* Troca */

void trocar(Estudante *a, Estudante *b) {

    Estudante temp = *a;
    *a = *b;
    *b = temp;
}

/* Bubble Sort */

void bubbleSort(int criterio) {

    for(int i=0; i<total-1; i++) {

        for(int j=0; j<total-i-1; j++) {

            int troca = 0;

            if(criterio == 1)
                troca =
                    estudantes[j].matricula >
                    estudantes[j+1].matricula;

            else if(criterio == 2)
                troca =
                    strcmp(estudantes[j].nome,
                           estudantes[j+1].nome) > 0;

            else if(criterio == 3)
                troca =
                    estudantes[j].nota <
                    estudantes[j+1].nota;

            if(troca)
                trocar(&estudantes[j],
                       &estudantes[j+1]);
        }
    }

    printf("\n[V] Ordenacao concluida (Bubble Sort).\n");
}

/* Selection Sort */

void selectionSort(int criterio) {

    for(int i=0; i<total-1; i++) {

        int pos = i;

        for(int j=i+1; j<total; j++) {

            if(criterio == 1 &&
                    estudantes[j].matricula <
                    estudantes[pos].matricula)
                pos = j;

            else if(criterio == 2 &&
                    strcmp(estudantes[j].nome,
                           estudantes[pos].nome) < 0)
                pos = j;

            else if(criterio == 3 &&
                    estudantes[j].nota >
                    estudantes[pos].nota)
                pos = j;
        }

        trocar(&estudantes[i],
               &estudantes[pos]);
    }

    printf("\n[V] Ordenacao concluida (Selection Sort).\n");
}

/* Insertion Sort */

void insertionSort(int criterio) {

    for(int i=1; i<total; i++) {

        Estudante chave = estudantes[i];
        int j = i - 1;

        if(criterio == 1) {

            while(j >= 0 &&
                    estudantes[j].matricula >
                    chave.matricula) {

                estudantes[j+1] = estudantes[j];
                j--;
            }
        }

        else if(criterio == 2) {

            while(j >= 0 &&
                    strcmp(estudantes[j].nome,
                           chave.nome) > 0) {

                estudantes[j+1] = estudantes[j];
                j--;
            }
        }

        else {

            while(j >= 0 &&
                    estudantes[j].nota <
                    chave.nota) {

                estudantes[j+1] = estudantes[j];
                j--;
            }
        }

        estudantes[j+1] = chave;
    }

    printf("\n[V] Ordenacao concluida (Insertion Sort).\n");
}

/*--------------------------------------------------*/
/* Pesquisa Linear por Matrícula */
/*--------------------------------------------------*/
void pesquisaLinearMatricula() {

    int mat;

    printf("\nMatricula: ");
    scanf("%d",&mat);

    for(int i=0; i<total; i++) {

        if(estudantes[i].matricula == mat) {

            printf("\n[V] Encontrado!\n");
            printf("%d | %s | %.2f\n",
                   estudantes[i].matricula,
                   estudantes[i].nome,
                   estudantes[i].nota);
            return;
        }
    }

    printf("\n[×] Nao encontrado.\n");
}

/* Pesquisa Linear por Nome */

void pesquisaLinearNome() {

    char nome[100];

    getchar();

    printf("\nNome: ");
    fgets(nome,100,stdin);

    nome[strcspn(nome,"\n")] = 0;

    for(int i=0; i<total; i++) {

        if(strcmp(estudantes[i].nome,nome)==0) {

            printf("\n[V] Encontrado!\n");
            printf("%d | %s | %.2f\n",
                   estudantes[i].matricula,
                   estudantes[i].nome,
                   estudantes[i].nota);
            return;
        }
    }

    printf("\n[×] Nao encontrado.\n");
}

/* Pesquisa Binaria */

void pesquisaBinaria() {

    int mat;

    printf("\nMatricula: ");
    scanf("%d",&mat);

    int inicio = 0;
    int fim = total - 1;

    while(inicio <= fim) {

        int meio = (inicio + fim)/2;

        if(estudantes[meio].matricula == mat) {

            printf("\n[V] Encontrado!\n");
            printf("%d | %s | %.2f\n",
                   estudantes[meio].matricula,
                   estudantes[meio].nome,
                   estudantes[meio].nota);
            return;
        }

        if(mat < estudantes[meio].matricula)
            fim = meio - 1;
        else
            inicio = meio + 1;
    }

    printf("\n[×] Nao encontrado.\n");
}

/* Gravar Texto */

void gravarTexto() {

    FILE *fp = fopen("saida.txt","w");

    if(fp == NULL) {
        printf("\n[×] Erro ao gravar ficheiro.\n");
        return;
    }

    for(int i=0; i<total; i++) {

        fprintf(fp,"%d;%s;%.2f\n",
                estudantes[i].matricula,
                estudantes[i].nome,
                estudantes[i].nota);
    }

    fclose(fp);

    printf("\n[V] Dados gravados em saida.txt\n");
}

/* Gravar Binário */

void gravarBinario() {

    FILE *fp = fopen("saida.bin","wb");

    if(fp == NULL) {
        printf("\n[×] Erro ao gravar ficheiro.\n");
        return;
    }

    fwrite(estudantes,
           sizeof(Estudante),
           total,
           fp);

    fclose(fp);

    printf("\n[V] Dados gravados em saida.bin\n");
}

/* Main */

int main() {

    int op;

    do {

        printf("\n=========================================");
        printf("\n>> > SISTEMA DE GESTÃO DE ESTUDANTES < <<");
        printf("\n=========================================");
        printf("\n[1] > Ler ficheiro");
        printf("\n[2] > Mostrar estudantes");
        printf("\n[3] > Ordenar");
        printf("\n[4] > Pesquisar");
        printf("\n[5] > Gravar texto");
        printf("\n[6] > Gravar binario");
        printf("\n[0] > Sair");
        printf("\nOpcao: ");

        scanf("%d",&op);

        switch(op) {

        case 1:
            lerFicheiro();
            break;

        case 2:
            mostrarEstudantes();
            break;

        case 3: {

            int alg, crit;

            printf("\n>> > Algoritmo < <<");
            printf("\n[1] > Bubble");
            printf("\n[2] > Selection");
            printf("\n[3] > Insertion");
            printf("\nEscolha: ");
            scanf("%d",&alg);

            printf("\n>> > Criterio < <<");
            printf("\n[1] > Matricula");
            printf("\n[2] > Nome");
            printf("\n[3] > Nota");
            printf("\nEscolha: ");
            scanf("%d",&crit);

            if(alg==1) bubbleSort(crit);
            else if(alg==2) selectionSort(crit);
            else if(alg==3) insertionSort(crit);

            break;
        }

        case 4: {

            int p;
            printf("\n>> > Pesquisa < <<");
            printf("\n[1] > Linear por Matricula");
            printf("\n[2] > Linear por Nome");
            printf("\n[3] > Binaria por Matricula");
            printf("\nEscolha: ");
            scanf("%d",&p);

            if(p==1)
                pesquisaLinearMatricula();
            else if(p==2)
                pesquisaLinearNome();
            else if(p==3)
                pesquisaBinaria();

            break;
        }

        case 5:
            gravarTexto();
            break;

        case 6:
            gravarBinario();
            break;
        }

    } while(op != 0);

    return 0;
}