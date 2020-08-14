#include "break_list.h"

BreakList::BreakList()
{
	add(id);
	add(start_time);
	add(duration);
	next_id = 0;
}

BreakList::~BreakList() = default;


/**
 *
 */
Glib::RefPtr<Gtk::ListStore> BreakList::ref()
{
	return ref_break_list;
}


/**
 *
 */
void BreakList::add_break(
	Glib::ustring new_start_time,
	Glib::ustring new_duration)
{
	//TODO: Make sure args are properly formatted time strings
	
	Gtk::TreeModel::iterator iter = ref_break_list->append();
	Gtk::TreeModel::Row row = *iter;
	row[id] = next_id;
	row[start_time] = new_start_time;
	row[duration] = new_duration;
	
	next_id++;
}
