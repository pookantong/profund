#include <stdio.h>
#include <stdbool.h>

int check_pos_rook(int x[], int y[], int num);
int result(int x[], int y[],int num);

int main(){
    int x[8],y[8];
    int count;
    do
    {
        printf("number of rook : ");
        scanf("%d",&count);
    } while (!(count<9&&count>0));
    for (int i = 0; i < count; i++)
    {
        do
        {
            printf("rook %d : ",i+1);
            scanf("%d %d",&x[i],&y[i]);
        } while (check_pos_rook(x,y,i));
        
    }
    
    int result_chess = result(x,y,count);
    printf("amount of pawn : %d",result_chess);

    return 0;
}

int check_pos_rook(int x[], int y[], int num){
    for (int i = 0; i < num; i++)
    {
        if (x[num]==x[i]&&y[num]==y[i])
        {
            return true;
        }
        
    }
    if (x[num]>8||y[num]>8||x[num]<1||y[num]<1)
    {
        return true;
    }
    
    return false;
} 

int result(int x[], int y[],int num){
    int all[8][8] = 
            {
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
            };
    int count_num=0;
    
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            all[x[i]-1][j] = 1;
            all[j][y[i]-1] = 1;
        }
    }
    
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (all[i][j]==0)
            {
                count_num++;
            }
        } 
    }
    return count_num;
}