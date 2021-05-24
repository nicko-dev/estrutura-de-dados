//============================================================================
// Name        : trab-edav2.cpp
// Author      : Nickolas Barbosa, mat: 2012297BCC
// Version     :
// Copyright   : Your copyright notice
// Description : Programa de gerenciamento de comandas de um restaurante
//============================================================================

#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;
#define max 30;

struct item {
	int codP; //codigo do item
	float valor; //valor do item
	item* proxP; //endereço do proximo item
};

struct comanda {
	int vago; // 1: comanda livre, 0: comanda em uso
	item* headItem; //head da lista de items
};

//Complexidade: O(n)

void comecaDia (comanda* cliente){

	//Inicializa os status de todas as comandas como livres (1) e esvazia a lista de items

	int maxClientes = max;

	for(int i=0; i<maxClientes; i++){
		cliente[i].vago = 1;
		cliente[i].headItem = NULL;
	}
}

//Complexidade: O(n)

float* criaCardapio(int maxItens){

	//Cria um cardápio genérico apenas para testar o programa. O cardápio poderia ser lido de uma tabela no formato CSV

	float* item = new float[maxItens];

	for (int i=0;i<maxItens;i++){
		item[i] = 5 + (float)(rand()%1001)/(1+rand()%10);
	}

	return item;
}

//Complexidade: O(1)

int checaComanda (comanda* cliente, int indexCliente){

	//Retorna o status da comanda
	int maxClientes = max;

	if (indexCliente<0 || indexCliente>=maxClientes || cliente[indexCliente].vago){
		cout<<"\nComanda inválida!";
		return 0; //Comanda não está em uso
	}
	return 1; //Comanda em uso

}

//Complexidade: O(n)


int printaComanda (comanda* cliente, int indexCliente){

	//Printa os itens da conta com seus seus respectivos valores

	if(!cliente[indexCliente].headItem){
		cout<<	"\nComanda vazia!\n";
		return 0;
	}

	item* atual = cliente[indexCliente].headItem;

	cout<<	"\n*————————————————————*"
			"\n  Comanda "<<indexCliente+1<<":\n"
			"\n  Item        Valor\n";

	ios  state(NULL);
	state.copyfmt(std::cout);

	while(atual!=NULL){
		cout<<"  "<<setfill('0')<<setw(3)<<(*atual).codP<<"       R$ "<<setfill(' ')<<fixed<<setw(6)<<setprecision(2)<<(*atual).valor<<endl;
		atual = (*atual).proxP;
	}

	cout.copyfmt(state);

	cout<<"\n*————————————————————*";

	return 1;
}

//Complexidade: O(n)

int addCliente (comanda* cliente){

	//Verifica a primeira comanda vazia (ordem crescente) e retorna o índice dela ou 0 se o restaurante estiver cheio.

	int maxClientes = max;

	for(int i=0; i<maxClientes; i++){
		if(cliente[i].vago){
			cliente[i].vago = 0;
			return i+1;
		}
	}
	return 0;
}

//Complexidade: O(n)

int addItem (comanda* cliente, int codProduto, float* cardapio){

	//Adiciona um ou mais novos itens a uma comanda.

	item* ultimo = (*cliente).headItem;
	item* novoItem = new item(); //cria o novo item

	(*novoItem).codP = codProduto; //preenche as infos do item a ser adicionado
	(*novoItem).valor = cardapio[codProduto-1];
	(*novoItem).proxP = NULL;

	if ((*cliente).headItem==NULL) //adiciona o novo item ao fim da lista
		(*cliente).headItem = novoItem;
	else{
		while((*ultimo).proxP!=NULL)
			ultimo = (*ultimo).proxP;
		(*ultimo).proxP = novoItem;
	}

	cout<< "Item "<< codProduto << " adicionado com sucesso";
	return 1;
}

//Complexidade: O(n)

int removeItem(comanda* cliente, int codProduto){

	//Cancela um ou mais itens de uma comanda

	item* anterior = (*cliente).headItem;
	item* atual = (*anterior).proxP;

	if((*anterior).codP==codProduto){ //verifica se o item buscado é o primeiro da fila e o remove se sim
		(*cliente).headItem = (*anterior).proxP;
		free(anterior);
		return 1;
	}

	do{ //procura pelo item no resto da lista e o remove se achar
		if ((*atual).codP==codProduto){
			(*anterior).proxP = (*atual).proxP;
			free (atual);
			return 1;
		}
		anterior = atual;
		atual = (*atual).proxP;
	}while(atual);
	return 0; //retorna 0 se o item não for encontrado
}

//Complexidade: O(n)

float fechaComanda (comanda* cliente, int indexCliente){

	//Calcula e printa o total da conta enquanto libera a memória usada pra armazená-la

	int continuar;

	if(!cliente[indexCliente].headItem){
		cout<<"\nComanda vazia!"
		"\nDigite 1 para liberar a comanda ou 0 para voltar: ";

		cin>>continuar;
		if(!continuar)
			return 0;

		cliente[indexCliente].vago = 1;
		cout<<"\nComanda liberada!";
		return 0;
	}

	item* atual = cliente[indexCliente].headItem;
	item* proximo = NULL;
	float total = 0;

	cout<<	"\n*————————————————————*"
			"\n  Comanda "<<indexCliente+1<<":\n"
			"\n  Item        Valor\n";

	ios  state(NULL);
	state.copyfmt(std::cout);

	while(atual){
		cout<<"  "<<setfill('0')<<setw(3)<<(*atual).codP<<"       R$ "<<setfill(' ')<<fixed<<setw(6)<<setprecision(2)<<(*atual).valor<<endl;
		total += (*atual).valor;
		proximo = (*atual).proxP;
		free(atual);
		atual=proximo;
	}

	cout<<"\n     Total: R$ "<<total;
	cout<<"\n*————————————————————*";

	cout.copyfmt(state);

	cliente[indexCliente].vago = 1;
	cliente[indexCliente].headItem = NULL;
	return total;
}

