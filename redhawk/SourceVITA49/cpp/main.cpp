#include <iostream>
#include "ossie/ossieSupport.h"

#include "SourceVITA49.h"
int main(int argc, char* argv[])
{
    SourceVITA49_i* SourceVITA49_servant;
    Component::start_component(SourceVITA49_servant, argc, argv);
    return 0;
}

