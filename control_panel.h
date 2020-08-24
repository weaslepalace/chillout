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
#include <gtkmm/checkbutton.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/label.h>
#include <gtkmm/eventbox.h>

/**
 *	
 */
class ControlPanel : public Gtk::Window
{
	public:
	ControlPanel(BreakList& break_list);
	virtual ~ControlPanel();
	Gtk::Window *win;	

	protected:
	Glib::RefPtr<Gtk::Builder>	builder;

	BreakList& break_list;
	Gtk::TreeView *view_break_list;
//	Gtk::Expander *exp_show_list;
	Gtk::Button *btn_add;
	Gtk::Popover *pop_add_break;	
	Gtk::SpinButton *spn_hour;
	Gtk::SpinButton *spn_min;
	Gtk::SpinButton *spn_duration;
	Gtk::SpinButton *spn_reoccuring_count;
	Gtk::RadioButton *rad_relative;
	Gtk::RadioButton *rad_absolute;
	Gtk::Label *lbl_break_desc;
	Gtk::Button *btn_add_commit;
	Gtk::EventBox *evt_box_warning;
	Gtk::Label *lbl_warning;
	Gtk::Label *lbl_break_cnt;

	void handle_add_click();
	void handle_rad_relative_select();
	void handle_rad_absolute_select();
	void handle_chk_reoccuring_select();
	void handle_add_spins();
	bool handle_min_spin_output();
	bool handle_evt_box_warning(GdkEventCrossing *evt);
	void handle_add_commit();

	private:
	std::pair<int, int> get_hhmm_local();
	Glib::ustring compose_break_description(
		int hour,
		int min,
		int dur,
		int cnt,
		bool absoulte);
};



#endif // CHILL_OUT_CONTROL_PANEL
