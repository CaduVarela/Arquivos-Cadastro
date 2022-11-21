#include <stdio.h>
#include <string.h>

typedef struct {
	char CPF[12];
	char nome[50];
	float salario;
	int situacao_cadastro;
} Funcionario;

int main() {
	Funcionario joao;
	strcpy(joao.nome, "Joao Banana");
	printf("%s", joao.nome);
	return 0;
}
