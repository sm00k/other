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

void add_tree(struct node **head, int val)
{
  if(!*head)
    {
      *head = malloc(sizeof(**head));
      (*head)->val = val;
      (*head)->height = 1;
      (*head)->left = NULL;
      (*head)->right = NULL;
      return;
    }
  if((*head)->val == val)
    return;
  if(val < (*head)->val)
    add_tree(&(*head)->left, val);
  else
    add_tree(&(*head)->right, val);
  fixheight(&(*head));
  if(bfactor(*head) == 2)
    {
      if(bfactor((*head)->right) < 0)
	small_right_round(&(*head)->right);
      small_left_round(&(*head));
      return;
    }
  if(bfactor(*head) == -2)
    {
      if(bfactor((*head)->left) > 0)
	small_left_round(&(*head)->left);
      small_right_round(&(*head));
      return;
    }
}
  

void print_tree(struct node *head)
{
  if(!head)
    return;
  print_tree(head->left);
  printf("%d\n", head->val);
  print_tree(head->right);
}

void search_tree(struct node *head, int s_key)
{
  if(!head)
    {
      printf("%s\n", "search value is not tree");
      return;
    }
  if(head->val == s_key)
    {
      printf("%d\n", head->val);
      return;
    }
  if(s_key < head->val)
    {
      #if DEBUG_PRINT
      printf("%d\n", head->val);
      #endif
      search_tree(head->left, s_key);
    }
  if(s_key > head->val)
    {
      #if DEBUG_PRINT
      printf("%d\n", head->val);
      #endif
      search_tree(head->right, s_key);
    }
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
  #if DEBUG_PRINT
  printf("%s %d\n", "height: ", head->height);
  #endif
  return 0;
}
