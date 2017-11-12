#include <chrono>
#include <cstdlib>
#include <iostream>
#include <signal.h>
#include <thread>

// OSX unix support
#include <unistd.h>

#include "RtMidi.h"
#include <AL/al.h>
#include <AL/alc.h>

void handleWrongByteCount(std::vector<unsigned char>& message){
    std::cout << "weird message. size=" << message.size() << std::endl;
    for(auto const& val: message){
        std::cout << "byte=" << val << std::endl;
    }
}

const unsigned char KEY_DOWN = 144;
const unsigned char KEY_UP = 128;
const unsigned char PAD_DOWN = 153;
const unsigned char OTHER = 176; // can be 1) encoder or 2) control key - check value for down/up 127 down/0
//encoders
// left: 21   right: 28

//pads
//
//      1       2       3       4       5       6       7       8
//    (40)     (41)    (42)    (43)    (48)    (49)    (50)    (51)
//
//      9       10      11      12      13      14      15      16
//    (36)     (37)    (38)    (39)    (44)    (45)    (46)    (47)

// keyboard
// left: 48   right: 72

std::vector<int> speeds;

void playSound(int number){
    int speed = speeds[number];

    std::string cmd = "afplay /Users/kylefritz/Desktop/rtmidi-hello/" + std::to_string(number) + ".wav -r " + std::to_string(speed);

    std::cout << cmd << std::endl;

    system(cmd.c_str());
}

void debug_message(unsigned char controlId, unsigned char mesageType, unsigned char messageInfo){
    std::cout << "controlId=" << (int)controlId << std::endl;
    std::cout << "type=" << (int)mesageType << std::endl;
    std::cout << "value=" << (int)messageInfo << std::endl;
}

int main()
{
    speeds.push_back(1); //dummy
    speeds.push_back(1);
    speeds.push_back(1);
    speeds.push_back(1);
    speeds.push_back(1);

    RtMidiIn *midiin = new RtMidiIn();
    midiin->openPort(0);
    midiin->ignoreTypes(false, false , false);

    std::cout << "Reading from midi port, CTRL+C to quit." << std::endl;

    std::vector<unsigned char> message;
    while(true){
        // read message
        midiin->getMessage(&message);
        if(message.size() == 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(10));
            continue;
        }
        if(message.size() != 3){
            handleWrongByteCount(message);
            continue;
        }

        auto mesageType = message[0];
        auto controlId = message[1];
        auto messageInfo = message[2];

//        debug_message(mesageType, controlId, messageInfo);

        if(mesageType == PAD_DOWN){
            if(controlId == 40){
                playSound(1);
            }
            if(controlId == 41){
                playSound(2);
            }
            if(controlId == 42){
                playSound(3);
            }
            if(controlId == 43){
                playSound(4);
            }
        }
        if(mesageType == OTHER){
            if(controlId == 21){
                speeds[1] = messageInfo/10;
            }
            if(controlId == 22){
                speeds[2] = messageInfo/10;
            }
            if(controlId == 23){
                speeds[3] = messageInfo/10;
            }
            if(controlId == 24){
                speeds[4] = messageInfo/10;
            }
        }
    }
}
