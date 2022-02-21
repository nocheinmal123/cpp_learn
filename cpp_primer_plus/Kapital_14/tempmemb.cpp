#include <iostream>
#include <string>

template<class T>
class beta{
    private:
        template<typename V>
        class hold{
            private:
                V val;
            public:
                hold(V v = 0): val(v){}
                void show() const{ std::cout << val << std::endl;}
                V Value() const { return val; }
        };
        hold<T> q;
        hold<int> n;
    public:
        beta(T t, int i): q(t), n(i){}
        auto sum(){ return q.Value() + n.Value();}
        void Show() const { q.show(); n.show();}
};


int main(){
    beta<double> guy(3.5, 10);
    guy.Show();
    std::cout << guy.sum() << std::endl;
    return 0;
}