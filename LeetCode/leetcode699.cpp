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
线段树
*/
typedef struct {
        int _l; int _r;
        int h;
        int set_tag;
}Node;
class Solution {
public:
    int height[1005];
    int num;
    void Init(){
        memset(height,0,sizeof(height));
        num = 0;
    }
    inline int get_mid(int k){
        return node[k]._l+((node[k]._r-node[k]._l)>>1);
    }
    inline int get_len(int k){
        return node[k]._r-node[k]._l+1;
    }
    inline int lc(int k){
        return (2*k);
    }
    inline int rc(int k){
        return (2*k+1);
    }
    Node node[5000];
    void Pushup(int k){
        node[k].h = max(node[lc(k)].h,node[rc(k)].h);
    }
    void Pushdw(int k){
        if(node[k].set_tag == 0) return;
        node[lc(k)].set_tag = node[k].set_tag;
        node[lc(k)].h = node[lc(k)].set_tag;
        
        node[rc(k)].set_tag = node[k].set_tag;
        node[rc(k)].h = node[rc(k)].set_tag;

        node[k].set_tag = 0;
    }
    void Build(int k,int l,int r){
        node[k]._l = l;
        node[k]._r = r;
        node[k].set_tag = 0;
        node[k].h = 0;
        // printf("k=%d l=%d r=%d\n",k,l,r);
        if(l == r){
            return;
        }
        int mid = get_mid(k);
        Build(lc(k),l,mid);
        Build(rc(k),mid+1,r);
        Pushup(k);
    }
    void Update(int k,int l,int r,int v){
        if(l <= node[k]._l && node[k]._r <= r){
            node[k].h = v;
            node[k].set_tag = v;
            return;
        }
        else{
            Pushdw(k);
            int mid = get_mid(k);
            if(l <= mid) Update(lc(k),l,r,v);
            if(r > mid) Update(rc(k),l,r,v);
            Pushup(k);
        }
    }
    int query(int k,int l,int r){
        if(l <= node[k]._l && node[k]._r <= r){
            return node[k].h;
        }
        else{
            Pushdw(k);
            int mid = get_mid(k);
            int ans1=0,ans2=0;
            if(l <= mid) ans1 = max(ans1,query(lc(k),l,r));
            if(r > mid) ans2 = max(ans2,query(rc(k),l,r));
            Pushup(k);
            return max(ans1,ans2);
        }
    }
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        Init();
        vector<int> temp;
        vector<pair<int,int> > square;
        int len_positions = positions.size();
        for(int i=0;i<len_positions;i++){
            height[i] = positions[i][1]; 
            temp.push_back(positions[i][0]+1);
            temp.push_back(positions[i][0]+positions[i][1]);
        }
        sort(temp.begin(),temp.end());
        int len = unique(temp.begin(),temp.end()) - temp.begin();
        for(int i=0;i<len_positions;i++){
            // int left = 0,right = 0;
            int left = lower_bound(temp.begin(),temp.begin()+len,positions[i][0]+1)-temp.begin();
            int right = lower_bound(temp.begin(),temp.begin()+len,positions[i][0]+positions[i][1])-temp.begin();
            square.push_back(make_pair(left,right));
        }
        // for(int i=0;i<len_positions;i++){
        //     std::cout<<square[i].first+1<<", "<<square[i].second+1<<std::endl;
        // }
        vector<int> ans;
        Build(1,1,len);
        // std::cout<<"node[1].h = "<<node[1].h<<std::endl;
        for(int i=0;i<len_positions;i++){
            int h_max = query(1,square[i].first+1,square[i].second+1)+height[i];
            Update(1,square[i].first+1,square[i].second+1,h_max);
            ans.push_back(node[1].h);

        }
        return ans;
    }
};

int main(){
    return 0;
}