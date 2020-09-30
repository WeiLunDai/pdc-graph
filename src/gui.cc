#include "gui.h"
#include "gdkmm/general.h"
#include "gdkmm/pixbuf.h"
#include "glibmm/refptr.h"
#include <glib.h>
#include <gdkmm.h>
#include <iostream>
#include <cmath>

HelloGraph::HelloGraph() : 
    title("TreeDisplay"),
    width(600),
    height(400),
    border_width(10),
    m_box_top(Gtk::ORIENTATION_HORIZONTAL, 0),
    m_Hbox(Gtk::ORIENTATION_HORIZONTAL, 5),
    m_Vbox(Gtk::ORIENTATION_VERTICAL),
    insert_button("Insert item"),
    delete_button("Delete item")
{
    // init 
    set_title(title);
    set_default_size(width, height); 
    set_border_width(border_width);
        
    // connect function
    insert_button.signal_clicked().connect(sigc::mem_fun(*this,
                &HelloGraph::on_button_clicked));
    delete_button.signal_clicked().connect(sigc::mem_fun(*this,
                &HelloGraph::on_button_clicked));

    // add layout
    add(treeArea);
    //add(m_box_top);
    m_box_top.pack_start(m_Hbox);
    m_box_top.pack_start(m_Vbox);

    m_Hbox.pack_start(insert_button);
    m_Hbox.pack_start(delete_button);

    // m_Vbox.pack_start(treeArea);

    show_all_children();
    // insert_button.show();
    // delete_button.show();
}

HelloGraph::~HelloGraph()
{
}

void HelloGraph::on_button_clicked() 
{
    std::cout << "Hello Graph" << std::endl;
}

/*----------------------------------*/

TreeArea::TreeArea() : 
    node_radius(25.0), line_width(4.0)
{
}

TreeArea::~TreeArea()
{
}

inline int TreeArea::width() const
{
    return get_allocation().get_width();
}

inline int TreeArea::height() const
{
    return get_allocation().get_height();
}

bool TreeArea::on_draw(CairoRef cr)
{
    Glib::RefPtr<Gdk::Pixbuf> image = Gdk::Pixbuf::create_from_file("./title.png");

    Gdk::Cairo::set_source_pixbuf(cr, image, (width() - image->get_width())/2, (height() - image->get_height())/2);
    //cr->rectangle(10, 10, image->get_width() + 20, image->get_height() + 20);
    //cr->fill();
    cr->paint();

    return true;
}

// bool TreeArea::on_draw(CairoRef cr)
// {
//     // get region size
//     int width = this->width();
//     int height = this->height();
//
//     draw_node(cr, width/3, height/3, "123");
//     draw_node(cr, width/3 * 2, height/3 * 2, "234");
//
//     return true;
// };

bool TreeArea::draw_node(CairoRef cr, int x, int y, const char *label) 
{
    cr->save();

    cr->set_source_rgb(100, 230, 160);
    draw_circle(cr, x, y, node_radius);
    draw_text(cr, x, y, label);

    cr->restore();

    return true;
}

bool TreeArea::draw_line(CairoRef cr, int start_x, int start_y, int end_x, int end_y)
{
    cr->save();
    
    cr->set_line_width(line_width);
    cr->set_source_rgb(5, 140, 50);
    cr->move_to(start_x, start_y);
    cr->line_to(end_x, end_y);

    cr->restore();
    cr->stroke();

    return true;
}

bool TreeArea::draw_circle(CairoRef cr, int circle_cx, int circle_cy, double radius) 
{
    cr->save();

    cr->set_line_width(line_width);
    cr->arc(circle_cx, circle_cy, radius, 0.0, 2.0 * M_PI);
    cr->set_source_rgba(0.0, 0.3, 0.8, 0.6);
    cr->fill_preserve();

    cr->restore();
    cr->stroke();
    
    return true;
}

bool TreeArea::draw_text(CairoRef cr, int text_cx, int text_cy, const char *text)
{
    Pango::FontDescription font;
    font.set_family("Monospace");
    font.set_weight(Pango::WEIGHT_BOLD);

    auto layout = create_pango_layout(std::string(text));

    int text_width;
    int text_height;

    layout->get_pixel_size(text_width, text_height);

    cr->move_to((text_cx - text_width/2),
                (text_cy - text_height/2));

    layout->show_in_cairo_context(cr);
    cr->stroke();

    return true;
};
