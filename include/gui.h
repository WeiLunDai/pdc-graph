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

    Graph& g;

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

protected:
    Gtk::Button insert_button;
    Gtk::Button delete_button;

    Gtk::Entry m_entry_insert;
    Gtk::Entry m_entry_delete;


};

class HelloGraph : public Gtk::Window
{
private:
    Graph g;

public:
    HelloGraph();
    ~HelloGraph();

    void add_node();
    void del_node();

protected:
    void on_button_clicked();

    // Gtk::Box    m_box_top;

    Gtk::Paned m_pan;

    TreeArea     treeArea;
    ActivityArea activityArea;
    
};

#endif
