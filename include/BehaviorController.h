#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_

#include "ZigbController.h"
#include "Controls.h"
#include "SerialHandler.h"

class BehaviorController {

    public:

        enum class ControllerState {
            WALK_FORWARD,
            WALK_BACKWARD,
            TURN_RIGHT,
            TURN_LEFT,
            STRAFE_LEFT,
            STRAFE_RIGHT,
            DIAGONAL_RIGHT,
            DIAGONAL_LEFT, 
            BEND_DOWN,
            STOP

        };


        BehaviorController(SerialHandler* serialHandler);
        virtual ~BehaviorController();

        void ChangeState(ControllerState state);


    private:
        ZigbController* m_zigb;
        SerialHandler* m_serialHandler;
};

#endif

