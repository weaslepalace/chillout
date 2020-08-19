#include "control_panel.h"

int main(int argc, char *argv[])
{
	auto app = Gtk::Application::create(
		argc,
		argv,
		"org.weaslepalace.chillout");

	BreakList break_list;
	break_list.ref_break_list = Gtk::ListStore::create(break_list);
	break_list.add_break("14:00", "5:00");
	ControlPanel control_panel(break_list);
	break_list.add_break("15:00", "5:00");

	return app->run(*control_panel.win);
}
