#include <vector>
#include <map>
#include <string>
#include <string.h>
#include <stdio.h>
#include <queue>
#include <stdlib.h>
#include <stack>
using namespace std;
int dirx[4] = {1,-1,0,0};
int diry[4] = {0,0,1,-1};
int board[55][55];
int R,C;
int sum;
bool judge(int x,int y){
    if(x >= 0 && x < R && y >= 0 && y < C){
        return true;
    }
    return false;
}
void Init(vector<vector<int>>& isInfected){
    memset(board,0,sizeof(board));
    R = isInfected.size();
    C = isInfected[0].size();
    sum = R*C;
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            board[i][j] = isInfected[i][j];
        }
    }
}
struct Node{
    int num_door;
    int num_env;
    int xs,ys;
};

bool operator<(const Node& a, const Node& b){
        return a.num_env < b.num_env;
}

class Solution {
public:
    int vis[55][55];
    int env[55][55];
    priority_queue<Node> virus;
    vector<pair<int,int>> boundary;
    void dfs(int i,int j,Node& node){
        for(int k=0;k<4;k++){
            if(judge(i+dirx[k],j+diry[k]) == false) continue;
            if(board[i+dirx[k]][j+diry[k]] == 0 && env[i+dirx[k]][j+diry[k]] == 0){
                env[i+dirx[k]][j+diry[k]] = 1;
                node.num_env ++;
            }
            if(board[i+dirx[k]][j+diry[k]] == 0) node.num_door ++;
        }
        for(int k=0;k<4;k++){
            if(judge(i+dirx[k],j+diry[k]) ==  false) continue;
            if(board[i+dirx[k]][j+diry[k]] == 1 && vis[i+dirx[k]][j+diry[k]] == 0){
                vis[i+dirx[k]][j+diry[k]] = 1;
                dfs(i+dirx[k],j+diry[k],node);
            }
        }
    }
    void cover(int i,int j,Node& node){
        for(int k=0;k<4;k++){
            if(judge(i+dirx[k],j+diry[k]) == false) continue;
            if(board[i+dirx[k]][j+diry[k]] == 0){
                boundary.push_back(make_pair(i+dirx[k], j+diry[k]));
            }
        }
        for(int k=0;k<4;k++){
            if(judge(i+dirx[k],j+diry[k]) ==  false) continue;
            if(board[i+dirx[k]][j+diry[k]] == 1 && vis[i+dirx[k]][j+diry[k]] == 0){
                vis[i+dirx[k]][j+diry[k]] = 1;
                cover(i+dirx[k],j+diry[k],node);
            }
        }
    }
    void infect(){
        int len = boundary.size();
        for(int i=0;i<len;i++){
            int x = boundary[i].first;
            int y = boundary[i].second;
            board[x][y] = 1;
        }
    }
    void count(int i,int j,Node& node){
        for(int k=0;k<4;k++){
            if(judge(i+dirx[k],j+diry[k]) == false) continue;
            if(board[i+dirx[k]][j+diry[k]] == 0 && env[i+dirx[k]][j+diry[k]] == 0){
                node.num_env ++;
                env[i+dirx[k]][j+diry[k]] = 1;
            }
            if(board[i+dirx[k]][j+diry[k]] == 0) node.num_door ++;
        }
        for(int k=0;k<4;k++){
            if(judge(i+dirx[k],j+diry[k]) ==  false) continue;
            if(board[i+dirx[k]][j+diry[k]] == 1 && vis[i+dirx[k]][j+diry[k]] == 0){
                vis[i+dirx[k]][j+diry[k]] = 1;
                count(i+dirx[k],j+diry[k],node);
            }
        }
    }
    void qurantin(int i,int j){
        board[i][j] = 2;
        for(int k=0;k<4;k++){
            if(judge(i+dirx[k], j+diry[k]) == false) continue;
            if(board[i+dirx[k]][j+diry[k]] == 1 && vis[i+dirx[k]][j+diry[k]] == 0){
                vis[i+dirx[k]][j+diry[k]] = 1;
                qurantin(i+dirx[k], j+diry[k]);
            }
        }
    }
    int containVirus(vector<vector<int>>& isInfected) {
        int ans = 0;
        Init(isInfected);
        memset(vis,0,sizeof(vis));
        for(int i=0;i<R;i++){
            for(int j=0;j<C;j++){
                if(board[i][j] && vis[i][j] == 0){
                    vis[i][j] = 1;
                    Node node;
                    node.xs = i;
                    node.ys = j;
                    node.num_door = 0;
                    node.num_env = 0;
                    memset(env,0,sizeof(env));
                    dfs(i,j,node);
                    virus.push(node);
                }
            }
        }
        // for(int i=0;i<R;i++){
        //     for(int j=0;j<C;j++){
        //         printf("%d ",board[i][j]);
        //     }
        //     printf("\n");
        // }
        while(virus.size()){
            Node node = virus.top();
            virus.pop();
            ans += node.num_door;
            memset(vis,0,sizeof(vis));
            vis[node.xs][node.ys] = 1;
            qurantin(node.xs,node.ys);
            // printf("num_door = %d\n",node.num_door);
            // for(int i=0;i<R;i++){
            //     for(int j=0;j<C;j++){
            //         printf("%d ",board[i][j]);
            //     }
            //     printf("\n");
            // }
            // printf("\n");

            int len = virus.size();
            vector<Node> vec;
            boundary.clear();
            while(len--){
                memset(vis,0,sizeof(vis));
                Node temp = virus.top();
                virus.pop();
                vis[temp.xs][temp.ys] = 1;
                cover(temp.xs,temp.ys,temp);
                vec.push_back(temp);
            }
            infect();
            len = vec.size();
            for(int i=0;i<len;i++) virus.push(vec[i]);
            // for(int i=0;i<R;i++){
            //     for(int j=0;j<C;j++){
            //         printf("%d ",board[i][j]);
            //     }
            //     printf("\n");
            // }
            // printf("\n");

            memset(vis,0,sizeof(vis));
            vec.clear();
            while(len--){
                Node temp = virus.top();
                virus.pop();
                if(vis[temp.xs][temp.ys]) continue;

                temp.num_door = 0;
                temp.num_env = 0;
                vis[temp.xs][temp.ys] = 1;
                memset(env,0,sizeof(env));
                count(temp.xs,temp.ys,temp);

                vec.push_back(temp);
            }
            len = vec.size();
            for(int i=0;i<len;i++) virus.push(vec[i]);
        }
        return ans;
    }
};

int main(){
    return 0;
}