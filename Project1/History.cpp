//
//  History.cpp
//  project1
//
//  Created by Megha Ilango on 1/13/18.
//  Copyright © 2018 Megha Ilango. All rights reserved.
//
#include <iostream>
using namespace std;
#include "History.h"

History::History(int nRows, int nCols):m_rows(nRows), m_cols(nCols){
    for(int i = 0; i<nRows; i++){
        for(int j = 0; j<nCols; j++){
            m_grid[i][j] = 0;
        }
    }
}

bool History::record(int r, int c){
    if(r<1 || r>m_rows || c<1 || c>m_cols) return false;
    m_grid[r-1][c-1] = m_grid[r-1][c-1] + 1;
    return true;
}

void History::display() const{
    clearScreen();
    char disp[MAXROWS][MAXCOLS];
    
    for(int i = 0; i<m_rows; i++){
        for(int j = 0; j<m_cols; j++){
            if(m_grid[i][j]==0){
                disp[i][j] = '.';
            }else{
                disp[i][j] = 64 + m_grid[i][j];
            }
        }
    }
    
    for(int i = 0; i<m_rows; i++){
        for(int j = 0; j<m_cols; j++){
            cout << disp[i][j];
        }
        cout << endl;
    }
    cout << endl;
    
}