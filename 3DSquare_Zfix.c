#include <unistd.h>
#include <raylib.h>
#include <math.h>

#define LIBGRAPH_IMPLEMENTATION
#include "libgraph.h"

#define FPS 60
#define WIDTH 600
#define HEIGHT 600
#define SIZESQUARE 10


typedef struct
{
    double x;
    double y;
    double z;
} COORD3DF;

typedef struct
{
    COORD3DF p[8];
} Square;

typedef struct
{
    int p[6][4];
} Square_Connexion;


COORD3DF convert(COORD3DF p)
{
    return (COORD3DF){p.x/p.z, p.y/p.z, p.z};
}

void Z_translation(COORD3DF *p, double trans)
{
    p->z += trans;
}

void XZ_rotation(COORD3DF *p, double theta)
{
    double c = cos(theta);
    double s = sin(theta);
    COORD3DF buf = {
	.x = p->x*c - p->z*s,
	.z = p->x*s + p->z*c
    };
    p->x = buf.x;
    p->z = buf.z;
}

void Square_init(Square *S)
{
    S->p[0] = (COORD3DF){ 0.25,  0.25,  0.25};
    S->p[1] = (COORD3DF){-0.25,  0.25,  0.25};
    S->p[2] = (COORD3DF){-0.25, -0.25,  0.25};
    S->p[3] = (COORD3DF){ 0.25, -0.25,  0.25};

    S->p[4] = (COORD3DF){ 0.25,  0.25, -0.25};
    S->p[5] = (COORD3DF){-0.25,  0.25, -0.25};
    S->p[6] = (COORD3DF){-0.25, -0.25, -0.25};
    S->p[7] = (COORD3DF){ 0.25, -0.25, -0.25};
}

void Square_Connexion_init(Square_Connexion *Sc)
{
    Sc->p[0][0] = 0;
    Sc->p[0][1] = 1;
    Sc->p[0][2] = 2;
    Sc->p[0][3] = 3;
    
    Sc->p[1][0] = 4;
    Sc->p[1][1] = 5;
    Sc->p[1][2] = 6;
    Sc->p[1][3] = 7;

    Sc->p[2][0] = 0;
    Sc->p[2][1] = 4;
    Sc->p[2][2] = 4;
    Sc->p[2][3] = 4;
    
    Sc->p[3][0] = 1;
    Sc->p[3][1] = 5;
    Sc->p[3][2] = 5;
    Sc->p[3][3] = 5;

    Sc->p[4][0] = 2;
    Sc->p[4][1] = 6;
    Sc->p[4][2] = 6;
    Sc->p[4][3] = 6;

    Sc->p[5][0] = 3;
    Sc->p[5][1] = 7;
    Sc->p[5][2] = 7;
    Sc->p[5][3] = 7;
}


int main()
{
    Square S;
    Square_Connexion Sc;
    int shape[] = {4,4,2,2,2,2};
    Vector2 Zero = {WIDTH/2, HEIGHT/2};    
    Square_init(&S);
    Square_Connexion_init(&Sc);
    
    InitWindow(WIDTH, HEIGHT, "3D rendering");
    SetTargetFPS(FPS);

    const double dt = 1.f/FPS;
    double dz    = 1;
    double angle = 0;
    while (!WindowShouldClose()) {
	dz    += 1*dt;
	angle += 1*M_PI*dt;	
	BeginDrawing();
	ClearBackground(BLACK);
		
	for (int i = 0; i < 8; i++) {
	    COORD3DF buf = S.p[i];
	    XZ_rotation(&buf, angle);
	    Z_translation(&buf, dz);
 	    DrawRectangle(Zero.x + convert(buf).x*(WIDTH/2) - SIZESQUARE/2, Zero.y + convert(buf).y*(-HEIGHT/2) - SIZESQUARE/2, SIZESQUARE, SIZESQUARE, RED);
	}

	for (int i = 0; i < 6; i++) {
	    for (int j = 0; j < shape[i]; j++) {
		COORD3DF buf[2] = {S.p[Sc.p[i][j]], S.p[Sc.p[i][(j+1)%4]]};
		XZ_rotation(&buf[0], angle);
		XZ_rotation(&buf[1], angle);
		Z_translation(&buf[0], dz);
		Z_translation(&buf[1], dz);

		buf[0] = convert(buf[0]);
		buf[1] = convert(buf[1]);
		
		DrawLine(Zero.x + buf[0].x*(WIDTH/2), Zero.y + -buf[0].y*(HEIGHT/2), Zero.x + buf[1].x*(WIDTH/2), Zero.y + -buf[1].y*(HEIGHT/2), GREEN);
	    }
	}
	
	DrawFPS(20, 20);
	EndDrawing();
    }
    CloseWindow();
    
    return 0;
}
