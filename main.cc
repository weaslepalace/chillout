#include "control_panel.h"
#include <iostream>

int main(int argc, char *argv[])
{
	auto app = Gtk::Application::create(
		argc,
		argv,
		"org.weaslepalace.chillout");

	BreakList break_list;
	break_list.ref_break_list = Gtk::ListStore::create(break_list);
	break_list.add_break(14, 0, 5);
	ControlPanel control_panel(break_list);

	return app->run(*control_panel.win);
}
