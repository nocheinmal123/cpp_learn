#include "12_queue.h"

int main(){
    using namespace QUEUE;
    Queue<int> que(100);
    que.push(100);
    for(int i=1;i<=40;i++){
        que.push(i);
        std::cout << "size = " << que.size() << std::endl;
        std::cout << que.front() << std::endl;
    }
    while(que.size()){
        std::cout << que.front() << std::endl;
        que.pop();
    }
    return 0;
}