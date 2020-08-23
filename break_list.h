#ifndef CHILL_OUT_BREAK_LIST
#define CHILL_OUT_BREAK_LIST

#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/liststore.h>

/**
 *
 */
class BreakList : public Gtk::TreeModelColumnRecord
{
	public:
	BreakList();
	virtual ~BreakList();
	bool add_break(int hour, int min, int dur);
	Glib::RefPtr<Gtk::ListStore> ref();	

	Gtk::TreeModelColumn<int> id;
	Gtk::TreeModelColumn<Glib::ustring> start_time;
	Gtk::TreeModelColumn<int> duration;

	Glib::RefPtr<Gtk::ListStore> ref_break_list;

	private:
	unsigned int next_id;
};

#endif //CHILL_OUT_BREAK_LIST
