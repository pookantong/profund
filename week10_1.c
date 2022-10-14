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
    
    int number=64,xsize = num,ysize = num;
    
    
    for (int i = 0; i < xsize; i ++)  
    {  
        for (int j = i + 1; j < xsize; j++)  
        {   
            if ( x[i] == x[j])  
            {    
                for (int k = j; k < xsize - 1; k++)  
                {  
                    x[k] = x[k + 1];  
                }    
                xsize--;    
                j--;      
            }  
        }  
    }
    for (int i = 0; i < ysize; i ++)  
    {  
        for (int j = i + 1; j < ysize; j++)  
        {   
            if ( y[i] == y[j])  
            {    
                for (int k = j; k < ysize - 1; k++)  
                {  
                    y[k] = y[k + 1];  
                }    
                ysize--;    
                j--;      
            }  
        }  
    }  
    for (int i = 0; i < xsize; i++)
    {
        number-=8;
    }
    for (int i = 0; i < ysize; i++)
    {
        number-=(8-xsize);
    }
    
    return number;
}