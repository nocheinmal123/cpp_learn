#include <vector>
#include <map>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
using namespace std;
/*
二分搜索，注意1需要特判
二分搜索的写法，这个题应该是寻找上界(mid需要找一个大的，也就是说(mid+1)*mid/2需要大于n)，
之后要补二分搜索写法总结
*/
class Solution {
public:
    int arrangeCoins(int n) {
        if(n == 1) return 1;
        long long left = 1;
        long long right = n;
        long long ans = 0;
        while(left <= right){
            long long mid = left+(right-left)/2;
            if(n > mid*(mid+1)/2) left = mid+1;
            else if(n > (mid-1)*mid/2){
                ans = mid;
                break;
            }
            else if(n <= (mid-1)*mid/2) right = mid;
        }
        // printf("ans = %d\n",ans);
        if(ans*(ans+1)/2 == n) return ans;
        else return ans-1;
    }
};

int main(){
    return 0;
}