#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int size;
typedef struct
{
    char data[100];
    struct node* left,* right;
} node;

node*newnode(char *data)
{
    node *n=malloc(sizeof(node));
    strcpy(n->data,data);
    n->left=NULL;
    n->right=NULL;
    return n;
}

node* insert(node* node, char * data)
{
    if (node == NULL)
        return newnode(data);
    if (strcasecmp(data,node->data) < 0)
        node->left = insert(node->left, data);
    else
        node->right = insert(node->right, data);
    return node;
}
int maxNumber(int x, int y)
{
    return x>y?x:y;
}
int Height(node *root)
{
    if ( root == NULL)
        return -1;
    else
        return 1 + maxNumber(Height(root->left),Height(root->right));
}
node* insidediction(node *root, char * word )
{
    while (root !=NULL)
    {

        if (strcasecmp(word,root->data)==0)
            return root;
        else if (strcasecmp(word,root->data)>0)
            root = root->right;
        else
            root = root->left;
    }
    return NULL;

}
node* suggestion (node*root,char*word)
{
    node*temp;
    while (root!=NULL)
    {
        if (strcasecmp(word,root->data)<0)
        {
            temp=root;
            root =root->left;
        }
        else
        {
            temp=root;
            root = root->right;
        }
    }
    return temp;
}
node * min (node*root)
{
    if (root==NULL)
        return NULL;
    while (root->left !=NULL)
        root=root->left;
    return root;
}

node * getsuccessor(node*root,char*data)
{
    node * current = suggestion(root,data);
    node * temp;
    if (current==NULL)
        return NULL;
    else  if (current->right!=NULL)
    {
        return min(current->right);
    }
    node *successor=NULL;
    node *pre = root;
    while (pre!=current)
        if (strcasecmp(current ->data,pre->data)<0)
        {

            successor=pre;
            pre = pre->left;


        }
        else pre=pre->right;
    return successor;

}
node *max (node *root){
     if (root==NULL)
        return NULL;
        node *temp = root->left;
  while (temp->right !=NULL)
        temp=temp->right;
    return temp;
}
node * getpredecessor(node*root,char*data){
  node * current = suggestion(root,data);
    node * temp;
      node *predecessor=NULL;
      while (root!=NULL){
    if (strcasecmp(current->data,root->data)<0){
        root=root->left;}
      else if  (strcasecmp(current->data,root->data)>0){
     predecessor = root;
     root=root->right;
      }else {
      if (root->left!=NULL){
        predecessor = max(root);
      }
      break;}
      }return root !=NULL? predecessor:NULL;
      }
void check_sentence(node*root,char*str)
{
    char*tokenize=strtok(str," ");
    char suges1 [20]="first";
    char suges2 [20]="second";
    char suges3 [20]="third";
    while (tokenize)
    {

        if (insidediction(root,tokenize))
        {
            printf("%s - correct\n",tokenize);
        }
        else
        {
            node*temp=suggestion(root,tokenize);
            node* succesor = getsuccessor(root,tokenize);
             node* predecessor = getpredecessor(root,tokenize);
            printf("%s - Incorrect , suggestions : %s - %s -%s\n",tokenize,(temp->data),(succesor->data),(predecessor->data));

        }
        tokenize=strtok(NULL," ");
    }
}
node * readfile (char *file )
{
    int i;
    char x[30];
    FILE* f= fopen(file, "r");

    fscanf(f,"%s\n",x);
    node * root= newnode(x);
    i++;

    while(!feof(f))
    {
        fscanf(f,"%s\n",x);

        insert(root, x);
        i++;

    }
   size = i;

    return root;
}
int main()
{ int z=1;

    node *root = NULL;
    char sent [100] ;
    char file []="Dictionary.txt";
    root=readfile(file);
       printf("Dictionary Loaded Successfully\n");
    printf("..............................\n");
    printf("size=%d\n",size);
printf("..............................\n");
printf("Height=%d\n",Height(root));
printf("..............................\n");
printf("Enter a sentences\n");
while (z=1){
gets(sent);
    check_sentence(root,sent);
}
    return 0;
}
