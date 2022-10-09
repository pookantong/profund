#include <stdio.h>

int main(){
    int m,n;
    scanf("%d %d",&m,&n);
    int matrix_1[m][n],matrix_2[m][n];
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d",& matrix_1[i][j]);
        }
        
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d",& matrix_2[i][j]);
        }
        
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix_1[i][j]+=matrix_2[i][j];
        }
        
    }
    printf("\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ",matrix_1[i][j]);
            if (j == n-1)
            {
                printf("\n");
            }
            
        }
    }
    
    return 0;
}