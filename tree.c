#include <stdio.h>
#include <stdlib.h>

#define DEBUG_PRINT 0

struct node{
  int val;
  unsigned char height;
  struct node *left, *right;
};

unsigned char height(struct node *p)
{
  return p?p->height:0;
}

int bfactor(struct node *p)
{
  return height(p->right)-height(p->left);
}

void fixheight(struct node **p)
{
  unsigned char hl = height((*p)->left);
  unsigned char hr = height((*p)->right);
  (*p)->height = (hl>hr ? hl:hr)+1;
}

void small_left_round(struct node **head)
{
  struct node *tmp;
  tmp = *head;
  *head = (*head)->right;
  tmp->right = (*head)->left;
  (*head)->left = tmp;
}

void small_right_round(struct node **head)
{
  struct node *tmp;
  tmp = *head;
  *head = (*head)->left;
  tmp->left = (*head)->right;
  (*head)->right = tmp;
}

void balance(struct node **head)
{
    if(bfactor(*head) == 2)
    {
      if(bfactor((*head)->right) < 0)
	small_right_round(&(*head)->right);
      small_left_round(&(*head));;
    }
  if(bfactor(*head) == -2)
    {
      if(bfactor((*head)->left) > 0)
	small_left_round(&(*head)->left);
      small_right_round(&(*head));
    }
}

struct node *node_create(int s_key)
{
  struct node *new_node;
  new_node = malloc(sizeof(new_node));
  new_node->val = s_key;
  new_node->height = 1;
  new_node->left = NULL;
  new_node->rigth = NULL;
  return new_node;
}

void extract(struct node **from, struct node *whither)
{
  *whither = *from;
  

void node_search(struct node **head, int s_key, struct node **extracted)
{
  if(!*head)
    {
      if(!*extracted)
	*head = node_create(s_key);
      return;
    }
  if(s_key == (*head)->val)
    {
      if(*extracted)
	extract(&(*head), &(*extracted));
      return;
    }
  if(s_key < (*head)->val)
    search_tree(&(*head)->left, s_key, &(*extracted));
  else
    search_tree(&(*head)->right, s_key, &(*extracted));
  fixheight(&(*head));
  balance(&(*head));
}

int main(int argc, char **argv)
{
  FILE *from;
  int c, buf_size, i;
  char *buf;
  struct node *head;
  from = fopen(argv[1], "r");
  if(!from)
    {
      fprintf(stderr, "File is not open!\n");
      exit(0);
    }
  buf_size = 1;
  buf = malloc(buf_size);
  i = 0;
  while((c = fgetc(from)) != EOF)
    {
      if(i == buf_size -1)
	{
	  buf_size *= 2;
	  buf = realloc(buf, buf_size);
	}
      if(c >= '0'&& c <= '9')
	{
	  buf[i] = c;
	  i++;
	}
      if(c <= ' ')
	{
	  buf[i] = 0;
	  add_tree(&head, atoi(buf));
	  free(buf);
	  buf_size = 1;
	  buf = malloc(buf_size);
	  i = 0;
	}
    }
  free(buf);
  search_tree(head, atoi(argv[2]));
  return 0;
}
