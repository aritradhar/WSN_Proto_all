#include<stdio.h>
void main()
{
    int i,j;
    int flag=0;
    for(i=0; i<10; i++)
    {

        for(j=0; j<10; j++)
        {
            if(j=5)
            {
                flag=2;
                break;

            }
        }
        if(flag==2)
            break;
    }
    printf("%d   %d       %d\n",i,j,flag);
    int a=100,b=52;
    float c=(float) a/b;
    printf("\n%f",c);
}
