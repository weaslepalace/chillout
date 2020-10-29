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
	void set_ref();	
	Gtk::TreeModelColumn<int> id;
	Gtk::TreeModelColumn<Glib::ustring> start_time;
	Gtk::TreeModelColumn<int> duration;
	std::time_t get_last_break();
	std::time_t get_next_break();
	void activate();

	private:
	Glib::RefPtr<Gtk::ListStore> ref_break_list;
	unsigned int next_id;
	std::time_t last_break;
	std::time_t next_break;
};

#endif //CHILL_OUT_BREAK_LIST
