#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
The Solution without using polymorphism
class CCreature{
    protected:
        int nPower;
        int nLifeValue;
    public:
        CCreature(){

        }
};

class CDragon;

class CWolf: public CCreature{
    public:
        void Hurted(int Power){
            nLifeValue -= Power;
        }
        void Fightback(CDragon* p){
            p->Hurted(nPower/2);
        }
        void Fightback(CGhost* p){
            p->Hurted(nPower/2);
        }
        void Attack(CDragon* p){
            p->Hurted(nPower);
            p->Fightback(this);
        }
        void Attack(CGhost* p){
            p->Hurted(nPower);
            p->Fightback(this);
        }   
};

class CGhost: public CCreature{
    public:
        void Hurted(int Power){
            nLifeValue -= Power;
        }
        void Fightback(CDragon* p){
            p->Hurted(nPower/2);
        }
        void Fightback(CGhost* p){
            p->Hurted(nPower/2);
        }
        void Attack(CDragon* p){
            p->Hurted(nPower);
            p->Fightback(this);
        }
        void Attack(CGhost* p){
            p->Hurted(nPower);
            p->Fightback(this);
        }
};

class CDragon: public CCreature{
    public:
        void Hurted(int Power){
            nLifeValue -= Power;
        }
        void Fightback(CWolf* p){
            p->Hurted(nPower/2);
        }
        void Fightback(CGhost* p){
            p->Hurted(nPower/2);
        }        
        void Attack(CWolf* pWolf){
            pWolf->Hurted(nPower);
            pWolf->Fightback(this);
        }
        void Attack(CGhost* pGhost){
            pGhost->Hurted(nPower);
            pGhost->Fightback(this);
        }
};
if we add one more CTHunderbird, firstly we have to write a new class called
CThunderbird, and then we have to add "Attack" func and "Fightback" fun for 
every class, which are already written
*/

class CCreature{
    protected:
        int nPower;
        int nLifeValue;
    public:
        CCreature(){

        }
        virtual void Attack(CCreature* p){
            p->Hurted(nPower);
            p->Fightback(this);
        }
        virtual void Hurted(int Power){
            nLifeValue -= nPower;
        }
        virtual void Fightback(CCreature* p){
            p->Hurted(nPower/2);
        }
};

class CWolf:public CCreature{
     public:
        virtual void Attack(CCreature* p){
            std::cout<<"WOlf attack"<<std::endl;
            p->Hurted(nPower);
            p->Fightback(this);
        }
        virtual void Hurted(int Power){
            std::cout<<"Wolf hurted"<<std::endl;
            nLifeValue -= nPower;
        }
        virtual void Fightback(CCreature* p){
            std::cout<<"Wolf fightback"<<std::endl;
            p->Hurted(nPower/2);
        }
};

class CGhost:public CCreature{
    public:
        virtual void Attack(CCreature* p){
            std::cout<<"Ghost attack"<<std::endl;
            p->Hurted(nPower);
            p->Fightback(this);
        }
        virtual void Hurted(int Power){
            std::cout<<"GHost hurted"<<std::endl;
            nLifeValue -= nPower;
        }
        virtual void Fightback(CCreature* p){
            std::cout<<"Ghost fightback"<<std::endl;
            p->Hurted(nPower/2);
        }
};

class CDragon:public CCreature{
    public:
        virtual void Attack(CCreature* p){
            std::cout<<"Dragon attack"<<std::endl;
            p->Hurted(nPower);
            p->Fightback(this);
        }
        virtual void Hurted(int Power){
            std::cout<<"Dragon hurted"<<std::endl;
            nLifeValue -= nPower;
        }
        virtual void Fightback(CCreature* p){
            std::cout<<"Dragon fightback"<<std::endl;
            p->Hurted(nPower/2);
        }
};

int main(){
    CCreature* pDragon = new CDragon();
    CCreature* pGhost = new CGhost();
    CCreature* PWolf = new CWolf();
    pDragon->Attack(pGhost);
    return 0;
}