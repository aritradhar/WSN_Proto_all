#include<stdio.h>
#include<math.h>
void main()
{
 int q,p,r,no_of_node;
 int a,a1,a2,a3,a4,a5,a6,a7,temp;
 int prime[20000];
 int count=0,z=0,z1,z2;
 int countt=0;
 int k;
 int i,j;
 int node[3000][2],count1=0,key[3000][50][2];
 int compromised[100],compromised_keys[2000][2],common_key[2000][2],count2=0,flag2=0,compromised_node;
 int flag_broken=0;
 FILE* fp;
 fp=fopen("ls.txt","a");
 fprintf(fp,"-----------------------------------------------\n");
 fprintf(fp,"             start of program                  \n");
 fprintf(fp,"-------------------------------------------------");
 printf("enter no of nodes supported :");
 scanf("%d",&no_of_node);
 fprintf(fp,"\nnodes : %d",no_of_node);

 for(a=2;a<100;a++)
 {
  count=0;
  for(a1=1;a1<=(a/2);a1++)
  {
   if(a1!=1)
   {
    if((a%a1)==0)
    count+=1;
   }
  }
  if(count==0)
  {
   prime[z]=a;
   prime[++z]=a*a;
   z++;
  }
 }
/* for(z1=0;z1<z;z1++)
 {
  printf("%d,",prime[z1]);
 }*/

 //finding q for given n where k=(q*q)
 for(z1=0;z1<z;z1++)
 {
  z2=prime[z1];
  temp=z2*z2;
  if(no_of_node==temp)
  {
   p=prime[z1];
   break;
  }
 }
 printf("\n p=%d",p);
 printf("enter value of k(2-%d)",p-1);
 scanf("%d",&k);
 fprintf(fp,"\nk : %d",k);
 printf("\nnodes: \n");

 fprintf(fp,"\n p=%d",p);
 fprintf(fp,"\nnodes: \n");

 for(i=0;i<p;i++)
 {
  for(j=0;j<p;j++)
  {
   node[count1][0]=i;
   node[count1][1]=j;
   count1++;
   printf("N(%d,%d) ",i,j);
   fprintf(fp,"N(%d,%d) ",i,j);
  }
  printf("\n");
  fprintf(fp,"\n");
 }
 //printf("%d",count1);
 //set of keys
 fprintf(fp,"\n keys : \n");
 for(a1=0;a1<k;a1++)
 {
  for(a2=0;a2<p;a2++)
  {
   fprintf(fp,"(%d,%d)",a1,a2);
  }
  fprintf(fp,"\n");
 }
 a1=0;
 a2=0;
 a3=0;
 // calculating keys
 for(a1=0;a1<p;a1++)    //a:a1 b:a2 x:a3 key(x,ax+b mod p)
 {
  for(a2=0;a2<p;a2++)
  {
   for(a3=0;a3<k;a3++)
   {
    key[a1*p+a2][a3][0]=a3;
    key[a1*p+a2][a3][1]=((a2*a3)+a1)%p;
   }
  }
 }
 //print keys
 fprintf(fp,"\n");
 for(a1=0;a1<p;a1++)
 {
  for(a2=0;a2<p;a2++)
  {
   for(a3=0;a3<k;a3++)
   {
    printf("(%d,%d);",key[a1*p+a2][a3][0],key[a1*p+a2][a3][1]);
    fprintf(fp,"(%d,%d);",key[a1*p+a2][a3][0],key[a1*p+a2][a3][1]);
   }
   countt++;
   printf("\n");
   fprintf(fp,"\n");
  }
 }
 //compromised calculate E(s)
 printf("Enter number of compromised nodes");
 scanf("%d",&compromised_node);
 for(a4=0;a4<compromised_node;a4++)
 {
  compromised[a4]=rand()%no_of_node;
 }
 printf("\n compromised node ids : ");
 fprintf(fp,"\n compromised node ids : ");
 for(a4=0;a4<compromised_node;a4++)
 {
  printf("\n%d",compromised[a4]);
  fprintf(fp,"\n%d",compromised[a4]);
 }
 printf("\ncompromised keys::");
 fprintf(fp,"\ncompromised keys::");
 count1=0;
 for(a1=0;a1<compromised_node;a1++)
 {
  for(a2=0;a2<k;a2++)
  {
   compromised_keys[count1][0]=key[compromised[a1]][a2][0];
   compromised_keys[count1][1]=key[compromised[a1]][a2][1];
   count1+=1;
  }
 }
 printf("\n%d\n",count1);

count2=0;
 flag2=0;
 flag_broken=0;
 for(a1=0;a1<no_of_node;a1++)
 {
  for(a2=0;a2<no_of_node;a2++)
  {
   for(a3=0;a3<k;a3++)
   {
    for(a4=0;a4<k;a4++)
    {
     for(a7=0;a7<compromised_node;a7++)
     {
      if((a1!=compromised[a7]) && (a2!=compromised[a7]) && a1!=a2)
      {
       if((key[a1][a3][0]==key[a2][a4][0])&&(key[a1][a3][1]==key[a2][a4][1]))     
       {
        common_key[count2][0]=key[a1][a3][0];
        common_key[count2][1]=key[a1][a3][1];
        count2+=1;
        printf("\nno of common keys between node %d and % d is %d",a1,a2,count2);
        fprintf(fp,"\nno of common keys between node %d and % d is %d",a1,a2,count2);
       }
      }
     }

    }
   } 
   for(a5=0;a5<count2;a5++)
   {
    for(a6=0;a6<count1;a6++)
    {
     if((common_key[a5][0]==compromised_keys[a6][0])&&(common_key[a5][1]==compromised_keys[a6][1]))
     flag2+=1;
    }
   }
   if(flag2!=0)
   {
    flag_broken+=1; 
   }
   flag2=0;
   count2=0;    //check it ..... :p 
  }  
 }
 printf("\nbroken : %d\n",flag_broken);
  

 
 //fprintf(fp,"\n countt= %d\n",countt);
 fprintf(fp,"-----------------------------------------------\n");
 fprintf(fp,"             end of program                  \n");
 fprintf(fp,"-------------------------------------------------");
}
