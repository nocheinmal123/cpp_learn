#include <vector>
#include <map>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <algorithm>
using namespace std;
/*
和leetcode907相似，都是单调栈。思路就是针对每个数字，找出如果以他作为最小值，往左延续
延伸最长为n，加上自己n+1，往右连续延伸最长为m，那么总长度为n+1+m。题目就转换为针对每个
数字num[i]，都有num[i]*(n[i]+1+m[i])，然后选出最大值
注意细节问题，比如
2,2,2
那么在计算从左往右第二个数字2的时候，n和m计算的时候需要注意，不能重复计算，也不能漏掉计算
*/
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        vector<int> left; left.clear();
        vector<int>right; right.clear();
        int len = heights.size();
        stack<int> s;
        for(int i=0;i<len;i++){
            while(!s.empty() && heights[i] <= heights[s.top()]) s.pop();
            if(s.empty()) left.push_back(i+1);
            else left.push_back(i - s.top());
            s.push(i);
        }
        while(!s.empty()) s.pop();
        for(int i=len-1;i>=0;i--){
            // std::cout<<heights[i]<<" ";
            while(!s.empty() && heights[i] < heights[s.top()]) s.pop();
            if(s.empty()){
                right.push_back(len - 1 - i);
                // std::cout<<len-i<<std::endl;
            }
            else{
                right.push_back(s.top() - 1 - i);
                // std::cout<<s.top()-1-i<<std::endl;
            } 
            s.push(i);
        }
        reverse(right.begin(),right.end());
        vector<int> ans;
        for(int i=0;i<len;i++) ans.push_back(heights[i]*(right[i] + left[i]));
        // for(int i=0;i<len;i++) printf("%d ",left[i]); printf("\n");
        // for(int i=0;i<len;i++) printf("%d ",right[i]); printf("\n");
        sort(ans.begin(),ans.end());
        return ans[len-1];
    }
};


int main(){
    return 0;
}