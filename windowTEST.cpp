
#include <ios>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <iostream>

#define WIDTH 1200
#define HEIGHT 700

bool run, isFull;

int lastFrame, fps, frameCount, timerFPS;

SDL_Renderer* renderer;
SDL_Window* window;

void fpsToConsole(int* lastTime);

class Cell{
    private:
        bool alive;
        int liveNeighbours;
    public:
        Cell(bool alive, int liveNeighbours);
        int getNeighbors();
        int isAlive();
        void updateSelf();
};

void update(){
    if(isFull) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    if(!isFull) SDL_SetWindowFullscreen(window, 0);

}

void input(){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT) run = 0;
    }
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    if (keystates[SDL_SCANCODE_ESCAPE]) run = false;
    if (keystates[SDL_SCANCODE_F1]) isFull = !isFull;

}

void draw(){

    

    //FPS UPDATE
    frameCount++;
    int timerFPS = SDL_GetTicks() - lastFrame;
    if(timerFPS<(1000/60)){
        SDL_Delay((1000/60) - timerFPS);
    }

    SDL_RenderPresent(renderer);
}

int main(void){
    run = 1;
    isFull = 0;
    static int lastTime = 0;

    //SDL SET UP
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) std::cout << "SDL INIT FAILED" << std::endl;
    if(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0)
        std::cout << "Window and Renderer Fail";
    
    SDL_ShowCursor(SDL_ENABLE);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    //SDL SET UP

    while(run){
        fpsToConsole(&lastTime);



        update();
        input();
        draw();
    }
    //SDL Clean Up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void fpsToConsole(int* lastTime){
    lastFrame = SDL_GetTicks();
        if (lastFrame >= (*lastTime+1000)){
            *lastTime = lastFrame;
            fps = frameCount;
            frameCount = 0;
        }
        std::cout << fps << std::endl;
}