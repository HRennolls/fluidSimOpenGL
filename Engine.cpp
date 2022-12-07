#define IX(x, y, z) ((x) + (y) * N + (z) * N * N)

struct FluidSquare {
    int size;
    float dt;
    float diff;
    float visc;

    float* s;
    float* density;

    float* Vx;
    float* Vy;

    float* Vx0;
    float* Vy0;
};
typedef struct FluidSquare FluidSquare;


FluidSquare* FluidCubeCreate(int size, int diffusion, int viscosity, float dt)
{
    FluidSquare* square = new FluidSquare;
    int N = size;

    square->size = size;
    square->dt = dt;
    square->diff = diffusion;
    square->visc = viscosity;

    square->s = new float[N * N]();
    square->density = new float[N * N]();

    square->Vx = new float[N * N]();
    square->Vy = new float[N * N]();

    square->Vx0 = new float[N * N]();
    square->Vy0 = new float[N * N]();

    return square;
}


void FluidSquareDelete(FluidSquare* square)
{
    delete(square->s);
    delete(square->density);

    delete(square->Vx);
    delete(square->Vy);

    delete(square->Vx0);
    delete(square->Vy0);

    delete(square);
}

void FluidSquareAddDensity(FluidSquare* square, int x, int y, int z, float amount)
{
    int N = square->size;
    square->density[IX(x, y, z)] += amount;
}

void FluidSquareAddVelocity(FluidSquare* square, int x, int y, int z, float amountX, float amountY, float amountZ)
{
    int N = square->size;
    int index = IX(x, y, z);

    square->Vx[index] += amountX;
    square->Vy[index] += amountY;
}
