#pragma once
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <iostream>

class cell{
    public:
    
    SDL_Rect Rect;
    int x, y, liveNeighbors, GRID_W, GRID_H, cellSize;
    bool alive, nextState;
        
        cell(int x, int y, int w, int h, int size){
            this->x = x;
            this->y = y;
            this->GRID_W = w;
            this->GRID_H = h;
            this->cellSize = size;

            this->liveNeighbors = 0;
            this->alive = false;
            this->nextState = false;

            Rect.x = x * cellSize;
            Rect.y = y * cellSize;
            Rect.w = Rect.h = cellSize;
        }

        void drawCellRect(SDL_Renderer *renderer);
        void statusAlive(cell** map);
        void statusDead(cell** map, int mode);
        void updateStatus(cell** map);
        void updateSelf();

};