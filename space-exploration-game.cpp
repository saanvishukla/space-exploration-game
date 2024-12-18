#include <iostream>

using namespace std;

const int MAX_SIZE = 10; 
const int RESOURCE_POINTS = 20;
const int ENEMY_PENALTY = 10;
const int INITIAL_SCORE = 10;
const int BOSS_SCORE=30;

struct Position {
    int x;
    int y;
};

struct Spaceship {
    Position pos;
    int score;
};

struct Boss {
    Position pos;
    int score;
};

void printMap(const char map[MAX_SIZE][MAX_SIZE], int rows, int cols, const Spaceship& ship) {
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (ship.pos.x == x && ship.pos.y == y) {
                cout << 'F' << ' ';
            } else {
                cout << map[y][x] << ' ';
            }
        }
        cout << endl;
    }
    cout << endl;
}

void initializeGame(Spaceship* ship, Boss* boss, char map[MAX_SIZE][MAX_SIZE], int rows, int cols){
;
    for (int shipRow=0;shipRow<rows;shipRow++)
    {
        for (int shipCol=0;shipCol<cols;shipCol++) 
        {
            if (map[shipRow][shipCol]=='F') 
            {
                ship->pos.x=shipCol;
                ship->pos.y=shipRow;
                ship->score=INITIAL_SCORE;
            }
            else if (map[shipRow][shipCol]=='B') 
            {
                boss->pos.y=shipRow;
                boss->pos.x=shipCol;
                boss->score=BOSS_SCORE;
            }
        }
    }
}
void moveSpaceship(Spaceship* ship, char direction, char map[MAX_SIZE][MAX_SIZE], int rows, int cols) 
{
    {
    int &moveRow=ship->pos.y;
    int &moveCol=ship->pos.x;

    switch (direction) 
    {
        case 'w': 
            if (moveRow-1<0)
            {
                return; 
            }
            if (map[moveRow][moveCol]=='F')
            {
                map[moveRow][moveCol]='.'; 
            }
            moveRow-=1; 
            break;
        case 'a': 
            if (moveCol - 1 < 0) 
            {
                return; 
            }
            if (map[moveRow][moveCol]=='F') 
            {
                map[moveRow][moveCol]='.'; 
            }
            moveCol-=1; 
            break;
        case 's': 
            if (moveRow + 1>=rows) 
            {
                return; 
            }
            if (map[moveRow][moveCol]=='F')
            {
                map[moveRow][moveCol]='.'; 
            }
            moveRow += 1; 
            break;
        case 'd': 
            if (moveCol + 1>=cols) 
            {
                return; 
            }
            if (map[moveRow][moveCol]=='F') 
            {
                map[moveRow][moveCol]='.'; 
            }
            moveCol+=1; 
            break;
        default:
            return; 
    }
}
}

void updateScore(Spaceship* ship, char map[MAX_SIZE][MAX_SIZE]) 
{
    int initialRow = ship->pos.y; 
    int initialCol = ship->pos.x; 

    if (map[initialRow][initialCol]=='R') 
    { 
        ship->score+=RESOURCE_POINTS;
        cout <<"Collected resource! Current score: " <<ship->score<<endl;
        map[initialRow][initialCol]='X'; 
    } 
    else if (map[initialRow][initialCol]=='E') 
    { 
        ship->score-=ENEMY_PENALTY;
        cout <<"Encountered enemy! Current score: "<<ship->score<<endl;
        map[initialRow][initialCol]='X'; 
    }
}

bool checkVictory(const Spaceship* ship, const Boss* boss) {
    if (ship->pos.x==boss->pos.x&&ship->pos.y==boss->pos.y) 
    {
        if (ship->score>=boss->score) 
        {
            return true; 
        }
    }
    return false;
}

int main() {
    Spaceship ship;
    Boss boss;
    char map[MAX_SIZE][MAX_SIZE];
    char moves[100]; 

    int rows, cols;
    cin >> rows >> cols;


    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            cin >> map[y][x];
        }
    }

    cin >> moves;
    cout << "Move Sequence: " << moves << endl;

    initializeGame(&ship, &boss, map, rows, cols);

    cout << "Initial Map:" << endl;
    printMap(map, rows, cols, ship);

    int step = 1;
    for (int i = 0; moves[i] != '\0'; ++i) {
        char move = moves[i];
        cout << "Step " << step++ << ": Move " << move << endl;
        moveSpaceship(&ship, move, map, rows, cols);
        updateScore(&ship, map);
        printMap(map, rows, cols, ship);

        if (ship.score < 0) {
            cout << "Score below 0, game over (death)." << endl;
            break;
        }

        if (checkVictory(&ship, &boss)) {
            cout << "Defeated the BOSS, space adventure successful! Total score: " << ship.score << endl;
            break;
        }
    }

    if (ship.score >= 0 && !checkVictory(&ship, &boss)) {
        cout << "Failed to defeat the BOSS, game over. Total score: " << ship.score << endl;
    }

    return 0;
}