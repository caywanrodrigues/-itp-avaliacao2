#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 10
#define NUM_NOTAS 3
#define TAM_NOME 30
#define META 6.0
#define EPSILON 1e-9

void limpar_resto_da_linha(char *buffer)
{
    if (strchr(buffer, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
}

int ler_inteiro_no_intervalo(const char *mensagem, int minimo, int maximo)
{
    char linha[64];
    char *fim;
    long valor;

    while (1) {
        printf("%s", mensagem);
        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            exit(1);
        }
        limpar_resto_da_linha(linha);
        valor = strtol(linha, &fim, 10);
        if (fim == linha || (*fim != '\n' && *fim != '\0')) {
            printf("Entrada invalida. Digite um numero inteiro.\n");
            continue;
        }
        if (valor < minimo || valor > maximo) {
            printf("Valor fora do intervalo (%d a %d).\n", minimo, maximo);
            continue;
        }
        return (int)valor;
    }
}

double ler_nota(const char *mensagem)
{
    char linha[64];
    char *fim;
    double valor;

    while (1) {
        printf("%s", mensagem);
        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            exit(1);
        }
        limpar_resto_da_linha(linha);
        valor = strtod(linha, &fim);
        if (fim == linha || (*fim != '\n' && *fim != '\0')) {
            printf("Entrada invalida. Digite um numero.\n");
            continue;
        }
        if (valor < 0.0 || valor > 10.0) {
            printf("Nota invalida. A nota deve estar entre 0 e 10.\n");
            continue;
        }
        return valor;
    }
}

void ler_nome_estudante(int indice, char *destino)
{
    char linha[TAM_NOME];
    size_t tamanho;
    size_t i;
    int vazio;

    while (1) {
        printf("Nome do estudante %d: ", indice + 1);
        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            exit(1);
        }
        limpar_resto_da_linha(linha);
        linha[strcspn(linha, "\n")] = '\0';
        tamanho = strlen(linha);
        vazio = 1;
        for (i = 0; i < tamanho; i++) {
            if (linha[i] != ' ' && linha[i] != '\t') {
                vazio = 0;
                break;
            }
        }
        if (vazio) {
            printf("O nome nao pode ser vazio.\n");
            continue;
        }
        strcpy(destino, linha);
        return;
    }
}

void ler_dados(int qtd, char nomes[][TAM_NOME], double notas[][NUM_NOTAS])
{
    int i, j;
    char mensagem[100];

    for (i = 0; i < qtd; i++) {
        ler_nome_estudante(i, nomes[i]);
    }

    for (i = 0; i < qtd; i++) {
        printf("\n--- Notas de %s ---\n", nomes[i]);
        for (j = 0; j < NUM_NOTAS; j++) {
            sprintf(mensagem, "%s - nota %d (0 a 10): ", nomes[i], j + 1);
            notas[i][j] = ler_nota(mensagem);
        }
    }
}

void calcular_medias(double notas[][NUM_NOTAS], int qtd, double *medias)
{
    int i, j;
    double soma;

    for (i = 0; i < qtd; i++) {
        soma = 0.0;
        for (j = 0; j < NUM_NOTAS; j++) {
            soma += notas[i][j];
        }
        medias[i] = soma / NUM_NOTAS;
    }
}

const char *obter_situacao(double media)
{
    if (media + EPSILON >= META) {
        return "atingiu a meta";
    }
    return "abaixo da meta";
}

void exibir_tabela(char nomes[][TAM_NOME], double notas[][NUM_NOTAS],
                   const double *medias, int qtd)
{
    int i, j;

    printf("\n%-*s %7s %7s %7s %7s  %s\n", TAM_NOME, "Nome",
           "Nota 1", "Nota 2", "Nota 3", "Media", "Situacao");

    for (i = 0; i < qtd; i++) {
        printf("%-*s", TAM_NOME, nomes[i]);
        for (j = 0; j < NUM_NOTAS; j++) {
            printf(" %7.2f", notas[i][j]);
        }
        printf(" %7.2f  %s\n", medias[i], obter_situacao(medias[i]));
    }
}

double calcular_media_geral(const double *medias, int qtd)
{
    int i;
    double soma = 0.0;

    for (i = 0; i < qtd; i++) {
        soma += medias[i];
    }
    return soma / qtd;
}

void informar_maior_media(char nomes[][TAM_NOME], const double *medias, int qtd)
{
    int i;
    double maior = medias[0];

    for (i = 1; i < qtd; i++) {
        if (medias[i] > maior) {
            maior = medias[i];
        }
    }

    printf("Maior media: %.2f\n", maior);
    printf("Estudante(s) com a maior media:\n");
    for (i = 0; i < qtd; i++) {
        if (maior - medias[i] <= EPSILON) {
            printf("  - %s\n", nomes[i]);
        }
    }
}

int main(void)
{
    char nomes[MAX_ALUNOS][TAM_NOME];
    double notas[MAX_ALUNOS][NUM_NOTAS] = {{0}};
    double *medias;
    int qtd;

    printf("=== Boletim da turma ===\n\n");

    qtd = ler_inteiro_no_intervalo("Quantidade de estudantes (1 a 10): ", 1, MAX_ALUNOS);

    medias = (double *)calloc((size_t)qtd, sizeof(double));
    if (medias == NULL) {
        printf("Erro: falha na alocacao de memoria.\n");
        return 1;
    }

    ler_dados(qtd, nomes, notas);

    calcular_medias(notas, qtd, medias);

    exibir_tabela(nomes, notas, medias, qtd);

    printf("\nMedia geral da turma: %.2f\n", calcular_media_geral(medias, qtd));
    informar_maior_media(nomes, medias, qtd);

    free(medias);
    medias = NULL;

    return 0;
}
