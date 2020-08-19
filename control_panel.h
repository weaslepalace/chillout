#ifndef CHILL_OUT_CONTROL_PANEL
#define CHILL_OUT_CONTROL_PANEL

#include "break_list.h"
#include <gtkmm/window.h>
#include <gtkmm/builder.h>
#include <gtkmm/revealer.h>
#include <gtkmm/expander.h>
#include <gtkmm/treeview.h>
//#include <gtkmm/liststore.h>
#include <gtkmm/treeviewcolumn.h>
#include <gtkmm/popover.h>
#include <gtkmm/spinbutton.h>

/**
 *	
 */
class ControlPanel : public Gtk::Window
{
	public:
//	ControlPanel();
	ControlPanel(BreakList& break_list);
	virtual ~ControlPanel();
	Gtk::Window *win;	

	protected:
	Glib::RefPtr<Gtk::Builder>	builder;

//	BreakList& break_list;
	Gtk::TreeView *view_break_list;
//	Gtk::Expander *exp_show_list;
	Gtk::Button *btn_add;

	void handle_add_click();

	private:
	std::pair<int, int> get_hhmm_local();
};


#endif // CHILL_OUT_CONTROL_PANEL
