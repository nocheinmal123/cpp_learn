#include "13_brass.h"

int main(){
    Brass Piggy("Porcelot Pigg", 381299, 4000.00);
    BrassPlus Hoggy("Horatio Hogg", 382288, 3000.00);
    Piggy.ViewAcct();
    std::cout << std::endl;

    Hoggy.ViewAcct();
    Hoggy.Deposit(1000);
    std::cout << "Hoggy's new balance: " << Hoggy.Balance() << std::endl;

    std::cout << "Withdaw $4200 from the Hoggy's Account:\n";
    Hoggy.Withdraw(4200);
    Hoggy.ViewAcct();
    return 0;
}