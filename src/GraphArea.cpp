#include <interface/GraphArea.hpp>

GraphArea::GraphArea() {}

bool GraphArea::on_draw (const Cairo::RefPtr<Cairo::Context>& context)
{
    context->set_source_rgb (0.1, 0.1, 0.1);
    context->paint();
    return true;
}

GraphArea::~GraphArea() {}
