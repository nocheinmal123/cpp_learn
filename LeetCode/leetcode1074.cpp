#include <vector>
#include <map>
#include <string>
#include <string.h>
#include <stdio.h>
#include <queue>
#include <stdlib.h>
#include <stack>
using namespace std;
/*
二维前缀和，注意图里面坐标表示的不是点，而是块
 _______________
|   |       |   |
|_A_|__ B___|   |
|   |       |   |
|   |       |   |
|_C_|___D___|   |    
|               |
|               |
|_______________|
在计算前缀和时候，
f[i][j] = f[i-1][j] + f[i][j-1] - f[i-1][j-1] + a[i][j]
在求D的面积的时候，假设xs,ys是D左上角块的坐标，xe,ye是D右下角块的坐标，那么有
fD = f[xe][ye] - f[xs-1][ye] - f[xe][ys-1] + f[xs-1]][ys-1]
*/
class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int r = matrix.size();
        int c = matrix[0].size();
        int area[105][105];
        int matrix_transform[105][105];
        memset(area,0,sizeof(area));
        memset(matrix_transform,0,sizeof(matrix_transform));
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                matrix_transform[i+1][j+1] = matrix[i][j];
            }
        }
        for(int i=1;i<=r;i++){
            for(int j=1;j<=c;j++){
                area[i][j] = area[i-1][j] + area[i][j-1] - area[i-1][j-1] + matrix_transform[i][j];
            }
        }
        int ans = 0;
        for(int xs=1;xs<=r;xs++){
            for(int ys=1;ys<=c;ys++){
                for(int xe=xs;xe<=r;xe++){
                    for(int ye=ys;ye<=c;ye++){
                        int sum = area[xe][ye] - area[xs-1][ye] - area[xe][ys-1] + area[xs-1][ys-1];
                        if(sum == target){
                            ans++;
                            // printf("---xs = %d, ys = %d, xe = %d, ye = %d\n",xs,ys,xe,ye);
                        } 
                        // printf("xs = %d, ys = %d, xe = %d, ye = %d\n",xs,ys,xe,ye);
                    }
                }
            }
        }
        return ans;
    }
};

int main(){
    return 0;
}