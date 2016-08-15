#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define max(a,b) (a>b?a:b)
#include<math.h>

typedef struct _node
{
  long value;
// linked-list
  struct _node *next;
// tree

  struct _node *left;
  struct _node *right;


} Node;



Node *
Load_File (char *Filename, long *Size)
{
  FILE *ptr;
  *Size = 0;
  ptr = fopen (Filename, "r");
  if (ptr == NULL)
    return NULL;
  char str[13];

  Node *temp = NULL;
  Node *list = NULL;
  while (fgets (str, 12, ptr))
    {
      list = (Node *) malloc (sizeof (Node));
      list->value = atoi (str);
      list->next = temp;
      list->left = NULL;
      list->right = NULL;
      temp = list;
      *Size = *Size + 1;
    }
  fclose (ptr);

  return list;
}

Node *
Construct_BST (Node * list)
{
  Node *tree;
  tree = list;
  tree->left = NULL;
  tree->right = NULL;
  Node *list_traverse = list->next;
  while (list_traverse != NULL)
    {

      Node *child = NULL;
      Node *parent = NULL;
      child = tree;

      while (child != NULL)
	{
	  //   printf("Value encountered : %ld\n",list_traverse->value);
	  if (list_traverse->value >= child->value)
	    {			//printf("going right\n");
	      parent = child;
	      child = child->right;
	    }
	  else if (list_traverse->value < child->value)
	    {			//printf("going left\n");
	      parent = child;
	      child = child->left;
	    }
	}
      if (list_traverse->value >= parent->value)
	{
	  parent->right = list_traverse;
	}
      //     printf("Value put : %ld\n",parent->right->value);}
      else if (list_traverse->value < parent->value)
	{
	  parent->left = list_traverse;
	}
      //  printf("Value put : %ld\n",parent->left->value); }

      list_traverse = list_traverse->next;
    }
  return list;
}

long *
Copy_contents (Node * tree, long size)
{
  long *array = malloc (sizeof (long) * ((size + 1)));
  int i = 0;
  while (tree != NULL)
    {
      array[i] = tree->value;
      i++;
      //printf("array[i] %ld\n",array[i]);
      tree = tree->next;
    }
  return array;
}



Node *
Balance_BST (long array[], long start, long end)
{



  if (start > end)
    return NULL;


  long mid = (start + end) / 2;
  Node *root = (Node *) malloc (sizeof (Node));
  root->value = array[mid];
  root->next = NULL;

  root->left = Balance_BST (array, start, mid - 1);

  root->right = Balance_BST (array, mid + 1, end);

  return root;

}



void
tree_destroy (Node * tree)
{
  if (tree)
    {

      // tree_destroy(tree->left);
      tree_destroy (tree->left);
      tree_destroy (tree->right);
      //tree_destroy(tree->right_balance);
      free (tree);
    }
}

long
partition (long a[], long lb, long ub)
{
  long pivot;
  pivot = a[lb];
  long down = lb;
  long up = ub;

  while (down < up)
    {
      while (a[down] <= pivot && down < ub)
	{
	  down++;
	}
      while (a[up] > pivot)
	{
	  up--;
	}
      if (down < up)
	{
	  long temp = a[down];
	  a[down] = a[up];
	  a[up] = temp;
	}
    }
  a[lb] = a[up];
  a[up] = pivot;
  return up;

}

void
quickSort (long *array, long lb, long ub)
{
  long part_idx;

  if (lb >= ub)
    {
      return;
    }

  part_idx = partition (array, lb, ub);
  quickSort (array, lb, part_idx - 1);
  quickSort (array, part_idx + 1, ub);

}

void
push_stack (Node * stack_array[], Node * tree)
{
  long i = 0;
  while (stack_array[i] != NULL)
    {
      i++;
    }

  stack_array[i] = malloc (sizeof (Node));
  stack_array[i] = tree;

}


Node *
pop_stack (Node ** stack_array)
{
  if (stack_array != NULL)
    {
      int i = 0;
      Node *temp = stack_array[i];
      int j = i + 1;
      while (stack_array[j] != NULL)
	{
	  stack_array[j - 1] = stack_array[j];
	  j++;
	}
      return temp;
    }
  else
    return NULL;
}


typedef struct _sNode
{
  Node *t;
  struct _sNode *next;
} Stack;


void
push (Stack ** top, Node * t)
{
  if (t == NULL)
    {
      return;
    }
  Stack *new = (Stack *) malloc (sizeof (Stack));

  new->next = (*top);
  new->t = t;

  (*top) = new;
}



int
isEmpty (Stack * top)
{
  return (top == NULL) ? 1 : 0;
}


Node *
pop (Stack ** top_ref)
{
  Node *res;
  Stack *top;


  if (isEmpty (*top_ref))
    {
      return NULL;
    }
  else
    {
      top = *top_ref;
      res = top->t;
      *top_ref = top->next;
      free (top);
      return res;
    }
}

