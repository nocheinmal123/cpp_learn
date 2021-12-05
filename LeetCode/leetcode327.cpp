#include <vector>
#include <map>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <stack>
using namespace std;
/*
权值线段树，注意转化题目，线段树维护的是前缀和，每次都是找到指定前缀和的
区间的个数
*/
struct Node{
    int _l; int _r;
    int count;
    int mid(){
        return _l+((_r-_l)>>1);
    }
    int len(){
        return _r-_l+1;
    }
};
class Solution {
public:
    Node node[4000000];
    vector<long long> PreSum;
    vector<long long> hash_table;
    void Init(){
        PreSum.clear();
        hash_table.clear();
    }
    void get_sum(const vector<int>& nums,const int lower,const int upper){
        Init();
        int len = nums.size();
        long long sum = 0;
        for(int i=0;i<len;i++){
            sum += nums[i];
            PreSum.push_back(sum);
            hash_table.push_back(sum);
            hash_table.push_back(sum - lower);
            hash_table.push_back(sum - upper);
        }
    }
    int hash(vector<long long>& hash_table){
        sort(hash_table.begin(),hash_table.end());
        int len = unique(hash_table.begin(), hash_table.end()) - hash_table.begin();
        return len;
    }
    void Pushup(int k){
        node[k].count = node[k<<1].count + node[k<<1|1].count;
    }
    void Build(int k,int l,int r){
        node[k]._l = l;
        node[k]._r = r;
        node[k].count = 0;
        if(l == r) return;
        int mid = node[k].mid();
        Build(k<<1,l,mid);
        Build(k<<1|1,mid+1,r);
    }
    void Update(int k,int x){
        if(node[k]._l == node[k]._r){
            node[k].count += 1;
            return;
        }
        else{
            int mid = node[k].mid();
            if(x <= mid) Update(k<<1,x);
            else Update(k<<1|1,x);
            Pushup(k);
        }
    }
    int Query(int k,int l,int r){
        if(l <= node[k]._l && node[k]._r <= r){
            return node[k].count;
        }
        else{
            int mid = node[k].mid();
            int ans = 0;
            if(l <= mid) ans += Query(k<<1,l,r);
            if(r > mid) ans += Query(k<<1|1,l,r);
            return ans;
        }
    }
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int ans = 0;
        get_sum(nums,lower,upper);
        int len = hash(hash_table);
        int size_nums = nums.size();
        // for(int i=0;i<len;i++){
        //     std::cout<<hash_table[i]<<" ";
        // }
        // std::cout<<endl;
        Build(1,1,len+10);
        for(int i=0;i<size_nums;i++){
            if(PreSum[i] <= upper && PreSum[i] >= lower) ans += 1;
            int L = lower_bound(hash_table.begin(), hash_table.begin()+len, PreSum[i]-upper)-hash_table.begin() + 1;
            int R = lower_bound(hash_table.begin(), hash_table.begin()+len, PreSum[i]-lower)-hash_table.begin() + 1;
            int pos = lower_bound(hash_table.begin(), hash_table.begin()+len, PreSum[i]) - hash_table.begin() + 1;
            // printf("pos = %d, Presum = %d, L=%d, R=%d\n",pos,PreSum[i],L,R);
            ans += Query(1,L,R);
            Update(1,pos);
        }
        return ans;
    }
};

int main(){
    return 0;
}