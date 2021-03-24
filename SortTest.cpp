/*
 * SortTest.cpp
 *
 *  Created on: Feb 25, 2021
 *      Author: Nick
 */

#include <iostream>
using namespace std;

void PreencheVetor (int* v, int n, int e, int d){

	int i;

	for (i = 0; i< n; i++){
		v[i] = (rand() % (d - e + 1)) + e;
	}
}

void PrintVetor (int* v, int n){

	int i;

	cout<< endl;

	for (i= 0; i< n; i++)
		cout<< v[i]<< " ";

}

void BubbleSort (int* v, int n){

//Compara cada elemento e realiza a troca se a condição for atendida

	int i, j, aux;

	for (i= 0; i< n; i++){
		for (j = i + 1; j < n; j++){
			if (v[i] > v[j]){
				aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
}

void SelectionSort (int* v, int n){

//Elege o primeiro elemento e só realiza a troca após compará-lo com todos os demais

	int i, j, aux, menor;

	for (i= 0; i< n; i++){

		menor= i;

		for (j = i + 1; j < n; j++){
			if (v[menor] > v[j])
				menor=j;
		}

		aux = v[i];
		v[i]=v[menor];
		v[menor] = aux;
	}

}

void InsertionSort (int* v, int n){

//Compara um elemento chave com seu anterior, se for menor, compara com o anterior (recursiva). A troca só realizada quando o elemento chave não for menor que o comparado.

	int i, j, chave;

	    for (i = 1; i < n; i++)
	    {
	        chave = v[i];
	        j = i - 1;

	        while (j >= 0 && v[j] > chave)
	        {
	            v[j + 1] = v[j];
	            j--;
	        }
	        v[j + 1] = chave;
	    }
}

void RecursiveInsertionSort (int* v, int n){

//Versão recursiva da função InsertionSort

	if (n <= 1)
		return;

	RecursiveInsertionSort(v, n-1);

	int ultimo = v[n-1], j = n-2;

	while (j >= 0 && v[j] > ultimo){

		v[j+1] = v[j];
		j--;

	}

	v[j+1] = ultimo;

}

void Merge (int* v, int inicio, int meio, int fim){

//Esta função é dividida em 2:
//MergeSort: subdivide o array em metades até não ser mais possível
//Merge: Concatena as subdivisões ordenadas em um unico vetor novamente

	int n1 = meio - inicio + 1;
	int n2 = fim - meio;

	int E[n1], D[n2], i, j;

	for (int i = 0; i < n1; i++)
		E[i] = v[inicio + i];
	for (int j = 0; j < n2; j++)
		D[j] = v[meio + 1 + j];

	int k = inicio;
	i = 0;
	j = 0;

	while (i < n1 && j < n2) {
		if (E[i] <= D[j]) {
			v[k] = E[i];
			i++;
		}

		else {
			v[k] = D[j];
			j++;
		}

		k++;
	}

	while (i < n1) {
		v[k] = E[i];
		i++;
		k++;
	}

	while (j < n2) {
		v[k] = D[j];
		j++;
		k++;
	}

}

void MergeSort (int* v, int inicio, int fim){

//Esta função é dividida em 2:
//MergeSort: subdivide o array em metades até não ser mais possível
//Merge: Concatena as subdivisões ordenadas em um unico vetor novamente

    if(inicio >= fim){
        return;
    }

	int meio;

	if (inicio < fim){
		meio = inicio + (fim - inicio)/2;
		MergeSort (v, inicio, meio);
		MergeSort (v, meio + 1, fim);
		Merge (v, inicio, meio, fim);
	}
}

int main() {

	int A[10];

	PreencheVetor (A, 10, 10, 40);

	PrintVetor (A, 10);
	MergeSort(A, 0, 10);
	PrintVetor (A, 10);

	return 0;
}
