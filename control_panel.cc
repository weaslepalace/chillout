#include "control_panel.h"

#include <iostream>
#include <ctime>


ControlPanel::ControlPanel(BreakList& break_list)
{
	builder = Gtk::Builder::create();
	builder->add_from_file("control.glade");
	
	builder->get_widget("win_control", win);

	builder->get_widget("tree_break_list", view_break_list);
	view_break_list->set_model(break_list.ref());
	view_break_list->append_column("Starting at", break_list.start_time);
	view_break_list->append_column("Duration", break_list.duration);

	builder->get_widget("btn_add", btn_add);
	btn_add->signal_clicked()
		.connect(sigc::mem_fun(*this, &ControlPanel::handle_add_click));
}


ControlPanel::~ControlPanel() = default;


std::pair<int, int> ControlPanel::get_hhmm_local()
{
	std::time_t now = std::time(nullptr);
	std::tm now_local;
	localtime_r(&now, &now_local);
	
	std::pair<int, int> hhmm;
	hhmm.first = now_local.tm_hour;
	hhmm.second = now_local.tm_min;

	return hhmm;
}


void ControlPanel::handle_add_click()
{
	Gtk::Popover *pop_add_break;	
	builder->get_widget("pop_add_break", pop_add_break);
	
	std::pair<int, int> hhmm = get_hhmm_local();	

	Gtk::SpinButton *spn_hour;
	Gtk::SpinButton *spn_min;
	builder->get_widget("spn_start_hour", spn_hour);
	builder->get_widget("spn_start_min", spn_min);
	spn_hour->set_value(hhmm.first * 1.0);
	spn_min->set_value(hhmm.second * 1.0);

	pop_add_break->popup();	
}
