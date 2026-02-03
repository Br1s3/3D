#include <unistd.h>
#include <raylib.h>
#include <math.h>

#define LIBGRAPH_IMPLEMENTATION
#include "libgraph.h"

#define FPS 60
#define WIDTH 120
#define HEIGHT 50
#define SIZESQUARE 200


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
    int p[2][4];
} Square_Connexion;


COORD3DF convert(COORD3DF p)
{
    return (COORD3DF){p.x/p.z, p.y/p.z, p.z};
}

void Z_translation(COORD3DF *p, int len, double trans)
{
    for (int i = 0; i < len; i++) {
	p[i].z += trans;
    }
}

void XZ_rotation(COORD3DF *p, int len, double theta)
{
    for (int i = 0; i < len; i++) {
	double c = cos(theta);
	double s = sin(theta);
	p[i].x = p[i].x*c - p[i].z*s;
	p[i].z = p[i].x*s + p[i].z*c;
	// p[i].y = p[i].x*s + p[i].y*c;
    }
}


int main()
{
    Square S;
    Square_Connexion Sc;
    
    S.p[0] = (COORD3DF){0.25, 0.25, 0.25};
    S.p[1] = (COORD3DF){-0.25, 0.25, 0.25};
    S.p[2] = (COORD3DF){0.25, -0.25, 0.25};
    S.p[3] = (COORD3DF){-0.25, -0.25, 0.25};

    S.p[4] = (COORD3DF){0.25, 0.25, -0.25};
    S.p[5] = (COORD3DF){-0.25, 0.25, -0.25};
    S.p[6] = (COORD3DF){0.25, -0.25, -0.25};
    S.p[7] = (COORD3DF){-0.25, -0.25, -0.25};

    Sc.p[0][0] = 0;
    Sc.p[0][1] = 1;
    Sc.p[0][2] = 3;
    Sc.p[0][3] = 2;
    
    Sc.p[1][0] = 4;
    Sc.p[1][1] = 5;
    Sc.p[1][2] = 7;
    Sc.p[1][3] = 6;

    
    char **console = mem_alloc(HEIGHT, WIDTH);

    const double dt = 1.f/FPS;    

    double dz = 1;
    for (double t = 0; t < 10; t+=dt) {
	dz+=dt;
	cons_clear(console, WIDTH, HEIGHT, '.');

	// for (int i = 0; i < 2; i++) {
	//     for (int j = 0; j < 4; j++) {
	// 	buf[0] = convert(S.p[Sc.p[i][j]]);
	// 	buf[1] = convert(S.p[Sc.p[i][j+1]]);
	// 	cons_rect(console, WIDTH, HEIGHT, buf[0].x*(WIDTH/2)-1, buf[0].y*(HEIGHT/2)-1, 2, 2, '@');		
	//     }
	// }
	
	for (int i = 0; i < 2; i++) {
	    int j = 0;
	    COORD3DF buf[2];
	    for (; j < 3; j++) {
		
		// XZ_rotation(&S.p[Sc.p[i][j+1]], 1, dz);
		buf[0] = convert(S.p[Sc.p[i][j]]);
		buf[1] = convert(S.p[Sc.p[i][j+1]]);
		// Z_translation(buf, 2, dz);

		// if (S.p[Sc.p[i][j]].z > 0)
		// cons_ligne(console, WIDTH, HEIGHT, buf[0].x*(WIDTH/2)-1, -buf[0].y*(HEIGHT/2)-1, buf[1].x*(WIDTH/2)-1, -buf[1].y*(HEIGHT/2)-1, '#');
		cons_rect(console, WIDTH, HEIGHT, buf[0].x*(WIDTH/2)-1, buf[0].y*(HEIGHT/2)-1, 2, 2, '@');
	    }
	    // XZ_rotation(&S.p[Sc.p[i][j]], 1, dz);
	    // XZ_rotation(&S.p[Sc.p[i][0]], 1, dz);
	    buf[0] = convert(S.p[Sc.p[i][j]]);
	    // buf[1] = convert(S.p[Sc.p[i][0]]);
	    // Z_translation(buf, 2, dz);
	    
	    // if (S.p[Sc.p[i][j]].z > 0)
	        cons_ligne(console, WIDTH, HEIGHT, buf[0].x*(WIDTH/2)-1, -buf[0].y*(HEIGHT/2)-1, buf[1].x*(WIDTH/2)-1, -buf[1].y*(HEIGHT/2)-1, '#');
	    cons_rect(console, WIDTH, HEIGHT, buf[0].x*(WIDTH/2)-1, buf[0].y*(HEIGHT/2)-1, 2, 2, '@');
	    // printf("{%lf, %lf, %lf}:%lf\n", S.p[i].x, S.p[i].y, S.p[i].z, dz);
	    printf("%d:{%lf, %lf, %lf}:%lf\n", i*4+j, buf[0].x, buf[0].y, S.p[i*4+j].z, dz);
	}
	
	Z_translation(S.p, 8, dt);
	XZ_rotation(S.p, 8, dt);

	usleep(100000);

	print_cons(console, WIDTH, HEIGHT);
    }
    mem_free(console, HEIGHT);
    /*
    InitWindow(WIDTH, HEIGHT, "3D rendering");
    SetTargetFPS(FPS);


    while (!WindowShouldClose()) {
	BeginDrawing();
	ClearBackground(BLACK);

	DrawRectangle(WIDTH/2, HEIGHT/2, SIZESQUARE, SIZESQUARE, RED);
	
	DrawFPS(20, 20);
	EndDrawing();
    }
    CloseWindow();
    */
    return 0;    
}
