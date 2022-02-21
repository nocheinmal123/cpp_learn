#include "worker0.h"

int main(){
    Waiter w1("Genis", 23, 77);
    Singer s1("fangsen", 78, 45);
    Worker* pw1 = new Waiter("kkkkk", 98,100);
    pw1->Show();
    Worker* pw2 = new Waiter(s1, 90);
    pw2->Show();
    Worker* ps1 = new Singer("hhhhh", 89,999);
    ps1->Show();
    Worker* ps2 = new Singer(s1, 88);
    ps2->Show();
    Worker* pw[5] = {new Waiter("Bob Apple", 314, 5),
                     new Singer("Beverly Hills", 522, 14),
                     new Waiter(s1, 7),
                     new Singer(w1,101)};
    for(int i=0;i<4;i++){
        pw[i]->Show();
    }
    return 0;
}