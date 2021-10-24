#include <vector>
#include <map>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
/*
无法直接按照字符串的字典序来排列，因为比如对于 "4", "42"来说，
"42"字典序大应该排在前面，组合成了 "424"，但是明显 "442"更大，
正确排序方法，考虑 s1+s2和s2+s1的大小关系
*/
using namespace std;
bool cmp(const string s1,const string s2){
        return s1+s2 > s2+s1;
    }
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string> temp;
        int len = nums.size();
        for(int i=0;i<len;i++){
            temp.push_back(to_string(nums[i]));
        }
        sort(temp.begin(),temp.end(),cmp);
        string ans = "";
        for(int i=0;i<len;i++){
            ans += temp[i];
            // std::cout<<temp[i]<<std::endl;
        }
        int len_str = ans.length();
        int mark = 0;
        for(int i=0;i<len_str;i++){
            if(ans[i] != '0'){
                mark = 1;
                break;
            }
        }
        if(mark) return ans;
        else return "0";
    }
};

int main(){
    return 0;
}
