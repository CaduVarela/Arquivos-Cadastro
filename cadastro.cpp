#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include <windows.h>

/*
Funcionalidades

(X) Inclusao
(X) Consulta
(X) Exclusao
(X) Alteracao
(X) Listagem
(X) Lixeira

*/

// Registro Funcionario
typedef struct {
	char CPF[12];
	char nome[50];
	float salario;
	char sit; // 0 --> ativo / 1 --> passivo
} Funcionario;

//Prototipos
void incluir();
int buscar(char [12]);
void listar(char);
int consultar();
int excluir();
int alterar(); 
int validarCPF(char [11]);

FILE *fp;
int main() {
	int opcao, exit = 0;

	setlocale(LC_ALL, "Portuguese");

	fp = fopen("cadfun.dad", "a+b"); // garantir que exista o arquivo
	fclose(fp);
	
	fp = fopen("cadfun.dad", "r+b"); // para sobreescrever

	// Menu
	do{
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
		opcao = getche(); // getche() retorna o codigo ASCII da tecla
		opcao -= 48; // tranforma o codigo da tecla no numero correspondente
		fflush(stdin);

		printf("\n");
		switch (opcao) {
			case 1:
				incluir();
				break;
			case 2:
				excluir();
				break;
			case 3:
				alterar();
				break;
			case 4: // Consulta
				consultar();
				break;
			case 5: // Listar
				system("cls");
				printf(" %35s CADASTROS \n", "");
				listar('0');
				break;
			case 6: // Lixeira
				system("cls");
				printf(" %36s LIXEIRA \n", "");
				listar('1');
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

void incluir() {
	Funcionario registro;
	int continuar = 1, duplicata;
	fseek(fp, 0, SEEK_END);

	do
	{
		system("cls");
		fflush(stdin);
		
		// Pega o CPF
		// Garante que o CPF esteja formatado
		do {
			// Pega o CPF
			printf("Digite o CPF: ");
			gets(registro.CPF);
			fflush(stdin);
			
			// Valida o CPF
			duplicata = buscar(registro.CPF);
			if(duplicata >= 0) printf("CPF já cadastrado!\n\n");
			if (!validarCPF(registro.CPF)) printf("CPF inválido!\n\n");
		} while(duplicata >= 0 || !validarCPF(registro.CPF));
		
		// Pega o nome
		printf("Digite o nome: ");
		gets(registro.nome);
		fflush(stdin);

		// Pega o salario e garante que seja numero
		registro.salario = -1;
		do {
			printf("Digite o salario: ");
			scanf("%f", &registro.salario);
			fflush(stdin);
		} while (registro.salario < 0);

		// Sit sempre comeca como '0' (ativo)
		registro.sit = '0';
		fwrite(&registro, sizeof(Funcionario), 1, fp);

		printf("Deseja continuar? (1-sim / 0-não): ");
		scanf("%d", &continuar);
		fflush(stdin);

	} while (continuar);
}

int buscar(char cpf[12]) {
	Funcionario registro;
	int i=0;
	
	// Percorre todos os registros presentes do arquivo
	// Retorna a posicao do CPF recebido pela função
	fseek(fp, 0, SEEK_SET);
	while(!feof(fp)){
		fseek(fp, i*sizeof(Funcionario), SEEK_SET);
		fread(&registro, sizeof(Funcionario), 1, fp);
		
		if(strcmp(registro.CPF,cpf)==0 && registro.sit == '0') return i;

		i++;
	}

	// Retorna -1 se não encontrar o CPF especificado
	return -1;
}

void listar(char sit) {
	Funcionario registro;
	int i;
	
	// Linha de cima da tabela
	printf(" ");
	for (i = 0; i < 80; i++) printf("_");
	printf("\n| CPF%9s | Nome%-46s | Salario    |\n", "", ""); // Cabecalho
	printf("|--------------+----------------------------------------------------+------------|\n");

	// Parte lógica
	fseek(fp, 0, SEEK_SET);
	while (!feof(fp)) {
		fread(&registro, sizeof(Funcionario), 1, fp);
		if (registro.sit == sit && !feof(fp))
			printf("| %12s | %-50s | %10.2f |\n", registro.CPF, registro.nome, registro.salario);
	}

	// Linha de baixo da tabela
	printf("|______________|____________________________________________________|____________|\n");

	system("pause");
}

int consultar() {
	Funcionario registro;
	char cpf[12];
	int indice;

	system("cls");
	
	// Procura pelo CPF (Primary key)
	printf("Digite o CPF: ");
	gets(cpf);
	fflush(stdin);

	// Tenta encontrar o CPF
	indice = buscar(cpf);
	
	// Verifica se o CPF não foi encontrado
	if (indice == -1){
		printf("\nCPF não encontrado!\n\n");
		system("pause");
		return -1;
	}

	// Le o registro
	fseek(fp, indice * sizeof(Funcionario), SEEK_SET);
	fread(&registro, sizeof(Funcionario), 1, fp);

	// Mostra o dados
	printf("\nCPF: %s \nNome: %s \nSalario: %.2f\n\n", registro.CPF, registro.nome, registro.salario);
	system("pause");

	return 0;
}

int excluir() {
    Funcionario registro;
    char cpf[12];
    int indice, opcao;

	system("cls");
	fflush(stdin);
	
	// Procura pelo CPF (Primary key)
	printf("Digite o CPF do Funcionário a ser excluído: ");
	gets(cpf);

    // Tenta encontrar o CPF
	indice = buscar(cpf);
	
	// Verifica se o CPF não foi encontrado
	if (indice == -1){
		printf("\nCPF não encontrado!\n\n");
		system("pause");
		return -1;
	}

	// Le o registro
	fseek(fp, indice * sizeof(Funcionario), SEEK_SET);
	fread(&registro, sizeof(Funcionario), 1, fp);

	// Mostra os dados
    printf("CPF: %s \nNome: %s \nSalario: %.2f\n",registro.CPF, registro.nome, registro.salario);
    printf("\nConfirma Funcionário? (1-sim / 2-não): ");
    scanf("%d",&opcao);

	
    if(opcao == 1){
		registro.sit = '1'; // altera na variavel registro
		
		// Posiciona e reescreve o registro inteiro no documento
		fseek(fp, indice*sizeof(Funcionario), SEEK_SET);
		fwrite(&registro, sizeof(Funcionario), 1, fp);
		
		// fseek(fp, (indice+1)*sizeof(Funcionario)-sizeof(char), SEEK_SET); // Perguntar pq n funciona
		// fseek(fp, indice*sizeof(Funcionario)+sizeof(Funcionario)-sizeof(char), SEEK_SET); // Perguntar pq n funciona
		// fwrite(&registro.sit, sizeof(char), 1, fp); // Perguntar pq n funciona

        printf("Exclusão do Funcionário com CPF %s feita com sucesso!\n\n", registro.CPF);
        system("pause");
    }
    return 0;
}

int alterar() {
	Funcionario registro;
	char cpf[12];
	int indice, opcao, alteracao, duplicata = 0;

	// buscar o registro
	system("cls");
	
	// Procura pelo CPF (Primary key)
	printf("Digite o CPF: ");
	gets(cpf);
	fflush(stdin);

	// Tenta encontrar o CPF
	indice = buscar(cpf);
	
	// Verifica se o CPF não foi encontrado
	if (indice == -1){
		printf("\nCPF não encontrado!\n\n");
		system("pause");
		return -1;
	}

	// Le o registro
	fseek(fp, indice * sizeof(Funcionario), SEEK_SET);
	fread(&registro, sizeof(Funcionario), 1, fp);
	
	// Mostra os dados
	printf("\n1 - CPF: %s \n2 - Nome: %s \n3 - Salario: %.2f\n\n", registro.CPF, registro.nome, registro.salario);
	
	printf("Deseja alterar esse registro? (1-sim / 0-nao): ");
	scanf("%d", &opcao);
	fflush(stdin);

	// Cai fora se não escolheu alterar o registro
	if (opcao != 1) return -1;

	// Altera o registro
	do {
		printf("O que deseja alterar? \n");
		scanf("%d", &alteracao);
		fflush(stdin);

		switch (alteracao) {
			case 1: // alterar CPF
				system("cls");
				// Garante que o CPF esteja formatado
				do {
					// Pega o CPF
					printf("Digite o CPF: ");
					gets(registro.CPF);
					fflush(stdin);
					
					// Valida o CPF
					duplicata = buscar(registro.CPF);
					if(duplicata >= 0) printf("CPF já cadastrado!\n\n");
					if (!validarCPF(registro.CPF)) printf("CPF inválido!\n\n");
				} while(duplicata >= 0 || !validarCPF(registro.CPF));
				break;
			case 2: // alterar nome
				system("cls");
				printf("Digite o novo nome: ");
				gets(registro.nome);
				fflush(stdin);
				break;
			case 3: // alterar salario
				system("cls");
				// Pega o salario e garante que seja numero
				registro.salario = -1;
				do {
					printf("Digite o salario: ");
					scanf("%f", &registro.salario);
					fflush(stdin);
				} while (registro.salario < 0);
				break;
			default:
				printf("Opção inválida!\n");
				break;
		}

		printf("Deseja alterar algo a mais? (1-sim / 0-não): ");
		scanf("%d", &opcao);
		fflush(stdin);
		if (opcao == 1) {
			system("cls");
			printf("");
			printf("\n1 - CPF: %s \n2 - Nome: %s \n3 - Salario: %.2f\n\n", registro.CPF, registro.nome, registro.salario);
		}
	} while (opcao == 1);

	// alteracao no arquivo
	fseek(fp, indice * sizeof(Funcionario), SEEK_SET);
	fwrite(&registro, sizeof(Funcionario), 1, fp);

	return 0;
}

int validarCPF(char cpf[11]) {
	int i;
	
	// Verifica se só tem numeros no CPF
	for (i=0; i<strlen(cpf); i++)
		if (cpf[i] < 48 || cpf[i] > 57) return 0;
		
	// Verifica se o CPF tem 11 digitos
	if (strlen(cpf) != 11) return 0;
	
	// Retorna 1 se o CPF é valido
	return 1;
}
