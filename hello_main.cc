#include "gui.h"
#include "graph.h"
#include <gtkmm-3.0/gtkmm.h>
#include <iostream>

int main(int argc, char* argv[]) {
    auto app =
        Gtk::Application::create("org.gtkmm.graph");

    std::cout << "hello" << std::endl ;
    HelloGraph helolgraph;
    return app->run(helolgraph);
}
