//ATeam Jessica, Elyse, Max, Leior, John
//cs300
//April 15, 2019
//seeker.cpp

#include "seeker.h"

using namespace std;

Seeker::Seeker() : pos(Tile* pos), nrg(int nrg), money(int money)
{
  items[] = {0};
}

Tile* seeker::getPos() const
{
  return pos;
}


