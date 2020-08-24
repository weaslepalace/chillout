//#include "front_panel.h"
#include "chill_out.h"
#include <iostream>

int main(int argc, char *argv[])
{
	ChillOut chill_out;

	auto app = Gtk::Application::create(
		argc,
		argv,
		"org.weaslepalace.chillout");
	return app->run(*chill_out.front_panel.win);
}
