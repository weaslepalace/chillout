#include "control_panel.h"

#include <iostream>
//ControlPanel::ControlPanel(BreakList& break_list)
ControlPanel::ControlPanel()
{
	builder = Gtk::Builder::create();
	builder->add_from_file("control.glade");
	
	builder->get_widget("win_control", win);

//	builder->get_widget("exp_show_list", exp_show_list);
//	exp_show_list
//		->property_expanded()
//		.signal_changed()
//		.connect(
//			sigc::mem_fun(*this, &ControlPanel::handle_show_list));
//
//	builder->get_widget("rvl_break_list", rvl_break_list);

//	builder->get_widget("tree_break_list", view_break_list);
//	view_break_list->set_model(break_list.ref());
//	view_break_list->append_column("Starting at", break_list.start_time);
//	view_break_list->append_column("Duration", break_list.duration);

	
//	Gtk::TreeViewColumn *col = tree_break_list->get_column(0);
//	std::cout << view_break_list->get_n_columns() << std::endl;
}


ControlPanel::~ControlPanel() = default;


