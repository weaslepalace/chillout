#include "break_list.h"
#include <iomanip>
#include <ctime>


BreakList::BreakList() :
	next_id(0),
	next_break(0),
	last_break(std::time(nullptr))
{
	add(id);
	add(start_time);
	add(duration);

}


BreakList::~BreakList() = default;


void BreakList::set_ref()
{
	ref_break_list = Gtk::ListStore::create(*this);
}


/**
 *
 */
Glib::RefPtr<Gtk::ListStore> BreakList::ref()
{
	return ref_break_list;
}


std::time_t BreakList::get_last_break()
{
	return last_break;
}


std::time_t BreakList::get_next_break()
{
	return next_break;
}


void BreakList::activate()
{
	last_break = next_break;

	//Grab the next break out of the TreeModel
	// I'm so confused.
	// There must be a better way to do this
	Glib::ustring break_start;
	ref_break_list->foreach_iter(
		[&] (const Gtk::TreeModel::iterator &iter)
		{
			Gtk::TreeModel::Row row = *iter;
			break_start = row[start_time];
			ref_break_list->erase(row);
			return true;
		});
		
	struct std::tm local;
	strptime(break_start.data(), "%H:%M", &local);
	next_break = mktime(&local);
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
	bool list_empty = true;
	ref_break_list->foreach_iter(
		[&] (const Gtk::TreeModel::iterator &iter)
		{
			Gtk::TreeModel::Row row = *iter;
			if(new_start_time == row[start_time])
			{
				match_found = true;
				return true;
			}
			list_empty = false;
			return false;
		});
	//Fail if trying to add a duplicate
	if(match_found)
	{
		return false;
	}

	if(list_empty)
	{
		std::time_t now = time(nullptr);
		struct std::tm local; 
		localtime_r(&now, &local);
		local.tm_hour = hour;
		local.tm_min = min;	
		next_break = mktime(&local);
	}

	Gtk::TreeModel::iterator iter = ref_break_list->append();
	Gtk::TreeModel::Row row = *iter;
	row[id] = next_id;
	row[start_time] = new_start_time;
	row[duration] = dur;
	
	next_id++;

	return true;
}
