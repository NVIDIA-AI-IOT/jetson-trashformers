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
            STOP,
            DIAGONAL_DORSAL_LEFT,
            DIAGONAL_DORSAL_RIGHT,
            DIAGONAL_FRONTAL_LEFT,
            DIAGONAL_FRONTAL_RIGHT

        };


        BehaviorController(SerialHandler* serialHandler);
        virtual ~BehaviorController();

        void ChangeState(ControllerState state);


    private:
        ZigbController* m_zigb;
        SerialHandler* m_serialHandler;
};

#endif

