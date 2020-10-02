#ifndef GTKMM_GUI_H
#define GTKMM_GUI_H

#include "graph.h"

#include <gtkmm.h>
#include <cairo.h>
#include <gtkmm/box.h>
#include <gtkmm/container.h>
#include <gtkmm/entry.h>
#include <gtkmm/grid.h>
#include <gtkmm/hvbox.h>
#include <gtkmm/hvpaned.h>
#include <gtkmm/widget.h>
#include <gtkmm/window.h>

class TreeArea : public Gtk::DrawingArea
{
private:
    // double node_radius;
    // double line_width;
    inline int width() const;
    inline int height() const;

    Graph& graph;

public:
    typedef const Cairo::RefPtr<Cairo::Context>& CairoRef;

    TreeArea(Graph& ref);
    virtual ~TreeArea();

    // bool draw_circle(CairoRef cr, int circle_cx, int circle_cy, double radius);
    // bool draw_text(CairoRef& cr, int text_cx, int text_cy, const char *text);

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    // bool draw_node(CairoRef cr, int x, int y, const char *label);
    // bool draw_line(CairoRef cr, int start_x, int start_y, int end_x, int end_y);
};

class HelloGraph;
class ActivityArea : public Gtk::Grid
{
private:

public:
    ActivityArea(HelloGraph& hg);
    std::string get_node_text();
    std::string get_src_text();
    std::string get_dest_text();

protected:
    Gtk::Button m_but_add_node;
    Gtk::Button m_but_del_node;
    Gtk::Button m_but_add_edge;
    Gtk::Button m_but_del_edge;

    Gtk::Entry m_entry_node;
    Gtk::Entry m_entry_src;
    Gtk::Entry m_entry_dest;


};

class HelloGraph : public Gtk::Window
{
private:
    Graph graph;

public:
    HelloGraph();
    ~HelloGraph();

    void add_node();
    void del_node();
    void add_edge();
    void del_edge();

protected:
    void on_button_clicked();

    Gtk::Paned m_pan;

    TreeArea     treeArea;
    ActivityArea activityArea;
    
};

#endif
