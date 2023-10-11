#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct usuario {
    char nome[200];
    char senha[200];
    int nivel_acesso;
} usuario;

// Estrutura para armazenar informa��es de alunos
typedef struct aluno {
    char idade[200];
    char nome[200];
    char matricula[200];
    char curso[200];
    char turno[20];
} aluno;

// Fun��o para visualizar registros de alunos
void vizualiza() {
    FILE *arq;
    arq = fopen("Alunos.txt", "r");
    aluno a;
    rewind(arq);

    while (fscanf(arq, "%s %s %s %s %s", a.nome, a.idade, a.matricula, a.curso, a.turno) != EOF) {
        printf("Nome: %s\n", a.nome);
        printf("Idade: %s\n", a.idade);
        printf("Matr�cula: %s\n", a.matricula);
        printf("Curso: %s\n", a.curso);
        printf("Turno: %s\n", a.turno);
        printf("\n------------------------------------------\n");
    }

    fclose(arq);
}

// Fun��o para adicionar um novo registro de aluno
void adiciona() {
    FILE *arq;
    arq = fopen("Alunos.txt", "a");
    aluno a;

    printf("Digite o nome do aluno: \n:>");
    gets(a.nome);
    printf("Digite a idade do aluno: \n:>");
    gets(a.idade);
    printf("Digite a matr�cula do aluno: \n:>");
    gets(a.matricula);
    printf("Digite o curso do aluno: \n:>");
    gets(a.curso);
    printf("Digite o turno do aluno: \n:>");
    gets(a.turno);

    fprintf(arq, "%s %s %s %s %s ", a.nome, a.idade, a.matricula, a.curso, a.turno);
    fclose(arq);
}

// Fun��o para modificar um registro de aluno
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
            printf("Digite a matr�cula: \n:>");
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
        printf("Aluno n�o encontrado.\n");
    } else {
        remove("Alunos.txt");
        rename("ArqTemp.txt", "Alunos.txt");
        printf("Registro alterado com sucesso.\n");
    }
}

// Fun��o para excluir um registro de aluno
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

    printf("Digite o nome buscado para exclu�-lo: \n:>");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    while (fscanf(arq, "%s %s %s %s %s", a.nome, a.idade, a.matricula, a.curso, a.turno) != EOF) {
        if (strcmp(a.nome, nomeBusca) == 0) {
            printf("Nome: %s\n", a.nome);
            printf("Idade: %s\n", a.idade);
            printf("Matr�cula: %s\n", a.matricula);
            printf("Curso: %s\n", a.curso);
            printf("Turno: %s\n", a.turno);
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
        printf("Registro exclu�do com sucesso!\n");
    } else {
        remove("ArqTemp.txt");
        printf("Nome n�o encontrado ou nenhum registro foi exclu�do.\n");
    }
}

// Fun��o para consultar um registro de aluno
void consulta() {
    aluno a;
    FILE *arq;
    arq = fopen("Alunos.txt", "r");

    if (arq == NULL) {
        printf("Arquivo de alunos n�o encontrado.\n");
        return;
    }

    char nomeBusca[200];
    int encontrado = 0;

    printf("Digite o nome buscado para consulta: \n:>");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    while (fscanf(arq, "%s %s %s %s %s", a.nome, a.idade, a.matricula, a.curso, a.turno) != EOF) {
        if (strcmp(a.nome, nomeBusca) == 0) {
            printf("Nome: %s\n", a.nome);
            printf("Idade: %s\n", a.idade);
            printf("Matr�cula: %s\n", a.matricula);
            printf("Curso: %s\n", a.curso);
            printf("Turno: %s\n", a.turno);
            printf("\n------------------------------------------\n");
            encontrado = 1;
            break;
        }
    }

    fclose(arq);

    if (!encontrado) {
        printf("Aluno n�o encontrado.\n");
    }
}

// Fun��o para cadastrar um novo usu�rio
void cadastraUsuario() {
    usuario u;
    FILE *arq;
    arq = fopen("Usuarios.txt", "a");

    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de usu�rios.\n");
        return;
    }

    int nivel_acesso;

    printf("Digite o nome do novo usu�rio: \n:>");
    gets(u.nome);

    printf("Digite a senha do novo usu�rio: \n:>");
    gets(u.senha);

    printf("Digite o n�vel de acesso do novo usu�rio (1 para administrador, 2 para usu�rio padr�o): \n:>");
    scanf("%d", &nivel_acesso);
    getchar(); // Limpa o buffer de entrada

    u.nivel_acesso = nivel_acesso;

    fprintf(arq, "%s %s %d\n", u.nome, u.senha, u.nivel_acesso);

    fclose(arq);
}

