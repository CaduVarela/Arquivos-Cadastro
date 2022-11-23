#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include <windows.h>

/*
Funcionalidades

<<<<<<< HEAD
(X) Inclus�o
(X) Consulta
(X) Exclus�o
( ) Altera��o
( ) Consulta
=======
(X) Inclus�o
( ) Consulta
( ) Exclus�o
( ) Altera��o
>>>>>>> parent of e5db9b4 (Merge branch 'Listagem')
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

<<<<<<< HEAD
void incluir(FILE *fp) {
=======
void inclusao(FILE *fp) {
>>>>>>> parent of e5db9b4 (Merge branch 'Listagem')
	Funcionario registro;
	int continuar=1;
	fseek(fp, 0, SEEK_END);

	do{
		system("cls");
<<<<<<< HEAD
		fflush(stdin);
=======
>>>>>>> parent of e5db9b4 (Merge branch 'Listagem')
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

<<<<<<< HEAD
		printf("Deseja continuar? (1-sim / 0-não): ");
=======
		printf("Deseja continuar? (1-sim / 0-n�o): ");
>>>>>>> parent of e5db9b4 (Merge branch 'Listagem')
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
		printf("CPF n�o encontrado!\n");
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
	// Linha (s� estiliza��o)
	printf(" ");
	for (i=0; i<80; i++) printf("_");
	printf("\n| CPF%9s | Nome%-46s | Salario    |\n", "", "");
	printf("|--------------+----------------------------------------------------+------------|\n");
	//
	
	// Parte l�gica
	fseek(fp, 0, SEEK_SET);
	while (!feof(fp)) {
		fread(&registro, sizeof(Funcionario), 1, fp);
		if (registro.sit != sit || feof(fp)) continue;
		printf("| %12s | %-50s | %10.2f |\n", registro.CPF, registro.nome, registro.salario);
	}
	
	// Linha (s� estiliza��o)
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

int excluir(FILE *fp){
	Funcionario registro;
	char cpf[12];
	int indice,escolha;

	system("cls");
	fflush(stdin);
	printf("Digite o CPF do Funcionário a ser excluído: ");
	gets(cpf);

	indice = buscar(fp, cpf);
	if(indice == -1){
		printf("CPF não encontrado!");
		system("pause");
		return -1;
	}

	fseek(fp,indice*sizeof(Funcionario), SEEK_SET);
	fread(&registro, sizeof(Funcionario), 1, fp);
	
	printf("CPF: %s \nNome: %s \nSalario: %.2f\n", registro.CPF, registro.nome, registro.salario);
	printf("\nConfirma Funcionário? (1-sim / 2-não): ");
	scanf("%d",&escolha);

	if(escolha == 1){
		
		printf("Exclusão do Funcionário com CPF %s feita com sucesso!\n\n", registro.CPF);
		system("pause");
	}
	
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
<<<<<<< HEAD
			case 1:
				incluir(fp);
				break;
			case 2:
				excluir(fp);
				break;
			case 4:
				consultar(fp);
=======
			case 1: // Inclus�o
				inclusao(fp);
				break;
			case 4: // Consulta
				consultar(fp);
				break;
			case 5: // Listar
				listar(fp, '0');
>>>>>>> parent of e5db9b4 (Merge branch 'Listagem')
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
