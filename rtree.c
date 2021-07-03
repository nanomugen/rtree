#include <stdio.h>
#include <stdlib.h>
#include "rtree.h"
/*CONSIDERAÇÕES
    1. Every leaf node contains between m and M index records unless it is the
root Thus, the root can have less entries than m
    2. For each index record in a leaf node, I is the smallest rectangle that spatially
contains the n-dimensional data object represented by the indicated tuple
    3. Every non-leaf node has between m and M children unless it is the root
    4. For each entry in a non-leaf node, i is the smallest rectangle that spatially
contains the rectangles in the child node
    5. The root node has at least two children unless it is a leaf
    6. All leaves appear on the same level. That means the tree is balanced

    NA LITERATURA ELE CONSIDERA O LEAF-NODE AQUELE QUE DETEM m-M DADOS COMO 'FILHOS' 
    AQUI POR UMA QUESTÃO DE SIMPLIFICAÇÃO PRA SABER SE UM NODE É LEAF SERÁ PESQUISADO 
    "NODE->CHILDREN[0]->CHILDREN[0]==NULL?" SE SIM QUER DIZER QUE ESTE NODE É LEAF 
    E SEU FILHO É DATA (O RECT EM SI É A INFORMAÇÃO AMAZENADA)


*/

int main(){
   
	printf("init\n");
    return 0;
}

node createNode(){
    node *node = malloc(sizeof(node));
    *node->r = createRect(0,0,0,0);
    node->prole=0;

    //printf("createNode(): criando o ponteiro node %d\n",*node);

    return *node; 
}
node createNode2(rect *r){
    node *node =  malloc(sizeof(node));;
	//printf("createNode2(rect): criado com create node o node %d com rect %d\n",node,r);
    *node->r = *r;
    node->prole=0;
    return *node;
}

rect createRect(int x0,int y0,int xf, int yf){
	
	rect *rect = malloc(sizeof(rect));
	rect->x0=x0;
	rect->y0=y0;
	rect->xf=xf;
	rect->yf=yf;
	printf("createRect(int,int,int,int):");
	return *rect;
}

//AQUI TA SÓ O PROTOTIPO, FALATA A LÓGICA PESADA AQUI DE MBR E SPLIT & MERGE
//aqui ta definido só até achar um null sem tratamento se tiver todos cheios
//não deve ter todos cheios para o tratamento de split vem depois disso no insert
void addChild(node *parent,node *child){
    //printf("addchild com %d parent e %d child\n",&parent,&child);
    int i;
    for(i=0;i<=M;i++){
        if(parent->children[i]==NULL) {
            parent->children[i]=child;
            break;
        }
    }

}

/*CONSIDERAÇÕES

    NA LITERATURA ELE CONSIDERA O LEAF-NODE AQUELE QUE DETEM m-M DADOS COMO 'FILHOS' 
    AQUI POR UMA QUESTÃO DE SIMPLIFICAÇÃO PRA SABER SE UM NODE É LEAF SERÁ PESQUISADO 
    "NODE->CHILDREN[0]->CHILDREN[0]==NULL?" SE SIM QUER DIZER QUE ESTE NODE É LEAF 
    E SEU FILHO É DATA (O RECT EM SI É A INFORMAÇÃO AMAZENADA)

*/
bool isLeaf(node *node){
    if(node==NULL) return false;
    if(node->children[0]==NULL) return false;    //se isso é true quer dizer que este é data(e não leaf)


    if(node->children[0]->children[0]==NULL) return true;
    
}

void Search(rect *r,node *node){//TODO CONFERIR LOGICA
    if(node==NULL) return;
    if(isBounded(node->r,r)==false) return;
    if(isLeaf(node)){//procurar pelos children que são os datas
        int i;
        for(i=0;i<node->prole;i++){
            if(isBounded(node->children[i]->r,r)){
                printf("found this data: p0(%d,%d) - p1(%d,%d)\n",node->children[i]->r->x0,node->children[i]->r->y0,node->children[i]->r->xf,node->children[i]->r->yf);
            }
        }
    }
    else{
        int i;
        for(i=0;i<node->prole;i++){
            Search(r,node->children[i]);
        }
    }
}

void RemoveOne(node* node){
    if(node==NULL) return;
    free(node);
}

bool isBounded(rect* r1,rect* r2){
    if(r1==NULL || r2==NULL)return false;
    if(((r1->x0 <= r2->x0 && r1->xf >= r2->x0)||(r1->x0 <= r2->xf && r1->xf >= r2->xf))
    &&((r1->y0 <= r2->y0 && r1->yf >= r2->y0)||(r1->y0 <= r2->yf && r1->yf >= r2->yf))){
        return true;
    }
    return false;
}

