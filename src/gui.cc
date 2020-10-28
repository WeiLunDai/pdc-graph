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
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/entry.h>
#include <gtkmm/enums.h>
#include <gtkmm/widget.h>
#include <gtkmm/window.h>
#include <ios>
#include <iostream>
#include <fstream>
#include <cmath>
#include <memory>

/*----------------------------------*/

TreeArea::TreeArea(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder) :
    Gtk::DrawingArea(cobject)
{
    HelloGraph *win;
    refBuilder->get_widget_derived("window", win);
    this->hg = win;
}

TreeArea::~TreeArea()
{
}

bool TreeArea::on_draw(CairoRef cr)
{
    auto image = Gdk::Pixbuf::create_from_file("./title.png");
    size_t width = get_allocation().get_width();
    size_t height = get_allocation().get_height();

    Gdk::Cairo::set_source_pixbuf(cr, image, (width - image->get_width())/2, (height - image->get_height())/2);

    cr->paint();

    return true;
}

/*----------------------------*/

HelloGraph::HelloGraph(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder) : 
    Gtk::Window(cobject), graph(new Graph())
{
    refBuilder->get_widget_derived("tree_area", treeArea);
    refBuilder->get_widget("node_add", b_node_add);
    refBuilder->get_widget("node_del", b_node_del);
    refBuilder->get_widget("edge_add", b_edge_add);
    refBuilder->get_widget("edge_del", b_edge_del);

    refBuilder->get_widget("node_entry", e_node);
    refBuilder->get_widget("edge_src", e_edge_src);
    refBuilder->get_widget("edge_dest", e_edge_dest);

    refBuilder->get_widget("dfs", b_dfs);
    refBuilder->get_widget("bfs", b_bfs);
    refBuilder->get_widget("clear", b_clear);
    refBuilder->get_widget("export", b_export);

    if (b_node_add)
        b_node_add->signal_clicked().connect(
                sigc::mem_fun(*this, &HelloGraph::add_node));
    if (b_node_del)
        b_node_del->signal_clicked().connect(
                sigc::mem_fun(*this, &HelloGraph::del_node));
    if (b_edge_add)
        b_edge_add->signal_clicked().connect(
                sigc::mem_fun(*this, &HelloGraph::add_edge));
    if (b_edge_del)
        b_edge_del->signal_clicked().connect(
                sigc::mem_fun(*this, &HelloGraph::del_edge));
    if (b_dfs)
        b_dfs->signal_clicked().connect(
                sigc::mem_fun(*this, &HelloGraph::dfs));
    if (b_bfs)
        b_bfs->signal_clicked().connect(
                sigc::mem_fun(*this, &HelloGraph::bfs));
    if (b_clear)
        b_clear->signal_clicked().connect(
                sigc::mem_fun(*this, &HelloGraph::clear));
    if (b_export)
        b_export->signal_clicked().connect(
                sigc::mem_fun(*this, &HelloGraph::exportData));

    redraw();
};
    // show_all_children();
void HelloGraph::redraw()
{
    graph->exportPng();
    treeArea->queue_draw();
}

void HelloGraph::add_node()
{
    graph->add( e_node->get_text() );
    redraw();
}

void HelloGraph::del_node()
{
    graph->del( e_node->get_text() );
    redraw();
}

void HelloGraph::add_edge()
{
    graph->add(e_edge_src->get_text(), e_edge_dest->get_text());
    redraw();
}

void HelloGraph::del_edge()
{
    graph->del(e_edge_src->get_text(), e_edge_dest->get_text());
    redraw();
}

HelloGraph::~HelloGraph()
{
}

void HelloGraph::dfs()
{
    Graph* tmp_graph = graph->depthFirstSearch( e_node->get_text() );

    graph.reset();
    graph = std::shared_ptr<Graph>(new Graph(*tmp_graph));

    redraw();
}

void HelloGraph::bfs()
{
    Graph* tmp_graph = graph->breathFirstSearch( e_node->get_text() );

    graph.reset();
    graph = std::shared_ptr<Graph>(new Graph(*tmp_graph));

    redraw();
}

void HelloGraph::clear()
{
    graph.reset();
    graph = std::shared_ptr<Graph>(new Graph());

    redraw();
}

void HelloGraph::exportData()
{
    std::ofstream out("output.txt", std::ios::out | std::ios::app);
    out << graph->info();
    out.close();
}

GraphApp::GraphApp() :
    build(Gtk::Builder::create())
{
    try {
        build->add_from_file("./builder.ui");
    }
    catch (const Gtk::BuilderError& ex)
    {
        std::cerr << "FileError: " << ex.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    build->get_widget_derived("window", window);
}

int GraphApp::run() 
{
    return Gtk::Application::run(*window);
}

