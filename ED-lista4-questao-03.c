/*
** Função :
** Autor : Maysa de Lima Maciel
** Data : 02/06/2024
** Observações:
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
  int dia;
  int mes;
  int ano;
} Data;

typedef struct {
  char nome_completo[80];
  char sexo;
  Data data_nascimento;
  float altura;
  float peso;
} PerfilSaude;

int calcular_idade(Data data_nascimento) {
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  int idade = tm.tm_year + 1900 - data_nascimento.ano;

  if (tm.tm_mon + 1 < data_nascimento.mes ||
      (tm.tm_mon + 1 == data_nascimento.mes &&
       tm.tm_mday < data_nascimento.dia)) {
    idade--;
  }

  return idade;
}

float calcular_IMC(float peso, float altura) {
  return peso / (altura * altura);
}

int frequencia_cardiaca_maxima(int idade) { return 220 - idade; }

int frequencia_cardiaca_ideal(int idade, char sexo) {
  int maxFC = frequencia_cardiaca_maxima(idade);
  if (sexo == 'M' || sexo == 'm') {
    return (int)(0.7 * maxFC);
  } else {
    return (int)(0.6 * maxFC);
  }
}

int exp_vida(char sexo) {
  if (sexo == 'M' || sexo == 'm') {
    return 75;
  } else {
    return 80;
  }
}

void dados(PerfilSaude *perfil) {
  printf("Digite o nome completo: ");
  getchar();
  fgets(perfil->nome_completo, sizeof(perfil->nome_completo), stdin);
  perfil->nome_completo[strcspn(perfil->nome_completo, "\n")] = '\0';

  printf("Digite o sexo (M/F): ");
  scanf(" %c", &perfil->sexo);

  printf("Digite a data de nascimento (digite um por vez): ");
  scanf("%d %d %d", &perfil->data_nascimento.dia, &perfil->data_nascimento.mes,
        &perfil->data_nascimento.ano);

  printf("Digite a altura (em metros): ");
  scanf("%f", &perfil->altura);

  printf("Digite o peso (em kg): ");
  scanf("%f", &perfil->peso);
}

void exibir_perfil(PerfilSaude perfil) {
  printf("\nPerfil de Saúde:\n");
  printf("Nome completo: %s\n", perfil.nome_completo);
  printf("Sexo: %c\n", perfil.sexo);
  printf("Data de nascimento: %02d/%02d/%04d\n", perfil.data_nascimento.dia,
         perfil.data_nascimento.mes, perfil.data_nascimento.ano);
  printf("Altura: %.2f metros\n", perfil.altura);
  printf("Peso: %.2f kg\n", perfil.peso);
}

void exibir_tabela_IMC() {
  printf("\nTabela de Valores do IMC:\n");
  printf("Menor que 18.5: Abaixo do peso\n");
  printf("Entre 18.5 e 24.9: Peso normal\n");
  printf("Entre 25 e 29.9: Sobrepeso\n");
  printf("Entre 30 e 34.9: Obesidade grau 1\n");
  printf("Entre 35 e 39.9: Obesidade grau 2\n");
  printf("40 ou maior: Obesidade grau 3\n");
}

int main() {
  int N;
  printf("Digite o número de perfis de saúde a serem cadastrados: ");
  scanf("%d", &N);

  PerfilSaude *perfis = (PerfilSaude *)malloc(N * sizeof(PerfilSaude));

  for (int i = 0; i < N; i++) {
    printf("\nCadastrando o perfil %d:\n", i + 1);
    dados(&perfis[i]);
  }

  for (int i = 0; i < N; i++) {
    exibir_perfil(perfis[i]);

    int idade = calcular_idade(perfis[i].data_nascimento);
    float imc = calcular_IMC(perfis[i].peso, perfis[i].altura);
    int fcMax = frequencia_cardiaca_maxima(idade);
    int fcIdeal = frequencia_cardiaca_ideal(idade, perfis[i].sexo);
    int expectativa = exp_vida(perfis[i].sexo) - idade;

    printf("Idade: %d anos\n", idade);
    printf("IMC: %.2f\n", imc);
    printf("Frequência cardíaca máxima: %d bpm\n", fcMax);
    printf("Frequência cardíaca ideal: %d bpm\n", fcIdeal);
    printf("Expectativa de vida: %d \n\n", expectativa);
  }

  free(perfis);

  exibir_tabela_IMC();

  return 0;
}