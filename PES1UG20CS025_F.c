#include"PES1UG20CS025_H.h"

rownode_t* create_rows()
{
   rownode_t *p,*q;
   rownode_t *temp;
  int r =10;
   int i;
   p=NULL;
   q=NULL;
   //create r number of row nodes
   for(i=0;i<r;i++)
   {
    temp=malloc(sizeof(rownode_t));
    temp->row=i;
    temp->next_row=NULL;
    temp->next_col=NULL;

    if (p==NULL)//first row node
    {
      p=temp;
      q=temp;
     }
     else
     {
      q->next_row=temp;
      q=temp;
     }
   }
   return p;//return the address of the first row node
}

void insert_matrix(rownode_t *head, int (*a)[10])
{
  int i,j;
  int r=10,c=10;
  rownode_t *p;
  p=head;
  
  for(i=0;i<r;i++)
  {
    for(j=0;j<c;j++)
      if(a[i][j]==0)
        insert_end(p,j);
    p=p->next_row;
  }
}	 
	 
void insert_end(rownode_t * p,int col)
{
  colnode_t *temp,*pres;
  
  temp= (colnode_t*)malloc(sizeof(colnode_t));
  temp->col=col;
  temp->flag=0;
  temp->row = p->row;
  temp->next_col=NULL;
  temp->next_row=NULL;
  temp->addr = temp;
  
  if(p->next_col==NULL)//first element in that row
    p->next_col=temp;
  else
  {
    pres= p->next_col;
    //move to last node
    while(pres->next_col!=NULL)
      pres=pres->next_col;
    
    pres->next_col=temp;
  }
}


void display(rownode_t *p)    //displays the sparse matrix.. * represents next_row pointer exist for that node.
{
	colnode_t *q;
	while(p!=NULL)
	{
		printf("%d->",p->row);
		
		q=p->next_col;
		while(q!=NULL) //display columns
		{
            if(q->next_row!=NULL)
                printf("*");
		   printf("(%d, ",p->row);
	       printf("%d )->",q->col);
		   q=q->next_col;
		}
		p=p->next_row;
		printf("\n");
	}
}	

//my addition
// a next_row pointer is assigned to a node only if there exists a valid node in the corresponding column of the next consecutive row
void insert_consec_pointer(rownode_t *p) //creating a pointer for next_row wherever applicable
{
    colnode_t *up,*down,*temp;
    rownode_t *next;

    while(p->next_row!=NULL)
    {
        up = p->next_col;
        next = p->next_row;
        down = next->next_col;
     
        while(up!=NULL)
        {
            temp = down;
            while(temp!=NULL)
            {
                if(up->col == temp->col)
                    up->next_row = temp;
                temp = temp->next_col;
            }
            up = up->next_col;
        }
        p=p->next_row;
    }
}
		
//function to find the path to be traced
//can navigate to almost every possible location
void find_way(rownode_t *t,int x1,int y1,int x2,int y2)
{
  colnode_t *temp = (colnode_t*)malloc(sizeof(colnode_t));
  colnode_t stack[30];

  int top = 0;
  //to reach the row of the start point coordinate
  if(t->next_col->row == x1)
    temp = t->next_col;

  else{
    while(t->next_col->row != x1)
      { 
        t = t->next_row;
        temp = t->next_col;
      }
  }

  //to reach the exact co-ordinate of the start point
  while(temp->col != y1)
  {
    temp = temp->next_col;
  }
  
  push(stack,*temp,&top); //the first step
  int count = 0;
  while((temp->col != y2 || temp->row != x2) && count != 50)
  {
    count = count + 1;
    if((temp->next_col == NULL || temp->next_col->flag == 1 || temp->next_col->col > y2) && (temp->next_row == NULL || temp->next_row->flag == 1 || temp->next_row->row > x2))
    {
      if(temp->row == 0 && temp->col == 0)    //to make sure backtracking stops at start point
        break;
      temp->flag = 1;   //flag to indicate that the node has already been visited and it shouldn't be visited again
      top-=2;
      temp = stack[top].addr;
      push(stack,*temp,&top);
      display_path(stack,top);
      //printf("(%d,%d,%d)",temp->row,temp->col,top);
    }
    else if(temp->next_col != NULL && temp->next_col->col == (temp->col+1) && temp->next_col->col <= y2 && temp->next_col->flag != 1)
    {
      temp = temp->next_col;
      push(stack,*temp,&top);
      //printf("(%d,%d,%d)",temp->row,temp->col,top);
      display_path(stack,top);
      continue;
    }
    else if((temp->next_col == NULL || temp->next_col->col != (temp->col+1 || temp->next_col->flag != 1)) && temp->next_row != NULL && temp->next_row->row <= x2)
    {
      temp = temp->next_row;
      push(stack,*temp,&top);
      //printf("(%d,%d,%d)",temp->row,temp->col,top);
      display_path(stack,top);
      continue;
    }
  } 
  //printf("(%d,%d,%d)",temp->row,temp->col,top);
  if(temp->row == x2 && temp->col == y2)
    {
      printf("\n\n Path found! : \n");
      display_path(stack,top);
      write_to_file(stack,top);
    }
  else
    {
      printf("\n Failed to find path :(");
      FILE *ptr = fopen("out.txt","w");
      fprintf(ptr,"Could not find a path!:\n");
      fclose(ptr);
    }
}

void push(colnode_t stack[],colnode_t t,int *top)
{
  int n = (*top)++;
  stack[n] = t;
}

void display_path(colnode_t stack[],int top)
{ printf("\n");
  for(int i=0;i<top;i++)
  {
    printf("(%d,%d)->",stack[i].row,stack[i].col);
  }
}

void write_to_file(colnode_t stack[],int top)
{
  FILE *ptr = fopen("out.txt","w");
  fprintf(ptr,"PATH FOUND!:\n");
  for(int i=0;i<top;i++)
  {
    fprintf(ptr,"(%d,%d)->",stack[i].row,stack[i].col);
  }
  fclose(ptr);
}