#include "gui/BookListPanel.hpp"
#include <string>
#include <vector>

namespace gui {

BookListPanel::BookListPanel(wxWindow *parent, app::AppController &ctrl)
    : wxPanel(parent, wxID_ANY), controller(ctrl) {
  InitLayout();
  RefreshList();
}

void BookListPanel::InitLayout() {
  wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

  // Create List Control
  listCtrl = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                            wxLC_REPORT | wxLC_SINGLE_SEL | wxBORDER_SUNKEN);

  InitColumns();

  sizer->Add(listCtrl, 1, wxEXPAND | wxALL, 10);
  SetSizer(sizer);
}

void BookListPanel::InitColumns() {
  listCtrl->InsertColumn(0, "ID", wxLIST_FORMAT_LEFT, 50);
  listCtrl->InsertColumn(1, "Title", wxLIST_FORMAT_LEFT, 200);
  listCtrl->InsertColumn(2, "Author", wxLIST_FORMAT_LEFT, 150);
  listCtrl->InsertColumn(3, "Status", wxLIST_FORMAT_LEFT, 100);
}

void BookListPanel::RefreshList() {
  listCtrl->DeleteAllItems();

  auto books = controller.getService().getAllBooks();

  for (const auto &book : books) {
    long index = listCtrl->GetItemCount();

    // ID
    index = listCtrl->InsertItem(index, std::to_string(book.id));

    // Title
    listCtrl->SetItem(index, 1, book.title);

    // Author
    listCtrl->SetItem(index, 2, book.author);

    // Status
    std::string status = book.isBorrowed ? "Borrowed" : "Available";
    listCtrl->SetItem(index, 3, status);
  }
}

} // namespace gui
