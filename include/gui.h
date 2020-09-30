#ifndef GTKMM_GUI_H
#define GTKMM_GUI_H

#include <gtkmm.h>
#include <cairo.h>
#include <gtkmm/entry.h>
#include <gtkmm/hvbox.h>
#include <gtkmm/hvpaned.h>

class TreeArea : public Gtk::DrawingArea
{
private:
    double node_radius;
    double line_width;
    inline int width() const;
    inline int height() const;

public:
    typedef const Cairo::RefPtr<Cairo::Context>& CairoRef;

    TreeArea();
    virtual ~TreeArea();

    bool draw_circle(CairoRef cr, int circle_cx, int circle_cy, double radius);
    bool draw_text(CairoRef& cr, int text_cx, int text_cy, const char *text);

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    bool draw_node(CairoRef cr, int x, int y, const char *label);
    bool draw_line(CairoRef cr, int start_x, int start_y, int end_x, int end_y);
};

class HelloGraph : public Gtk::Window 
{
private:
    std::string title;
    int width;
    int height;
    int border_width;
public:
    HelloGraph();
    ~HelloGraph();

protected:
    void on_button_clicked();

    Gtk::Box    m_box_top;
    Gtk::Box    m_Vbox;
    TreeArea    treeArea;
    Gtk::Button insert_button;
    Gtk::Button delete_button;
    Gtk::Paned m_pan;
    Gtk::HBox m_box_insert;
    Gtk::HBox m_box_delete;
    Gtk::Entry m_entry_insert;
    Gtk::Entry m_entry_delete;

};

#endif
