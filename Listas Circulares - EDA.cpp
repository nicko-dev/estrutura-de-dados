//============================================================================
// Name        : T3-EDA.cpp
// Author      : Nickolas Barbosa
// Description : Manipulacao de listas circulares
//============================================================================

#include <iostream>
using namespace std;

struct node {
	int index;
	node *nextNode;
};

void printaListaCircular (node *lastNode) {

	if(lastNode == NULL){ //Lista Vazia
		cout<<"LISTA VAZIA!!"<<endl;
		return;
	}

	node *atual = lastNode->nextNode;
	int primeiro = atual->index;

	do{
		cout<< "Node " << atual->index <<endl;
		atual=atual->nextNode;
	}while (atual->index != primeiro);

	return;
}

int tamanhoLista (node *lastNode){

	int tamanho = 0;

	if(lastNode == NULL) //Lista Vazia
		return tamanho;
	else{
		int primeiro = lastNode->index;
		node *atual = lastNode;
		do{
			tamanho++;
			atual = atual->nextNode;
		}while (atual->index != primeiro);
	}

	return tamanho;
}

node *criaListaVazia (){ //Cria uma lista vazia

	node *lastNode = new node();
	lastNode = NULL;
	return lastNode;

}

void addNode (node** lastNode){ //Adiciona um novo nó no no fim da fila

	node *atual = *lastNode;
	node *newNode = new node();

	if(atual == NULL){ //Lista Vazia
		newNode->index = 0;
		newNode->nextNode = newNode;
	}
	else{
	newNode->index = atual->index + 1;
	newNode->nextNode = atual->nextNode;
	atual->nextNode = newNode;
	}

	*lastNode = newNode;
}

void removeNode (node **lastNode, int removeIndex){ //remove nó que contem a informação especificada

	if(*lastNode == NULL){ //Lista Vazia
		cout<<"LISTA VAZIA!!"<<endl;
		return;
	}

	if((*lastNode)->nextNode == *lastNode){ //Lista com apenas 1 elemento
		free(*lastNode);
		*lastNode=NULL;
		return;
	}


	node *atual = (*lastNode)->nextNode;
	node *anterior = *lastNode;
	int primeiro = atual->index;

	//if(atual->index == removeIndex)

	do{
		if(atual->index == removeIndex){
			anterior->nextNode = atual->nextNode;
			free(atual);
			cout<< "Nó "<<removeIndex<<" removido com sucesso"<<endl;
			return;
		}
		anterior = atual;
		atual = atual->nextNode;
	}while (atual->index != primeiro);

	cout<<"No "<< removeIndex<<" nao encontrado. Nenhum no removido"<<endl;
	return;
}


int main() {

	node *lastNode = criaListaVazia();
	int tamListaInicial=30;

	cout<<"*-*-*TESTANDO FUNCOES DE LISTA CIRCULAR*-*-*"<<endl;

	for(int i=0; i<tamListaInicial;i++)
		addNode (&lastNode);

	cout<< "\nLista inicial: "<<endl;
	printaListaCircular(lastNode);
	cout<< "\nA lista contem " << tamanhoLista(lastNode)<<" no(s)" <<endl;
	cout<<"\n_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_\n"
		  "\nRemovendo nos:"<<endl;

	removeNode(&lastNode, 5);
	removeNode(&lastNode, 13);
	removeNode(&lastNode, 22);
	removeNode(&lastNode, 28);

	cout<<"\nTentando remover nos que nao estao na lista:"<<endl;

	removeNode(&lastNode, 5);
	removeNode(&lastNode, 44);

	cout<<"\n_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_"<<endl;

	cout<< "\nLista apos a remocao: "<<endl;
	printaListaCircular(lastNode);
	cout<< "\nA lista contem " << tamanhoLista(lastNode)<<" no(s)" <<endl;

	cout<<"\n_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_\n"
			  "\nAdicionando 3 novos nos:"<<endl;

	for(int i=0; i<3;i++)
			addNode (&lastNode);
	cout<< "\nLista apos a adicao: "<<endl;
	printaListaCircular(lastNode);
	cout<< "\nA lista contem " << tamanhoLista(lastNode)<<" no(s)" <<endl;


	cout<<"\n*-*-*-*-*-*-*-*FIM DOS TESTES*-*-*-*-*-*-*-*"<<endl;

	return 0;
}
