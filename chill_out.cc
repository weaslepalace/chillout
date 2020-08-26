#include "chill_out.h"
#include <iostream>

ChillOut::ChillOut()
	: front_panel(break_list)
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
	std::cout << "Tick!" << std::endl;
	return true;
}


