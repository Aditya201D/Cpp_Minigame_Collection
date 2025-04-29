#include <raylib.h>
#include <iostream>
#include <deque>
#include <raymath.h>
using namespace std;

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;
int offsetValue = 75;       //for creating a decorative boundary around the game screen

double lastUpdateTime = 0;      //will be used to slow down the snake's speed

//this below function ensures that the snake's body will run the function Update() every 200 millisec
//not 60 times per second. The value of interval variable is 0.2
bool eventTriggered(double interval){
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval){
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

bool ElementInDeque(Vector2 element, deque<Vector2> deque){
    for (unsigned int i = 0; i<deque.size(); i++){
        if(Vector2Equals(deque[i], element)){
            return true;
        }
    }
    return false;
}

class Snake{
public:
    deque<Vector2> body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};   //starting points for snake body
    Vector2 direction = {1,0};      //initialising direction of snake
    bool AddSegment = false;

    void Draw(){
        for (unsigned int i = 0; i<body.size(); i++){
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment = Rectangle{offsetValue + x * cellSize, offsetValue + y * cellSize, float(cellSize), float(cellSize)};
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
        }
    }
    void Update(){
        body.push_front(Vector2Add(body[0], direction));

        if(AddSegment == true){
            AddSegment = false;
        } else{
            body.pop_back();
        }
    }

    void Reset(){
        body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};   //resetting points for snake body
        Vector2 direction = {1,0}; 
    }
};

class Food{
public:
    Vector2 position = {5,6};
    Texture2D texture;

    Food(deque<Vector2> snakeBody){
        Image image = LoadImage("Graphics/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos(snakeBody);
    }

    ~Food(){
        UnloadTexture(texture);
    }

    void Draw(){
        DrawTexture(texture, offsetValue + position.x * cellSize, offsetValue+ position.y * cellSize, WHITE);
    }

    Vector2 GenerateRandomCell(){
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount -1);
        return Vector2{x,y};
    }

    Vector2 GenerateRandomPos(deque<Vector2> snakeBody){
        Vector2 position = GenerateRandomCell();
        while(ElementInDeque(position, snakeBody)){
            position = GenerateRandomCell();
        }
        return position;
    }
};

class Game{
public:
    Snake snake = Snake();
    Food food = Food(snake.body);
    bool running = true;
    int score = 0;
    Sound eatSound;
    Sound wallSound;

    Game(){
        InitAudioDevice();
        eatSound = LoadSound("Sounds/eat.mp3");
        wallSound = LoadSound("Sounds/wall.mp3");
    }

    ~Game(){
        UnloadSound(eatSound);
        UnloadSound(wallSound);
        CloseAudioDevice();
    }

    void Draw(){
        food.Draw();
        snake.Draw();
    }

    void Update(){
        if(running){
        snake.Update();
        CheckCollisionWithFood();
        CheckCollisionWithEdges();
        CheckCollisionWithTail();
        }
    }

    void CheckCollisionWithFood(){
        if(Vector2Equals(snake.body[0], food.position)){
            food.position = food.GenerateRandomPos(snake.body);
            snake.AddSegment = true;
            score++;
            PlaySound(eatSound);
        }
    }

    void CheckCollisionWithEdges(){
        if(snake.body[0].x == cellCount || snake.body[0].x == -1){
        GameOver();
        }
        if(snake.body[0].y == cellCount || snake.body[0].y == -1){
        GameOver();
        }
    }

    void CheckCollisionWithTail(){
        deque<Vector2> headlessBody = snake.body;       //creating a new deque by name headlessbody
        headlessBody.pop_front();
        if(ElementInDeque(snake.body[0], headlessBody)){    //we check if the head of the orginal body exists in headless body deque
            GameOver();
        }
    }

    void GameOver(){
        snake.Reset();
        food.position = food.GenerateRandomPos(snake.body);
        running = false;
        score = 0;
        PlaySound(wallSound);
    }
};

int main(){
    cout<<"Starting the game..."<<endl;
    InitWindow(2*offsetValue + cellSize*cellCount, 2*offsetValue + cellSize*cellCount , "Snake Game");
    SetTargetFPS(60);

    Game game = Game();

    while(!WindowShouldClose()){
        BeginDrawing();

        if (eventTriggered(0.2)){
            game.Update();
        }

        if(IsKeyPressed(KEY_UP) && game.snake.direction.y != 1){     //second condition added to ensure 
            game.snake.direction = {0,-1};                          //that snake is not originally moving in the 
            game.running = true;                                    //opposite direction and make the movement smoother
        }                                                           
        if(IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1){
            game.snake.direction = {0,1};
            game.running = true;
        }
        if(IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1){
            game.snake.direction = {-1,0};
            game.running = true;
        }
        if(IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1){
            game.snake.direction = {1,0};
            game.running = true;
        }

        ClearBackground(green);
        DrawRectangleLinesEx(Rectangle{(float)offsetValue-5, (float)offsetValue -5, (float)cellSize*cellCount + 10, (float)cellSize*cellCount + 10}, 5, darkGreen);
        DrawText("Classic Snake", offsetValue - 5, 20, 40, darkGreen);
        DrawText(TextFormat("%i",game.score), offsetValue - 5, offsetValue + cellSize*cellCount + 10, 40, darkGreen);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}