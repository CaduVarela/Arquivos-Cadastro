#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include <windows.h>

/*
Funcionalidades

( ) Inclus�o
( ) Exclus�o
( ) Altera��o
( ) Listagem
( ) Lixeira

*/

// Registro Funcion�rio
typedef struct {
	char CPF[12];
	char nome[50];
	float salario;
	char sit; // 0 --> ativo / 1 --> passivo
} Funcionario;

void listar(FILE *fp) {
	Funcionario registro;
	int continuar=1;
	fseek(fp, 0, SEEK_END);
	num_registros = ftell(fp) / sizeof(Funcionario);
	
	while(!feof(fp)){
		fseek(fp,i*sizeof(Funcionario),SEEK_SET);
		fread(&cpf_corrente,sizeof(char)*12,1,fp);

		if(strcmp(cpf_corrente,cpf)==0) return i;

		i++;
	}
	
	return -1;
}

int main() {
	int opcao, exit=0;
	FILE *fp;
	
	setlocale(LC_ALL, "Portuguese");
	
	fp = fopen("cadfun.dad", "a+b");
	
	// Menu
	do {
		system("cls");
		printf("-= MENU =-\n");
		printf("1 - Adicionar\n");
		printf("2 - Excluir\n");
		printf("3 - Alterar\n");
		printf("4 - Consultar\n");
		printf("5 - Listar\n");
		printf("6 - Lixeira\n");
		printf("0 - Sair\n\n");
		
		printf("Selecione a op��o: ");
		opcao = getche(); /* getche() retorna o codigo ASCII da tecla */
		opcao -= 48; /* tranforma o codigo da tecla no numero correspondente */
		
		printf("\n");
		switch (opcao) {
			case 5:
				listar(fp);
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
