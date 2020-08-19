#include "control_panel.h"

#include <iostream>


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


void ControlPanel::handle_add_click()
{
	Gtk::Popover *pop_add_break;	
	builder->get_widget("pop_add_break", pop_add_break);
	pop_add_break->popup();	
}
