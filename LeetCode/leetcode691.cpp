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
BFS+状态压缩
状态: 字符串压缩成二进制，如果该位被找到替代了，那么从0变成1
*/
class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        int len_stickers = stickers.size();
        int len_target = target.length();
        queue<int> que;
        int vis[70000];
        memset(vis,0,sizeof(vis));
        vis[0] = 1;
        que.push(0);
        int step = 0;
        while(!que.empty()){
            int len = que.size();
            while(len--){
                int now = que.front();
                que.pop();
                for(int k=0;k<len_stickers;k++){
                    int temp = now;
                    int state_word = 0; 
                    // 针对target中的每个字母，都需要遍历一遍第k个单词
                    // 所以，当第k个单词中的第j个字母被用完了，也需要用二进制记录一下，防止下次遍历该单词时候
                    // 又把这个字母用上了，所以需要用state_word记录
                    for(int i=0;i<len_target;i++){
                        if(temp>>(len_target-1-i)&1) continue;
                        int len_word = stickers[k].length();
                        for(int j=0;j<len_word;j++){
                            if(target[i] == stickers[k][j]){
                                if(state_word>>(len_word-1-j)&1) continue; //如果第j个字母被用过了
                                temp = temp | (1<<(len_target-1-i));
                                state_word = state_word | (1<<(len_word-1-j));
                                break;
                            }
                        }
                    }
                    // std::cout<<"temp = "<<temp<<std::endl;
                    // std::cout<<"state_word = "<<state_word<<std::endl;
                    if(temp == (1<<len_target)-1) return step+1;
                    if(vis[temp] == 0){
                        vis[temp] = 1;
                        que.push(temp);
                    }
                }
            }
            step++;
            // std::cout<<std::endl;
        }
        return -1;
    }
};

int main(){
    return 0;
}