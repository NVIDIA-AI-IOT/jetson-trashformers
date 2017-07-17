#include "KeyboardController.h"

KeyboardController::KeyboardController(ZigbController* zigb) { //CONSTRUCTOR
    this->zigb = zigb;
}


void KeyboardController::Init(){
    tcgetattr(STDIN_FILENO,&old_tio);

    new_tio=old_tio;

    new_tio.c_lflag &=(~ICANON & ~ECHO);

    tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);

}

void KeyboardController::RunInput(){
    while(true){
        //zigb->Stop();
        c = getchar();
        //printf("%d \n", c);

        if(c == ' '){
            printf("Stopping!\n");
            zigb->Stop(); 
        }
        else if(c == 'w'){
            printf("Forward!\n");
            zigb->SendCommand(BUTTON_WALK_FORWARD);
        }
        else if(c == 's'){
            printf("Back!\n");
            zigb->SendCommand(BUTTON_WALK_BACKWARD);
        }
        else if(c == 'a'){
            printf("Turn Left!\n");
            zigb->SendCommand(BUTTON_TURN_LEFT);
        }
        else if(c == 'd'){
            printf("Turn Right!\n");
            zigb->SendCommand(BUTTON_TURN_RIGHT);
        }
        else if(c == 'q'){
            printf("Sidestep Left!\n");
            zigb->SendCommand(BUTTON_SIDESTEP_LEFT); 
        }
        else if(c == 'e'){
            printf("Sidestep Right!\n");
            zigb->SendCommand(BUTTON_SIDESTEP_RIGHT);
        }
        else if(c == 'n'){
            printf("DIAGONOL FRONTAL Left!\n");
            zigb->SendCommand(BUTTON_DIAGONAL_FRONTAL_LEFT);
        }
        else if(c == 'm'){
            printf("DIAGONAL FRONTAL Right!\n");
            zigb->SendCommand(BUTTON_DIAGONAL_FRONTAL_RIGHT);
        }
    }
}

void KeyboardController::Terminate(){
    tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
}

KeyboardController::~KeyboardController() {

}
