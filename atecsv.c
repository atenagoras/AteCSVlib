/* Arquivo C com as funções, estruturas e typedefs para implementar processamento    *
 * de arquivos CSV em programas que precisam disso. Eventualmente, haverá um header  *
 * para este arquivo.                                                                *
 * - Próxima versão destas funções devem ser capazes de trabalhar com listas         *
 * encadeadas, e alocação de memória para ponteiros de caracteres DENTRO             *
 * da estrutura.                                                                     *
 *                                                                                   *
 *                                                 Atenágoras Souza Silva 28/01/2016 */

/* Provavelmente as bibliotecas stdio.h e string.h serão necessárias, mas conto       *
 * Que serão chamadas nos programas de teste ou principais, também.                   *
 *------------------------------------------------------------------------------------- 
 * ********* Descrição dos Cabeçalhos  ********************************************** *
 * stdlib.h: Contém as funções de gerenciamento dinâmico de memória (malloc(),        *
 *                                                   exit(), calloc(), realoc() etc   *
 * string.h: Contém as funções de manipulação de strings (strtok() é essencial aqui)  *
 * stdio.h: Contém as funções de entrada e saída padrões da Linguagem C               *
 * ************************************************************************************/

/*                             Relatos e Alterações                                   *
 * - No primeiro teste, verificou-se que a função separadorCSV() ao alocar memória à  *
 *   estrutura que foi passada por referência, altera seu endereço, mas não o reporta *
 *   à função que fez a chamada e enviou a estrutura.                                 *
 *   Devo criar uma versão que desta função que não aloca memória à estrutura.        *
 *   Isto é tarefa da função que chamará separadorCSV().                              *
 *   > Em main(): Alocação de Memória à estrutura na função principal                 *  
 *   >          : receber no ponteiro *CamposCSV o endereço da estrutura              * 
 *     declarada Dentro de separadorCSV()                                             *
 *   >          : Definir tamanho_csv chamando função ContaCampos() em                *
 *     atecsv.c                                                                       *
 *   > Em separadorCSV(): receber o Nº de campos da função como parâmetro             *
 *   >                    Função declarada como ponteiro de estrutura do              *
 *     tipo AteCSVString                                                              *
 *   >                  : Devolver o ponteiro para a estrutura declarada na           *
 *     função, em vez da estrutura, pois de outro modo, só retornaria o               *
 *     primeiro campo                                                                 *
 *                                                (31/02/2016)                        *
 *                                                                                    *
 * ********************************************************************************** */
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

typedef struct csv_string{
	char campo[256];
} AteCSVString; // estrutura para ler os campos de cada linha

// Função para contar o número de campos em uma linha contando o número de delimitadores
int ContaCampos(char Linha[], char delim){
	/*delim é o delimitador de campos da string, por exemplo ';', ou ',', a escolha do usuário.*/
	int tamanho=strlen(Linha),cont=0,Ncampos,i;
	char Delim[2];
	for (i=0;i<tamanho;i++)
		if (Linha[i] == delim)
			cont++;
	if ((Linha[i] == delim) ||(Linha[i-1] == delim)) // Define Nº de campos de acordo com o
		Ncampos = cont;                          // Nº de delimitadores encontrados.
	else                                             // Se tiver um delimitador no final da
		Ncampos = cont+1;                        // linha, Ncampos=cont. Não é o padrão.
	return Ncampos;
}

// Função para processar uma linha/string de cada vez
AteCSVString * separadorCSV(char Linha[],int Ncampos, char delim){
	/*delim é o delimitador de campos da string, por exemplo ';', ou ',', a escolha do usuário.*/
	int tamanho = strlen(Linha),cont=0, i;
	AteCSVString *campos;
	char *pchar, Delim[2];
	Delim[0] = delim;
	campos = (AteCSVString *) malloc(Ncampos*sizeof(AteCSVString)); // Alocando Memória para cada campo.
	// Separando os campos da Linha CSV de fato
	pchar = strtok(Linha, Delim);
	i=0;
	while(pchar != NULL){
		printf("Dentro de separadorCSV: %s\n",pchar);
		strcpy(campos[i].campo,pchar);
		pchar = strtok(NULL, Delim);
		i++;
	}
	return campos;
}

// Voltar a trabalhar nesta versão da função quando aprender a lidar melhor com ponteiros
/*int separadorCSV(char Linha[],AteCSVString *campos, char delim){
	//delim é o delimitador de campos da string, por exemplo ';', ou ',', a escolha do usuário.
	int tamanho = strlen(Linha),cont=0,Ncampos, i;
	char *pchar, Delim[2];
	Delim[0] = delim;
	for (i=0;i<tamanho;i++)
		if (Linha[i] == delim)
			cont++;
	if ((Linha[i] == delim) ||(Linha[i-1] == delim)) // Define Nº de campos de acordo com o
		Ncampos = cont;                          // Nº de delimitadores encontrados.
	else                                             // Se tiver um delimitador no final da
		Ncampos = cont+1;                        // linha, Ncampos=cont. Não é o padrão.
	campos = (AteCSVString *) malloc(Ncampos*sizeof(AteCSVString)); // Alocando Memória para cada campo.
	// Separando os campos da Linha CSV de fato
	pchar = strtok(Linha, Delim);
	i=0;
	while(pchar != NULL){
		printf("Dentro de separadorCSV: %s\n",pchar);
		strcpy((*(campos+i)).campo,pchar);
		pchar = strtok(NULL, Delim);
		i++;
	}
	return Ncampos;
	// Importante para que o programa a chamar a função saiba o tamanho do array
	// de estrutura AteCSVString para "varrê-lo no código
}*/
