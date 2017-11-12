#include <iostream>
#include <cstdlib>
#include "RtMidi.h"
int main()
{
    RtMidiIn *midiIn = new RtMidiIn();
    auto portCount = midiIn->getPortCount();
    std::cout << "midi portCount=" << portCount << std::endl;

    auto portName = midiIn->getPortName(0);
    std::cout << "port_name=" << portName << std::endl;
    
    return 0;
}
