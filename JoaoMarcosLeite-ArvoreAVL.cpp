#include <iostream>

using namespace std;


struct no{

  int num;
  int alt;
  struct no* esq;
  struct no* dir;
};

typedef struct no* noPtr;

int verificarMaior(int x,int y){ //Complexidade O(1)
  if(x > y){
    return x;
  } else{
    return y;
  }

}

int calcularAltura(noPtr *raiz){ //Complexidade O(1)

  if(*raiz == NULL){
    return 0;
  } else {
    return (*raiz)->alt;
  }

}

int atualizarAltura(noPtr *raiz){ //Complexidade O(1)
  if(*raiz == NULL){
    return 0;
  } else {
    return (*raiz)->alt = 1 + verificarMaior(calcularAltura(&(*raiz)->esq) , calcularAltura(&(*raiz)->dir)); 
  }
}

int calcularFB(noPtr *raiz){ //Complexidade O(1)

  noPtr aux = *raiz;

  if(*raiz == NULL){
    return 0;
  } else {
    return calcularAltura(&aux->esq) - calcularAltura(&aux->dir);
  }
}

noPtr novoNo(int x){ //Complexidade O(1)
   noPtr p = new(no);
    p->num = x;
    p-> esq = NULL;
    p->dir = NULL;
    p->alt = 1;
    return p;
}

bool arvoreVazia(noPtr *raiz){//Complexidade O(1)
  if (*raiz == NULL){
    return true;
  } else {
    return false;
  }
}

noPtr rotacaoLL(noPtr *raiz){ //Complexidade O(1)
  if(*raiz != NULL){
    noPtr a = (*raiz)->dir;
    noPtr b = a->esq;
    
    a->esq = *raiz;
    (*raiz)->dir = b;

    atualizarAltura(raiz);
    atualizarAltura(&a); 
    
    return a;
  } else {

    return *raiz;
  }
}

noPtr rotacaoRR(noPtr *raiz){ //Complexidade O(1)
  if(*raiz != NULL){
    noPtr a = (*raiz)->esq;
    noPtr b = a->dir;
    
    a->dir = *raiz;
    (*raiz)->esq = b;

    atualizarAltura(raiz);
    atualizarAltura(&a);

    return a;

  } else {

    return *raiz;
  }
  
}

noPtr inserir(noPtr *raiz, int x){ //Complexidade O(log n)

  if(arvoreVazia(raiz)){

    return novoNo(x);

  } else {

    if((*raiz)->num !=x){
      if(x < (*raiz)->num){
        (*raiz)->esq = inserir(&(*raiz)->esq,x);
      } else if (x > (*raiz)->num){
        (*raiz)->dir = inserir(&(*raiz)->dir,x);
      }
    }

    atualizarAltura(raiz);

    int fb = calcularFB(raiz);

    if(fb > 1){
      if(x < (*raiz)->esq->num){

        return rotacaoRR(raiz);

      }else{
        (*raiz)->esq = rotacaoLL(&(*raiz)->esq);
        *raiz = rotacaoRR(raiz);
      } 

    }else if( fb < -1){
      if(x > (*raiz)->dir->num){

        return rotacaoLL(raiz);

      }else{

        (*raiz)->dir = rotacaoRR(&(*raiz)->dir);
        *raiz = rotacaoLL(raiz);

       }
    } 
  }

  return *raiz;

}

noPtr maiorLadoEsq(noPtr *raiz){ //Complexidade O(n)

  noPtr aux = *raiz;

  while(aux->dir != NULL){
    aux = aux-> dir;
  }

  return aux;


}

noPtr retirar(noPtr *raiz, int x){ //Complexidade O(log n)

  if(arvoreVazia(raiz)){
    return *raiz;

  } else{
      if( x < (*raiz)-> num){

      (*raiz)->esq = retirar(&(*raiz)->esq,x);

      } else if (x > (*raiz)-> num){

        (*raiz)->dir = retirar(&(*raiz)->dir,x);

      }else{

        if((*raiz)->esq == NULL || (*raiz)->dir == NULL ){

          noPtr p;

          if((*raiz)->esq ==NULL){
            p = (*raiz)-> dir;
          } else {
            p = (*raiz)-> esq;
          }

          if(p == NULL){
            p = *raiz;
            *raiz = NULL;
          } else{
            *raiz = p;
          }

          free(p);

        }else{
          
          noPtr p = maiorLadoEsq(&(*raiz)->esq);
          (*raiz)-> num = p-> num;
          (*raiz)->esq = retirar(&(*raiz)->esq, p->num);
      }
    }
  }

  atualizarAltura(raiz);

  if(calcularFB(raiz) > 1 && x < (*raiz)->esq->num){

    return rotacaoRR(raiz) ;
  }

  if(calcularFB(raiz) > 1 && x > (*raiz)->esq->num){
    (*raiz)->esq = rotacaoLL(&(*raiz)->esq);
    return rotacaoRR(raiz);
  }

  if(calcularFB(raiz) < -1 && x > (*raiz)->dir->num){
    return rotacaoLL(raiz);
  }

  if(calcularFB(raiz) < -1 && x < (*raiz)->dir->num){
    (*raiz)->dir = rotacaoRR(&(*raiz)->dir);
    return rotacaoLL(raiz);
  }
  
  return *raiz;
}

void listarArvoreInOrder(noPtr *raizes){ //Complexidade O(log n)
  
  if(*raizes != NULL){
    listarArvoreInOrder(&(*raizes)->esq);
    cout << " - " << (*raizes)-> num;
    listarArvoreInOrder(&(*raizes)->dir);
  }
}

void liberarEspaco(noPtr *no){ //Complexidade O(log n)

  if(*no != NULL){

    liberarEspaco(&(*no)->esq);
    liberarEspaco(&(*no)->dir);
    free(no);
  }
}

int main(){

  noPtr arvore = NULL;
  noPtr q;  
  int op,x,y;

  do{
    cout<< "Digite o valor de Operacao:" << endl <<
    "1 - Inserir elemento na Arvore" << endl << 
    "2 - Retirar Elemento da Arvore" << endl <<
    "3 - Listar a Arvore"<< endl;

    cin >> op;

    switch(op){

      case 1: 
      cout << "Qual numero voce quer inserir na arvore?" << endl;
      cin >> x;
      arvore = inserir(&arvore, x);
      break;  

      case 2: 
      if(arvoreVazia(&arvore)){

        cout << "A Arvore esta vazia!" << endl;
      } else {

      cout << "Qual elemento voce quer retirar?"<<endl;
      cin >> y;
      arvore = retirar(&arvore,y);
      }

      break;

      case 3: 
      if(arvoreVazia(&arvore)){

        cout << "A Arvore esta vazia!" << endl;
      } else {
    
        cout<< "Arvore(inOrder):" <<endl;
        listarArvoreInOrder(&arvore);
        cout << endl;

      }
        
      break;

    }  

  } while(op != 0);

  liberarEspaco(&arvore);
  
}