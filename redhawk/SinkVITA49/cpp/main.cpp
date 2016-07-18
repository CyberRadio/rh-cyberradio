#include <iostream>
#include "ossie/ossieSupport.h"

#include "SinkVITA49.h"
int main(int argc, char* argv[])
{
    SinkVITA49_i* SinkVITA49_servant;
    Component::start_component(SinkVITA49_servant, argc, argv);
    return 0;
}

