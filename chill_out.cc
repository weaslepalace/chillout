#include "chill_out.h"
#include <iostream>

ChillOut::ChillOut() :
	front_panel(break_list),
	percent(0.0),
	hour(0),
	min(0),
	sec(0)
{
	//FIXME: This feels clunky
	break_list.set_ref();
	front_panel.bind_break_list();
	
	//Just a test
	break_list.add_break(16, 39, 1);
	break_list.add_break(17, 41, 1);
}


ChillOut::~ChillOut() = default;


void ChillOut::start_timer()
{
	timer_conn = Glib::signal_timeout().connect(
		sigc::mem_fun(*this, &ChillOut::handle_timer_tick), 1000);
}


bool ChillOut::handle_timer_tick()
{
	std::time_t last = break_list.get_last_break();
	std::time_t next = break_list.get_next_break();
	//Prevent divide-by-zero
	if(next == last)
	{
		return true;
	}
	std::time_t now = std::time(nullptr);

	if(now >= next)
	{
		break_list.activate();
		front_panel.update(1.0, 0, 0, 0);	
	}
	else
	{
		double percent = static_cast<double>(now - last) / (next - last);
		std::time_t until = next - now;	
		int min = until / 60;
		int hour = min / 60;
		front_panel.update(percent, hour % 24, min % 60, until % 60);
	}

	return true;
}


