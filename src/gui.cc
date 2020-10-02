#include "gui.h"
#include "gdkmm/pixbuf.h"
#include "giomm/inputstream.h"
#include "giomm/resolver.h"
#include "glibmm/refptr.h"
#include "sigc++/functors/mem_fun.h"
#include "sigc++/functors/ptr_fun.h"
#include <gdkmm.h>
#include <glibmm.h>
#include <glib.h>
#include <gtkmm/aboutdialog.h>
#include <gtkmm/entry.h>
#include <gtkmm/enums.h>
#include <gtkmm/widget.h>
#include <iostream>
#include <cmath>

/*----------------------------------*/

TreeArea::TreeArea(Graph& ref) :
    graph(ref)
    //node_radius(25.0), line_width(4.0)
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
    graph.exportPngByte();

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

// bool TreeArea::draw_node(CairoRef cr, int x, int y, const char *label)
// {
//     cr->save();
//
//     cr->set_source_rgb(100, 230, 160);
//     draw_circle(cr, x, y, node_radius);
//     draw_text(cr, x, y, label);
//
//     cr->restore();
//
//     return true;
// }
//
// bool TreeArea::draw_line(CairoRef cr, int start_x, int start_y, int end_x, int end_y)
// {
//     cr->save();
//
//     cr->set_line_width(line_width);
//     cr->set_source_rgb(5, 140, 50);
//     cr->move_to(start_x, start_y);
//     cr->line_to(end_x, end_y);
//
//     cr->restore();
//     cr->stroke();
//
//     return true;
// }
//
// bool TreeArea::draw_circle(CairoRef cr, int circle_cx, int circle_cy, double radius)
// {
//     cr->save();
//
//     cr->set_line_width(line_width);
//     cr->arc(circle_cx, circle_cy, radius, 0.0, 2.0 * M_PI);
//     cr->set_source_rgba(0.0, 0.3, 0.8, 0.6);
//     cr->fill_preserve();
//
//     cr->restore();
//     cr->stroke();
//
//     return true;
// }

// bool TreeArea::draw_text(CairoRef cr, int text_cx, int text_cy, const char *text)
// {
//     Pango::FontDescription font;
//     font.set_family("Monospace");
//     font.set_weight(Pango::WEIGHT_BOLD);
//
//     auto layout = create_pango_layout(std::string(text));
//
//     int text_width;
//     int text_height;
//
//     layout->get_pixel_size(text_width, text_height);
//
//     cr->move_to((text_cx - text_width/2),
//                 (text_cy - text_height/2));
//
//     layout->show_in_cairo_context(cr);
//     cr->stroke();
//
//     return true;
// };

ActivityArea::ActivityArea(HelloGraph& hg) :
    m_but_add_node("add node"),
    m_but_del_node("del node"),
    m_but_add_edge("add edge"),
    m_but_del_edge("del edge")
{
    attach(m_entry_node, 0, 0, 1, 1);
    attach(m_entry_src, 0, 1, 1, 1);
    attach(m_entry_dest, 1, 1, 1, 1);

    attach(m_but_add_node, 0, 2, 1, 1);
    attach(m_but_del_node, 1, 2, 1, 1);
    attach(m_but_add_edge, 0, 3, 1, 1);
    attach(m_but_del_edge, 1, 3, 1, 1);

    m_but_add_node.signal_clicked().connect(sigc::mem_fun( hg ,&HelloGraph::add_node));
    m_but_del_node.signal_clicked().connect(sigc::mem_fun( hg ,&HelloGraph::del_node));
    m_but_add_edge.signal_clicked().connect(sigc::mem_fun( hg ,&HelloGraph::add_edge));
    m_but_del_edge.signal_clicked().connect(sigc::mem_fun( hg ,&HelloGraph::del_edge));

    m_entry_node.set_text("node");
    m_entry_src.set_text("src");
    m_entry_dest.set_text("dest");
}

std::string ActivityArea::get_node_text()
{
    return m_entry_node.get_text();
}

std::string ActivityArea::get_src_text()
{
    return m_entry_src.get_text();
}

std::string ActivityArea::get_dest_text()
{
    return m_entry_dest.get_text();
}

/*----------------------------*/

HelloGraph::HelloGraph() : 
    m_pan(Gtk::ORIENTATION_HORIZONTAL),
    treeArea(graph),
    activityArea(*this)
    //m_box_top(Gtk::ORIENTATION_HORIZONTAL, 0),
    //m_Vbox(Gtk::ORIENTATION_VERTICAL),
{
    // init 
    set_title("TreeDisplay");
    set_default_size(600, 400); 
    set_border_width(10);

    // add layout
    add(m_pan);
    // m_pan.add1(m_Vbox);
    m_pan.add1(activityArea);
    m_pan.add2(treeArea);

    show_all_children();
}

HelloGraph::~HelloGraph()
{
    Gtk::Widget* en =  m_pan.get_child1();
    Glib::ustring str = ((Gtk::Entry*)en)->get_text();
    Node new_node = Node(str.c_str());
    graph.add(new_node);
}

void HelloGraph::add_node()
{
    Node node = Node( activityArea.get_node_text() );

    graph.add(node);
    treeArea.queue_draw();
}

void HelloGraph::del_node()
{
    Node node = Node( activityArea.get_node_text() );
    
    graph.del(node);
    treeArea.queue_draw();
}

void HelloGraph::add_edge()
{
    Node src_node = Node( activityArea.get_src_text() );
    Node dest_node = Node( activityArea.get_dest_text() );
    src_node.add(dest_node);
    Edge edge = Edge(src_node);

    graph.add(edge);
    //std::cout << graph.info() << std::endl;

    treeArea.queue_draw();
}

void HelloGraph::del_edge()
{
    Node src_node = Node( activityArea.get_src_text() );
    Node dest_node = Node( activityArea.get_dest_text() );
    src_node.add(dest_node);
    Edge edge = Edge(src_node);

    graph.del(edge);
    //std::cout << graph.info() << std::endl;

    treeArea.queue_draw();
}

void HelloGraph::on_button_clicked() 
{
    std::cout << "hello" << std::endl;
}

