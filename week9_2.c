#include <stdio.h>

int main(){
    int m,n;
    scanf("%d %d",&m,&n);
    int matrix_1[m*n];
    int matrix_2[m*n];
    for (int i = 0; i < m*n; i++)
    {
        scanf("%d",& matrix_1[i]); 
    }
    for (int i = 0; i < m*n; i++)
    {
        scanf("%d",& matrix_2[i]);

    }
    for (int i = 0; i < m*n; i++)
    {
        matrix_1[i]+=matrix_2[i];
        if (i%n==0)
        {
            printf("\n");
        }
        
        printf("%d ",matrix_1[i]);
    }
    return 0;
}