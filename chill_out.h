#ifndef CHILL_OUT_H
#define CHILL_OUT_H

#include "front_panel.h"
#include "break_list.h"

class ChillOut
{
	public:
	ChillOut();
	virtual ~ChillOut();

	FrontPanel front_panel;
	BreakList break_list;
};

#endif //CHILL_OUT_H
