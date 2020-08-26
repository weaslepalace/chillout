#ifndef CHILL_OUT_H
#define CHILL_OUT_H

#include "front_panel.h"
#include "break_list.h"
#include <glibmm/main.h>

class ChillOut
{
	public:
	ChillOut();
	virtual ~ChillOut();
	void start_timer();
	
	FrontPanel front_panel;
	BreakList break_list;

	private:
	sigc::connection timer_conn;
	bool handle_timer_tick();	
};

#endif //CHILL_OUT_H
