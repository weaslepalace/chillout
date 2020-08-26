//#include "front_panel.h"
#include "chill_out.h"
#include <iostream>

int main(int argc, char *argv[])
{

	auto app = Gtk::Application::create(
		argc,
		argv,
		"org.weaslepalace.chillout");

	ChillOut chill_out;

	return app->run(*chill_out.front_panel.win);
}
