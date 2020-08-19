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

	builder->get_widget("pop_add_break", pop_add_break);
	builder->get_widget("spn_start_hour", spn_hour);
	builder->get_widget("spn_start_min", spn_min);
	builder->get_widget("rad_start_rel", rad_relative);
	builder->get_widget("rad_start_abs", rad_absolute);
	builder->get_widget("chk_start_reoccuring", chk_reoccuring);
	builder->get_widget("spn_duration", spn_duration);
	builder->get_widget("lbl_break_description", lbl_break_desc);
	builder->get_widget("btn_add_commit", btn_add_commit);
	
	rad_relative->signal_toggled()
		.connect(sigc::mem_fun(
			*this,
			&ControlPanel::handle_rad_relative_select));
	
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
	//Initialize start time spin buttons with local time
	std::pair<int, int> hhmm = get_hhmm_local();	
	spn_hour->set_value(hhmm.first * 1.0);
	spn_min->set_value(hhmm.second * 1.0);

	pop_add_break->popup();	
}


void ControlPanel::handle_rad_relative_select()
{
	chk_reoccuring->show();
	spn_hour->set_value(0.0);
	spn_min->set_value(5.0);
}
