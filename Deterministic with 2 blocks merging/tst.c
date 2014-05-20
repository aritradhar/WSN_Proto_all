#include<stdio.h>
void main()
{
    long int i,j;
    long int flag=0;
    int c=0;
    int a[2000000];
    for(i=0;i<2000000;i++)
    a[i]=0;
    for(i=0;i<2000000;i++)
    {
    printf("%d",a[i]);
    c++;
    }
    printf("%d",c);
}
