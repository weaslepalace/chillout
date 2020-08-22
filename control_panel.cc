#include "control_panel.h"

#include <iostream>
#include <iomanip>
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
	builder->get_widget("evt_box_warning", evt_box_warning);
	builder->get_widget("lbl_warning", lbl_warning);
	
	rad_relative->signal_toggled()
		.connect(sigc::mem_fun(
			*this,
			&ControlPanel::handle_rad_relative_select));
	
	rad_absolute->signal_toggled()
		.connect(sigc::mem_fun(
			*this,
			&ControlPanel::handle_rad_absolute_select));
	spn_hour->signal_value_changed()
		.connect(sigc::mem_fun(
			*this,
			&ControlPanel::handle_add_spins));
	spn_min->signal_value_changed()
		.connect(sigc::mem_fun(
			*this,
			&ControlPanel::handle_add_spins));
	spn_duration->signal_value_changed()
		.connect(sigc::mem_fun(
			*this,
			&ControlPanel::handle_add_spins));
	spn_min->signal_output()
		.connect(sigc::mem_fun(
			*this,
			&ControlPanel::handle_min_spin_output));
	evt_box_warning->signal_enter_notify_event()
		.connect(sigc::mem_fun(
			*this,
			&ControlPanel::handle_evt_box_warning));
		
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


/**
 *	Handle the click signal for the ADD button
 */
void ControlPanel::handle_add_click()
{
	//Initialize start time spin buttons with local time
	std::pair<int, int> hhmm = get_hhmm_local();	
	spn_hour->set_value(hhmm.first * 1.0);
	spn_min->set_value(hhmm.second * 1.0);	
	lbl_warning->hide();

	pop_add_break->popup();	
}


void ControlPanel::handle_rad_relative_select()
{
	chk_reoccuring->show();
	spn_hour->set_value(0.0);
	spn_min->set_value(5.0);
}


void ControlPanel::handle_rad_absolute_select()
{
	chk_reoccuring->set_active(false);
	chk_reoccuring->hide();
	std::pair<int, int> hhmm = get_hhmm_local();
	spn_hour->set_value(hhmm.first * 1.0);
	spn_min->set_value(hhmm.second * 1.0);
}


void ControlPanel::handle_chk_reoccuring_select()
{
	int hour = (int)spn_hour->get_value();
	int min = (int)spn_min->get_value();
	int dur = (int)spn_duration->get_value();

	Glib::ustring desc = Glib::ustring::compose(
		"Add %1 minute break every %2:%3 from now",
		dur,
		hour,
		Glib::ustring::format(std::setfill(L'0'), std::setw(2), min));
}


void ControlPanel::handle_add_spins()
{
	int hour = (int)spn_hour->get_value();
	int min = (int)spn_min->get_value();
	int dur = (int)spn_duration->get_value();
	
	Glib::ustring desc;
	if(rad_absolute->get_active())
	{
		desc = Glib::ustring::compose(
			"Add %1 minute break at %2:%3",
			dur,
			hour,
			Glib::ustring::format(std::setfill(L'0'), std::setw(2), min));
	}
	else if(!chk_reoccuring->get_active())
	{
		desc = Glib::ustring::compose(
			"Add %1 minute break %2:%3 from now",
			dur,
			hour,
			Glib::ustring::format(std::setfill(L'0'), std::setw(2), min));
	}
	else
	{
		desc = Glib::ustring::compose(
			"Add %1 minute break every %2:%3",
			dur,
			hour,
			Glib::ustring::format(std::setfill(L'0'), std::setw(2), min));
	}

	lbl_break_desc->set_label(desc);
}


bool ControlPanel::handle_min_spin_output()
{
	int val = (int)spn_min->get_value();
	auto mm = Glib::ustring::format(std::setfill(L'0'), std::setw(2), val);
	spn_min->set_text(mm);
	return true;
}


bool ControlPanel::handle_evt_box_warning(GdkEventCrossing *evt)
{
	lbl_warning->show();
	return true;
}
