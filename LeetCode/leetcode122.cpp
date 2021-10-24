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
贪心，贪心策略是只要第n+1天是涨的，那么就买第n天的
只要是第n+1天是跌的，就在第n天卖掉（如果有股票的话）
同时，需要在末位加入-1，用来保证肯定会在最后一天卖出（如果手头有股票的话）
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int sum = 0;
        int len = prices.size();
        int temp = -1;
        vector<int> res; res.clear();
        res.push_back(10001);
        for(int i=0;i<len;i++) res.push_back(prices[i]);
        res.push_back(-1);
        for(int i=1;i<=len;i++){
            if(res[i] < res[i+1] && temp == -1){
                temp = res[i];
                // std::cout<<"buy in: "<<res[i]<<std::endl;
            }
            else if(temp != -1 && res[i] > res[i+1]){
                // std::cout<<"sold out: "<<res[i]<<std::endl;
                sum += res[i] - temp;
                temp = -1;
            }
        }
        return sum;
    }
};

int main(){
    return 0;
}