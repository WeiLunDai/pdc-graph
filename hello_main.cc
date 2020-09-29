#include "gui_tree.h"
#include "graph.h"
#include <gtkmm-3.0/gtkmm.h>

int main(int argc, char* argv[]) {
    auto app =
        Gtk::Application::create("org.gtkmm.graph");

    //Gtk::Window window;
     HelloGraph helolgraph;
    return app->run(helolgraph);
}
