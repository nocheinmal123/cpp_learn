#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class Demo{
    private:
        int value;
        static int value2;
    public:
        explicit Demo(int x){
            value = x;
        }
        void SetValue();
        int GetVaue() const{
            // SetValue(); wrong, in this kind of const member func, the call of 
            // normal member func is not allowed, cauz the normal member func
            // could change the member var
            value2 ++; // right, const member func can call
            return value;
        }
        void Compare(){ // non-static member func can call static member-var
            printf("value2 = %d\n",value2);
        }
};

int Demo::value2 = 10;
Demo obj_Demo(10);

const Demo obj_Demo2(100);

int main(){
    obj_Demo.Compare();
    printf("%d\n",obj_Demo2.GetVaue());
    // obj_Demo2.Compare(); wrong, const obj can call const member-func
    // cauz, the member var of const obj can't be changed, the non const
    // member func could change the value of member var of const pbj
    int ans = obj_Demo2.GetVaue();
    printf("ans = %d\n",ans);
    return 0;
}