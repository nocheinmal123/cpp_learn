#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;
/*
贪心，贪心策略如下：
当一个洗衣机需要衣服的时候，他可以同时从左右两边获取
所以，针对第i个洗衣机，当我们简化提议，将从左往右，将
左边依次清零，得到的balance，也就是需要向右边传递的
衣服数量（>0表示向右传递，<0表示实际上右边需要向左传递）
有以下公式：
max(第i个洗衣机需要的衣服，经过第i个洗衣机向右传递的衣服量)
第i个洗衣机需要的衣服数量:          machines[i] - num
经过第i个洗衣机向右传递的衣服数量:   balance
*/
class Solution {
public:
    int findMinMoves(vector<int>& machines) {
        int sum = 0; int len = machines.size();
        for(int i=0;i<len;i++) sum += machines[i];
        if(sum%len) return -1;
        int num = sum/len;
        int balance = 0;
        int ans = 0;
        for(int i=0;i<len;i++){
            balance += machines[i] - num;
            ans = max(ans, max(machines[i] - num, abs(balance)));
        }        
        return ans;
    }
};

int main(){
    return 0;
}