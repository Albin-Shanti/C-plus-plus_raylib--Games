#include<raylib.h>

Color Darkgreen = { 1, 122, 48, 255 };
Color green = { 4, 184, 73, 255 };
Color Light_green = { 72, 250, 140, 255 };
Color yellow = { 243, 213, 91, 255 };


int playerScore = 0;
int computerScore = 0;

// creating the ball class
class Ball {

public:
	float x, y;
	int speedX, speedY;
	int radius;

	void Draw() {

		DrawCircle(x, y, radius, yellow);
	}

	void Update() {

		x += speedX;
		y += speedY;
		
		//creating the ball movement and bouncing characteristic.

		if (y + radius >= GetScreenHeight() || y - radius <= 0) {

			speedY *= -1;
		}
		
		// the score calculating system;
		if (x + radius >= GetScreenWidth()) {
			
			computerScore++;
			resetBall();
		}
		if (x - radius <= 0) {

			playerScore++;
			resetBall();
		}
	}

	void resetBall() {

		x = GetScreenWidth() / 2;
		y = GetScreenHeight() / 2;

		int speedChoices[2] = { -1, 1 };
		speedX *= speedChoices[GetRandomValue(0, 1)];
		speedY *= speedChoices[GetRandomValue(0, 1)];
	}

};

//Player controlled paddles

class Paddle {

public:

	float x, y, width, height;
	int speed;

	void Draw() {

		DrawRectangleRounded(Rectangle{ x, y, width, height }, 0.8, 0, WHITE);
	}
	void Update(){

		// Move the paddle according to player input.
		if (IsKeyDown(KEY_UP)) {

			y = y - speed;
		}
		if (IsKeyDown(KEY_DOWN)) {

			y = y + speed;
		}
		limitMovement();
	}

protected:
	
	// Limits the paddle movement inside the game window.
	void limitMovement() {

		if (y <= 0) {
			y = 0;
		}
		if (y + height >= GetScreenHeight()) {
			y = GetScreenHeight() - height;
		}
	}
};

// creating the computer controlled paddles

class CpuPaddle: public Paddle {

public:

	void Update(int ball_y) {

		// moves the paddle according to the ball movement
		if (y + height / 2 > ball_y) {

			y = y - speed;
		}
		if (y + height / 2 <= ball_y) {

			y = y + speed;
		}
		limitMovement();
	}

};

// Object creation for the classes

Ball ball;
Paddle player;
CpuPaddle computer;

// main function
int main() {


	const int screenWidth = 1200;
	const int screenHeight = 800;

	// Initializing the window
	InitWindow(screenWidth,screenHeight, "PONG");
	SetTargetFPS(60);

	//Initilizing the class attributes.

	ball.radius = 20;
	ball.x = screenWidth / 2;
	ball.y = screenHeight / 2;
	ball.speedX = 7;
	ball.speedY = 7;

	player.width = 25;
	player.height = 120;
	player.x = screenWidth - player.width - 10;
	player.y = screenHeight / 2 - player.height / 2;
	player.speed = 6;

	computer.width = 25;
	computer.height = 120;
	computer.x = 10;
	computer.y = screenHeight / 2 - computer.height / 2;
	computer.speed = 6;

	//Main game loop
	
	while (!WindowShouldClose()) {
		
		BeginDrawing();
		
		// updating the game assets
		ball.Update();
		player.Update();
		computer.Update(ball.y);

		//Checking for collisions
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player.x, player.y, player.width, player.height })) {

			ball.speedX *= -1;
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ computer.x, computer.y, computer.width, computer.height })) {

			ball.speedX *= -1;
		}
		
		// clears the previous objects in the background at a 60 fps framerate
		ClearBackground(Darkgreen);
		DrawRectangle(screenWidth / 2, 0, screenWidth / 2, screenHeight, green);
		DrawCircle(screenWidth / 2, screenHeight / 2, 150, Light_green);
		
		// drawing the game assets
		DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
		ball.Draw();
		computer.Draw();
		player.Draw();
		DrawText(TextFormat("%i", computerScore), screenWidth / 4 - 20, 20, 80, WHITE);
		DrawText(TextFormat("%i", playerScore), 3 * screenWidth / 4 - 20, 20, 80, WHITE);
		EndDrawing();
	
	}

	CloseWindow();
	return 0;
}