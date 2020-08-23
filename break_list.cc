#include "break_list.h"
#include <iomanip>

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
bool BreakList::add_break(int hour, int min, int dur)
{
	Glib::ustring new_start_time = Glib::ustring::compose(
		"%1:%2",
		hour,
		Glib::ustring::format(std::setfill(L'0'), std::setw(2), min));
	
	//Search for attempts to add duplicates
	bool match_found = false;
	ref_break_list->foreach_iter(
		[&] (const Gtk::TreeModel::iterator &iter)
		{
			Gtk::TreeModel::Row row = *iter;
			if(new_start_time == row[start_time])
			{
				match_found = true;
				return true;
			}
			return false;
		});
	//Fail if trying to add a duplicate
	if(match_found)
	{
		return false;
	}

	Gtk::TreeModel::iterator iter = ref_break_list->append();
	Gtk::TreeModel::Row row = *iter;
	row[id] = next_id;
	row[start_time] = new_start_time;
	row[duration] = dur;
	
	next_id++;

	return true;
}
