#include <Arduino.h>

#include "custom_colors.h"

#define MAPPER_MIN          0
#define MAPPER_MAX        100

Color::Color() {
    _R = _G = _B = _W = 0;
}

void Color::mapRO(int mapper) {
    // Map from R (255,  0,  0) to O (255,127,  0)
    if ( mapper < MAPPER_MIN || mapper > MAPPER_MAX) {
        return;
    }

    _R = 255;
    _G = map(mapper, MAPPER_MIN, MAPPER_MAX,   0, 127);
    _B = 0;
    _W = 0;
}

void Color::mapOY(int mapper) {
    // Map from O (255,127,  0) to Y (255,255,  0)
    if ( mapper < MAPPER_MIN || mapper > MAPPER_MAX) {
        return;
    }

    _R = 255;
    _G = map(mapper, MAPPER_MIN, MAPPER_MAX, 127, 255);
    _B = 0;
    _W = 0;
}

void Color::mapYG(int mapper) {
    // Map from Y (255,255,  0) to G (  0,255,  0)
    if ( mapper < MAPPER_MIN || mapper > MAPPER_MAX) {
        return;
    }

    _R = map(mapper, MAPPER_MIN, MAPPER_MAX, 255,   0);
    _G = 255;
    _B = 0;
    _W = 0;
}

void Color::mapGB(int mapper) {
    // Map from G (  0,255,  0) to B (  0,  0,255)
    if ( mapper < MAPPER_MIN || mapper > MAPPER_MAX) {
        return;
    }

    _R = 0;
    _G = map(mapper, MAPPER_MIN, MAPPER_MAX, 255,   0);
    _B = map(mapper, MAPPER_MIN, MAPPER_MAX,   0, 255);
    _W = 0;
}

void Color::mapBP(int mapper) {
    // Map from B (  0,  0,255) to P (255,  0,127)
    if ( mapper < MAPPER_MIN || mapper > MAPPER_MAX) {
        return;
    }

    _R = map(mapper, MAPPER_MIN, MAPPER_MAX,   0, 255);
    _G = 0;
    _B = map(mapper, MAPPER_MIN, MAPPER_MAX, 255, 127);
    _W = 0;
}

void Color::mapPR(int mapper) {
    // Map from P (255,  0,127) to R (255,  0,  0)
    if ( mapper < MAPPER_MIN || mapper > MAPPER_MAX) {
        return;
    }

    _R = 255;
    _B = 0;
    _B = map(mapper, MAPPER_MIN, MAPPER_MAX, 127, 0);
    _W = 0;
}

void Color::mapW() {
    // Not sure what real purpose this will serve.
    _R = _G = _B = _W = 255;

}

int Color::return_R() {return _R;}
int Color::return_G() {return _G;}
int Color::return_B() {return _B;}
int Color::return_W() {return _W;}