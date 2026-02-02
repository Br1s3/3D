#include <raylib.h>

#define WIDTH 1200
#define HEIGHT 800
#define FPS 200
#define SQUARESIZE 100


int main()
{
    Vector2 EscapePoint = {WIDTH/2-100, -HEIGHT/2+100};
    Vector2 Zero = {WIDTH/2, HEIGHT/2};
    
    InitWindow(WIDTH, HEIGHT, "3D rendering");
    SetTargetFPS(200);
    
    while (!WindowShouldClose()) {
	Vector2 PosMouse = {GetTouchX(), GetTouchY()};
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && ((PosMouse.x > 0 && PosMouse.x < WIDTH) && (PosMouse.y > 0 && PosMouse.y < HEIGHT))) {
	    EscapePoint.x = PosMouse.x - WIDTH/2;
	    EscapePoint.y = PosMouse.y - HEIGHT/2;
	}
	BeginDrawing();
	ClearBackground(BLACK);

	DrawCircle(EscapePoint.x + WIDTH/2, EscapePoint.y + HEIGHT/2, 10, WHITE);

	DrawLine(Zero.x - EscapePoint.x, Zero.y, Zero.x + EscapePoint.x, Zero.y, WHITE);
	DrawLine(Zero.x, Zero.y - EscapePoint.y, Zero.x, Zero.y + EscapePoint.y, WHITE);
	DrawLine(Zero.x - EscapePoint.x, Zero.y - EscapePoint.y, Zero.x + EscapePoint.x, Zero.y + EscapePoint.y, WHITE);


	Vector2 ratio = {EscapePoint.x/WIDTH, EscapePoint.y/HEIGHT};
	// square 1
	DrawLine(Zero.x-SQUARESIZE-ratio.x*SQUARESIZE, Zero.y+SQUARESIZE-ratio.y*SQUARESIZE, Zero.x+SQUARESIZE-ratio.x*SQUARESIZE, Zero.y+SQUARESIZE-ratio.y*SQUARESIZE, RED);
	DrawLine(Zero.x-SQUARESIZE-ratio.x*SQUARESIZE, Zero.y-SQUARESIZE-ratio.y*SQUARESIZE, Zero.x+SQUARESIZE-ratio.x*SQUARESIZE, Zero.y-SQUARESIZE-ratio.y*SQUARESIZE, RED);
	DrawLine(Zero.x+SQUARESIZE-ratio.x*SQUARESIZE, Zero.y+SQUARESIZE-ratio.y*SQUARESIZE, Zero.x+SQUARESIZE-ratio.x*SQUARESIZE, Zero.y-SQUARESIZE-ratio.y*SQUARESIZE, RED);
	DrawLine(Zero.x-SQUARESIZE-ratio.x*SQUARESIZE, Zero.y-SQUARESIZE-ratio.y*SQUARESIZE, Zero.x-SQUARESIZE-ratio.x*SQUARESIZE, Zero.y+SQUARESIZE-ratio.y*SQUARESIZE, RED);

	// square 2
	DrawLine(Zero.x-SQUARESIZE+ratio.x*SQUARESIZE, Zero.y+SQUARESIZE+ratio.y*SQUARESIZE, Zero.x+SQUARESIZE+ratio.x*SQUARESIZE, Zero.y+SQUARESIZE+ratio.y*SQUARESIZE, BLUE);
	DrawLine(Zero.x-SQUARESIZE+ratio.x*SQUARESIZE, Zero.y-SQUARESIZE+ratio.y*SQUARESIZE, Zero.x+SQUARESIZE+ratio.x*SQUARESIZE, Zero.y-SQUARESIZE+ratio.y*SQUARESIZE, BLUE);
	DrawLine(Zero.x+SQUARESIZE+ratio.x*SQUARESIZE, Zero.y+SQUARESIZE+ratio.y*SQUARESIZE, Zero.x+SQUARESIZE+ratio.x*SQUARESIZE, Zero.y-SQUARESIZE+ratio.y*SQUARESIZE, BLUE);
	DrawLine(Zero.x-SQUARESIZE+ratio.x*SQUARESIZE, Zero.y-SQUARESIZE+ratio.y*SQUARESIZE, Zero.x-SQUARESIZE+ratio.x*SQUARESIZE, Zero.y+SQUARESIZE+ratio.y*SQUARESIZE, BLUE);

	// Close the square
	DrawLine(Zero.x-SQUARESIZE-ratio.x*SQUARESIZE, Zero.y+SQUARESIZE-ratio.y*SQUARESIZE, Zero.x-SQUARESIZE+ratio.x*SQUARESIZE, Zero.y+SQUARESIZE+ratio.y*SQUARESIZE, GREEN);
	DrawLine(Zero.x-SQUARESIZE-ratio.x*SQUARESIZE, Zero.y-SQUARESIZE-ratio.y*SQUARESIZE, Zero.x-SQUARESIZE+ratio.x*SQUARESIZE, Zero.y-SQUARESIZE+ratio.y*SQUARESIZE, GREEN);
	DrawLine(Zero.x+SQUARESIZE-ratio.x*SQUARESIZE, Zero.y+SQUARESIZE-ratio.y*SQUARESIZE, Zero.x+SQUARESIZE+ratio.x*SQUARESIZE, Zero.y+SQUARESIZE+ratio.y*SQUARESIZE, GREEN);
	DrawLine(Zero.x+SQUARESIZE-ratio.x*SQUARESIZE, Zero.y-SQUARESIZE-ratio.y*SQUARESIZE, Zero.x+SQUARESIZE+ratio.x*SQUARESIZE, Zero.y-SQUARESIZE+ratio.y*SQUARESIZE, GREEN);


	
	DrawFPS(20, 20);
	EndDrawing();
    }
    CloseWindow();
    return 0;
}
