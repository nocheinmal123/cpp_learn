#include "arraytp.h"

int main(){
    ArrayTP<int, 10> sums;
    ArrayTP<double, 10> aves;
    // 递归定义
    ArrayTP<ArrayTP<int, 5>, 10> twodee;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 5; j++){
            twodee[i][j] = (i + 1) * (j + 1);
            sums[i] += twodee[i][j];
        }
        aves[i] = (double) sums[i] / 10;
    }
    return 0;
}