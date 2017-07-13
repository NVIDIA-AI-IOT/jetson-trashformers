#ifndef CONTROLS_H_
#define CONTROLS_H_

/* ALL ZIGB CONTROLS */
static const int BUTTON_U = 1;
static const int BUTTON_D = 2;
static const int BUTTON_L = 4;
static const int BUTTON_R = 8;
static const int BUTTON_1 = 16;
static const int BUTTON_2 = 32;
static const int BUTTON_3 = 64;
static const int BUTTON_4 = 128;
static const int BUTTON_5 = 256;
static const int BUTTON_6 = 512;

/* HUMAN READABLE VERSION OF ZIGB CONTROLS  */
static const int BUTTON_WALK_FORWARD            = BUTTON_U;
static const int BUTTON_WALK_BACKWARD           = BUTTON_D;
static const int BUTTON_WALK_FORWARD_LEFT       = BUTTON_U + BUTTON_L;
static const int BUTTON_WALK_FORWARD_RIGHT      = BUTTON_U + BUTTON_R; 
static const int BUTTON_TURN_LEFT               = BUTTON_L;
static const int BUTTON_TURN_RIGHT              = BUTTON_R;
static const int BUTTON_SIDESTEP_LEFT           = BUTTON_L + BUTTON_5;
static const int BUTTON_SIDESTEP_RIGHT          = BUTTON_R + BUTTON_5;
static const int BUTTON_SIDESTEP_FAST_LEFT      = BUTTON_L + BUTTON_5 + BUTTON_6;
static const int BUTTON_SIDESTEP_FAST_RIGHT     = BUTTON_R + BUTTON_5 + BUTTON_6;
static const int BUTTON_DIAGONAL_FRONTAL_LEFT   = BUTTON_L + BUTTON_U + BUTTON_5;
static const int BUTTON_DIAGONAL_FRONTAL_RIGHT  = BUTTON_R + BUTTON_U + BUTTON_5;
static const int BUTTON_DIAGONAL_DORSAL_LEFT    = BUTTON_L + BUTTON_D + BUTTON_5;
static const int BUTTON_DIAGONAL_DORSAL_RIGHT   = BUTTON_R + BUTTON_D + BUTTON_5;
static const int BUTTON_GET_UP_FACING_UP        = BUTTON_1 + BUTTON_U;
static const int BUTTON_GET_UP_FACING_DOWN      = BUTTON_1 + BUTTON_D;
static const int BUTTON_BEND_DOWN 		        = BUTTON_3;

#endif //CONTROLS_H_
