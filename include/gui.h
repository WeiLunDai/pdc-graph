#ifndef GTKMM_GUI_H
#define GTKMM_GUI_H

#include "graph.h"

#include <fstream>
#include <gtkmm.h>
#include <cairo.h>
#include <gtkmm/box.h>
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
    inline int width() const;
    inline int height() const;

    HelloGraph* hg;

public:
    typedef const Cairo::RefPtr<Cairo::Context>& CairoRef;

    TreeArea(HelloGraph& hg);
    virtual ~TreeArea();

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

};

class HelloGraph : public Gtk::Window
{
private:
    std::ofstream out;

public:
    std::shared_ptr<Graph> graph;
    HelloGraph();
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
    Gtk::Paned m_pan;

    TreeArea treeArea;

    Gtk::Frame m_frame_node;
    Gtk::Grid m_grid_node;
    Gtk::Entry m_entry_node;
    Gtk::Button m_but_add_node;
    Gtk::Button m_but_del_node;

    Gtk::Frame m_frame_edge;
    Gtk::Grid m_grid_edge;
    Gtk::Entry m_entry_src;
    Gtk::Entry m_entry_dest;
    Gtk::Button m_but_add_edge;
    Gtk::Button m_but_del_edge;

    Gtk::Frame m_frame_adv;
    Gtk::VBox m_vbox_adv;
    Gtk::Button m_but_dfs;
    Gtk::Button m_but_bfs;
    Gtk::Button m_but_clear;
    Gtk::Button m_but_export;

    Gtk::VBox m_vbox;
};

#endif
