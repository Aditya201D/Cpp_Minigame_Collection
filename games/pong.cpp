#include <iostream>
#include <raylib.h>
using namespace std;

int player_score = 0;
int cpu_score = 0;

Color Green = Color{38, 185, 154, 255};
Color Dark_green = Color{20, 160, 133, 255};
Color Light_green = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};

class Ball{
public:
float x,y;
int speed_x, speed_y;
int radius;
void Draw(){
    DrawCircle(x,y, radius, YELLOW);
}
void Update(){      //this method will increase the speed of the ball each loop
    x+=speed_x;
    y+=speed_y;

    if(y+radius >=GetScreenHeight() || y - radius <=0){
        speed_y *= -1;
    }
    if(x+radius >= GetScreenWidth()){       //when ball touches the right side of the screen
        cpu_score++;
        ResetBall();
    }
    if(x - radius<=0){      //ball touches the left side of screen
        player_score++;
        ResetBall();
    }
}
void ResetBall(){
    x=GetScreenWidth()/2;
    y=GetScreenHeight()/2;

    int speed_choices[2] = {-1,1};      //setting the direction randomly once the ball restarts from center
    speed_x *= speed_choices[GetRandomValue(0,1)];
    speed_y *= speed_choices[GetRandomValue(0,1)];
}
};

class Paddle{
protected:
void LimitMovement(){
    if(y<=0){
        y=0;
    }
    if(y+height>=GetScreenHeight()){
        y= GetScreenHeight() - height;
    }
}
public:
float x,y;
float width, height;
int speed;

void Draw(){
    DrawRectangleRounded(Rectangle{x,y,width,height},0.8,0, WHITE);
}

void Update(){
    if(IsKeyDown(KEY_UP)){
        y = y-speed;
    }
    if(IsKeyDown(KEY_DOWN)){
        y = y+speed;
    }
    LimitMovement();
}
};

class CPU_Paddle : public Paddle{
public:
void Update(int ball_y){
    if (y+height/2 > ball_y){   //this block will make the AI paddle move upwards
        y = y-speed;
    }
    if (y+height/2 <=ball_y){   //this will make the paddle go down
        y = y+speed;
    }
    LimitMovement();
}
};

Ball ball;
Paddle player;
CPU_Paddle cpu;

int main () {

    cout<<"Starting the game" << endl;
    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "My Pong Game");        //starting up game window
    SetTargetFPS(60);       //defines the game speed, if not used then pc will run the game as fast as possible, which is not good

    ball.radius = 20;
    ball.x = screen_width/2;
    ball.y = screen_height/2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    player.width = 25;
    player.height = 120;
    player.x = screen_width - player.width -10;     //10 pixels is offset from the screen
    player.y = screen_height/2 - player.height/2;
    player.speed = 6;

    cpu.height = 120;
    cpu.width = 25;
    cpu.x = 10;
    cpu.y = screen_height/2 - cpu.height/2;
    cpu.speed =6;

    //this loop runs 60 times per sec
    while(!WindowShouldClose()){
        BeginDrawing();

        //Updating
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        //checking for collisions of the ball with the paddles
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height})){
            ball.speed_x *= -1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})){
            ball.speed_x *= -1;
        }

        ClearBackground(Dark_green);     //this function erases the ball once it moves out of screen 
        DrawRectangle(screen_width/2, 0, screen_height/2, screen_height, Green);
        DrawCircle(screen_width/2, screen_height/2, 150, Light_green);
        DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);
        ball.Draw();
        cpu.Draw();        
        player.Draw();
        DrawText(TextFormat("%i",cpu_score), screen_width/4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i",player_score), 3* screen_width/4 - 20, 20, 80, WHITE);
        
        EndDrawing();
    }

    CloseWindow();  //closing game window
    return 0;
}