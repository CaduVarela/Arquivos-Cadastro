#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include <windows.h>

/*
Funcionalidades

(X) Inclusão
( ) Consulta
( ) Exclusão
( ) Alteração
( ) Listagem
( ) Lixeira

*/

// Registro Funcionário
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

void listar(FILE *fp, char sit) {
	Funcionario registro;
	int i;
	
	system("cls");
	// Linha (só estilização)
	printf(" ");
	for (i=0; i<80; i++) printf("_");
	printf("\n| CPF%9s | Nome%-46s | Salario    |\n", "", "");
	printf("|--------------+----------------------------------------------------+------------|\n");
	//
	
	// Parte lógica
	fseek(fp, 0, SEEK_SET);
	while (!feof(fp)) {
		fread(&registro, sizeof(Funcionario), 1, fp);
		if (registro.sit != sit || feof(fp)) continue;
		printf("| %12s | %-50s | %10.2f |\n", registro.CPF, registro.nome, registro.salario);
	}
	
	// Linha (só estilização)
	printf("|");
	for (i=0; i<14; i++) printf("_");
	printf("|");
	for (i=0; i<52; i++) printf("_");
	printf("|");
	for (i=0; i<12; i++) printf("_");
	printf("|");
	printf("\n");
	//
	
	system("pause");
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
		
		printf("Selecione a opção: ");
		opcao = getche(); /* getche() retorna o codigo ASCII da tecla */
		opcao -= 48; /* tranforma o codigo da tecla no numero correspondente */
		
		printf("\n");
		switch (opcao) {
			case 1: // Inclusão
				inclusao(fp);
				break;
			case 4: // Consulta
				consultar(fp);
				break;
			case 5: // Listar
				listar(fp, '0');
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
