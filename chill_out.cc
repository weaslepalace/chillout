#include "chill_out.h"

ChillOut::ChillOut()
	: front_panel(break_list)
{
	//FIXME: This feels clunky
	break_list.set_ref();
	front_panel.bind_break_list();
}


ChillOut::~ChillOut() = default;
