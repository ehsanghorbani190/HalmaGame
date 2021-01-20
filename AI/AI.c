// ReSharper disable CppClangTidyModernizeUseAuto
// ReSharper disable CppUseAuto
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
        printf("%d,%d\n", root->position.x,root->position.y);
        structure(root->left, level + 1);
    }
}
int getValue(struct Node* root)
{
	
}
// int main() {
//     srand(time(NULL));
//     int min,max;
// 	struct Node *fnode= (struct Node*)malloc(sizeof(struct Node));
//     struct Node* temp;
//     fnode->value = 0;
//     fnode->right = NULL;
//     fnode->left = NULL;
//     addChild(fnode);
//     addCase(fnode->left);
//     addCase(fnode->left);
//     addCase(fnode->left);
  
	
//     //min=getMin(fnode->left);
//     //max = getMax(fnode->left);
//     //structure(fnode, 0);
//     return 0;
// }
