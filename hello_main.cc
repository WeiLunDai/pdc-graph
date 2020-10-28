#include "glibmm/refptr.h"
#include "gui.h"
#include "graph.h"
#include "sigc++/functors/mem_fun.h"
#include <gtkmm-3.0/gtkmm.h>
#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/window.h>
#include <iostream>


int main(int argc, char* argv[]) {
    // auto app =
    //     Gtk::Application::create("org.gtkmm.graph");

    GraphApp GA;
    return GA.run();
    //return app->run(ma);
}
