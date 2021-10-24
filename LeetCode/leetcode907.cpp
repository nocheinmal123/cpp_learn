#include <vector>
#include <map>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
using namespace std;
/*
为什么采用从左到右，再从右到左的遍历方法呢，首先我们应该解决怎么规定子数组的问题。一开始，
我认为，子数组可以采用尾部固定，然后从前到该位置，有多少个数字就是多少个子数组的方法，比如
2,3,5,4,1,6
对于元素4，来说，那么子数组就是[2,3,5,4],[3,5,4],[5,4],[4]一共4个，但是这种方法不利于
解决这个问题，因为每次求出了一个单调栈，你需要再遍历这个单调栈。还是对于元素4来说，单调栈这
时的状态应该是，(1),(2),(4)，意思是以元素4作为结尾，那么单调栈的内容就是这个。此时，必须
再次遍历单调栈，才能得出答案。
第二种规定子数组的方法是规定某个元素作为最小值，那么前后能到达的最远距离是什么(左边元素个数n右边元素个数m)，
比如元素4时，那么前面有元素5，后面没有，那么以元素4作为最小值的子数组就是[5,4],[4]。这种方法需要求出
左右两侧的元素个数，对于元素4,m=2,n=1
还有需要注意比如[2,2]这种，他的子数组是
(1)
(1),(2)
(2)
对于(1),(2)来说，如果while条件都不带"="，那么就会造成子数组的计算没有(1),(2)，如果都带了
"="，那么就会造成(1),(2)被计算了两次。因为实际上得规定好，当有连续相等的数时，这些连续的数字是
算在m里面还是n里面，不能多计算，也不能不计算
*/

class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        const int mod = 1000000007;
        long long left[30005];
        long long right[30005];
        memset(left,0,sizeof(left));
        memset(right,0,sizeof(right));
        stack<int> s;
        int len = arr.size();
        for(int i=0;i<len;i++){
            while(!s.empty() && arr[i]<=arr[s.top()]){  //要么这里需要等号
                s.pop();
            }
            if(s.empty()) left[i] = i + 1;
            else left[i] = i - s.top();
            s.push(i);
        }
        while(!s.empty()) s.pop();
        for(int i=len-1;i>=0;i--){
            while(!s.empty() && arr[i]<arr[s.top()]){   //要么这里需要等号
                s.pop();
            }
            if(s.empty()) right[i] = len - i;
            else right[i] = s.top() - i;
            s.push(i);
        }
        long long ans = 0;
        // for(int i=0;i<len;i++) printf("%d ",left[i]); printf("\n");
        // for(int i=0;i<len;i++) printf("%d ",right[i]); printf("\n");
        for(int i=0;i<len;i++) {
            ans += arr[i]*left[i]*right[i];
            ans %= mod;
        }
        return ans;
    }
};

int main(){
    return 0;
}