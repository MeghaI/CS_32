//
//  Game.hpp
//  project1
//
//  Created by Megha Ilango on 1/13/18.
//  Copyright © 2018 Megha Ilango. All rights reserved.
//

#ifndef Game_h
#define Game_h


class City;

int decodeDirection(char dir);

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nFlatulans);
    ~Game();
    
    // Mutators
    void play();
    
private:
    City* m_city;
};


#endif /* Game_h */
