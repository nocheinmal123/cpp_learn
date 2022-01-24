#include "13_4.h"

int main(){
    Port* p_port = new Port("nick", 20, "stage");
    std::cout << p_port->BottleCount() << std::endl;
    p_port->Show();
    p_port = new VintagePort("vintageport",34,"ghgh",2022);
    p_port->Show();
    Port obj_port = Port("port obj", 16, "ooo");
    obj_port.Show();
    Port copy_port(obj_port);
    copy_port.Show();
    copy_port += 1;
    std::cout << copy_port << std::endl;
    obj_port -= 1;
    std::cout << obj_port << std::endl;

    VintagePort obj_vintageport("vintage port obj", 75, "lllkkk", 2025);
    obj_vintageport.Show();
    VintagePort obj2("vintage2",56, "iii", 23);
    obj_vintageport = obj2;
    obj_vintageport.Show();
    return 0;
}