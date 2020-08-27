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
}


ChillOut::~ChillOut() = default;


void ChillOut::start_timer()
{
	timer_conn = Glib::signal_timeout().connect(
		sigc::mem_fun(*this, &ChillOut::handle_timer_tick), 1000);
}


bool ChillOut::handle_timer_tick()
{
	front_panel.countdown_to_next_break(   //Rename this
		percent,
		hour % 24,
		min % 60,
		sec % 60); 
	
	//This is just a test.
	//	The actual code should pull up the next break, and compute the percent
	//	of time remaining before the next break, then compute the hours,
	//	minutes, and seconds until the next break.
	percent += 0.1;
	if(percent >= 1.0)
	{
		percent = 0.0;
	}
	sec++;
	min = sec / 60;
	hour = min / 60;
	//End test.

	return true;
}


