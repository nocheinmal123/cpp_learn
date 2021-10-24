#include <vector>
#include <map>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
using namespace std;
/*
如果从i节点出发，在到达j几点，发现 remain+gas[j]-cost[j] < 0,那么，从i到j之间任意一个节点出发，都不能到达j
起点只可能在j+1，证明：
反证法，如果在i到j之间，存在k，使得虽然i不能到j，但是k可以到j，那么必然有
sum(k.....j) >= 0。但是又因为i可以到k，那么必然有 sum(i......k) >= 0，
那么也就是说i可以到达j，与i不能达到j矛盾，所以，只要某个点不能到达终点，那么从该点到终点的中间任意一点作为起点
都不行
*/
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int len = gas.size();
        int sum = 0;
        for(int i=0;i<len;i++) sum += gas[i] - cost[i];
        if(sum < 0) return -1;
        int start = 0;
        int remain = 0;
        for(int i=0;i<len;i++){
            remain += gas[i] - cost[i];
            if(remain < 0){
                remain = 0;
                start = i+1;
            }
        }
        return start;
    }
};

int main(){
    return 0;
}
