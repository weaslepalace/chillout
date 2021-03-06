#ifndef CHILL_OUT_FRONT_PANEL
#define CHILL_OUT_FRONT_PANEL

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
#include <gtkmm/levelbar.h>
#include <gtkmm/progressbar.h>

/**
 *	
 */
class FrontPanel : public Gtk::Window
{
	public:
	FrontPanel(BreakList& break_list);
	virtual ~FrontPanel();
	Gtk::Window *win;	
	
	void bind_break_list();
	void update(double percent, int hour, int min, int sec);
 
	protected:
	Glib::RefPtr<Gtk::Builder>	builder;

	BreakList& break_list;
	Gtk::TreeView *view_break_list;
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
	Gtk::LevelBar *bar_next_break;
	Gtk::ProgressBar *pbar_next_break;
	Gtk::Label *lbl_next_brk_cnt;

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
	void initialize_absolute_time();
	Glib::ustring compose_break_description(
		int hour,
		int min,
		int dur,
		int cnt,
		bool absoulte);
};



#endif // CHILL_OUT_FRONT_PANEL
