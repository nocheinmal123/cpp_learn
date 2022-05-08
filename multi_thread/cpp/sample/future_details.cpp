#include <iostream>
#include <mutex>
#include <future>
#include <thread>
#include <condition_variable>
#include <vector>
#include <numeric>

// std::future详细解释 + 例程
/*
适用场景：
在异步编程模式下，一般会有这样的场景，即一个线程（生产者）准备好一个任务后，
需要通知一个或者多个其他线程（消费者）进行处理，这个时候我们想到了mutex，
但是互斥锁只是保护临界资源，在这种场景下是不适用的。对，这个时候可以用条件变量，
但是条件变量使用起来特别繁琐，需要mutex配合使用，虽然在C++11下对条件变量以及mutex进行了RAII封装，
分别是std::condition_variable以及std::unique_lock（不能使用std::lock_guard），
但是用起来还是不够简洁。而std::future提供了方便，快捷的解决上述问题的方法
*/
// 共享状态标志指的是std::future_status
// 所谓共享状态，指的是promise-future或者packaged_task-future共享
/**
 * 一个有效的（valid）std::future对象通常由以下三种方式来创建，并与某个共享状态关联：
 * 1. std::promise对象调用get_future()
 * 2. std::packaged_task对象调用get_future()
 * 3. std::async()
 * 
 * 成员函数：
 * 1. 移动构造函数和默认构造函数（用于创建无共享状态的future对象）
 * 2. std::future::valid() 检查future对象是否拥有共享状态，即是不是能够调用get()
 *    由默认构造函数创建的future对象显然不具有共享状态。除非它被move赋值过，因为
 *    移动构造函数创建的future对象往往拥有共享状态，只不过是否可以立即调用get()访问，
 *    还需要确认共享状态标志是否已被设置为ready
 * 3. std::future::get() 阻塞式获得共享状态的值，如果future对象调用get()时，
 *    共享状态标志尚未被设置为ready，那么本线程将阻塞至其变为ready
 * 4. std::future::wait() 等待共享状态标志变为ready，在此之前线程将会一直阻塞
 * 5. std::future::wait_for(),  与wait()不同，wait_for()只会允许为此等待一段时间
 *    _Rel_time，耗尽这个时间共享状态标志仍不为ready，wait_for()一样会返回
 * 6. std::future::share() 调用该函数之后，future对象不和任何共享状态关联，也就不再valid的了
 *    share()不难理解，将共享状态“分享”了出去，本来只有promise-future或者
 *    packaged_task-future共享，现在将其分享出去，对比future调用一次get()即失效，
 *    这样的分享显然也会让future对象失效 
 * */

namespace FUTURE {

    int featureTest_1() {
         {  //  constructor/get/operator=
            std::cout << "************constructor Test*************\n";
            auto get_val = []() {
                return 10;
            };
            std::future<int> foo; // default-constructed
            std::future<int> bar = std::async(get_val); // move-constructed
            int x = bar.get(); // move constructor will be called
            std::cout << "bar.get() = " << x << std::endl;

            std::future<int> foo2(std::async(get_val));
            std::cout  << "foo2.get() = " << foo2.get() << std::endl;
         }

         {  // shared
            std::cout << "************shared Test*************\n";
            std::future<int> res = std::async([]() {
                return 100;
            });
            std::shared_future<int> shared_res = res.share();
            // std::shared_future<int> shared_res(res.share()); // or we can use 
            // std::shared_future<int> shared_res(std::move(res)); // or we can use
            std::cout << "res valid = " << res.valid() << std::endl; // res will be invalid after shared_res

            std::cout << "first time get = " << shared_res.get() << std::endl;
            std::cout << "second time get = " << shared_res.get() << std::endl;
         }

         {  // valid
            std::cout << "************valid Test*************\n";
            std::future<int> foo = std::async([]() {
                return 90;
            });
            std::future<int> bar(std::move(foo));
            if (foo.valid()) {
                std::cout << "foo is valid.\n";
            } else {
                std::cout << "foo is invalid.\n";
            }
            if (bar.valid()) {
                std::cout << "bar is valid.\n";
            } else {
                std::cout << "bar is invalid.\n";
            }
         }

         {  //  wait
            auto is_prime = [](int x) {
                for(int i = 2; i < x; i++) {
                    if (x % i == 0 && x != 2) return false;
                }
                return true;
            };
            std::future<bool> res = std::async(is_prime, 194232491);
            std::cout << "Checking ..." << std::endl;
            res.wait(); // 纯粹的阻塞作用
            std::future_status status = res.wait_for(std::chrono::milliseconds(0));
            if (status == std::future_status::ready) {
                std::cout << "Checking finished.\n";
                if (res.get()) std::cout << "194232491 is prime.\n";
                else std::cout << "194232491 is not prime.\n";
            } else {
                std::cout << "Still in checking ...\n";
            }
         }

         {  //  wait_for
            auto is_prime = [](int x) {
                for(int i = 2; i < x; i++) {
                    if (x % i == 0 && x != 2) return false;
                }
                return true;
            };
            std::future<bool> res = std::async(is_prime, 700020007);
            std::cout << "Checking " << std::endl;
            while(res.wait_for(std::chrono::milliseconds(100)) == std::future_status::timeout) {
                std::cout << ".";
            }
            std::cout << "\n";
            if (res.get()) std::cout << "194232491 is prime.\n";
            else std::cout << "194232491 is not prime.\n";
         }
    }

    // std::future <-> std::packaged_task
    int featureTest_2() {
        std::cout << "*************************featureTest_2****************\n";
        std::packaged_task<int()> pt([]() {
            return 17;
        }); // wrap the function
        std::future<int> f1 = pt.get_future(); // get future
        std::thread task1(std::move(pt));
        std::future<int> f2 = std::async(std::launch::async, [] {
            return 8;
        });

        std::promise<int> p;
        std::future<int> f3 = p.get_future();
        std::thread task2([&p]() {
            p.set_value_at_thread_exit(303);
        });
        task2.detach();

        std::cout << "Waiting ...\n";

        f1.wait();
        f2.wait();
        f3.wait();
        std::cout << "Done! f1.get() = " << f1.get() << ", f2.get() = " << f2.get() << ".\n";
        std::cout << "DOne! f3.get() = " << f3.get() << "\n";
        task1.join();

    }

    void initilizer(std::promise<int>* promise_) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        promise_->set_value(999);
        return;
    } 

    void featureTest_3() {
        std::cout << "*************************featureTest_3***************\n";
        std::promise<int> p;
        std::future<int> res = p.get_future();
        std::thread task(initilizer, &p);
        res.wait();
        std::cout << res.get() << std::endl;
        task.join();
        return;
    }

} // namespace

void test_packaged_task() {
    std::cout << "test_packaged_task called.\n";
}

int main() {
    FUTURE::featureTest_1();
    FUTURE::featureTest_2();
    FUTURE::featureTest_3();

    std::packaged_task<void()> pkg_func(test_packaged_task);
    pkg_func(); // packaged_task包装过的函数也可以直接调用
    
    return 0;
}