#include <iostream>
#include "helloworld.h"
#include <gtkmm-3.0/gtkmm.h>

int main(int argc, char* argv[]) {
    auto app = 
        Gtk::Application::create("org.gtkmm.example");

    //Gtk::Window window;
    HelloWorld helolworld;
    return app->run(helolworld);
}
