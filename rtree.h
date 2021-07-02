#include <stdio.h>
#define M 5
#define m 3
typedef struct {
    int x0,y0,xf,yf;
} rect;
struct node;
typedef struct node{
    rect r;
    struct node *children[M+1];
    int prole;
} node;

node createNode();
node createNode2(rect r);
rect createRect(int x0,int y0,int xf, int yf);
void addChild(node *parent, node *child);
