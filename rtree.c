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
    printf("init test\n");
    rect r;
    r.x0=7;
    printf("%d\n",r.y0);
    node n;
    n.r.x0=2;
    printf("print do n.r.x0: %d\n",n.r.x0);
    node n2;
    n2.r.x0=3;
    n.children[0]= &n2;
    printf("teste de alocar o node filho(n.children[0]->r.x0): %d\n",n.children[0]->r.x0);
    //printf("teste de alocar o node filho(n.children[0]->r.x0): %d\n",n2.children[0]->r.x0); segmentation fault
    addChild(&n2,&n);
    printf("teste de alocar o node filho(n.children[0]->r.x0): %d\n",n.children[0]->r.x0);
    printf("teste de alocar o node filho(n2.children[0]->r.x0): %d\n",n2.children[0]->r.x0);

    printf("print do n.r.x0: %d\n\n",n.r.x0);

    node n3 = createNode();
    printf("MEIO: criou o n3 com create node, endereco de n3 (&n3):%d\n",&n3);
    node n4 = createNode2(r);
    printf("n3.r.x0: %d\n",n3.r.x0);
    printf("n4.r.x0: %d\n",n4.r.x0);
    addChild(&n3,&n4);
	printf("adicionou o n4 como filho de n3, teste: n3.children[0]->r.x0: %d\n",n3.children[0]->r.x0);
    return 0;
}

node createNode(){
    node *node = malloc(sizeof(node));
    printf("createNode(): criando o ponteiro node %d\n",*node);

    return *node; 
}
node createNode2(rect r){
    node node =  createNode();
	printf("createNode2(rect): criado com create node o node %d com rect %d\n",node,r);
    node.r = r;
    return node;
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
