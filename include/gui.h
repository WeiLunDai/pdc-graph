#ifndef GTKMM_GUI_H
#define GTKMM_GUI_H

#include "graph.h"

#include <gtkmm.h>
#include <cairo.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/widget.h>
#include <gtkmm/window.h>
#include <memory>

class TreeArea : public Gtk::DrawingArea
{
private:
    std::shared_ptr<Graph> graph;

    Gtk::Entry* e_node;
    Gtk::Entry* e_edge_src;
    Gtk::Entry* e_edge_dest;

public:
    typedef const Cairo::RefPtr<Cairo::Context>& RefCairo;
    typedef const Glib::RefPtr<Gtk::Builder>& RefBuilder;

    TreeArea(BaseObjectType* cobject, RefBuilder refBuilder);
    virtual ~TreeArea();

    void redraw();

    void add_node();
    void del_node();
    void add_edge();
    void del_edge();

    void dfs();
    void bfs();
    void clear();
    void exportData();

protected:
    bool on_draw(RefCairo cr) override;

};

class HelloGraph : public Gtk::Window
{
private:

public:
    typedef const Glib::RefPtr<Gtk::Builder>& RefBuilder;

    HelloGraph();
    HelloGraph(BaseObjectType* cobject, RefBuilder refBuilder);
    ~HelloGraph();

protected:
    TreeArea *treeArea;

    Gtk::Button* b_node_add;
    Gtk::Button* b_node_del;
    Gtk::Button* b_edge_add;
    Gtk::Button* b_edge_del;

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
