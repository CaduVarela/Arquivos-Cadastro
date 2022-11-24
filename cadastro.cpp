#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include <windows.h>

/*
Funcionalidades

(X) Inclus�o
(X) Consulta
(X) Exclus�o
( ) Altera��o
(X) Listagem
(X) Lixeira

*/

// Registro Funcion�rio
typedef struct
{
	char CPF[12];
	char nome[50];
	float salario;
	char sit; // 0 --> ativo / 1 --> passivo
} Funcionario;

void incluir(FILE *fp)
{
	Funcionario registro;
	int continuar = 1;
	fseek(fp, 0, SEEK_END);

	do
	{
		system("cls");
		fflush(stdin);
		printf("Digite o CPF: ");
		// falta checar a primary key
		gets(registro.CPF);
		fflush(stdin);

		printf("Digite o nome: ");
		gets(registro.nome);
		fflush(stdin);

		printf("Digite o salario: ");
		scanf("%f", &registro.salario);
		fflush(stdin);

		registro.sit = '0';
		fwrite(&registro, sizeof(Funcionario), 1, fp);

		printf("Deseja continuar? (1-sim / 0-n�o): ");
		scanf("%d", &continuar);
		fflush(stdin);

	} while (continuar);
}

int buscar(FILE *fp,char cpf[12]){
	Funcionario registro;
	int i=0;
	
	fseek(fp, 0, SEEK_SET);
	while(!feof(fp)){
		fseek(fp,i*sizeof(Funcionario),SEEK_SET);
		fread(&registro,sizeof(Funcionario),1,fp);
		
		if(strcmp(registro.CPF,cpf)==0 && registro.sit == '0') return i;

		i++;
	}

	return -1;
}

void listar(FILE *fp, char sit)
{
	Funcionario registro;
	int i;
	
	// Linha (s� estiliza��o)
	printf(" ");
	for (i = 0; i < 80; i++)
		printf("_");
	printf("\n| CPF%9s | Nome%-46s | Salario    |\n", "", "");
	printf("|--------------+----------------------------------------------------+------------|\n");
	//

	// Parte l�gica
	fseek(fp, 0, SEEK_SET);
	while (!feof(fp))
	{
		fread(&registro, sizeof(Funcionario), 1, fp);
		if (registro.sit != sit || feof(fp))
			continue;
		printf("| %12s | %-50s | %10.2f |\n", registro.CPF, registro.nome, registro.salario);
	}

	// Linha (s� estiliza��o)
	printf("|");
	for (i = 0; i < 14; i++)
		printf("_");
	printf("|");
	for (i = 0; i < 52; i++)
		printf("_");
	printf("|");
	for (i = 0; i < 12; i++)
		printf("_");
	printf("|");
	printf("\n");
	//

	system("pause");
}

int consultar(FILE *fp)
{
	Funcionario registro;
	char cpf[12];
	int indice;

	system("cls");
	
	printf("Digite o CPF: ");
	gets(cpf);
	fflush(stdin);

	indice = buscar(fp, cpf);
	if (indice == -1)
	{
		printf("\nCPF n�o encontrado!\n\n");
		system("pause");
		return -1;
	}

	fseek(fp, indice * sizeof(Funcionario), SEEK_SET);
	fread(&registro, sizeof(Funcionario), 1, fp);

	printf("\nCPF: %s \nNome: %s \nSalario: %.2f\n\n", registro.CPF, registro.nome, registro.salario);
	system("pause");

	return 0;
}

int excluir(FILE *fp){

    Funcionario registro;
    char cpf[12];
    int indice,escolha;

	system("cls");
	fflush(stdin);
	printf("Digite o CPF do Funcion�rio a ser exclu�do: ");
	gets(cpf);

    indice = buscar(fp, cpf);
    if(indice == -1){
        printf("CPF n�o encontrado!\n");
        system("pause");
        return -1;
    }

	fseek(fp, indice * sizeof(Funcionario), SEEK_SET);
	fread(&registro, sizeof(Funcionario), 1, fp);

    printf("CPF: %s \nNome: %s \nSalario: %.2f\n",registro.CPF, registro.nome, registro.salario);
    printf("\nConfirma Funcion�rio? (1-sim / 2-n�o): ");
    scanf("%d",&escolha);

    if(escolha == 1){
		registro.sit = '1';
		fseek(fp, indice*sizeof(Funcionario), SEEK_SET);
		// fseek(fp, (indice+1)*sizeof(Funcionario)-sizeof(char), SEEK_SET);
		// fseek(fp, indice*sizeof(Funcionario)+sizeof(Funcionario)-sizeof(char), SEEK_SET);
		//fwrite(&registro.sit, sizeof(char), 1, fp);
		fwrite(&registro, sizeof(Funcionario), 1, fp);

        printf("Exclus�o do Funcion�rio com CPF %s feita com sucesso!\n\n", registro.CPF);
        system("pause");
    }
    return 0;
}

