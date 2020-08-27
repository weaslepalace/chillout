#include "front_panel.h"

#include <iostream>
#include <iomanip>
#include <ctime>

//TODO: Add a check for durations longer that the break period for reoccuring breaks
FrontPanel::FrontPanel(BreakList& bl)
	: break_list(bl)
{
	builder = Gtk::Builder::create();
	builder->add_from_file("front_panel.glade");
	
	builder->get_widget("win_front_panel", win);

	builder->get_widget("tree_break_list", view_break_list);

	builder->get_widget("btn_add", btn_add);
	btn_add->signal_clicked()
		.connect(sigc::mem_fun(*this, &FrontPanel::handle_add_click));

	builder->get_widget("pop_add_break", pop_add_break);
	builder->get_widget("spn_start_hour", spn_hour);
	builder->get_widget("spn_start_min", spn_min);
	builder->get_widget("rad_start_rel", rad_relative);
	builder->get_widget("rad_start_abs", rad_absolute);
	builder->get_widget("spn_duration", spn_duration);
	builder->get_widget("lbl_break_description", lbl_break_desc);
	builder->get_widget("btn_add_commit", btn_add_commit);
	builder->get_widget("evt_box_warning", evt_box_warning);
	builder->get_widget("lbl_warning", lbl_warning);
	builder->get_widget("spn_reoccuring_count", spn_reoccuring_count);
	builder->get_widget("lbl_break_cnt", lbl_break_cnt);
	builder->get_widget("bar_next_break", bar_next_break);
	builder->get_widget("lbl_next_brk_cnt", lbl_next_brk_cnt);
	
	rad_relative->signal_toggled()
		.connect(sigc::mem_fun(
			*this,
			&FrontPanel::handle_rad_relative_select));
	rad_absolute->signal_toggled()
		.connect(sigc::mem_fun(
			*this,
			&FrontPanel::handle_rad_absolute_select));
	spn_hour->signal_value_changed()
		.connect(sigc::mem_fun(*this, &FrontPanel::handle_add_spins));
	spn_min->signal_value_changed()
		.connect(sigc::mem_fun(*this, &FrontPanel::handle_add_spins));
	spn_duration->signal_value_changed()
		.connect(sigc::mem_fun(*this, &FrontPanel::handle_add_spins));
	spn_reoccuring_count->signal_value_changed()
		.connect(sigc::mem_fun(*this, &FrontPanel::handle_add_spins));
	spn_min->signal_output()
		.connect(sigc::mem_fun(
			*this,
			&FrontPanel::handle_min_spin_output));
	evt_box_warning->signal_enter_notify_event()
		.connect(sigc::mem_fun(
			*this,
			&FrontPanel::handle_evt_box_warning));
		
	btn_add_commit->signal_clicked()
		.connect(sigc::mem_fun(*this, &FrontPanel::handle_add_commit));
}


FrontPanel::~FrontPanel() = default;


std::pair<int, int> FrontPanel::get_hhmm_local()
{
	std::time_t now = std::time(nullptr);
	std::tm now_local;
	localtime_r(&now, &now_local);
	
	std::pair<int, int> hhmm;
	hhmm.first = now_local.tm_hour;
	hhmm.second = now_local.tm_min;

	return hhmm;
}


Glib::ustring FrontPanel::compose_break_description(
	int hour,
	int min,
	int dur,
	int cnt,
	bool absolute)
{
	Glib::ustring desc;
	Glib::ustring mm = Glib::ustring::format(
		std::setfill(L'0'),
		std::setw(2),
		min);

	if(absolute)
	{
		desc = Glib::ustring::compose(
			"Add %1 minute break at %2:%3",
			dur,
			hour,
			mm);
	}
	else if(1 == cnt)
	{
		desc = Glib::ustring::compose(
			"Add %1 minute break %2:%3 from now",
			dur,
			hour,
			mm);
	}
	else
	{
		desc = Glib::ustring::compose(
			"Add %1 breaks for %2 minute%3 every %4:%5",
			cnt,
			dur,
			dur > 1 ? "s" : "",
			hour,
			mm);
	}

	return desc;
}


void FrontPanel::initialize_absolute_time()
{
	//Add 5 minutes to the current time to display as the default value
	std::pair<int, int> hhmm = get_hhmm_local();
	hhmm.first = hhmm.first + ((hhmm.second + 5) / 60);
	hhmm.second = (hhmm.second + 5) % 60;
	spn_hour->set_value(hhmm.first * 1.0);
	spn_min->set_value(hhmm.second * 1.0);
}


void FrontPanel::bind_break_list()
{
	view_break_list->set_model(break_list.ref());
	view_break_list->append_column("Starting at", break_list.start_time);
	view_break_list->append_column("Duration", break_list.duration);
}


/**
 *	Handle the click signal for the ADD button
 */
void FrontPanel::handle_add_click()
{
	//Initialize start time spin buttons with local time
	initialize_absolute_time();
	lbl_warning->hide();

	pop_add_break->popup();	
}


void FrontPanel::handle_rad_relative_select()
{
	lbl_break_cnt->show();
	spn_reoccuring_count->show();
	spn_reoccuring_count->set_value(1.0);
	spn_hour->set_value(0.0);
	spn_min->set_value(5.0);
}


void FrontPanel::handle_rad_absolute_select()
{
	lbl_break_cnt->hide();
	spn_reoccuring_count->hide();
	spn_reoccuring_count->set_value(1.0);
	initialize_absolute_time();
}


void FrontPanel::handle_add_spins()
{
	int hour = (int)spn_hour->get_value();
	int min = (int)spn_min->get_value();
	int dur = (int)spn_duration->get_value();
	int cnt = (int)spn_reoccuring_count->get_value();
	int abs = rad_absolute->get_active();

	Glib::ustring desc = compose_break_description(hour, min, dur, cnt, abs);
	lbl_break_desc->set_label(desc);
}


bool FrontPanel::handle_min_spin_output()
{
	int val = (int)spn_min->get_value();
	auto mm = Glib::ustring::format(std::setfill(L'0'), std::setw(2), val);
	spn_min->set_text(mm);
	return true;
}


bool FrontPanel::handle_evt_box_warning(GdkEventCrossing *evt)
{
	lbl_warning->show();
	return true;
}


void FrontPanel::handle_add_commit()
{
	int hour = (int)spn_hour->get_value();
	int min = (int)spn_min->get_value();
	int dur = (int)spn_duration->get_value();
	int cnt = (int)spn_reoccuring_count->get_value();
	int abs = rad_absolute->get_active();

	if(abs)
	{
		break_list.add_break(hour, min, dur);
	}
	else
	{
		std::pair<int, int> now = get_hhmm_local();
		for(int i = 0; i < cnt; i++)
		{
			int min_cnt = min * (i + 1);
			int mm = (now.second + min_cnt) % 60;
			int hh = (now.first + hour + (min_cnt / 60)) % 24;
			break_list.add_break(hh, mm, dur);
		}
	}
}


void FrontPanel::countdown_to_next_break(double percent, int hour, int min, int sec)
{
	Glib::ustring hhmm = Glib::ustring::compose(
		"%1:%2:%3",
		Glib::ustring::format(std::setfill(L'0'), std::setw(2), hour),
		Glib::ustring::format(std::setfill(L'0'), std::setw(2), min),
		Glib::ustring::format(std::setfill(L'0'), std::setw(2), sec));
	lbl_next_brk_cnt->set_text(hhmm);
	bar_next_break->set_value(percent);	
}
