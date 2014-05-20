#include<stdio.h>
#include<math.h>

int arr_node[30000];    //random nodes array
int q,p,r,no_of_node;
int a,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,temp;
int prime[20000];
int count=0,zp=0,z1,z2;
int countt=0;
int k;
int i,j;
int node[30000][2],count1=0,key_set[6000][70][2],irr_poly[3],add_poly[3],mul_poly[3],vector[200][2];
int merge_node,z,merge_set[6000][10];
int merge_key_set[6000][300][2],nodes_left;
int flag1=0;
int max_unique;
int node_id1,node_id2;

void vectorize(int p)
{
    int pt=sqrt(p),i;
    for(i=0; i<pt; i++)                //vector ax+b0
    {
        for(j=0; j<pt; j++)
        {
            vector[i*pt+j][0]=j;      //b
            vector[i*pt+j][1]=i;      //a
        }
    }
}

int get_x_bar(int x,int p)
{
    int i,pt=sqrt(p);
    int x_bar;
    for(i=0; i<pt; i++)
    {
        if((x+i)%pt==0)
        {
            x_bar=i;
            break;
        }
    }
    return x_bar;
}

void addpoly(int *polya,int *polyb)
{
    int i;
    for(i=2; i>=0; i--)
    {
        *(add_poly+i)=*(polya+i)+*(polyb+j);
    }
}

void mulpoly(int *polya,int *polyb)
{
    int i;
    for(i=2; i>=0; i--)
    {
        for(j=2; j>=0; j--)
        {
            *(mul_poly+(i+j))=*(mul_poly+(i+j))+(*(polya+i))*(*(polyb+j));
        }
    }
}
int isprime(int x)
{
    int a,a1,count;
    count=0;
    for(a1=1; a1<=(x/2); a1++)
    {
        if(a1!=1)
        {
            if((x%a1)==0)
                count+=1;
        }
    }
    if(count==0)
    {
        return 1;
    }
    else
        return 0;
}