// Fun��o para aloca��o de mem�ria
void alocar_memoria(){
    aluno *p;
    p = (aluno *)malloc(sizeof(aluno));

    if (p == NULL)
    {
        printf("Erro de aloca��o de mem�ria. Cancelando.");
        exit(1);
    }
}

//Fun��o para liberar a mem�ria
void liberar_memoria(){

    aluno *p;
    free(p);
}

int main() {
    int entrada;
    setlocale(LC_ALL, "Portuguese");
    alocar_memoria();
    FILE *arq;
    arq = fopen("Alunos.txt", "r");

    if (arq == NULL) {
        fopen("Alunos.txt", "w");
    }

    fclose(arq);

    // Verifica se o arquivo de usu�rios j� existe
    FILE *arqUsuarios;
    arqUsuarios = fopen("Usuarios.txt", "r");

    if (arqUsuarios == NULL) {
        // Se o arquivo n�o existe, cria-o e adiciona o usu�rio "admin"
        arqUsuarios = fopen("Usuarios.txt", "w");
        if (arqUsuarios != NULL) {
            usuario admin;
            strcpy(admin.nome, "admin");
            strcpy(admin.senha, "admin");
            admin.nivel_acesso = 1; // N�vel de acesso de administrador
            fprintf(arqUsuarios, "%s %s %d\n", admin.nome, admin.senha, admin.nivel_acesso);
            fclose(arqUsuarios);
        } else {
            printf("Erro ao criar o arquivo de usu�rios.\n");
            return 1;
        }
    } else {
        // Se o arquivo de usu�rios j� existe, fecha-o
        fclose(arqUsuarios);
    }

    int nivel_acesso = 0; // Inicialmente, o usu�rio n�o est� logado

    do {
        int loginSucesso = 0;

        // Loop para autentica��o do usu�rio
        printf("                       LOGIN                          \n");
        while (!loginSucesso) {
        	printf("====================================================\n");
            printf("Digite o nome de usu�rio ou sair: \n=>");
            char nomeUsuario[200];
            gets(nomeUsuario);

            if (strcmp(nomeUsuario, "sair") == 0) {
                return 0;
            }

            printf("Digite a senha: \n:>");
            char senhaUsuario[200];
            gets(senhaUsuario);

            arqUsuarios = fopen("Usuarios.txt", "r");

            if (arqUsuarios == NULL) {
                printf("Arquivo de usu�rios n�o encontrado.\n");
                printf("====================================================\n");
                return 0;
            }

            usuario u;
            int encontrou = 0;
            while (fscanf(arqUsuarios, "%s %s %d", u.nome, u.senha, &u.nivel_acesso) != EOF) {
                if (strcmp(u.nome, nomeUsuario) == 0 && strcmp(u.senha, senhaUsuario) == 0) {
                    nivel_acesso = u.nivel_acesso;
                    encontrou = 1;
                    loginSucesso = 1;
                    break;
                }
            }

            fclose(arqUsuarios);

            if (!encontrou) {
                printf("\nUsu�rio ou senha incorretos.\n\n");
            }
        }

        do {
            printf("\n------------------------------------------\n");
            printf("\tALTERA��O DE REGISTRO\n\n");
            printf("\tEscolha uma op��o:\n");

            printf("\n1. Adicionar registro");
            printf("\n2. Visualizar registro");
            printf("\n3. Modificar registro");
            printf("\n4. Excluir registro");
            printf("\n5. Consultar registro");

            if (nivel_acesso == 1) {

                printf("\n6. Cadastrar novo usu�rio");
            }

            printf("\n7. Sair\n");

            printf("\n------------------------------------------\n=>");
            scanf("%i", &entrada);
            getchar();

            switch (entrada) {
                case 1:
                    adiciona();
                    break;
                case 2:
                    vizualiza();
                    break;
                case 3:
                    modifica();
                    break;
                case 4:
                    exclui();
                    break;
                case 5:
                    consulta();
                    break;
                case 6:
                    if (nivel_acesso == 1) {
                        cadastraUsuario();
                    } else {
                        printf("Apenas administradores podem cadastrar novos usu�rios.\n");
                    }
                    break;
                case 7:
                    if (remove("ArqTemp.txt") == 0) {
                        printf("Arquivo tempor�rio removido.\n");
                        liberar_memoria();
                    }
                    return 0;
                default:
                    printf("Valor Inv�lido\n");
            }

            if (entrada != 6) {
                break;
            }
        } while (1);
    } while (1);
}