int alterar(FILE *fp)
{
	Funcionario registro;
	char cpf[12];
	int indice, continuar = 1, continuar2 = 1, alteracao;

	system("cls");
	printf("Digite o CPF: ");
	gets(cpf);
	fflush(stdin);

	indice = buscar(fp, cpf);
	if (indice == -1)
	{
		printf("\nCPF não encontrado!\n\n");
		system("pause");
		return -1;
	}

	fseek(fp, indice * sizeof(Funcionario), SEEK_SET);
	fread(&registro, sizeof(Funcionario), 1, fp);
	printf("\n1-CPF: %s \n2-Nome: %s \n3-Salario: %.2f\n\n", registro.CPF, registro.nome, registro.salario);
	printf("Deseja alterar esse registro? (1-sim / 0-nao): \n");
	scanf("%d", &continuar);
	fflush(stdin);

	if (continuar == 1)
	{
		printf("O que deseja alterar?\n");
		scanf("%d", &alteracao);
		fflush(stdin);

		do
		{
			switch (alteracao)
			{
			case 1:
				system("cls");
				printf("Digite o novo CPF\n");
				gets(registro.CPF);
				fflush(stdin);
				break;
			case 2:
				system("cls");
				printf("Digite o novo nome\n");
				gets(registro.nome);
				fflush(stdin);
				break;
			case 3:
				system("cls");
				printf("Digite o novo salário\n");
				scanf("%f", &registro.salario);
				fflush(stdin);
				break;
			default:
				printf("Opção não encontrada");
				break;
			}

			printf("Deseja alterar algo a mais? (1-sim / 0-não): \n\n");
			scanf("%d", &continuar2);
			if (continuar2 == 1)
				printf("\n1-CPF: %s \n2-Nome: %s \n3-Salario: %.2f\n\n", registro.CPF, registro.nome, registro.salario);
		} while (continuar2 == 1);

		fseek(fp, indice * sizeof(Funcionario), SEEK_SET);
		fwrite(&registro, sizeof(Funcionario), 1, fp);

		return 0;
	}
	else
		return -1;
}

int main()
{
	int opcao, exit = 0;
	FILE *fp;

	setlocale(LC_ALL, "Portuguese");

	fp = fopen("cadfun.dad", "a+b");
	fclose(fp);
	
	fp = fopen("cadfun.dad", "r+b"); // para sobreescrever

	// Menu
	do
	{
		system("cls");
		printf("-= MENU =-\n");
		printf("1 - Adicionar\n");
		printf("2 - Excluir\n");
		printf("3 - Alterar\n");
		printf("4 - Consultar\n");
		printf("5 - Listar\n");
		printf("6 - Lixeira\n");
		printf("0 - Sair\n\n");

		printf("Selecione a opção: ");
		opcao = getche(); /* getche() retorna o codigo ASCII da tecla */
		opcao -= 48; /* tranforma o codigo da tecla no numero correspondente */
		fflush(stdin);

		printf("\n");
		switch (opcao) {
			case 1:
				incluir(fp);
				break;
			case 2:
				excluir(fp);
				break;
			case 4: // Consulta
				consultar(fp);
				break;
			case 5: // Listar
				system("cls");
				printf(" %35s CADASTROS \n", "");
				listar(fp, '0');
				break;
			case 6: // Lixeira
				system("cls");
				printf(" %36s LIXEIRA \n", "");
				listar(fp, '1');
				break;
			case 0: // Sair / Fechar
				printf("Fechando...\n");
				Sleep(500);
				exit = 1;
				break;
			default:
				printf("Op��o inv�lida!\n");
				Sleep(500);
				break;
		}
	} while (!exit);

	fclose(fp);
	return 0;
}