void random(int n)
{
    int x,y,j,f;
    for(x=0; x<n; x++)
    {
        y=(abs(x*x+x+1))%n;
        if(x==0)
            arr_node[0]=y;
        else
        {
            while(1)
            {
                f=0;
                for(j=0; j<x; j++)
                {
                    if(arr_node[j]==y)
                        f=1;
                }
                if(f==0)
                {
                    arr_node[x]=y;
                    break;
                }
                else
                {
                    y=(y+1)%n;
                }
            }
        }
    }
}
void main()
{
    FILE* fp;
    fp=fopen("ls_mb.txt","a");
    fprintf(fp,"-----------------------------------------------\n");
    fprintf(fp,"             start of program                  \n");
    fprintf(fp,"-------------------------------------------------");
    printf("Enter no of merged nodes:");
    scanf("%d",&merge_node);
    fprintf(fp,"\nmerged nodes : %d",merge_node);
    printf("\nenter value of z(designed for z=2)");
    scanf("%d",&z);
    no_of_node=merge_node*z;
    printf("\nTotal nodes in the network: %d",no_of_node);
    fprintf(fp,"\nTotal nodes in the network: %d",no_of_node);
    for(a=2; a<100; a++)
    {
        count=0;
        for(a1=1; a1<=(a/2); a1++)
        {
            if(a1!=1)
            {
                if((a%a1)==0)
                    count+=1;
            }
        }
        if(count==0)
        {
            prime[zp]=a;
            prime[++zp]=a*a;
            zp++;
        }
    }
    temp=0;
    for (i=0; i<zp-1; i++)
    {
        for (j=0; j<zp-1-i; j++)
        {
            if (prime[j]>prime[j+1])
            {
                temp=prime[j];
                prime[j]=prime[j+1];
                prime[j+1]=temp;
            }
        }
    }
    temp=0;

//finding q for given n where k=(q*q)
    for(z1=0; z1<zp; z1++)
    {
        z2=prime[z1];
        temp=z2*z2;
        if(no_of_node<=temp)
        {
            p=prime[z1];
            break;
        }
    }
    for(z1=0; z1<zp; z1++)
    {
        z2=prime[z1];
        temp=z2*z2;
        if(merge_node<=temp)
        {
            r=prime[z1];
            break;
        }
    }
    int pt;
    if(isprime(p)==1)
        pt=p;
    if(isprime(p)==0)
        pt=sqrt(p);
    int r1=r*r;
    float r1c2=r1*(r1-1)*0.5;
    fprintf(fp,"\nqt : %d\n",pt);
    printf("\n p=%d",p);
    printf("\n r=%d",r);
    printf("\nenter value of k(2-%d) (keys per node)",p-1);
    scanf("%d",&k);
    fprintf(fp,"\nk : %d",k);
    fprintf(fp,"\nr : %d",r);
    int x=r+1;
    float px=(float) k/x;
    printf("\npx: %f",px);
    fprintf(fp,"\npx: %f",px);
    printf("\nnodes: \n");
    fprintf(fp,"\n p=%d",p);
    fprintf(fp,"\nnodes: \n");

    for(i=0; i<p; i++)
    {
        for(j=0; j<p; j++)
        {
            node[count1][0]=i;
            node[count1][1]=j;
            count1++;
            printf("N(%d,%d) ",i,j);
            fprintf(fp,"N(%d,%d) ",i,j);
        }
        printf(";;\n");
        fprintf(fp,"\n");
    }
//printf("%d",count1);
//set of keys
    fprintf(fp,"\n keys : \n");
    for(a1=0; a1<k; a1++)
    {
        for(a2=0; a2<p; a2++)
        {
            fprintf(fp,"(%d,%d)",a1,a2);
        }
        fprintf(fp,"\n");
    }
    a1=0;
    a2=0;
    a3=0;
// calculating keys
    if(isprime(p)==1)
    {
        for(a1=0; a1<p; a1++)  //a:a1 b:a2 x:a3 key(x,ax+b mod p)
        {
            for(a2=0; a2<p; a2++)
            {
                for(a3=0; a3<k; a3++)
                {
                    key_set[a1*p+a2][a3][0]=a3;
                    key_set[a1*p+a2][a3][1]=((a1*a3)+a2)%p;
                }
            }
        }
    }
    if(isprime(p)==0)
    {
        vectorize(p);
        printf("\nEnter the irreducable ")
        for(a1=0; a1<p; a1++)  //a:a1 b:a2 x:a3 key(x,ax+b mod p)
        {
            for(a2=0; a2<p; a2++)
            {
                for(a3=0; a3<k; a3++)
                {

                }
            }
        }
    }
//print keys
    fprintf(fp,"\n");
    for(a1=0; a1<p; a1++)
    {
        for(a2=0; a2<p; a2++)
        {
            for(a3=0; a3<k; a3++)
            {
                printf("(%d,%d);",key_set[a1*p+a2][a3][0],key_set[a1*p+a2][a3][1]);
                fprintf(fp,"(%d,%d);",key_set[a1*p+a2][a3][0],key_set[a1*p+a2][a3][1]);
            }
            countt++;
            printf("\n");
            fprintf(fp,"\n");
        }
    }
    fprintf(fp,"\n countt= %d\n",countt);

//merging block
    printf("\nno of merged blocks : %d",merge_node);
    fprintf(fp,"\nno of merged blocks : %d",merge_node);
    printf("\nno of nodes left after merging : %d",nodes_left);
    fprintf(fp,"\nno of nodes left after merging : %d",nodes_left);

    random(no_of_node);
    fprintf(fp,"\nRandom nodes");
    for(a1=0; a1<no_of_node; a1++)
    {
        printf("\n%d",arr_node[a1]);
        fprintf(fp,"\n%d",arr_node[a1]);
    }
    printf("\n");
    fprintf(fp,"\n");
    for(a1=0; a1<merge_node; a1++)
    {
        for(a2=0; a2<z; a2++)
        {
            merge_set[a1][a2]=arr_node[a1*z+a2];
        }
    }

    printf("New merged node:\n");
    fprintf(fp,"New merged node:\n");
    for(a1=0; a1<merge_node; a1++)
    {
        for(a2=0; a2<z; a2++)
        {
            printf("%d,",merge_set[a1][a2]);
            fprintf(fp,"%d,",merge_set[a1][a2]);
        }
        printf("\n");
        fprintf(fp,"\n");
    }
    max_unique=k*z;
    printf("Maximum no of unique keys in one merged block : %d\n",max_unique);
    fprintf(fp,"Maximum no of unique keys in one merged block : %d\n",max_unique);
    printf("Keys in the merged nodes:\n");
    fprintf(fp,"Keys in the merged nodes:\n");

    /*for(a1=0; a1<merge_node; a1++)
     {
         for(a2=0; a2<z; a2++)
         {
             for(a3=0; a3<k; a3++)
             {
                 merge_key_set[a1][a2*k+a3][0]=key_set[merge_set[a1][a2]][a3][0];
                 merge_key_set[a1][a2*k+a3][1]=key_set[merge_set[a1][a2]][a3][1];
             }
         }
     }

     for(a1=0; a1<merge_node; a1++)
     {
         for(a2=0; a2<z; a2++)
         {
             for(a3=0; a3<k; a3++)
             {
                 printf("(%d,%d);",merge_key_set[a1][a2*k+a3][0],merge_key_set[a1][a2*k+a3][1]);
                 fprintf(fp,"(%d,%d);",merge_key_set[a1][a2*k+a3][0],merge_key_set[a1][a2*k+a3][1]);
             }
         }
         printf(";\n");
         fprintf(fp,"\n");
     }*/
    int node_status[50000],merge_block[50000][2];
    printf("Merging..");
    int a0=0;
    for(a1=0; a1<no_of_node; a1++)  //setting status not merged
    {
        node_status[a1]=1;
    }
    for(a1=0; a1<no_of_node; a1++)
    {
        printf("Node%d :: Status:%d\n",a1,node_status[a1]);
        fprintf(fp,"Node%d :: Status:%d\n",a1,node_status[a1]);
    }

    int flag_n1=0,flag_n2=0,flag_n3=0;
    for(a1=0; a1<merge_node; a1++)
    {
        //1st
        for(a2=0; a2<no_of_node; a2++)
        {
            if(node_status[a2]==0)
                continue;
            node_status[a2]=0;
            break;
        }
        merge_block[a0][0]=a2;
        for(a6=0; a6<k; a6++)
        {
            merge_key_set[a0][a6][0]=key_set[a2][a6][0];
            merge_key_set[a0][a6][1]=key_set[a2][a6][1];
        }
        //2nd
        for(a3=0; a3<no_of_node; a3++)
        {
            if(a3==a2 || node_status[a3]==0)
                continue;
            for(a4=0; a4<k; a4++)
            {
                for(a5=0; a5<k; a5++)
                {
                    if(merge_key_set[a0][a4][0]==key_set[a3][a5][0] && merge_key_set[a0][a4][1]==key_set[a3][a5][1])
                    {
                        node_status[a3]=0;
                        flag_n1=1;
                        break;

                    }
                    if(flag_n1==1)
                        break;
                }
                if(flag_n1==1)
                    break;
            }
            if(flag_n1==1)
                break;
        }
        flag_n1=0;
        if(node_status[a3]==0 && a3<no_of_node)
        {
            for(a7=a6; a7<2*k; a7++)
            {
                merge_key_set[a0][a7][0]=key_set[a3][a7-a6][0];
                merge_key_set[a0][a7][1]=key_set[a3][a7-a6][1];
            }
            merge_block[a1][1]=a3;
            a0++;
        }
        else
        {
            node_status[a0]=1;
        }
    }
    int count_perticipate=0;      //count perticipating nodes in the merging
    for(a1=0; a1<no_of_node; a1++)
    {
        if(node_status[a1]==0)
            count_perticipate++;
    }
    int left_over=no_of_node-count_perticipate;
    int left_over_node_list[2000];               //contains all the node idss of the left over nodes

    //process the left over nodes
    a9=0;
    for(a8=0; a8<no_of_node; a8++)
    {
        if(node_status[a8]==1)
        {
            left_over_node_list[a9]=a8;
            //fprintf(fp,"\nleft over %d",left_over_node_list[a9]);
            a9++;
        }
    }

    for(a9=0; a9<left_over; a9+=2)
    {
        a0++;
        merge_block[a0][0]=left_over_node_list[a9];
        merge_block[a0][1]=left_over_node_list[a9+1];
    }

    for(a9=0; a9<left_over; a9+=2)
    {
        for(a10=0; a10<k; a10++)
        {
            a0++;
            merge_key_set[a0][a10][0]=key_set[a9][a10][0];
            merge_key_set[a0][a10][1]=key_set[a9][a10][1];
            node_status[left_over_node_list[a9]]=0;
            merge_key_set[a0][k+a10][0]=key_set[a9+1][a10][0];
            merge_key_set[a0][k+a10][1]=key_set[a9+1][a10][1];
            node_status[left_over_node_list[a9+1]]=0;
        }
    }


    printf("\nEnter any two merged node id to check direct communication(0-%d):",merge_node-1);
    scanf("%d%d",&node_id1,&node_id2);
    fprintf(fp,"\nAttempt to check communication between nodes %d and %d\n",node_id1,node_id2);
    for(a2=0; a2<max_unique; a2++)
    {
        for(a3=0; a3<max_unique; a3++)
        {
            if((merge_key_set[node_id1][a2][0]==merge_key_set[node_id2][a3][0])&&(merge_key_set[node_id1][a2][1]==merge_key_set[node_id2][a3][1]))
                flag1++;
        }
    }
    if(flag1!=0)
    {
        printf("\nDirect communication possible\n");
        fprintf(fp,"\nDirect communication possible\n");
    }
    if(flag1==0)
    {
        printf("\nDirect communication not possible\n");
        fprintf(fp,"\nDirect communication not possible\n");
    }
    // calculate E(s) and V(s)
    int compromised_node,a4,compromised[500];
    printf("Enter number of compromised nodes");
    scanf("%d",&compromised_node);
    for(a4=0; a4<compromised_node; a4++)
    {
        compromised[a4]=rand()%merge_node;
    }
    printf("\n compromised node ids : ");
    fprintf(fp,"\n compromised node ids : ");
    for(a4=0; a4<compromised_node; a4++)
    {
        printf("\n%d",compromised[a4]);
        fprintf(fp,"\n%d",compromised[a4]);
    }
    printf("\ncompromised keys::");
    fprintf(fp,"\ncompromised keys::");
    int compromised_keys[10000][2];
    for(a1=0; a1<compromised_node; a1++)
    {
        for(a2=0; a2<max_unique; a2++)
        {
            compromised_keys[count1][0]=merge_key_set[compromised[a1]][a2][0];
            compromised_keys[count1][1]=merge_key_set[compromised[a1]][a2][1];
            count1+=1;
        }
    }
    printf("\n%d\n",count1);
    int count2=0,node_list[10000];
    int flag2=0;
    int flag_broken=0;
    int common_key[50000][2];
    //checking links
    for(a1=0; a1<no_of_node; a1++)
    {

        for(a2=0; a2<compromised_node; a2++)
        {
            if(a1==compromised[a2])
            {
                node_list[a1]=0;
                break;
            }
            else
                node_list[a1]=a1;
        }            //disable compromised nodes
    }
    for(a1=0; a1<no_of_node; a1++)
        fprintf(fp,"\n%d",node_list[a1]);
    for(a1=0; a1<merge_node; a1++)
    {
        if(node_list[a1]==0)
        {
            continue;
        }
        for(a2=0; a2<merge_node; a2++)
        {
            if(node_list[a2]==0)
                continue;
            if(a1==a2)
            {
                continue;
            }

            count2=0;
            for(a3=0; a3<max_unique; a3++)
            {
                for(a4=0; a4<max_unique; a4++)
                {
                    if(merge_key_set[a1][a3][0]==merge_key_set[a2][a4][0] && merge_key_set[a1][a3][1]==merge_key_set[a2][a4][1])
                    {
                        common_key[count2][0]=merge_key_set[a1][a3][0];
                        common_key[count2][1]=merge_key_set[a1][a3][1];
                        fprintf(fp,"(%d,%d);",common_key[count2][0],common_key[count2][1]);
                        count2++;
                        //printf("\nno of common keys between node %d and %d is %d",a1,a2,count2);
                        //fprintf(fp,"\nno of common keys between node %d and %d is %d",a1,a2,count2);
                    }
                }
            }
            if(a1!=a2)
            {
                printf("\nno of common keys between node %d and %d is %d",a1,a2,count2);
                //fprintf(fp,"\nno of common keys between node %d and %d is %d",a1,a2,count2);
            }

            for(a5=0; a5<count2; a5++)
            {
                for(a6=0; a6<count1; a6++)
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
            count2=0;
        }
        for(a5=0; a5<count2; a5++)
        {
            common_key[a5][0]=9999;
            common_key[a5][1]=9999;
        }
    }
    flag_broken=flag_broken/6;                                                              //eliminate 2 way communication
    printf("\nbroken links: %d\n",flag_broken);
    fprintf(fp,"\nbroken links: %d\n",flag_broken);
    float total_links;
    total_links=r1c2*px;
    printf("\nTotal links : %.0f",total_links);
    fprintf(fp,"\nTotal links : %0.f,",total_links);
    float es;
    es=(float) flag_broken/total_links;
    printf("\nE(s)=%f",es);
    fprintf(fp,"\nE(s)=%f",es);
    fprintf(fp,"-----------------------------------------------\n");
    fprintf(fp,"             end of program                  \n");
    fprintf(fp,"-------------------------------------------------");
}
