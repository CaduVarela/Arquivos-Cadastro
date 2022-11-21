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
	int situacao_cadastro; // 0 --> ativo / 1 --> excluido
} Funcionario;

int main() {
	int opcao, exit=0;
	
	setlocale(LC_ALL, "Portuguese");
	
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
	
	return 0;
}
