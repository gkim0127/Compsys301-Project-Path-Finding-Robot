#include <stdio.h>
#include "map.h"

int row = sizeof(map) / sizeof(map[0]);
int column = sizeof(map[0])/sizeof(map[0][0]);   



int main(){
    int oneDMap[row*column];
    int adjacentMap[row*column][row*column];
    int numOfValid = 0;

    int k = 0;
    for(int i =0; i < 15; i++){
        for(int j =0; j <19; j++){
            /*
            oneDMap[k] = map[i][j];
            k++;
             */
            printf("%d",map[i][j]);
            
            if(map[i][j] == 0){
                numOfValid ++;
                if(i>1){
                    if(map[i-1][j] == 0){
                        adjacentMap[(i-1)*column+j][(i-2)*column+j] =1;
                    }
                }

            }
        }
        printf("\n");
    }
    //printf("%d",numOfValid);
    printf("%d",row);
    printf("\n");
    printf("%d",column);



    return 0;
}