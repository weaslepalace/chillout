//#include "front_panel.h"
#include "chill_out.h"
#include <iostream>

int main(int argc, char *argv[])
{
	auto app = Gtk::Application::create(     //Earned Wisdom:
		argc,                                //Never instantiate an object
		argv,                                //that depends on Gtk without
		"org.weaslepalace.chillout");        //first creating the app

	ChillOut chill_out;
	chill_out.start_timer();

	return app->run(*chill_out.front_panel.win);
}
