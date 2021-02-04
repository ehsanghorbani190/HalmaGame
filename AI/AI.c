
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct Position{
    int x;
    int y;
};
struct Node {
    int value;
    struct Position position;
    struct Node* left;
    struct Node* right;
};

struct Node* addChild(struct Node* parent,int val,int x,int y) {
	
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));  // NOLINT(modernize-use-auto)
    parent->left = node;
    node->value = val;
    node->position.y=y;
    node->position.x=x;
    node->left = NULL;
    node->right = NULL;

    return node;
}

struct Node*  addCase(struct Node* node,int val,int x,int y) {
    if (node == NULL)
        return NULL;
    if (node->right != NULL)
        addCase(node->right,val,x,y);
    else
    {
        struct Node* _node = (struct Node*)malloc(sizeof(struct Node));  
        node->right = _node;
        _node->value = val;
        _node->position.y=y;
        _node->position.x=x;
        _node->left = NULL;
        _node->right = NULL;
        return  _node;
    }
    
}

int getMin(struct Node* node)
{
    int min = 2147483647;
    struct Node* _node;
    _node = node;
    if (_node->value < min)
        min = _node->value;
    while (_node->right != NULL)
    {
        _node = _node->right;
        if (_node->value < min)
            min = _node->value;
   } 
    return min;
}

int getMax(struct Node* node)
{
    int min = 2147483647;
    struct Node* _node;
    _node = node;
    if (_node->value > min)
        min = _node->value;
    while (_node->right != NULL)
    {
        _node = _node->right;
        if (_node->value > min)
            min = _node->value;
    }
    return min;
}
int getDepth(struct Node* node)
{
    if (node == NULL)
        return 0;
	else
	{
        int lDepth = getDepth(node->left);
        int rDepth = getDepth(node->right);
	}
}

int untility(int x, int y,int step, int type)
{
    
    if (type == 1)
    {
        for (int i = boardSize - beadType; i < boardSize; i++)
            for (int j = boardSize - 1; j > boardSize - beadType - 1; j--)
                if (i + j > 2 * boardSize - beadType - 2)
                    if (y == i && x == j)
                    return -100+step;
        for (int i = boardSize - 2, j = boardSize - beadType; i >= boardSize - beadType, j <= boardSize - 2; i--, j++)
             if (y == i && x == j)
                return -100+step;
        return step;
    }
    if (type == 2)
    {
        for (int i = 0; i < beadType; i++)
            for (int j = beadType - 1 - i; j >= 0; j--)
                if (y == i && x == j)
                    return 100-step;

        for (int i = 1, j = beadType - 1; i<beadType, j> 0; i++, j--)
            if (y == i && x == j)
                return 100-step;
        return -step;
    }
}

void padding(char ch, int n)
{
    int i;

    for (i = 0; i < n; i++)
        putchar(ch);
}

void structure(struct Node* root, int level)
{
    int i;

    if (root == NULL) {
        padding('\t', level);
        puts("~");
    }
    else {
        structure(root->right, level);
        padding('\t', level);
        //printf("(%d,%d)\n", root->position.x,root->position.y);
        printf("%d\n", root->value);
        structure(root->left, level + 1);
    }
}
int getValue(struct Node* root)
{
	
}
void swap(int _x, int _y, int x, int y)
{
  int temp =boardBead[_y][_x];
  boardBead[_y][_x] = boardBead[y][x];
  boardBead[y][x] = temp;
}
void getNeighbor(struct Node *node,int depth,int _x , int _y);

void addNodeForBead(struct Node *node,int depth)
{
  struct Node *n= (struct Node*)malloc(sizeof(struct Node));
 

  for (int y = 0; y < boardSize; y++){
    for (int x = 0; x < boardSize; x++)
      if (isValidMove(node->position.x, node->position.y, x, y))
      {

        if (node->left == NULL)
          n=addChild(node, untility(x, y, depth, 2), x, y);
        else
          n=addCase(node->left, untility(x, y, depth, 2), x, y);
         if(n->value<=0 )
          getNeighbor(n,depth+1,node->position.x, node->position.y);
      }
  }
    
}

void getNeighbor(struct Node *node,int depth,int _x , int _y)
{
  if(depth>7)
  return;
  int x = node->position.x, y = node->position.y;
 
    swap(_x, _y, node->position.x, node->position.y);
    addNodeForBead(node,depth);
    swap(node->position.x, node->position.y,_x, _y );
  
  
}
