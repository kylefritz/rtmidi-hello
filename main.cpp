#include <chrono>
#include <cstdlib>
#include <iostream>
#include <signal.h>
#include <thread>

// OSX unix support
#include <unistd.h>

#include "RtMidi.h"

int main()
{
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
            std::cout << "weird message. size=" << message.size() << std::endl;
            for(auto const& val: message){
                std::cout << "byte=" << val << std::endl;
            }
            continue;
        }

        auto mesageType = message[0];
        auto controlId = message[1];
        auto messageInfo = message[2];

        // type=144; key down
        // type=128; key up

        // type=153; pad down
        // type=137; pad up

        // type=153; pad down
        // type=137; pad up

        // type=176; rotary encoder; dial control pad (value=127 down; 0 up)
        // type=176; control pad (value=127 down; 0 up)

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

        std::cout << "controlId=" << (int)controlId << std::endl;
        std::cout << "type=" << (int)mesageType << std::endl;
        std::cout << "value=" << (int)messageInfo << std::endl;

        std::cout << std::endl;
    }
}
