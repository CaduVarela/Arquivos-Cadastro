#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include <windows.h>

/*
Funcionalidades

(X) Inclus�o
( ) Consulta
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

void inclusao(FILE *fp) {
	Funcionario registro;
	int continuar=1;
	fseek(fp, 0, SEEK_END);

	do{
		system("cls");
		printf("Digite o CPF: ");
		//falta checar a primary key
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

		printf("Deseja continuar? (1-sim / 0-não): ");
		scanf("%d",&continuar);
		fflush(stdin);

	}while(continuar);
		
}

int buscar(FILE *fp,char cpf[12]){
	int i=0;
	char cpf_corrente[12];
	
	while(!feof(fp)){
		fseek(fp,i*sizeof(Funcionario),SEEK_SET);
		fread(&cpf_corrente,sizeof(char)*12,1,fp);

		if(strcmp(cpf_corrente,cpf)==0) return i;

		i++;
	}
	
	return -1;
}

int consultar(FILE *fp){
	Funcionario registro;
	char cpf[12];
	int indice;

	system("cls");
	printf("Digite o CPF: ");
	gets(cpf);
	
	indice = buscar(fp, cpf);

	if(indice == -1){
		printf("CPF não encontrado!\n");
		system("pause");
		return -1;
	}

	fseek(fp, indice*sizeof(Funcionario), SEEK_SET);
	fread(&registro, sizeof(Funcionario), 1, fp);

	printf("CPF: %s \nNome: %s \nSalario: %.2f\n", registro.CPF, registro.nome, registro.salario);
	system("pause");

	return 0;
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
			case 1:
				inclusao(fp);
				break;
			case 4:
				consultar(fp);
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
