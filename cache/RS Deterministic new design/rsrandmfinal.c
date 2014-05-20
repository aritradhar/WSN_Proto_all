#include<stdio.h>
#include<math.h>

int arr_node[8000];//random nodes array
int node,prime[1000],z1,z2,z3,temp,count;

int n,qrs,k,d;
int no_of_nodes,max_comm_keys,keys_per_node;
int a,a1,poly_set[500][400][2];
int i1,i2,i3,key_set[10201][101][2];
int poly1[10],poly2[10],poly3[10],result[10],result_poly[10]; //store polynomials one at a time
int z,merge_node,merge_set[6000][250];
int nodes_left;   //nodes left after merging
int max_unique;  //max no of unique keys in one merged block
int merge_key_set[5000][200][2],merge_key_set_copy[5000][200][2];  //merging bblock key set and copy set
int comp1,comp2;
int x;
int i,j,i4,i5,ex1,ex2,ex3;
int a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12;
int node_id1,node_id2;
int flag1=0;
int p1,p2;
int compromised_node;
int compromised[100000],compromised_keys[80000][2],count1=0,common_key[80000][2],count2=0,flag2=0;
int flag_broken=0,node_list[50000],node_status[50000];
int qt;
int merge_block[8000][4];

void sort()
{
    int t1,t2,tmp;
    for(t1=1; t1<n; t1++)
    {
        tmp=prime[t1]; /*k is to be inserted at proper place*/
        for(t2=t1-1; t2>=0 && tmp<prime[t2]; t1--)
            prime[t2+1]=prime[t2];
        prime[t2+1]=tmp;
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
//for(j=0;j<n;j++)
// printf("\n%d",arr_node[j]);
}
void main()
{
    z1=0;
    z2=0;
    FILE* fp;
    FILE* fp1;
    FILE* fp2;
    fp=fopen("record_mb_gen.txt","a");
    fp1=fopen("mb_stat.txt","a");
    fp2=fopen("key_stat.txt","a");
    if(fp==NULL && fp1==NULL && fp2==NULL)
    {
        printf("cannot open file");
    }
    fprintf(fp,"------------------------------------------------");
    fprintf(fp,"Start of program");
    fprintf(fp,"------------------------------------------------\n");
    for(a2=0; a2<10; a2++)
    {
        result[a2]=0;                  //initialize result
    }

    printf("------- Enter Reed Solomon Code Parameters--------\n");
    printf("enter n:");
    scanf("%d",&n);
    k=2;                          //here oly k=2 is considered
    printf("Enter no of nodes (merged) ::");
    scanf("%d",&node);
    printf("Enter z(no of nodes to merge a block) :: ");
    scanf("%d",&z);
    d=n-k+1;
    no_of_nodes=node*z;

//extract primes
    for(a=2; a<150; a++)
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
            prime[z1]=a;                                  //set of primes
            prime[++z1]=a*a;                          //prime or prime power
            z1++;
        }
    }
    //sort
    temp=0;
    for (i=0; i<z1-1; i++)
    {
        for (j=0; j<z1-1-i; j++)
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
    /*
    sort();
    fprintf(fp,"z1:%d-----------------------------------------",z1);
    fprintf(fp,"\n sorted\n");
    for(z2=0; z2<z1; z2++)
    {
        fprintf(fp,"\n%d",prime[z2]);
    }*/

//finding qrs for given no_of_nodes where n<(qrs^2)
    for(z2=0; z2<z1; z2++)
    {
        z3=prime[z2];
        temp=(z3*z3);
        if(no_of_nodes<=temp)
        {
            qrs=prime[z2];
            break;
        }
    }
    //qrs=37;                                                 //order of the reed solomon
    printf("\nq=%d\n",qrs);
    fprintf(fp,"\nq=%d\n",qrs);
    if(isprime(qrs)==1)
        qt=qrs;
    if(isprime(qrs)==0)
        qt=sqrt(qrs);
    //qt=37;                                                  //iff qrs=prime the qt=qrs else qt=sqrt(qrs)
    fprintf(fp,"\nqt : %d\n",qt);



    max_comm_keys=k-1;
    keys_per_node=qrs-1;
    printf("\nDistance : %d",d);
    printf("\nno of nodes supported : %d",no_of_nodes);
    printf("\nno of keys in each node : %d",keys_per_node);
    printf("\n maximum common keys : %d",max_comm_keys);
    fprintf(fp,"\nno of nodes supported : %d",no_of_nodes);
    fprintf(fp,"\nno of keys in each node : %d",keys_per_node);
    fprintf(fp,"\n maximum common keys : %d\n",max_comm_keys);

//generating polynomials pi(x)

    printf("\n");
    for(a=0; a<qrs; a++)
    {
        for(a1=0; a1<qrs; a1++)
        {
            poly_set[a][a1][0]=a;
            poly_set[a][a1][1]=a1;
        }
    }

//print polynomials  pi(x)
    for(a=0; a<qrs; a++)
    {
        for(a1=0; a1<qrs; a1++)
        {
            printf("%dX+%d ",poly_set[a][a1][0],poly_set[a][a1][1]);
            fprintf(fp,"%dX+%d\n ",poly_set[a][a1][0],poly_set[a][a1][1]);
            printf("%d",poly_set[0][1][1]);
            printf("\n");
        }
    }

//generating keys
    for(i1=0; i1<no_of_nodes; i1++)
    {
        for(i2=0; i2<keys_per_node; i2++)
        {
            // key_set[i1][i2][0]=poly_set[i1][i2][1]+poly_set[i1][i2][0]*(i2+1);   //wrong conception
            key_set[i1][i2][1]=i2+1;
        }
    }
    for(i1=0; i1<qrs; i1++)  //total no of kets qrs^2*keys_per_node
    {
        for(i2=0; i2<qrs; i2++)
        {
            for(x=0; x<keys_per_node; x++)
            {
                if(poly_set[i1][i2][0]==0||(poly_set[i1][i2][1]==0&&poly_set[i1][i2][0]==1))
                {
                    key_set[i1*qrs+i2][x][0]=poly_set[i1][i2][1]+poly_set[i1][i2][0]*(x+1);
                    //place key in from the polynomial set
                    //here poly_set remains same for the keys_per_node times and key_set
                    //changes at every iteration
                }

                else                  //poynomial calc
                {
                    //key_set[i1*qrs+i2][x][0]=poly_set[i1][i2][1]+poly_set[i1][i2][0]*(x+1);

                    //here poly_set[i1][i2][0] is the coefficient of x
                    //(x+1) are the values substituted to x (1,2,3)
                    //poly_set[i1][i2][1] is the constant terms
                    //for all the cases 1=1;2=x;3=x+1
                    //ex1=highest power of poly1
                    //ex2=highest power of poly 2
                    //ex3=hifhest power of poly 3
                    //a3=ex1+ex2 highest power of result=poly1*poly2
                    //a4=highest power of result_poly=poly3+result
                    ex1=1;
                    ex2=1;
                    ex3=1;

                    for(p1=0; p1<qt; p1++)       //poly_set[i1][i2][0]
                    {
                        for(p2=0; p2<qt; p2++)
                        {
                            if((p1*qt+p2)==poly_set[i1][i2][0])
                            {
                                poly1[2]=0;
                                poly1[1]=p1;
                                poly1[0]=p2;
                                break;
                            }
                        }
                    }

                    for(p1=0; p1<qt; p1++)       //(x+1)
                    {
                        for(p2=0; p2<qt; p2++)
                        {
                            if((p1*qt+p2)==(x+1))
                            {
                                poly2[2]=0;
                                poly2[1]=p1;
                                poly2[0]=p2;
                                break;
                            }
                        }
                    }
                    for(p1=0; p1<qt; p1++)       //poly_set[i1][i2][1]
                    {
                        for(p2=0; p2<qt; p2++)
                        {
                            if((p1*qt+p2)==poly_set[i1][i2][1])
                            {
                                poly3[2]=0;
                                poly3[1]=p1;
                                poly3[0]=p2;
                                break;
                            }
                        }
                    }

                    a3=ex1+ex2;

                    if(ex3>a3)
                        a4=ex3;
                    if(ex3<a3)
                        a4=a3;
                    if(ex3==a3)
                        a4=a3;

                    for(i=ex1; i>=0; i--)  //polynomial multiplication
                    {
                        for(j=ex2; j>=0; j--)
                        {
                            result[i+j]+=poly1[i]*poly2[j];
                        }
                    }

                    //fprintf(fp,"\n-------------\n");
                    //fprintf(fp,"value of x:%d",(x+1));
                    //fprintf(fp,"\ncoefficient of x:%d",poly_set[i1][i2][0]);
                    //fprintf(fp,"\nvalue of constant term:%d",poly_set[i1][i2][1]);
                    //fprintf(fp,"\ncoefficient of x polynomial:");
                    for(i=ex1; i>=0; i--)
                        //fprintf(fp,"%dX^%d+",poly1[i],i);
                        //fprintf(fp,"\nvalue of x polynomial:");
                        for(i=ex2; i>=0; i--)
                            //fprintf(fp,"%dX^%d+",poly2[i],i);
                            //fprintf(fp,"\nvalue of constant term polynomial:");
                            for(i=ex3; i>=0; i--)
                                //fprintf(fp,"%dX^%d+",poly3[i],i);
                                printf("\n");

                    //fprintf(fp,"\n---Multiplication part---\n");
                    for(i=ex1; i>=0; i--)
                        //fprintf(fp,"%dX^%d+",poly1[i],i);
                        //fprintf(fp," * ");
                        for(j=ex2; j>=0; j--)
                            //fprintf(fp,"%dX^%d+",poly2[j],j);
                            //fprintf(fp," : ");
                            for(i4=a3; i4>=0; i4--)      //polynonomial multiplication print
                            {
                                printf("%dX^%d+",result[i4],i4);
                                //fprintf(fp,"%dX^%d+",result[i4],i4);
                            }
                    //fprintf(fp,"\b");
                    //fprintf(fp," ");
                    printf("\b");
                    printf(" ");

                    for(i5=a4; i5>=0; i5--)                  //polynomial addition
                    {
                        result_poly[i5]=result[i5]+poly3[i5];
                    }
                    //fprintf(fp,"\n---Addition part---\n");

                    for(i=ex3; i>=0; i--)
                        //fprintf(fp,"%dX^%d+",poly3[i],i);
                        //fprintf(fp," + ");
                        for(i=a3; i>=0; i--)
                            //fprintf(fp,"%dX^%d+",result[i],i);
                            //fprintf(fp," : ");
                            for(i=a4; i>=0; i--)               //addition print
                            {

                                printf("%dX^%d+",result_poly[i],i);
                                //fprintf(fp,"%dX^%d+",result_poly[i],i);
                            }

                    //fprintf(fp,"\b");
                    //fprintf(fp," ");
                    printf("\b");
                    printf(" ");
                    printf("\n");

                    for(a5=2; a5>=0; a5--)
                    {
                        result_poly[a5]=result_poly[a5]%qt;
                    }
                    while(1)
                    {
                        if(result_poly[0]!=0 && result_poly[1]!=0 && result_poly[2]!=0)
                        {
                            result_poly[0]-=1;
                            result_poly[1]-=1;
                            result_poly[2]-=1;
                        }
                        else
                            break;
                    }
                    if(result_poly[2]==0 && result_poly[1]!=0 && result_poly[0]!=0)
                    {
                        key_set[i1*qrs+i2][x][0]=result_poly[1]*qt+result_poly[0];
                    }

                    if(result_poly[2]!=0 && result_poly[1]!=0 && result_poly[0]==0)
                    {
                        if(result_poly[2]>result_poly[1])
                        {
                            key_set[i1*qrs+i2][x][0]=(qt+1)*result_poly[2]-2*result_poly[1];
                        }
                        if(result_poly[2]<result_poly[1])
                        {
                            key_set[i1*qrs+i2][x][0]=qt*result_poly[1]-result_poly[2];
                        }
                        if(result_poly[2]==result_poly[1])
                        {
                            key_set[i1*qrs+i2][x][0]=(qt-1)*result_poly[1];
                        }
                    }
                    if(result_poly[2]!=0 && result_poly[1]==0 && result_poly[0]!=0)
                    {
                        if(result_poly[2]<result_poly[0])
                        {
                            key_set[i1*qrs+i2][x][0]=(qt-1)*result_poly[2]+result_poly[0];
                        }
                        if(result_poly[2]>result_poly[0])
                        {
                            key_set[i1*qrs+i2][x][0]=(qt+1)*result_poly[2]-result_poly[0];
                        }
                        if(result_poly[2]==result_poly[0])
                        {
                            key_set[i1*qrs+i2][x][0]=qt*result_poly[2];
                        }
                    }
                    if(result_poly[2]!=0 && result_poly[1]==0 && result_poly[0]==0)
                    {
                        key_set[i1*qrs+i2][x][0]=(qt+1)*result_poly[2];
                    }
                    if(result_poly[2]==0 && result_poly[1]!=0 && result_poly[0]==0)
                    {
                        key_set[i1*qrs+i2][x][0]=qt*result_poly[1];
                    }
                    if(result_poly[2]==0 && result_poly[1]==0 && result_poly[0]!=0)
                    {
                        key_set[i1*qrs+i2][x][0]=result_poly[0];
                    }


                    //reinitialize all result poly
                    for(a2=0; a2<10; a2++)
                    {
                        result[a2]=0;  //initialize result
                    }

                    for(a2=0; a2<10; a2++)
                    {
                        result_poly[a2]=0;  //initialize result
                    }
                }
            }
        }
    }
    printf("\n");
    fprintf(fp,"\n");
    for(i1=0; i1<no_of_nodes; i1++)
    {
        for(i2=0; i2<keys_per_node; i2++)
        {
            printf("(%d,%d); ",key_set[i1][i2][0],key_set[i1][i2][1]);
            //fprintf(fp,"(%d,%d); ",key_set[i1][i2][0],key_set[i1][i2][1]);
        }
        fprintf(fp,"\n");
        printf("\n");
    }

//merging block
    merge_node=floor(no_of_nodes/z);
    nodes_left=no_of_nodes%z;
    printf("\nno of merged blocks : %d",merge_node);
    fprintf(fp,"\nno of merged blocks : %d",merge_node);
    printf("\nno of nodes left after merging : %d",nodes_left);
    fprintf(fp,"\nno of nodes left after merging : %d",nodes_left);
    max_unique=keys_per_node*z;
    int z_c;
    //merging 1-keys in common
    if(qrs%2!=0)                                            //if qrs is odd
    {
        a3=0;
        z_c=0;
        for(a1=0; a1<qrs-3; a1=a1+2)                        //taking 2 rows at a time
        {
            for(a2=0; a2<qrs-1; a2++)                       //iteration will go from 0 rro qrs-2
            {
                merge_set[a3][0]=a1*qrs+a2;                 //merging diagonal elements
                merge_set[a3][1]=(a1+1)*qrs+(a2+1);
                fprintf(fp1,"\n<(%d,%d) (%d,%d)>   %d",merge_set[a3][0]/qrs,merge_set[a3][0]%qrs,merge_set[a3][1]/qrs,merge_set[a3][1]%qrs,a3);
                a3++;
            }
            merge_set[a3][0]=(a1+1)*qrs+0;                 //2 left nodes of top left and bottom right corner
            merge_set[a3][1]=a1*qrs+(qrs-1);
            fprintf(fp1,"\n<(%d,%d) (%d,%d)>   %d",merge_set[a3][0]/qrs,merge_set[a3][0]%qrs,merge_set[a3][1]/qrs,merge_set[a3][1]%qrs,a3);
            a3++;
            fprintf(fp1,"\n");
        }
        //handling upper 3 rows
        for(a5=0;a5<qrs-1;a5=a5+2)
        {
            for(a4=a1;a4<qrs-1;a4++)            //q-3 to q-2
            {
                merge_set[a3][0]=a4*qrs+a5;
                merge_set[a3][1]=(a4+1)*qrs+(a5+1);
                fprintf(fp1,"\n<(%d,%d) (%d,%d)>   %d",merge_set[a3][0]/qrs,merge_set[a3][0]%qrs,merge_set[a3][1]/qrs,merge_set[a3][1]%qrs,a3);
                a3++;
            }
            merge_set[a3][0]=(qrs-3)*qrs+(a5+1);                 //2 left nodes of top left and bottom right corner
            merge_set[a3][1]=(qrs-1)*qrs+a5;
            fprintf(fp1,"\n<(%d,%d) (%d,%d)>   %d",merge_set[a3][0]/qrs,merge_set[a3][0]%qrs,merge_set[a3][1]/qrs,merge_set[a3][1]%qrs,a3);
            a3++;
            fprintf(fp1,"\n");
        }
    }
    fclose(fp1);
    printf("\n%d",a3);      //count a3 is correct

    for(a1=0;a1<merge_node;a1++)
    {
        for(z_c=0;z_c<keys_per_node;z_c++)           //adding keys
            {
                merge_key_set[a1][z_c][0]=key_set[merge_set[a1][0]][z_c][0];                               //check it
                merge_key_set[a1][z_c][1]=key_set[merge_set[a1][0]][z_c][1];
                merge_key_set[a1][z_c+(keys_per_node)][0]=key_set[merge_set[a1][1]][z_c][0];
                merge_key_set[a1][z_c+(keys_per_node)][1]=key_set[merge_set[a1][1]][z_c][1];
            }
    }

    for(a1=0;a1<merge_node;a1++)
    {
        for(z_c=0;z_c<2*keys_per_node;z_c++)
        {
            fprintf(fp2,"(%d,%d)",merge_key_set[a1][z_c][0],merge_key_set[a1][z_c][1]);
        }
        fprintf(fp2,"\n");
    }
    fclose(fp);

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
    count2=0;
    flag2=0;
    flag_broken=0;
    //checking links
    for(a1=0; a1<no_of_nodes; a1++)
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
    for(a1=0; a1<no_of_nodes; a1++)
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
    total_links=(node*(node-1))*0.5;
    printf("\nTotal links : %.0f",total_links);
    fprintf(fp,"\nTotal linkss : %.0f",total_links);
    float es;
    es=(float) flag_broken/total_links;
    printf("\nE(s)=%f",es);
    fprintf(fp,"\nE(s)=%f",es);
    int flag_c=0,flag_vs=0,vs;
    for(a1=0; a1<merge_node; a1++)
    {
        flag_c=0;
        if(node_list[a1]==0)
            continue;
        for(a2=0; a2<max_unique; a2++)
        {
            for(a3=0; a3<compromised_node*max_unique; a3++)
            {
                if((merge_key_set[a1][a2][0]==compromised_keys[a3][0]) && (merge_key_set[a1][a2][1]==compromised_keys[a3][1]))
                {
                    flag_c++;
                }
            }
        }
        if(flag_c==max_unique)
            flag_vs++;
        flag_c=0;
    }
    vs=(float) flag_vs/merge_node;
    printf("\n V(s):%d",vs);
    int vt=0,flag_vt=0;
    float vts;
    printf("\n");
    fprintf(fp,"\n");
    for(a1=0; a1<merge_node; a1++)
    {
        flag_vt=0;
        if(node_list[a1]==0)
            continue;
        for(a2=0; a2<max_unique; a2++)
        {
            for(a3=0; a3<compromised_node*max_unique; a3++)
            {
                if((merge_key_set[a1][a2][0]==compromised_keys[a3][0]) && (merge_key_set[a1][a2][1]==compromised_keys[a3][1]))
                {
                    flag_vt=1;
                    // break;
                }
            }
            //if(flag_vt==1)
            // break;
        }
        if(flag_vt==1)
        {
            vt++;
            //printf("%d,",a1);
            //fprintf(fp,"%d,",a1);
        }

    }
    vts=(float) vt/node;
    printf("\n%d",vt);
    printf("\nVT(%d) = %f",compromised_node,vts);

    fprintf(fp,"------------------------------------------------");
    fprintf(fp,"End of program");
    fprintf(fp,"------------------------------------------------\n");
    fclose(fp);
}
