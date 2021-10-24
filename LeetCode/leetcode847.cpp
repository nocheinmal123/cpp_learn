#include <vector>
#include <map>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <stack>
using namespace std;
/*
BFS+状态压缩
状态：在当前点的时候，所有点的访问状态
vis[15][1<<15]
*/
class Solution {
public:
    struct Node{
        int u;
        int state;
        Node(int _u,int _state):u(_u),state(_state){}
    };
    int shortestPathLength(vector<vector<int>>& graph) {
        int num = graph.size();
        int state = 1;
        int vis[15][1<<15];
        memset(vis,0,sizeof(vis));
        queue<Node> que;
        while(!que.empty()) que.pop();
        for(int i=0;i<num;i++){
            int temp = state<<i;
            // std::cout<<"temp = "<<temp<<std::endl;
            que.push(Node(i,temp));
        }
        int ans = 0;
        while(!que.empty()){
            int len = que.size();
            while(len--){
                Node temp = que.front();
                que.pop();
                int u = temp.u;
                int state = temp.state;
                if(state == (1<<num) - 1) return ans;
                for(int i=0;i<graph[u].size();i++){
                    int v = graph[u][i];
                    int temp_state = (state | (1<<v));
                    if(vis[v][temp_state]) continue;
                    que.push(Node(v,temp_state));
                    vis[v][temp_state] = 1;
                }
            }
            ans++;
        }
        return ans;
    }
};

int main(){
    return 0;
}