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

Node *Load_File (char *Filename, long *Size);
Node *Construct_BST (Node * list);
long *Copy_contents (Node * tree, long size);
Node *Balance_BST (long array[], long start, long end);
void tree_destroy (Node * tree);
long partition (long a[], long lb, long ub);
void quickSort (long *array, long lb, long ub);
void push_stack (Node * stack_array[], Node * tree);

void Print_BST_Preorder (FILE * ptr, Node * tree);
long Print_BST_Inorder (FILE * ptr, Node * root);

void Print_BST_Postorder (FILE * ptr, Node * root);

void Print_BST_BF (FILE * ptr, Node * tree);
int Search_List (Node * list, long key, double *N_Comp);
int Search_Tree (Node * tree, long key, double *N_Comp);
int Search_Tree_Balanced (Node * balanced_tree, long key, double *N_Comp);


int
main (int argc, char *argv[])
{
  long size;
  Node *list, *temp;

  list = Load_File (argv[2], &size);
  if (list == NULL)
    {
      return EXIT_FAILURE;
    }
  temp = list;

  long *array = Copy_contents (temp, size);
  //printf("%ld\n",array[0]);
  //  long i = 0;

  Node *tree = Construct_BST (list);
  FILE *ptr;
  ptr = fopen (argv[3], "w");

  if ((strcmp (argv[1], "e")) == 0)
    {
      Print_BST_Preorder (ptr, tree);
    }
  else if ((strcmp (argv[1], "i")) == 0)
    {
      Print_BST_Inorder (ptr, tree);
    }
  else if ((strcmp (argv[1], "o")) == 0)
    {
      Print_BST_Postorder (ptr, tree);
    }
  else if ((strcmp (argv[1], "b")) == 0)
    {
      Print_BST_BF (ptr, tree);
    }

  fclose (ptr);
  //  printf("BREADTH FIRST\n");
  //printPreorder(tree);

  // 
  quickSort (array, 0, size - 1);




  //  Node *balanced = Balance_BST(tree, NULL, find_middle(sorted_tree,NULL));

  Node *balanced = Balance_BST (array, 0, size - 1);
  free (array);

  long key;

  double N_Comp = 0;
  FILE *fptr;
  fptr = fopen (argv[4], "w");
  printf ("Number of Nodes: %ld\n", size);

  fscanf (stdin, "%ld", &key);


  while (key != -1)
    {
//printf("Key checked %ld\n",key);
      fprintf (fptr, "\nKEY = %ld\n", key);
      N_Comp = 0;
      Search_List (list, key, &N_Comp);
      fprintf (fptr, "  Number of Comparisons for Searching in LIST %lf\n",
	       N_Comp);
      N_Comp = 0;
      Search_Tree (tree, key, &N_Comp);
      fprintf (fptr,
	       "  Number of Comparisons for Searching in BINARY TREE %lf\n",
	       N_Comp);
      N_Comp = 0;
      Search_Tree_Balanced (balanced, key, &N_Comp);
      fprintf (fptr,
	       "  Number of Comparisons for Searching in BALANCED BINARY TREE %lf\n",
	       N_Comp);
      N_Comp = 0;
      fscanf (stdin, "%ld", &key);
    }
  fclose (fptr);


  tree_destroy (tree);
  tree_destroy (balanced);


  return 0;
}
