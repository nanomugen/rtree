#include <stdio.h>
#define M 5
#define m 3
#define bool int
#define true 1
#define false 0
typedef struct {
    int x0,y0,xf,yf;
} rect;
struct node;
typedef struct node{
    rect *r;
    struct node *children[M+1];
    struct node *father;
    int prole;
} node;

node createNode();
node createNode2(rect *r);
rect createRect(int x0,int y0,int xf, int yf);
void addChild(node *parent, node *child);
bool isLeaf(node *node);
void Search(rect* r,node* node);//melhor só encontrar e dar print no lugar de fazer um array
void RemoveOne(node* node);
void ClearAll(node* node);
bool isBounded(rect* r1,rect* r2);
