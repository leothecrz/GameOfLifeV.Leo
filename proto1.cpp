
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <cstdlib>
#include <time.h>
#include <iostream>

#define WIDTH  100
#define HEIGHT 37

void userInput(void);

void nextGen(void);
void setStatus(int y, int x);
void updateMap(void);
void PRINT(void);

void checkNeighbors(int*, int, int);

int run = 1;
long long int generation = 0;
int tempMap[HEIGHT][WIDTH];
int map[HEIGHT][WIDTH];

int main(int argc, char* argv[]){

    system("clear");

    int random;
    int valid = 0;
    while(!valid){
        std::cout << "Random fill? 1/0: ";
        int in;
        std::cin >> in;
        switch (in) {
        case 1:
            random = 1;
            valid = 1;
            break;
        case 0:
            random = 0;
            valid = 1;
            break;
        default:
            std::cout << "ENTER VALID INPUT!\n\n";
            break;
        };
    }

    if(random){
        int SEED = time(0) + 410;
        srand(SEED);

        for(int i=0; i<HEIGHT;i++){
            for(int j=0; j<WIDTH; j++){
                map[i][j] = (rand() % 2);
                tempMap[i][j] = 0;
            }
        }
    } else {
        userInput();
    }

    PRINT();
    while(run){

        sleep(1);
        nextGen();
        updateMap();
        system("clear");
        PRINT();
    }
    return 0;

}

void updateMap(void){
    int keepGoing = 0;
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            map[i][j] = tempMap[i][j];
            if(map[i][j]){
                keepGoing = 1;
            }
        }
    }
    if(!keepGoing)
        run = 0;
    
}

void PRINT(void){
    std::cout << "\n" << generation << "\n";
    for(int i=0; i<HEIGHT;i++){
        for(int j=0; j<WIDTH;j++){
            if(map[i][j]){
                std::cout << "#";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void nextGen(void){

    for(int i=0; i<HEIGHT;i++){
        for(int j=0; j<WIDTH; j++){
            setStatus(i, j);
        }
    }
    generation++;
}

void setStatus(int y, int x){

    int liveNeighbors = 0;

    checkNeighbors(&liveNeighbors, x, y);
    
    if(map[y][x]){
        if (liveNeighbors > 3 || liveNeighbors < 2){
            tempMap[y][x] = 0;
        } else {
            tempMap[y][x] = 1;
        } 
    } else {
        if (liveNeighbors == 3){
            tempMap[y][x] = 1;
        } else {
            tempMap[y][x] = 0;
        }
    }

    
}

void checkNeighbors(int *liveNeighbors, int x, int y){

    int rightX = x + 1;
    if (x==WIDTH)
        rightX = 0;

    int leftX = x - 1;
    if (x==0)
        leftX = WIDTH;

    int lowerY = y + 1;
    if (y==HEIGHT)
        lowerY = 0;

    int topY = y - 1;
    if (y==0)
        topY = HEIGHT;
    
    if (map[topY][leftX])
        (*liveNeighbors)++;
    if (map[topY][x])
        (*liveNeighbors)++;
    if (map[topY][rightX])
        (*liveNeighbors)++;

    if (map[y][leftX])
        (*liveNeighbors)++;
    if (map[y][rightX])
        (*liveNeighbors)++;
    
    if (map[lowerY][leftX])
        (*liveNeighbors)++;
    if (map[lowerY][x])
        (*liveNeighbors)++;
    if (map[lowerY][rightX])
        (*liveNeighbors)++;
}

void userInput(void){
    
    char c;
    int firstNum = 0;
    int secondNum = 0;
    int getInput = 1;

    while(getInput){
	
	system("clear");
	PRINT();
	
	std::cout << "X: ";
        std::cin >> firstNum;
	std::cout << "Y: ";
	std::cin >> secondNum;
	std::cout << "\n";
	if((secondNum == -1) || (firstNum == -1))
			getInput = 0;
	if(firstNum < WIDTH && secondNum < HEIGHT)
        	map[secondNum][firstNum] = 1;
    }

}