long
Print_BST_Preorder (FILE * ptr, Node * tree)
{

  long depth = 0;
  long max_depth = 0;
  if (tree == NULL)
    return 0;

  Stack *stack = NULL;
  push (&stack, tree);

  while (stack != NULL)
    {
      Node *temp = pop (&stack);
      depth--;
      fprintf (ptr, "%ld\n", temp->value);
      if (temp != NULL)
	{
	  // if (temp->right){
	  push (&stack, temp->right);	//}
	  depth++;
	  // if (temp->left){
	  push (&stack, temp->left);	//}
	  depth++;
	}
      if (depth > max_depth)
	max_depth = depth;
    }

  return max_depth;
}

long
Print_BST_Inorder (FILE * ptr, Node * root)
{

  Node *current = root;
  long max_depth = 0;
  long depth = 0;
  Stack *s = NULL;		

  do
    {
      while (current != NULL)
	{
	  push (&s, current);
	  depth++;
	  current = current->left;
	}


      if (s != NULL)
	{
	  current = pop (&s);
	  depth--;
	  fprintf (ptr, "%ld\n", current->value);

	  current = current->right;
	}

      if (depth > max_depth)
	max_depth = depth;

    }
  while (!isEmpty (s) || current != NULL);


  return 0;
}

Node *
top (Stack ** stack)
{
  if (*stack != NULL)
    {
      Stack *front = *stack;

      return front->t;
    }
  else
    return NULL;
}

long
Print_BST_Postorder (FILE * ptr, Node * root)
{
  if (!root)
    return 0;

  long depth = 0;
  Stack *stack = NULL;
  Stack *output = NULL;		//using two stacks for post order traversal
  push (&stack, root);
  while (stack != NULL)
    {

      Node *current = pop (&stack);

      push (&output, current);

      if (current->left)
	push (&stack, current->left);
      if (current->right)
	push (&stack, current->right);
    }
  Node *temp = pop (&output);
  while (temp != NULL)
    {
      depth++;
      fprintf (ptr, "%ld\n", temp->value);
      temp = pop (&output);

    }
  return depth;
  // printf("%ld\n",temp->value);
}

void
push_queue (Stack ** front, Stack ** end, Node * t)
{
  Stack *temp = *front;
  if (temp == NULL)
    {
      Stack *new = (Stack *) malloc (sizeof (Stack));
      new->next = NULL;
      new->t = t;
      *front = new;
      *end = new;
      return;
    }
  else
    {
      temp = *end;
//  while(temp->next != NULL)
      //     temp = temp->next;

      Stack *new = (Stack *) malloc (sizeof (Stack));
      new->next = NULL;
      new->t = t;
      temp->next = new;
      *end = new;
    }
}

long
Print_BST_BF (FILE * ptr, Node * tree)
{
  long depth = 0;
  Stack *q = NULL;
  Stack *e = NULL;
  push_queue (&q, &e, tree);
  while (q != NULL)
    {
      Node *temp = pop (&q);
      depth--;
      fprintf (ptr, "%ld\n", temp->value);

      if (temp->right)
	{
	  depth++;
	  push_queue (&q, &e, temp->right);
	}
      if (temp->left)
	{
	  depth++;
	  push_queue (&q, &e, temp->left);
	}

    }
  return depth;
}


int
Search_List (Node * list, long key, double *N_Comp)
{

  int found = 0;
  while (list != NULL)
    {
      if (key == list->value)
	{
	  fprintf (stdout, "found \n");
	  found = 1;
	  return 1;
	}
      else
	{			//fprintf(stdout,"List values checked %ld\n",list->value);
	  *N_Comp = *N_Comp + 1;
	  list = list->next;
	}

    }
  if (found == 0)
    {
      fprintf (stdout, "not found \n");
      return 0;
    }
  return 0;
}


int
Search_Tree (Node * tree, long key, double *N_Comp)
{

  if (tree == NULL)
    {				/*fprintf(stdout,"not found ST\n"); */
      return 0;
    }

  if (tree->value < key)
    {
      *N_Comp = *N_Comp + 1;
      Search_Tree (tree->right, key, N_Comp);
    }

  else if (tree->value > key)
    {
      *N_Comp = *N_Comp + 1;
      Search_Tree (tree->left, key, N_Comp);
    }

  else if (tree->value == key)
    {
      *N_Comp = *N_Comp + 1;
      /*fprintf(stdout,"found ST\n"); */ return 1;
    }


  return 0;
}


int
Search_Tree_Balanced (Node * balanced_tree, long key, double *N_Comp)
{

  if (balanced_tree == NULL)
    {				/*fprintf(stdout,"not found BT\n"); */
      return 0;
    }

  if (balanced_tree->value == key)
    {
      /*fprintf(stdout,"found BT\n"); */ return 1;
    }

  else if (balanced_tree->value < key)
    {
      *N_Comp = *N_Comp + 1;
      Search_Tree_Balanced (balanced_tree->right, key, N_Comp);
    }

  else if (balanced_tree->value > key)
    {
      *N_Comp = *N_Comp + 1;
      Search_Tree_Balanced (balanced_tree->left, key, N_Comp);
    }



  return 0;
}
