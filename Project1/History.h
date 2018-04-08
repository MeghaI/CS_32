//
//  History.hpp
//  project1
//
//  Created by Megha Ilango on 1/13/18.
//  Copyright © 2018 Megha Ilango. All rights reserved.
//

#ifndef History_h
#define History_h

#include "globals.h"

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
    
private:
    const int m_rows;
    const int m_cols;
    int m_grid[MAXROWS][MAXCOLS];
};


#endif /* History_h */
