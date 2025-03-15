#include <stdio.h>
#include <stdlib.h>

#define AlUNOS 1
#define DISCIPLINAS 5

typedef struct{
    char nome[20];
    float media, pf, final;
} DISCIPLINA;   

typedef struct{
    DISCIPLINA dis[DISCIPLINAS];
    char nome[20];
} AlUNO;

void leitura();
void reprovados();

AlUNO aluno[AlUNOS];

int main() {
    FILE *arquivo = fopen("registro.txt", "w");
    if(arquivo==NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    printf("Dados dos alunos de Ciencia da Computacao:\n");
    leitura(arquivo);
    reprovados(arquivo);
    fclose(arquivo);
    return 0;
}

void leitura(FILE *arquivo) {
    for(int i=0; i<AlUNOS; i++) {
        printf("Aluno %d:\n", i+1);
        printf("Nome: ");
        scanf("%s", aluno[i].nome);
        fprintf(arquivo, "Aluno %d: %s\n\n", i+1, aluno[i].nome);
        for(int j=0; j<DISCIPLINAS; j++) {
            printf("\nDisciplina %d:\n", j+1);
            fprintf(arquivo, "Disciplina %d:\n", j+1);
            printf("Nome da disciplina: ");
            scanf("%s", aluno[i].dis[j].nome);
            fprintf(arquivo, "%s\n", aluno[i].dis[j].nome);
            printf("Media: ");
            scanf("%f", &aluno[i].dis[j].media);
            fprintf(arquivo, "Media: %f:\n", aluno[i].dis[j].media);
            if(aluno[i].dis[j].media<7){
                printf("Nota da prova final: ");
                scanf("%f", &aluno[i].dis[j].pf);
                fprintf(arquivo, "Nota da prova final: %f:\n", aluno[i].dis[j].pf);
            } else {
                aluno[i].dis[j].pf=(-1);
            }
        }
    } 
}

void reprovados(FILE *arquivo) {
    //calcula as notas finais
    for(int i=0; i<AlUNOS; i++) {
        for(int j=0; j<DISCIPLINAS; j++) {
            if(aluno[i].dis[j].pf!=(-1)) {
                aluno[i].dis[j].final = (aluno[i].dis[j].media+aluno[i].dis[j].pf)/2;
            } else {
                aluno[i].dis[j].final = aluno[i].dis[j].media;
            }
        }
    }
    printf("\n\nAlunos reprovados:\n");
    fprintf(arquivo, "Alunos reprovados:\n");
    for(int i=0; i<AlUNOS; i++) {
        if(aluno[i].dis[0].final<5 || aluno[i].dis[1].final<5 || aluno[i].dis[2].final<5 || aluno[i].dis[3].final<5 || aluno[i].dis[4].final<5) {
            printf("\n%s reprovado em:\n", aluno[i].nome);
            fprintf(arquivo, "%s reprovado em:\n", aluno[i].nome);
            for(int j=0; j<DISCIPLINAS; j++) {
                if(aluno[i].dis[j].final<5) {
                    printf("%s\n", aluno[i].dis[j].nome);
                    fprintf(arquivo, "%s\n", aluno[i].dis[j].nome);
                }
            }
        }
    }
}