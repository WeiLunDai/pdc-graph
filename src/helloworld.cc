#include "../include/helloworld.h"
#include <iostream>

HelloWorld::HelloWorld() : 
    m_box_top(Gtk::ORIENTATION_VERTICAL, 0),
    m_Hbox(Gtk::ORIENTATION_HORIZONTAL),
    m_Vbox(Gtk::ORIENTATION_VERTICAL),
    insert_button("Insert item"),
    delete_button("Delete item") 
{
    set_default_size(300, 300);
    set_border_width(10);

    insert_button.signal_clicked().connect(sigc::mem_fun(*this,
                &HelloWorld::on_button_clicked));
    delete_button.signal_clicked().connect(sigc::mem_fun(*this,
                &HelloWorld::on_button_clicked));

    add(m_box_top);
    m_box_top.pack_start(m_Hbox);
    m_box_top.pack_start(m_Vbox);

    m_Hbox.pack_start(insert_button);
    m_Hbox.pack_start(delete_button);

    show_all_children();
    // insert_button.show();
    // delete_button.show();
}

HelloWorld::~HelloWorld()
{
}

void HelloWorld::on_button_clicked() 
{
    std::cout << "Hello World" << std::endl;
}
