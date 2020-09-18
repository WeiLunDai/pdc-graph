#ifndef GTKMM_EXAMPLE_HELLOWORLD_H
#define GTKMM_EXAMPLE_HELLOWORLD_H

#include <gtkmm-3.0/gtkmm.h>
#include <gtkmm-3.0/gtkmm/box.h>

class HelloWorld : public Gtk::Window 
{
    public:
        HelloWorld();
        ~HelloWorld();

    protected:
        void on_button_clicked();

    Gtk::Box    m_box_top;
    Gtk::Box    m_Hbox;
    Gtk::Box    m_Vbox;
    Gtk::Button insert_button;
    Gtk::Button delete_button;

};

#endif
