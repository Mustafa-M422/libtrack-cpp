#include "gui/MainFrame.hpp"

namespace gui {

MainFrame::MainFrame(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)) {
  // Simple hello world label for verification
  new wxStaticText(this, wxID_ANY, "Welcome to LibTrack-CPP GUI!",
                   wxPoint(20, 20), wxDefaultSize);

  CreateStatusBar();
  SetStatusText("Ready");
}

} // namespace gui
