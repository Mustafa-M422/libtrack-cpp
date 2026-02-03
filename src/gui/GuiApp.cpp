#include "gui/GuiApp.hpp"
#include "gui/MainFrame.hpp"

namespace gui {

bool GuiApp::OnInit() {
  // Initialize Shared App Logic
  appController = std::make_unique<app::AppController>();
  appController->initialize();

  MainFrame *frame = new MainFrame("LibTrack-CPP (wxWidgets)", *appController);
  frame->Show(true);
  return true;
}

} // namespace gui

// Macro to generate the main() entry point for the GUI
wxIMPLEMENT_APP(gui::GuiApp);
