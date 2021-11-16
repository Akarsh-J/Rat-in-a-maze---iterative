#include<stdio.h>
#include<stdlib.h>
struct col_node {
	int col;
  int row;
  int flag;
  struct col_node *next_row;
	struct col_node *next_col;
  struct col_node *addr;
};

struct row_node {
	int row;
	struct col_node *next_col;
	struct row_node *next_row;
};

typedef struct row_node rownode_t;
typedef struct col_node colnode_t;

rownode_t *create_rows();
void insert_end(rownode_t*,int);
void insert_matrix(rownode_t*, int(*)[]);
void display(rownode_t*);
void insert_consec_pointer(rownode_t *);
void find_way(rownode_t *t,int x1,int y1,int x2,int y2);
colnode_t pop(colnode_t t[],int *top);
void push(colnode_t stack[],colnode_t t,int *top);
colnode_t pop(colnode_t stack[],int *top);
void display_path(colnode_t stack[],int top);
void write_to_file(colnode_t stack[],int top);