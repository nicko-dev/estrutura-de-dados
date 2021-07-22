void printaGrauUm (no* p){
	
	if (p == NULL) { //árvore vazia
    	cout << "Arvore vazia!!" << endl;
    	return;
    }
	
	if(p->esq == NULL){ //subarvore esquerda vazia
		if(p->dir != NULL){ //subarvore direita não vazia
			cout << p->dados << endl; //printa o nó p, de grau 1
			printaGrauUm (p->dir) //repete o processo na subárvore direita
		}
		else{ //ambas subarvores vazias, p é folha
			return;
		}
	}
	else { //subarvore esquerda não vazia
		if (p->dir == NULL){ //subarvore direita vazia
			cout << p->dados << endl; //printa o nó p, de grau 1
			printaGrauUm (p->esq) //repete o processo na subárvore esquerda
		}
		else{ //ambas subarvores não vazias
			printaGrauUm (p->dir);
			printaGrauUm (p->esq); //repete o processo para ambas subarvores
		}
	}
}