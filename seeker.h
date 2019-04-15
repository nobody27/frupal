 //ATeam Jessica, Elyse, Max, Leior, John
 //cs300
 //April 10, 2019
 //seeker.h

#ifndef SEEKER_H
#define SEEKER_H

class Seeker
{
  public:
    //constructor
    Seeker(Tile* pos, int nrg, int money, int items[]);
   
    //movement functions
    Tile* getPos() const;
    bool setPos(int xVaule, int yValue);
    void printPos();
    void look();

    //get/set energy
    int getNrg();
    bool setNrg(int nrg);

    //get/set money
    int getMoney();
    bool setMoney(int money);

    //items
    bool useItem(int Item);
    bool buyItem(int Item);

  private:
    Tile* pos;
    int nrg;
    int money;
    int items[10];
};
 
#endif

