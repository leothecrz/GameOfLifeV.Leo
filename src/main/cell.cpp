#include "cell.hpp"

void cell::drawCellRect(SDL_Renderer *renderer){
    if(alive){
        SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);
        SDL_RenderFillRect(renderer,  &(this->Rect));
    } else {
        SDL_SetRenderDrawColor(renderer, 41, 41, 41, 255);
        SDL_RenderFillRect(renderer,  &(this->Rect));

    }
    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
    SDL_RenderDrawRect(renderer, &(this->Rect));

}

void cell::statusAlive(cell** map){
    this->alive = true;

    int rightX = x + 1;
    if (rightX == GRID_W)
        rightX = 0;

    int leftX = x - 1;
    if (leftX==(-1))
        leftX = (GRID_W - 1);

    int lowerY = y + 1;
    if (lowerY == GRID_H)
        lowerY = 0;

    int topY = y - 1;
    if (topY==(-1))
        topY = (GRID_H - 1);

    map[topY][leftX].liveNeighbors++;
    map[y][leftX].liveNeighbors++;
    map[lowerY][leftX].liveNeighbors++;

    map[topY][x].liveNeighbors++;
    map[lowerY][x].liveNeighbors++;

    map[topY][rightX].liveNeighbors++;
    map[y][rightX].liveNeighbors++;
    map[lowerY][rightX].liveNeighbors++;
   
}

void cell::statusDead(cell** map, int mode){
    this->alive = false;
    if(mode){
         int rightX = x + 1;
        if (rightX == GRID_W)
            rightX = 0;

        int leftX = x - 1;
        if (leftX==(-1))
            leftX = (GRID_W - 1);

        int lowerY = y + 1;
        if (lowerY == GRID_H)
            lowerY = 0;

        int topY = y - 1;
        if (topY==(-1))
            topY = (GRID_H - 1);

        map[topY][leftX].liveNeighbors--;
        map[y][leftX].liveNeighbors--;
        map[lowerY][leftX].liveNeighbors--;

        map[topY][x].liveNeighbors--;
        map[lowerY][x].liveNeighbors--;

        map[topY][rightX].liveNeighbors--;
        map[y][rightX].liveNeighbors--;
        map[lowerY][rightX].liveNeighbors--;
    }
}

void cell::updateSelf(){
    if(!alive){
        if(liveNeighbors == 3){
            this->nextState = true;
        } else {
            this->nextState = false;
        }
    } else {
        if(this->liveNeighbors < 2 || this->liveNeighbors > 3){
            this->nextState = false;
        } else {
            this->nextState = true;
        }
    }

    this->liveNeighbors = 0;
}

void cell::updateStatus(cell **map){
    if(!alive){
        if(nextState)
            statusAlive(map);
        return;
    } else{
        if (nextState) {
            statusAlive(map);
            return;
        } else {
            statusDead(map, 0);
        }
    
    }
}