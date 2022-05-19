
#include "main.hpp"
#include "cell.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>

int cellSize = 22;
int mapH = 30;
int mapW = 60;

cell** cellMap;

int HEIGHT = cellSize * mapH;
int WIDTH = cellSize * mapW;

bool run = 1;
bool pause = 1;
bool pen = 1;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

int main(int argc, char* argv[]){
    
    cellMap = new cell*[mapH];
    for(int k=0;k<mapH;k++){
        cellMap[k] = (cell*) std::malloc((mapW) * sizeof(cell)); //Each pointer points
    }

    for(int i=0;i<mapH;i++){
        for(int j=0;j<mapW;j++){
            cellMap[i][j] =  cell(j,i,mapW,mapH,cellSize);
        }
    }

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        std::cout << "SDL initiazation failed: " << SDL_GetError();
    
    window = SDL_CreateWindow("Leo's Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    if (window == NULL)
        std::cout << "Window initiazation failed: " << SDL_GetError();

   
    draw();
    while(run){
        
        getInputs();
        if(!pause){
            int Tick = 400;
            SDL_Delay(Tick / 2);
            draw();
            SDL_Delay(Tick/2);
            update();
        }
        SDL_Delay(10);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    for(int i=0;i<mapH;i++){
        delete[] cellMap[i];
    }
    delete[] cellMap;

    return 0;
}

void getInputs(){

    SDL_Event events;
    int X, Y;
    Uint32 buttons;

    SDL_PumpEvents();

    while(SDL_PollEvent(&events)){
        
        switch (events.type) {
            case(SDL_QUIT):
                run = 0;
                break;

            case(SDL_MOUSEBUTTONDOWN):

                buttons = SDL_GetMouseState(&X, &Y);

                if((buttons & SDL_BUTTON_LEFT) > 0){
                    int x = floor(X/cellSize);
                    int y = floor(Y/cellSize);
                    if(pen){
                        if (!(cellMap[y][x].alive))
                            cellMap[y][x].statusAlive(cellMap);
                    } else{
                        cellMap[y][x].statusDead(cellMap, 1);
                    }

                    cellMap[y][x].drawCellRect(renderer);
                    SDL_RenderPresent(renderer);
                }


            case(SDL_KEYDOWN):

                const Uint8 *keystates = SDL_GetKeyboardState(NULL);
                if(keystates[SDL_SCANCODE_R])
                    randomFILL();
                
                if(keystates[SDL_SCANCODE_RETURN]){
                    if(pause){
                        std::cout << "Game State Unpaused" << std::endl;
                        pause = false;
                    } else {
                        std::cout << "Game State Paused" << std::endl;
                        pause = true;
                    }
                }
                if(keystates[SDL_SCANCODE_S]){
                    if(pen){
                        pen = false;
                    } else{
                        pen = true;
                    }
                }
                
                break;             
        }
    }
}

void draw(){

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) &&
        SDL_RenderClear(renderer);

    for(int i=0;i<mapH;i++){
        for(int j=0;j<mapW;j++){
            cellMap[i][j].drawCellRect(renderer);
        }
    }
    
    SDL_RenderPresent(renderer);
}

void update(){

    for(int i=0;i<mapH;i++){
        for(int j=0;j<mapW;j++){
            cellMap[i][j].updateSelf();
        }
    }
    for(int i=0;i<mapH;i++){
        for(int j=0;j<mapW;j++){
            cellMap[i][j].updateStatus(cellMap);
        }
    }
}

void randomFILL(void){
    std::cout << "RANDOM FILL\n";
    int live = 0;
    for(int i=0; i<mapH;i++){
        for(int j=0; j<mapW;j++){
            live = (rand() % 12 == 3);
            if (live){
                cellMap[i][j].statusAlive(cellMap);
            }
        }
    }
    draw(); 
}
