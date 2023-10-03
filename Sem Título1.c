#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
/*
Este programa tem como objetivo ser um metodo de cadastro em arquivo de alunos em 
em uma universadade. 
O programa utiliza de um menu simples para direcionar o usuario
atraves das ações desejadas.
Utilizando de uma struct, o programa salva em um arquivo de texto os dados dos alunos (nome,
idade, nome, matricula, curso e o turno) e retorna a consulta quando desejado. 
Podemos manipular os dados salvos dados da maneira que quisermos, bastando selecionar a ação
no menu.
*/



typedef struct aluno{
	char idade[200];
	char nome[200];
	char matricula[200];
	char curso[200];
	char turno[20];
}aluno;
void vizualiza(){
	FILE *arq;
	arq = fopen("Alunos.txt","r");
	aluno a;
	rewind(arq);
	while(fscanf(arq, "%s %s %s %s %s", a.nome, a.idade, a.matricula, a.curso, a.turno) != EOF){
		printf("A nome é: %s\n",a.nome);
		printf("A idade é: %s\n",a.idade);
		printf("A matricula é: %s\n",a.matricula);
		printf("A curso é: %s\n",a.curso);
		printf("A turno é: %s\n",a.turno);
		printf("\n------------------------------------------\n");
	}
	fclose(arq);
}
void adiciona(){
	FILE *arq;
	arq = fopen("Alunos.txt","a");
	aluno a;
	printf("Digite o nome do aluno: \n:>");
	gets(a.nome);
	printf("Digite a idade do aluno: \n:>");
	gets(a.idade);
	printf("Digite o matricula do aluno: \n:>");
	gets(a.matricula);
	printf("Digite o curso do aluno: \n:>");
	gets(a.curso);
	printf("Digite o turno do aluno: \n:>");
	gets(a.turno);
	fprintf(arq, "%s %s %s %s %s ", a.nome, a.idade, a.matricula, a.curso, a.turno);
	fclose(arq);
}
void modifica() {
    aluno a;
    aluno b;
    FILE *arq;
    FILE *arqtemp;
    arq = fopen("Alunos.txt", "r");
    arqtemp = fopen("ArqTemp.txt", "w");
    if (arq == NULL || arqtemp == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }
    char nomeBusca[200];
    int encontrado = 0;
    printf("Digite o nome buscado ou digite \"sair\": \n:>");
    gets(nomeBusca);
    while (fscanf(arq, "%s %s %s %s %s", a.nome, a.idade, a.matricula, a.curso, a.turno) != EOF) {
        if (strcmp(a.nome, nomeBusca) == 0) {
            printf("Digite o novo nome: \n:>");
            gets(b.nome);
            printf("Digite a idade: \n:>");
            gets(b.idade);
            printf("Digite a matricula: \n:>");
            gets(b.matricula);
            printf("Digite o novo curso: \n:>");
            gets(b.curso);
            printf("Digite o novo turno: \n:>");
            gets(b.turno);
            encontrado = 1;
            fprintf(arqtemp, "%s %s %s %s %s\n", b.nome, b.idade, b.matricula, b.curso, b.turno);
        } else {
            fprintf(arqtemp, "%s %s %s %s %s\n", a.nome, a.idade, a.matricula, a.curso, a.turno);
        }
    }
    fclose(arq);
    fclose(arqtemp);
    if (encontrado == 0) {
        remove("ArqTemp.txt");
        printf("Aluno não encontrado.\n");
    } else {
        remove("Alunos.txt");
        rename("ArqTemp.txt", "Alunos.txt");
        printf("Registro alterado com sucesso.\n");
    }
}
void exclui() {
    aluno a;
    FILE *arq;
    FILE *arqtemp;
    arq = fopen("Alunos.txt", "r");
    arqtemp = fopen("ArqTemp.txt", "w");
    if (arq == NULL || arqtemp == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }
    char nomeBusca[200];
    int encontrado = 0;
    printf("Digite o nome buscado para exclui-lo: \n:>");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0'; 
    while (fscanf(arq, "%s %s %s %s %s", a.nome, a.idade, a.matricula, a.curso, a.turno) != EOF) {
        if (strcmp(a.nome, nomeBusca) == 0) {
            printf("A nome é: %s\n", a.nome);
            printf("A idade é: %s\n", a.idade);
            printf("A matricula é: %s\n", a.matricula);
            printf("A curso é: %s\n", a.curso);
            printf("A turno é: %s\n", a.turno);
            printf("\n------------------------------------------\n");
            printf("Deseja excluir este nome? (s/n) \n:>");
            char resposta[3];
            fgets(resposta, sizeof(resposta), stdin);
            resposta[strcspn(resposta, "\n")] = '\0'; 
            if (strcmp(resposta, "s") == 0) {
                encontrado = 1;
            } else {
                fprintf(arqtemp, "%s %s %s %s %s\n", a.nome, a.idade, a.matricula, a.curso, a.turno);
            }
        } else {
            fprintf(arqtemp, "%s %s %s %s %s\n", a.nome, a.idade, a.matricula, a.curso, a.turno);
        }
    }
    fclose(arq);
    fclose(arqtemp);
    
    if (encontrado) {
        remove("Alunos.txt");
        rename("ArqTemp.txt", "Alunos.txt");
        printf("Registro excluído com sucesso!\n");
    } else {
        remove("ArqTemp.txt"); 
        printf("Nome não encontrado ou nenhum registro foi excluído.\n");
    }
}
void consulta() {
    aluno a;
    FILE *arq;
    arq = fopen("Alunos.txt", "r");
    if (arq == NULL) {
        printf("Arquivo de alunos não encontrado.\n");
        return;
    }
    char nomeBusca[200];
    int encontrado = 0;
    printf("Digite o nome buscado para consulta: \n:>");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0'; 
    while (fscanf(arq, "%s %s %s %s %s", a.nome, a.idade, a.matricula, a.curso, a.turno) != EOF) {
        if (strcmp(a.nome, nomeBusca) == 0) {
            printf("A nome é: %s\n", a.nome);
            printf("A idade é: %s\n", a.idade);
            printf("A matricula é: %s\n", a.matricula);
            printf("A curso é: %s\n", a.curso);
            printf("A turno é: %s\n", a.turno);
            printf("\n------------------------------------------\n");
            encontrado = 1;
            break;
        }
    }
    fclose(arq);
    
    if (!encontrado) {
        printf("Aluno não encontrado.\n");
    }
}
int main() {
    int entrada;
    setlocale(LC_ALL, "Portuguese");
    FILE *arq;
    arq = fopen("Alunos.txt", "r");
    if (arq == NULL) {
        fopen("Alunos.txt", "w");
    }
    fclose(arq);

    do {
    printf("\n------------------------------------------\n");
    printf("\tALTERAÇÃO DE REGISTRO\n\n");
    printf("\tEscolha uma opção:\n");
    printf("\n1. Adicionar registro");
    printf("\n2. Visualizar registro");
    printf("\n3. Modificar registro");
    printf("\n4. Excluir registro");
    printf("\n5. Consultar registro");
    printf("\n6. Sair\n");
    printf("\n------------------------------------------\n=>");
    scanf("%i", &entrada);
    getchar();

    if (entrada == 1) {
        adiciona();
    } else if (entrada == 2) {
        vizualiza();
    } else if (entrada == 3) {
        modifica();
    } else if (entrada == 4) {
        exclui();
    } else if (entrada == 5) {
        consulta();  // Corrected function name
    } else if (entrada == 6) {
        if (remove("ArqTemp.txt") == 0) {
            printf("Arquivo temporário removido.\n");
        }
        return 0;
    } else {
        printf("Valor Inválido\n");
     }
    } while (1);
    
    return 0;
	}
