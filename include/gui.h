#ifndef GTKMM_GUI_H
#define GTKMM_GUI_H

#include "glibmm/refptr.h"
#include "graph.h"

#include <fstream>
#include <gtkmm.h>
#include <cairo.h>
#include <gtkmm/box.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/container.h>
#include <gtkmm/entry.h>
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>
#include <gtkmm/hvbox.h>
#include <gtkmm/hvpaned.h>
#include <gtkmm/paned.h>
#include <gtkmm/widget.h>
#include <gtkmm/window.h>
#include <memory>

class HelloGraph;
class TreeArea : public Gtk::DrawingArea
{
private:
    HelloGraph* hg;

public:
    typedef const Cairo::RefPtr<Cairo::Context>& CairoRef;

    TreeArea(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);
    virtual ~TreeArea();

protected:
    bool on_draw(CairoRef cr) override;

};

class HelloGraph : public Gtk::Window
{
private:
    std::shared_ptr<Graph> graph;

    void redraw();
public:
    HelloGraph();
    HelloGraph(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);
    ~HelloGraph();

    void add_node();
    void del_node();
    void add_edge();
    void del_edge();

    void dfs();
    void bfs();
    void clear();
    void exportData();

protected:
    TreeArea *treeArea;

    Gtk::Button* b_node_add;
    Gtk::Button* b_node_del;
    Gtk::Button* b_edge_add;
    Gtk::Button* b_edge_del;

    Gtk::Entry* e_node;
    Gtk::Entry* e_edge_src;
    Gtk::Entry* e_edge_dest;

    Gtk::Button* b_dfs;
    Gtk::Button* b_bfs;
    Gtk::Button* b_clear;
    Gtk::Button* b_export;

};

class GraphApp : public Gtk::Application
{
    private:
    Glib::RefPtr<Gtk::Builder> build;
    HelloGraph *window;

    public:
    GraphApp();
    int run();
};

#endif
