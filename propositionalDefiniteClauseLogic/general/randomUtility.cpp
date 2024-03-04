#include "randomUtility.h"

RandUtil::RandUtil() {
    srand(time(nullptr));
}

// returns a random integer between a and b (inclusive)
int RandUtil::randint(int a, int b) {
    return rand() % (b - a + 1) + a;
}

// returns a random (real) number between a and b (inclusive)
double RandUtil::randnum(double a, double b) {
    double randNumBetween0and1 = (double) rand() / RAND_MAX;
    return a + (b - a) * randNumBetween0and1;
}