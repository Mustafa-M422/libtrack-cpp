#include "gui/GuiApp.hpp"
#include "gui/MainFrame.hpp"

namespace gui {

bool GuiApp::OnInit() {
  MainFrame *frame = new MainFrame("LibTrack-CPP (wxWidgets)");
  frame->Show(true);
  return true;
}

} // namespace gui

// Macro to generate the main() entry point for the GUI
wxIMPLEMENT_APP(gui::GuiApp);