//Complexidade: O(n)

int fechaDia (comanda *cliente, float totalDia){

	//Fecha o dia e imprime o valor geral. Só finaliza se não houverem contas pendentes

	int resposta, maxClientes = max;

	for (int i=0; i<maxClientes;i++){ //verifica se alguma comanda ainda está aberta e pergunta se o usuário deseja fechá-la
		if(cliente[i].headItem){
			cout<<"\nComanda "<<i+1<<" em uso!"
			<<"\nDigite 1 para fechar a comanda ou 0 para sair: ";
			cin>> resposta;
			if(!resposta)
				return 0;
			else
				totalDia+=fechaComanda(cliente, i);
		}
	}

	cout<<	"\n\nNenhuma comanda em aberto."
			"\nRealizando fechamento do dia..."
			"\nValor total do dia: R$ "<<fixed<<setprecision(2)<< totalDia;
	return 1;
}

int main() {

	int resposta, maxItens = 40, maxClientes = max;
	float totalDia = 0;

	float* cardapio = criaCardapio(maxItens);
	comanda* cliente = new comanda[maxClientes];
	comecaDia(cliente);

	do {
		cout<<  "\n ______________________________"
				"\n|                              |"
				"\n| Olá! O que deseja fazer?     |"
				"\n| 1: Abrir conta               |"
				"\n| 2: Adicionar item            |"
				"\n| 3: Cancelar item             |"
				"\n| 4: Exibir itens na comanda   |"
				"\n| 5: Fechar conta              |"
				"\n| 6: Fechar dia e sair         |"
				"\n|______________________________|"
				"\n\nDigite sua resposta e tecle ENTER: ";
		cin>> resposta;
		cout<<"\n+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n";


		switch(resposta){
			case 1: //Verifica disponibilidade e abre uma comanda
			{
				int indexCliente = addCliente(cliente);
				if(indexCliente)
					cout<<"\nComanda número "<<indexCliente<<" liberada\n";
				else
					cout<< "\nRestaurante lotado no momento, aguarde a liberação de uma comanda.\n";
				break;
			}

			case 2: //Adiciona item a uma comanda aberta
			{
				int codProduto, indexCliente, continuar = 0;

				do{
					cout<<"\nDigite o número da comanda ou 0 para voltar: ";
					cin>> indexCliente;
					if(!indexCliente)
						break;
					continuar = checaComanda(cliente, indexCliente-1);
				}while(!continuar);

				while(continuar){
					cout<<"\nDigite o código do produto entre 1 e 40: ";
					cin>> codProduto;
						if(codProduto<1 || codProduto>maxItens){
							cout<<"Código inválido!\n";
							continue;
						}
					addItem(&cliente[indexCliente-1], codProduto, cardapio);
					cout<<"\nPara adicionar outro item digite 1 ou digite 0 para finalizar: ";
					cin>>continuar;
				}

				break;
			}

			case 3: //Remove um item de uma comanda aberta
			{
				int codProduto, indexCliente, continuar = 0;

				do{
					cout<<"\nDigite o número da comanda ou 0 para voltar: ";
					cin>> indexCliente;
					if(!indexCliente)
						break;
					continuar = checaComanda(cliente, indexCliente-1);
				}while(!continuar);

				while(continuar){
					if(!printaComanda (cliente, indexCliente-1))
						break;
					cout<<"\nDigite o código do item a ser cancelado: ";
					cin>> codProduto;
					if(!removeItem(&cliente[indexCliente-1], codProduto)){
						cout<<"\nCódigo inválido, nenhum item cancelado.";
					}
					cout<< "\nDigite 1 para realizar outro cancelamento ou 0 para finalizar: ";
					cin>> continuar;
				}

				break;
			}

			case 4: //Imprime os itens de uma comanda com seus respectivos valores
			{
				int continuar, indexCliente;

				do{
					cout<<"\nDigite o número da comanda ou 0 para voltar: ";
					cin>> indexCliente;
					if(!indexCliente)
						break;
					continuar = checaComanda(cliente, indexCliente-1);
				}while(!continuar);

				if(indexCliente)
					printaComanda (cliente, indexCliente-1);

				break;
			}

			case 5: //Fecha uma comanda e imprime o total
			{
				int indexCliente, continuar;

				do{
					cout<<"\nDigite o número da comanda ou 0 para voltar: ";
					cin>> indexCliente;
					if(!indexCliente)
						break;
					continuar = checaComanda(cliente, indexCliente-1);
				}while(!continuar);

				if(indexCliente)
					totalDia += fechaComanda(cliente, indexCliente-1);
				break;
			}

			case 6: //Fecha o dia e imprime o valor geral do dia
			{
				if(!fechaDia(cliente, totalDia))
					resposta = 0;
				break;
			}
			default:
			{
				cout<<"\nOPÇÃO INVÁLIDA!";
				break;
			}
		}
	}while(resposta != 6);
	return 0;
}
