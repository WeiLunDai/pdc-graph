#include "gui.h"
#include "gdkmm/pixbuf.h"
#include "giomm/resolver.h"
#include "glibmm/refptr.h"
#include "sigc++/functors/mem_fun.h"
#include "sigc++/functors/ptr_fun.h"
#include <gdkmm.h>
#include <glibmm.h>
#include <glib.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/entry.h>
#include <gtkmm/widget.h>
#include <gtkmm/window.h>
#include <ios>
#include <iostream>
#include <fstream>
#include <memory>

/*----------------------------------*/

TreeArea::TreeArea(BaseObjectType* cobject, RefBuilder refBuilder) :
    Gtk::DrawingArea(cobject), graph(std::shared_ptr<Graph>(new Graph()))
{
    refBuilder->get_widget("node_entry", e_node);
    refBuilder->get_widget("edge_src", e_edge_src);
    refBuilder->get_widget("edge_dest", e_edge_dest);

    redraw();
}

TreeArea::~TreeArea()
{
}

bool TreeArea::on_draw(RefCairo cr)
{
    auto image = Gdk::Pixbuf::create_from_file("./title.png");
    size_t width = get_allocation().get_width();
    size_t height = get_allocation().get_height();

    Gdk::Cairo::set_source_pixbuf(cr, image, (width - image->get_width())/2, (height - image->get_height())/2);

    cr->paint();

    return true;
}

void TreeArea::redraw()
{
    graph->exportPng();
    queue_draw();
}

void TreeArea::add_node()
{
    graph->add( e_node->get_text() );
    redraw();
}

void TreeArea::del_node()
{
    graph->del( e_node->get_text() );
    redraw();
}

void TreeArea::add_edge()
{
    graph->add(e_edge_src->get_text(), e_edge_dest->get_text());
    redraw();
}

void TreeArea::del_edge()
{
    graph->del(e_edge_src->get_text(), e_edge_dest->get_text());
    redraw();
}

void TreeArea::dfs()
{
    Graph* tmp_graph = graph->depthFirstSearch( e_node->get_text() );

    graph.reset();
    graph = std::shared_ptr<Graph>(new Graph(*tmp_graph));

    redraw();
}

void TreeArea::bfs()
{
    Graph* tmp_graph = graph->breathFirstSearch( e_node->get_text() );

    graph.reset();
    graph = std::shared_ptr<Graph>(new Graph(*tmp_graph));

    redraw();
}

void TreeArea::clear()
{
    graph.reset();
    graph = std::shared_ptr<Graph>(new Graph());

    redraw();
}

void TreeArea::exportData()
{
    std::ofstream out("output.txt", std::ios::out | std::ios::app);
    out << graph->info();
    out.close();
}

/*----------------------------*/

HelloGraph::HelloGraph(BaseObjectType* cobject, RefBuilder refBuilder) : 
    Gtk::Window(cobject)
{
    refBuilder->get_widget_derived("tree_area", treeArea);
    refBuilder->get_widget("node_add", b_node_add);
    refBuilder->get_widget("node_del", b_node_del);
    refBuilder->get_widget("edge_add", b_edge_add);
    refBuilder->get_widget("edge_del", b_edge_del);

    refBuilder->get_widget("dfs", b_dfs);
    refBuilder->get_widget("bfs", b_bfs);
    refBuilder->get_widget("clear", b_clear);
    refBuilder->get_widget("export", b_export);

    if (b_node_add)
        b_node_add->signal_clicked().connect(
                sigc::mem_fun(treeArea, &TreeArea::add_node));
    if (b_node_del)
        b_node_del->signal_clicked().connect(
                sigc::mem_fun(treeArea, &TreeArea::del_node));
    if (b_edge_add)
        b_edge_add->signal_clicked().connect(
                sigc::mem_fun(treeArea, &TreeArea::add_edge));
    if (b_edge_del)
        b_edge_del->signal_clicked().connect(
                sigc::mem_fun(treeArea, &TreeArea::del_edge));
    if (b_dfs)
        b_dfs->signal_clicked().connect(
                sigc::mem_fun(treeArea, &TreeArea::dfs));
    if (b_bfs)
        b_bfs->signal_clicked().connect(
                sigc::mem_fun(treeArea, &TreeArea::bfs));
    if (b_clear)
        b_clear->signal_clicked().connect(
                sigc::mem_fun(treeArea, &TreeArea::clear));
    if (b_export)
        b_export->signal_clicked().connect(
                sigc::mem_fun(treeArea, &TreeArea::exportData));
};
    // show_all_children();

HelloGraph::~HelloGraph()
{
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

