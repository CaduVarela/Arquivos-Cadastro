#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include <windows.h>

/*
Funcionalidades

( ) Inclusão
( ) Exclusão
( ) Alteração
( ) Consulta
( ) Listagem
( ) Lixeira

*/

// Registro Funcionário
typedef struct {
	char CPF[12];
	char nome[50];
	float salario;
	char sit; // 0 --> ativo / 1 --> excluido
} Funcionario;

void listar(FILE *fp) {
	Funcionario registro;
	int i, num_registros;
	
	fseek(fp, 0, SEEK_END);
	num_registros = ftell(fp) / sizeof(Funcionario);
	
	fseek(fp, 0, SEEK_SET);
	printf("");
	for (i=0; i<num_registros; i++) {
		//fread(registro, sizeof(Funcionario), SEEK_CUR);
		fread(registro.CPF, sizeof(registro.CPF), 1, fp);
		fread(registro.nome, sizeof(registro.nome), 1, fp);
		fread(registro.salario, sizeof(registro.salario), 1, fp);
		fread(registro.sit, sizeof(registro.sit), 1, fp);
		if (registro.sit == '1') continue;
		printf("%12s | %50s | %f", registro.CPF, registro.nome, registro.salario);
	}
}

int main() {
	int opcao, exit=0;
	FILE *fp;
	
	setlocale(LC_ALL, "Portuguese");
	
	fopen("cadfun.dad", "a+b");
	
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
		
		printf("Selecione a opção: ");
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
				printf("Opção inválida!\n");
				Sleep(500);
				break;
		}
	} while (!exit);
	
	fclose(fp);
	return 0;
}
