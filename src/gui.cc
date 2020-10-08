#include "gui.h"
#include "gdkmm/device.h"
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
#include <fstream>
#include <cmath>
#include <memory>

/*----------------------------------*/

TreeArea::TreeArea(HelloGraph& hg)
{
    this->hg = &hg;
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
    hg->graph->exportPng();

    Glib::RefPtr<Gdk::Pixbuf> image = Gdk::Pixbuf::create_from_file("./title.png");

    Gdk::Cairo::set_source_pixbuf(cr, image, (width() - image->get_width())/2, (height() - image->get_height())/2);

    cr->paint();

    return true;
}

/*----------------------------*/

HelloGraph::HelloGraph() : 
    graph(new Graph()),
    m_pan(Gtk::ORIENTATION_HORIZONTAL),
    treeArea(*this),
    m_frame_node("Node"),
    m_but_add_node("Add"),
    m_but_del_node("del"),
    m_frame_edge("Edge"),
    m_but_add_edge("Add"),
    m_but_del_edge("Del"),
    m_frame_adv("Advance"),
    m_but_dfs("DFS"),
    m_but_bfs("BFS"),
    m_but_clear("Clear"),
    m_but_export("Export")
{
    out.open("output.txt", std::ios::out);
    // init 
    set_title("TreeDisplay");
    set_default_size(600, 400); 
    set_border_width(10);

    // main layout
    add(m_pan);
    m_pan.add1(m_vbox);
    m_pan.add2(treeArea);

    // left part
    m_vbox.pack_start(m_frame_node);
    m_vbox.pack_start(m_frame_edge);
    m_vbox.pack_start(m_frame_adv);

    // node part
    m_frame_node.add(m_grid_node);
    m_grid_node.attach(m_entry_node, 0, 0, 2, 1);
    m_grid_node.attach(m_but_add_node, 0, 1, 1, 1);
    m_grid_node.attach(m_but_del_node, 1, 1, 1, 1);

    // edge part
    m_frame_edge.add(m_grid_edge);
    m_grid_edge.attach(m_entry_src, 0, 0, 1, 1);
    m_grid_edge.attach(m_entry_dest, 1, 0, 1, 1);
    m_grid_edge.attach(m_but_add_edge, 0, 1, 1, 1);
    m_grid_edge.attach(m_but_del_edge, 1, 1, 1, 1);

    // adv part
    m_frame_adv.add(m_vbox_adv);
    m_vbox_adv.pack_start(m_but_dfs);
    m_vbox_adv.pack_start(m_but_bfs);
    m_vbox_adv.pack_start(m_but_clear);
    m_vbox_adv.pack_start(m_but_export);

    m_but_add_node.signal_clicked().connect(sigc::mem_fun(*this, &HelloGraph::add_node));
    m_but_del_node.signal_clicked().connect(sigc::mem_fun(*this, &HelloGraph::del_node));
    m_but_add_edge.signal_clicked().connect(sigc::mem_fun(*this, &HelloGraph::add_edge));
    m_but_del_edge.signal_clicked().connect(sigc::mem_fun(*this, &HelloGraph::del_edge));
    m_but_dfs.signal_clicked().connect(sigc::mem_fun(*this, &HelloGraph::dfs));
    m_but_bfs.signal_clicked().connect(sigc::mem_fun(*this, &HelloGraph::bfs));
    m_but_clear.signal_clicked().connect(sigc::mem_fun(*this, &HelloGraph::clear));
    m_but_export.signal_clicked().connect(sigc::mem_fun(*this, &HelloGraph::exportData));

    show_all_children();
}

HelloGraph::~HelloGraph()
{
    out.close();
    // Gtk::Widget* en =  m_pan.get_child1();
    // Glib::ustring str = ((Gtk::Entry*)en)->get_text();
    // Node new_node = Node(str.c_str());
    // graph->add(new_node);
}

void HelloGraph::add_node()
{
    Node node = Node( m_entry_node.get_text() );

    graph->add(&node);

    treeArea.queue_draw();
}

void HelloGraph::del_node()
{
    graph->del( m_entry_node.get_text() );

    treeArea.queue_draw();
}

void HelloGraph::add_edge()
{
    graph->add(m_entry_src.get_text(), m_entry_dest.get_text());
    //std::cout << graph.info() << std::endl;

    treeArea.queue_draw();
}

void HelloGraph::del_edge()
{
    graph->del(m_entry_src.get_text(), m_entry_dest.get_text());
    //std::cout << graph.info() << std::endl;

    treeArea.queue_draw();
}

void HelloGraph::dfs()
{
    Node node = Node(m_entry_node.get_text());
    Graph* tmp_graph = graph->depthFirstSearch(&node);

    graph = std::shared_ptr<Graph>(new Graph(*tmp_graph));
    //*tmp_graph = graph->depthFirstSearch(node);
    //delete(graph);
    //graph = tmp_graph;
    std::cout << tmp_graph->info();

    treeArea.queue_draw();
}

void HelloGraph::bfs()
{
    Node node = Node(m_entry_node.get_text());
    Graph* tmp_graph = graph->breathFirstSearch(&node);

    graph = std::shared_ptr<Graph>(new Graph(*tmp_graph));
    // delete(graph);
    // graph = tmp_graph;
    std::cout << tmp_graph->info();

    treeArea.queue_draw();
}

void HelloGraph::clear()
{
    graph.reset();
    graph = std::shared_ptr<Graph>(new Graph());

    treeArea.queue_draw();
}

void HelloGraph::exportData()
{
    out << graph->info();
}

