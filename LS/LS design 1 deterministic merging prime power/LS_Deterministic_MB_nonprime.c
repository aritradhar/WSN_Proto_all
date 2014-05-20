#include<stdio.h>
#include<math.h>

int arr_node[30000];    //random nodes array
int q,p,pt,r,no_of_node;
int a,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,temp;
int prime[20000];
int count=0,zp=0,z1,z2;
int countt=0;
int k;
int i,j;
int node[30000][2],count1=0,key_set[6000][70][2],irr_poly[3],add_poly[3],mul_poly[3],vector[200][2],poly_a[3],poly_b[3],poly_x[3];
int merge_node,z,merge_set[6000][10],merge_k=0;
int merge_key_set[6000][300][2],nodes_left;
int flag1=0;
//int max_unique;
int node_id1,node_id2;

void merge_blocksnp()
{
    //printf("%d",p);
    /*for(a12=0; a12<6000; a12++)
    {
        for(a13=0; a13<300; a13++)
        {
            merge_key_set[a12][a13][0]=0;
            merge_key_set[a12][a13][1]=0;
        }
    }*/
    merge_k=0;
    for(a4=0; a4<p-4; a4=a4+2)                                                      //merging apart from last 3 rows
    {
        for(a5=0; a5<p; a5++)
        {
            if((a5%pt)!=0)
            {
                for(a6=0; a6<k; a6++)
                {
                    merge_key_set[merge_k][a6][0]=key_set[a4*p+a5][a6][0];
                    merge_key_set[merge_k][a6][1]=key_set[a4*p+a5][a6][1];

                    merge_key_set[merge_k][a6+k][0]=key_set[(a4+1)*p+(a5-1)][a6][0];
                    merge_key_set[merge_k][a6+k][1]=key_set[(a4+1)*p+(a5-1)][a6][1];
                    //printf("(%d,%d)(%d,%d)",merge_key_set[merge_k][a6][0],merge_key_set[merge_k][a6][1],merge_key_set[merge_k][a6+k][0],merge_key_set[merge_k][a6+k][1],merge_k);
                }
                merge_k++;
                printf("\n<(%d,%d)  (%d,%d)>",a4,a5,a4+1,a5-1);
            }
            if((a5%pt)==0)
            {
                for(a7=0; a7<k; a7++)
                {
                    merge_key_set[merge_k][a7][0]=key_set[a4*p+a5][a7][0];
                    merge_key_set[merge_k][a7][1]=key_set[a4*p+a5][a7][1];

                    merge_key_set[merge_k][a7+k][0]=key_set[(a4+1)*p+(a5+(pt-1))][a7][0];
                    merge_key_set[merge_k][a7+k][1]=key_set[(a4+1)*p+(a5+(pt-1))][a7][1];
                    //printf("(%d,%d)(%d,%d)",merge_key_set[merge_k][a6][0],merge_key_set[merge_k][a6][1],merge_key_set[merge_k][a6+k][0],merge_key_set[merge_k][a6+k][1]);
                }
                merge_k++;
                printf("\n<(%d,%d)  (%d,%d)>",a4,a5,a4+1,a5+(pt-1));
            }
        }
    }
    //printf("%d",merge_k);
    for(a8=0; a8<p-4; a8=a8+2)                               //handling last 3 rows without last 3X3   0 to p-4
    {
        for(a9=0; a9<k; a9++)
        {
            merge_key_set[merge_k][a9][0]=key_set[(p-3)*p+a8][a9][0];
            merge_key_set[merge_k][a9][1]=key_set[(p-3)*p+a8][a9][1];

            merge_key_set[merge_k][a9+k][0]=key_set[(p-1)*p+(a8+1)][a9][0];
            merge_key_set[merge_k][a9+k][1]=key_set[(p-1)*p+(a8+1)][a9][1];
            //printf("(%d,%d)(%d,%d)",key_set[(p-3)*p+a8][a9][0],key_set[(p-3)*p+a8][a9][1],key_set[(p-1)*p+(a8+1)][a9][0],key_set[(p-1)*p+(a8+1)][a9][1]);
        }
        //printf("\n");
        merge_k++;

        //printf("M(%d)::",merge_k);
        for(a10=0; a10<k; a10++)
        {
            merge_key_set[merge_k][a10][0]=key_set[(p-2)*p+a8][a10][0];
            merge_key_set[merge_k][a10][1]=key_set[(p-2)*p+a8][a10][1];

            merge_key_set[merge_k][a10+k][0]=key_set[(p-3)*p+(a8+1)][a10][0];
            merge_key_set[merge_k][a10+k][1]=key_set[(p-3)*p+(a8+1)][a10][1];
            //printf("(%d,%d)(%d,%d)",key_set[(p-3)*p+(a8+1)][a10][0],key_set[(p-3)*p+(a8+1)][a10][1],key_set[(p-2)*p+a8][a10][0],key_set[(p-2)*p+a8][a10][1]);
            //printf("(%d)(%d,%d)(%d,%d)",merge_key_set[merge_k][a10][0],merge_key_set[merge_k][a10][1],merge_key_set[merge_k][a10+k][0],merge_key_set[merge_k][a10+k][1]);
        }
        merge_k++;

        //printf("\nM(%d)::",merge_k);
        for(a11=0; a11<k; a11++)
        {
            merge_key_set[merge_k][a11][0]=key_set[(p-2)*p+(a8+1)][a11][0];
            merge_key_set[merge_k][a11][1]=key_set[(p-2)*p+(a8+1)][a11][1];

            merge_key_set[merge_k][a11+k][0]=key_set[(p-1)*p+a8][a11][0];
            merge_key_set[merge_k][a11+k][1]=key_set[(p-1)*p+a8][a11][1];
            //printf("(%d,%d)(%d,%d)",merge_key_set[merge_k][a11][0],merge_key_set[merge_k][a11][1],merge_key_set[merge_k][a11+k][0],merge_key_set[merge_k][a11+k][1]);
        }
        merge_k++;
        //printf("%d,",merge_k);
        printf("\n<(%d,%d)  (%d,%d)>",p-3,a8,p-1,a8+1);
        printf("\n<(%d,%d)  (%d,%d)>",p-3,a8+1,p-2,a8);
        printf("\n<(%d,%d)  (%d,%d)>",p-2,a8+1,p-1,a8);

    }
    //merging last 3X3
    for(a9=0; a9<k; a9++)
    {
        merge_key_set[merge_k][a9][0]=key_set[(p-3)*p+(p-3)][a9][0];
        merge_key_set[merge_k][a9][1]=key_set[(p-3)*p+(p-3)][a9][1];

        merge_key_set[merge_k][a9+k][0]=key_set[(p-1)*p+(p-2)][a9][0];
        merge_key_set[merge_k][a9+k][1]=key_set[(p-1)*p+(p-2)][a9][1];
    }
    merge_k++;

    for(a9=0; a9<k; a9++)
    {
        merge_key_set[merge_k][a9][0]=key_set[(p-3)*p+(p-2)][a9][0];
        merge_key_set[merge_k][a9][1]=key_set[(p-3)*p+(p-2)][a9][1];

        merge_key_set[merge_k][a9+k][0]=key_set[(p-2)*p+(p-3)][a9][0];
        merge_key_set[merge_k][a9+k][1]=key_set[(p-2)*p+(p-3)][a9][1];
    }
    merge_k++;

    for(a9=0; a9<k; a9++)
    {
        merge_key_set[merge_k][a9][0]=key_set[(p-3)*p+(p-1)][a9][0];
        merge_key_set[merge_k][a9][1]=key_set[(p-3)*p+(p-1)][a9][1];

        merge_key_set[merge_k][a9+k][0]=key_set[(p-2)*p+(p-2)][a9][0];
        merge_key_set[merge_k][a9+k][1]=key_set[(p-2)*p+(p-2)][a9][1];
    }
    merge_k++;

    for(a9=0; a9<k; a9++)
    {
        merge_key_set[merge_k][a9][0]=key_set[(p-2)*p+(p-1)][a9][0];
        merge_key_set[merge_k][a9][1]=key_set[(p-2)*p+(p-1)][a9][1];

        merge_key_set[merge_k][a9+k][0]=key_set[(p-1)*p+(p-3)][a9][0];
        merge_key_set[merge_k][a9+k][1]=key_set[(p-1)*p+(p-3)][a9][1];
    }
    merge_k++;

    printf("\n<(%d,%d)  (%d,%d)>",p-3,p-3,p-1,p-2);
    printf("\n<(%d,%d)  (%d,%d)>",p-3,p-2,p-2,p-3);
    printf("\n<(%d,%d)  (%d,%d)>",p-3,p-1,p-2,p-2);
    printf("\n<(%d,%d)  (%d,%d)>",p-2,p-1,p-1,p-3);
    printf("%d\n",merge_k);

    for(a10=0;a10<merge_k;a10++)
    {
        printf("M(%d)",a10);
        for(a11=0;a11<2*k;a11++)
        {
            printf("(%d,%d),",merge_key_set[a10][a11][0],merge_key_set[a10][a11][1]);
        }
        printf("\n");
    }
}

