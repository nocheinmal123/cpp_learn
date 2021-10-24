#include <vector>
#include <map>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
using namespace std;
/*
单调队列，采用双端队列构造，每次需要检查双端队列的前部是否已经超过了窗口的大小(也就是k)，
新进入的元素从双端队列尾部压入
*/
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int len = nums.size();
        vector<int> ans; ans.clear();
        deque<int> que; while(!que.empty()) que.pop_front();
        for(int i=0;i<len;i++){
            while(!que.empty() && nums[i] > nums[que.back()]){
                que.pop_back();
            }
            que.push_back(i);
            while(!que.empty() && que.front() < i-k+1){
                que.pop_front();
            }
            if(i >= k-1) ans.push_back(nums[que.front()]);
        }
        return ans;
    }
};

int main(){
    return 0;
}