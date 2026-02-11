#include <raylib.h>
#include <math.h>

#define FPS 60
#define WIDTH 1200
#define HEIGHT 800
#define SQUARESIZE 100

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

void Square_init(Square *S)
{
    S->p[0] = (COORD3DF){ 0.5,  0.5,  0.5};
    S->p[1] = (COORD3DF){-0.5,  0.5,  0.5};
    S->p[2] = (COORD3DF){-0.5, -0.5,  0.5};
    S->p[3] = (COORD3DF){ 0.5, -0.5,  0.5};

    S->p[4] = (COORD3DF){ 0.5,  0.5, -0.5};
    S->p[5] = (COORD3DF){-0.5,  0.5, -0.5};
    S->p[6] = (COORD3DF){-0.5, -0.5, -0.5};
    S->p[7] = (COORD3DF){ 0.5, -0.5, -0.5};
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

// double convert(double p, int size)
// {
//     return p += size;
// }

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


int main()
{
    Vector2 EscapePoint = {WIDTH/2-100, -HEIGHT/2+100};
    Vector2 Zero = {WIDTH/2, HEIGHT/2};
    Square S;
    Square_init(&S);
    Square_Connexion Sc;
    Square_Connexion_init(&Sc);

    InitWindow(WIDTH, HEIGHT, "3D rendering");
    SetTargetFPS(FPS);

    const double dt = 1.f/FPS;
    double dz = 1;
    double angle = 0;
    while (!WindowShouldClose()) {
	Vector2 PosMouse = {GetTouchX(), GetTouchY()};
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && ((PosMouse.x > 0 && PosMouse.x < WIDTH) && (PosMouse.y > 0 && PosMouse.y < HEIGHT))) {
	    EscapePoint.x = PosMouse.x - WIDTH/2;
	    EscapePoint.y = PosMouse.y - HEIGHT/2;
	}
	// dz    += 1.f*dt;
	angle += 1.f*M_PI*dt;
	BeginDrawing();
	ClearBackground(BLACK);

	DrawCircle(EscapePoint.x + WIDTH/2, EscapePoint.y + HEIGHT/2, 10, WHITE);

	DrawLine(Zero.x - EscapePoint.x, Zero.y, Zero.x + EscapePoint.x, Zero.y, WHITE);
	DrawLine(Zero.x, Zero.y - EscapePoint.y, Zero.x, Zero.y + EscapePoint.y, WHITE);
	DrawLine(Zero.x - EscapePoint.x, Zero.y - EscapePoint.y, Zero.x + EscapePoint.x, Zero.y + EscapePoint.y, WHITE);

	Vector2 ratio = {EscapePoint.x/WIDTH, EscapePoint.y/HEIGHT};
	Square buf;
	int shape[] = {4,4,2,2,2,2};

	for (int i = 0; i < 8; i++) {
	    buf.p[i].x = S.p[i].x; buf.p[i].y = S.p[i].y; buf.p[i].z = S.p[i].z;
	    XZ_rotation(&buf.p[i], angle);
	    Z_translation(&buf.p[i], dz);
	    DrawCircle(Zero.x + convert(buf.p[i]).x*SQUARESIZE+buf.p[i].z*SQUARESIZE*ratio.x, Zero.y + convert(buf.p[i]).y*SQUARESIZE+buf.p[i].z*SQUARESIZE*ratio.y, 10, RED); //bon
	}

	for (int i = 0; i < 6; i++) {
	    for (int j = 0; j < shape[i]; j++) {
		COORD3DF temp[2] = {S.p[Sc.p[i][j]], S.p[Sc.p[i][(j+1)%4]]};

		XZ_rotation(&temp[0], angle);
		XZ_rotation(&temp[1], angle);
		Z_translation(&temp[0], dz);
		Z_translation(&temp[1], dz);
		
		DrawLine(Zero.x + convert(temp[0]).x*SQUARESIZE+temp[0].z*SQUARESIZE*ratio.x, Zero.y + convert(temp[0]).y*SQUARESIZE+temp[0].z*SQUARESIZE*ratio.y, Zero.x + convert(temp[1]).x*SQUARESIZE+temp[1].z*SQUARESIZE*ratio.x, Zero.y + convert(temp[1]).y*SQUARESIZE+temp[1].z*SQUARESIZE*ratio.y, GREEN); // bon
	    }
	}
	
	DrawFPS(20, 20);
	EndDrawing();
    }
    CloseWindow();
    return 0;
}