void vectorize(int p)
{
    int pt=sqrt(p),i;
    for(i=0; i<pt; i++)                //vector ax+b
    {
        for(j=0; j<pt; j++)
        {
            vector[i*pt+j][0]=j;      //b
            vector[i*pt+j][1]=i;      //a
        }
    }
}

int get_x_bar(int x,int pt)
{
    int i;
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
        *(add_poly+i)=*(polya+i)+*(polyb+i);
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
    printf("This program is for F(p)\n");
    printf("Enter no of merged nodes:");
    srand(0);
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
    //for(i=0; i<zp; i++)
    //printf("%d,",prime[i]);
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
    if(isprime(p)==1)
        pt=p;
    if(isprime(p)==0)
        pt=sqrt(p);
    int r1=r*r;
    float r1c2=r1*(r1-1)*0.5;
    fprintf(fp,"\nqt : %d\n",pt);
    printf("\n p=%d",p);
    printf("\n r=%d",r);
    printf("\nenter value of k(2-%d) (keys per node)",p);
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
    int l_t;
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

    else
    {
        vectorize(p);
        printf("\nEnter the irreducable polynomial in z(%d)(From higher to lower degree)",pt);
        for(l_t=2; l_t>=0; l_t--)
        {
            printf("\nX^%d:",l_t);
            scanf("%d",&irr_poly[l_t]);
        }
        for(a1=0; a1<p; a1++)  //a:a1 b:a2 x:a3 key(x,ax+b mod p)
        {
            for(a2=0; a2<p; a2++)
            {
                for(a3=0; a3<k; a3++)
                {
                    key_set[a1*p+a2][a3][0]=a3;

                    poly_a[0]=vector[a1][0];
                    poly_a[1]=vector[a1][1];

                    poly_b[0]=vector[a2][0];
                    poly_b[1]=vector[a2][1];

                    poly_x[0]=vector[a3][0];
                    poly_x[1]=vector[a3][1];

                    mulpoly(poly_a,poly_x);
                    addpoly(mul_poly,poly_b);
                    //printf("\n %dX^2+%dX+%d + %dX+%d=%dX^2+%dX+%d",mul_poly[2],mul_poly[1],mul_poly[0],poly_b[1],poly_b[0],add_poly[2],add_poly[1],add_poly[0]);

                    add_poly[0]=add_poly[0]%pt;
                    add_poly[1]=add_poly[1]%pt;
                    add_poly[2]=add_poly[2]%pt;

                    //printf("\n %dX^2+%dX+%d",add_poly[2],add_poly[1],add_poly[0]);

                    while(1)
                    {
                        if((add_poly[2]-irr_poly[2]<0)||(add_poly[1]-irr_poly[1]<0)||(add_poly[0]-irr_poly[0]<0))
                            break;
                        else
                        {
                            add_poly[2]=add_poly[2]-irr_poly[2];
                            add_poly[1]=add_poly[1]-irr_poly[1];
                            add_poly[0]=add_poly[0]-irr_poly[0];
                        }
                    }

                    //printf("\n %dX^2+%dX+%d",add_poly[2],add_poly[1],add_poly[0]);

                    if((add_poly[2]!=0)&&(add_poly[1]!=0)&&(add_poly[0]==0))   //const 0
                    {
                        add_poly[1]=add_poly[1]+add_poly[2]*irr_poly[1];
                        add_poly[0]=add_poly[2]*get_x_bar(irr_poly[0],pt);
                        add_poly[2]=0;
                    }

                    if((add_poly[2]!=0)&&(add_poly[1]==0)&&(add_poly[0]!=0))     //X 0
                    {
                        add_poly[1]=add_poly[2]*irr_poly[1];
                        add_poly[0]=add_poly[0]+add_poly[2]*get_x_bar(irr_poly[0],pt);
                        add_poly[2]=0;
                    }

                    if((add_poly[2]!=0)&&(add_poly[1]==0)&&(add_poly[0]==0))        //const,X 0
                    {
                        add_poly[1]=add_poly[2]*irr_poly[1];
                        add_poly[0]=add_poly[2]*get_x_bar(irr_poly[0],pt);
                        add_poly[2]=0;
                    }

                    add_poly[0]=add_poly[0]%pt;
                    add_poly[1]=add_poly[1]%pt;
                    add_poly[2]=add_poly[2]%pt;

                    //printf("\n %dX^2+%dX+%d",add_poly[2],add_poly[1],add_poly[0]);

                    if((add_poly[2]==0)&&(add_poly[1]==0)&&(add_poly[0]==0))          //all 0
                    {
                        key_set[a1*p+a2][a3][1]=0;
                    }


                    if((add_poly[2]==0)&&(add_poly[1]!=0)&&(add_poly[0]!=0))       //X^2 0
                    {
                        key_set[a1*p+a2][a3][1]=add_poly[1]*pt+add_poly[0];
                    }

                    if((add_poly[2]==0)&&(add_poly[1]!=0)&&(add_poly[0]==0))        //X^2, const 0
                    {
                        key_set[a1*p+a2][a3][1]=add_poly[1]*pt;
                    }

                    if((add_poly[2]==0)&&(add_poly[1]==0)&&(add_poly[0]!=0))         //X^2,X 0
                    {
                        key_set[a1*p+a2][a3][1]=add_poly[0];
                    }



                    for(l_t=2; l_t>=0; l_t--)
                    {
                        add_poly[l_t]=0;
                        mul_poly[l_t]=0;
                    }
                }
            }
        }
    }
//print keys
    fprintf(fp,"\n");
    printf("\n");
    printf("Node                                            keys");
    printf("\n----------------------------------------------------------\n");
    for(a1=0; a1<p; a1++)
    {
        for(a2=0; a2<p; a2++)
        {
            printf("Node(%d,%d) => %d => ",a1,a2,(a1*p+a2));
            for(a3=0; a3<k; a3++)
            {
                printf("(%d,%d);",key_set[a1*p+a2][a3][0],key_set[a1*p+a2][a3][1]);
                //fprintf(fp,"(%d,%d);",key_set[a1*p+a2][a3][0],key_set[a1*p+a2][a3][1]);
            }
            countt++;
            printf("\n");
            //fprintf(fp,"\n");
        }
        printf("\n");
    }
    //fprintf(fp,"\n countt= %d\n",countt);

//merging block
    int node_status[50000],merge_block[50000][2];

    //procedure call for node merging and merge key set gebneration
    merge_blocksnp();

    // calculate E(s) and V(s)
    int compromised_node,compromised[500];
    printf("\nEnter number of compromised nodes");
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
        for(a2=0; a2<2*k; a2++)
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

    for(a1=0; a1<merge_node; a1++)
    {

        for(a2=0; a2<compromised_node; a2++)
        {
            if(a1==compromised[a2])
            {
                node_list[a1]=-1;
                break;
            }
            else
                node_list[a1]=a1;
        }            //disable compromised nodes
    }
    //for(a1=0; a1<no_of_node; a1++)
       // fprintf(fp,"\n%d",node_list[a1]);
    for(a1=0; a1<merge_node; a1++)
    {
        if(node_list[a1]==-1)
        {
            continue;
        }
        for(a2=0; a2<merge_node; a2++)
        {
            if(node_list[a2]==-1)
                continue;
            if(a1==a2)
            {
                continue;
            }

            count2=0;
            for(a3=0; a3<2*k; a3++)
            {
                for(a4=0; a4<2*k; a4++)
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
                       // break;
                }
            }

            if(flag2!=0)
            {
                flag_broken+=1;
            }
            flag2=0;
            count2=0;
        }
        for(a5=0; a5<10; a5++)
        {
            common_key[a5][0]=9999;
            common_key[a5][1]=9999;
        }
    }
    flag_broken=flag_broken/2;                                                              //eliminate 2 way communication
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
