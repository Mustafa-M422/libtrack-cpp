#include "gui/MainFrame.hpp"

namespace gui {

MainFrame::MainFrame(const wxString &title, app::AppController &ctrl)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)),
      controller(ctrl) {

  // Create the main panel (implied or explicit)
  // We'll just put the BookListPanel directly in the frame for now,
  // or a simple sizer if we want to expand later.

  wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

  bookListPanel = new BookListPanel(this, controller);
  mainSizer->Add(bookListPanel, 1, wxEXPAND | wxALL, 0);

  SetSizer(mainSizer);

  CreateStatusBar();
  SetStatusText("Ready - " +
                std::to_string(controller.getService().getAllBooks().size()) +
                " books loaded.");
}

} // namespace gui
