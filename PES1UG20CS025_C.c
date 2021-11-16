#include"PES1UG20CS025_H.h"

int main()
{
  int a[10][10];
  int i,j,row,col;
  rownode_t *head,*p;
  head=NULL;
  
  //read from file

  FILE * ptr = fopen("input.txt","r");
  int start_x,start_y,end_x,end_y;
  fscanf(ptr,"%d",&start_x);
  fscanf(ptr,"%d",&start_y);
  fscanf(ptr,"%d",&end_x);
  fscanf(ptr,"%d",&end_y);

  for(i=0;i<10;i++){
      for(j=0;j<10;j++){
        fscanf(ptr,"%d",&a[i][j]);
      }
  }
  fclose(ptr); 

  head=create_rows();
  insert_matrix(head,a);
  insert_consec_pointer(head);
  printf("\n Traversed path: ");
  find_way(head,start_x,start_y,end_x,end_y);
 }