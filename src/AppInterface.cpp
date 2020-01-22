#include <interface/AppInterface.hpp>
#include <iostream>

AppInterface::AppInterface () : 
horizontal_box (Gtk::ORIENTATION_HORIZONTAL, 20),
vertical_box (Gtk::ORIENTATION_VERTICAL, 20),
btn_plot ("Plot")
{
    set_size_request (900, 600);
    set_title ("gtkmm-2d-graph");
    set_border_width (10);
    
    // Signal handling
    btn_plot.signal_clicked().connect (sigc::mem_fun (*this, &AppInterface::on_text_input));
    e_buffer = Gtk::EntryBuffer::create();
    e_function.set_buffer (e_buffer);
    e_function.signal_activate().connect (sigc::mem_fun (*this, &AppInterface::on_text_input));
    
    // Layout
    btn_plot.set_size_request (100, 30);
    e_function.set_size_request (-1, 30);
    add (vertical_box);
    horizontal_box.pack_start (e_function, Gtk::PACK_EXPAND_WIDGET);
    horizontal_box.pack_start (btn_plot, Gtk::PACK_SHRINK);
    vertical_box.pack_start (ga_graph, Gtk::PACK_EXPAND_WIDGET);
    vertical_box.pack_start (horizontal_box, Gtk::PACK_SHRINK);
    
    // CSS
    css_provider = Gtk::CssProvider::create();
    auto window_style_context = get_style_context();
    auto btn_style_context = btn_plot.get_style_context();
    auto entry_style_context = e_function.get_style_context();
    window_style_context->add_provider (css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    btn_style_context->add_provider (css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    entry_style_context->add_provider (css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    css_provider->signal_parsing_error().connect(sigc::mem_fun(*this, &AppInterface::on_parsing_error));
    try
    {
        css_provider->load_from_path ("style.css");
    }
    catch (const Gtk::CssProviderError& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch (const Glib::Error& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    vertical_box.show_all_children();
    vertical_box.show();
}

AppInterface::~AppInterface () {}

void AppInterface::on_text_input ()
{
    try
    {
        ga_graph.new_function (e_buffer->get_text());
    }
    catch (std::invalid_argument *e)
    {
        std::cerr << e->what() << std::endl;
        delete e;
    }
}

void AppInterface::on_parsing_error(const Glib::RefPtr<const Gtk::CssSection>& section, const Glib::Error& error)
{
  std::cerr << "on_parsing_error(): " << error.what() << std::endl;
  if (section)
  {
    const auto file = section->get_file();
    if (file)
    {
      std::cerr << "  URI = " << file->get_uri() << std::endl;
    }

    std::cerr << "  start_line = " << section->get_start_line() + 1
              << ", end_line = " << section->get_end_line() + 1 << std::endl;
    std::cerr << "  start_position = " << section->get_start_position()
              << ", end_position = " << section->get_end_position() << std::endl;
  }
}
