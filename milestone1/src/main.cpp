#include <iostream>
#include <fstream>
#include <string>
#include "engine.h"
#include "scene.h"

int main(int argc, char **argv)
{
    if (argc != 4)
    {
      std::cout<<"Usage: milestonel_exe <environment> ‹lights> ‹bezier>" << std::endl;
          exit (1);
    }
    Scene *scene = new Scene(argv[1], argv[2], argv[3]);
    Engine *engine = new Engine();
    engine->SetScene(scene);
    engine->Run();
}
