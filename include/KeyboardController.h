#ifndef KEYBOARDCONTROLLER_H_ 
#define KEYBOARDCONTROLLER_H_

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include "Controls.h"

#include "ZigbController.h"

class KeyboardController{
public:
    KeyboardController(ZigbController* zigb);

    virtual ~KeyboardController();

    void Init();
    void RunInput();
    void Terminate();


private:
    ZigbController *zigb;
    struct termios old_tio, new_tio;
    unsigned char c;

};

#endif //KEYBOARDCONTROLLER_H_
