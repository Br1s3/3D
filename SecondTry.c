#include <raylib.h>
#include <math.h>

#define WIDTH 1200
#define HEIGHT 800
#define FPS 200

#define FOVY_PERSPECTIVE    45.0f


int main()
{
    Camera camera;
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = FOVY_PERSPECTIVE;
    camera.projection = CAMERA_PERSPECTIVE;



    // = { , , , ,  };

    InitWindow(WIDTH, HEIGHT, "3D rendering");
    SetTargetFPS(60);

    double t = 0;
    for (int i = 0; !WindowShouldClose(); t += 0.1) {
	i = 10*sin(t);
	
	BeginDrawing();
	{
	    ClearBackground(BLACK);
	    BeginMode3D(camera);
	    
            DrawCube((Vector3){-4.0f, 0.0f, 2.0f}, 2.0f, 5.0f, 2.0f, RED);

	    // camera.position.x = i;
	    camera.target.x = i;
	    // camera.target.z = i;
	    
	    // camera.up.z = i;

	    EndMode3D();
	}
	
	DrawFPS(20, 20);
	EndDrawing();
    }

    CloseWindow();
    return 0;    
}
