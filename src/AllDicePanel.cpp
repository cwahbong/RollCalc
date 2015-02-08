#include "AllDicePanel.h"

#include "DicePanel.h"

#include <wx/sizer.h>

namespace roll_calc {

struct AllDicePanel::Member {
  DicePanel * const d4DicePanel;
  DicePanel * const d6DicePanel;
  DicePanel * const d8DicePanel;
  DicePanel * const d10DicePanel;
  DicePanel * const d12DicePanel;

  Member(wxWindow * parent)
  : d4DicePanel{new DicePanel{parent, wxID_ANY, 4}},
    d6DicePanel{new DicePanel{parent, wxID_ANY, 6}},
    d8DicePanel{new DicePanel{parent, wxID_ANY, 8}},
    d10DicePanel{new DicePanel{parent, wxID_ANY, 10}},
    d12DicePanel{new DicePanel{parent, wxID_ANY, 12}}
  {/* Empty. */}
};

AllDicePanel::AllDicePanel(
    wxWindow * parent,
    wxWindowID id,
    const wxPoint & pos,
    const wxSize & size,
    long style,
    const wxString & name)
  : wxPanel{parent, id, pos, size, style, name},
  _{new Member{this}}
{
  auto * sizer = new wxGridSizer(1);
  sizer->Add(_->d4DicePanel, 0, wxALIGN_CENTER);
  sizer->Add(_->d6DicePanel, 0, wxALIGN_CENTER);
  sizer->Add(_->d8DicePanel, 0, wxALIGN_CENTER);
  sizer->Add(_->d10DicePanel, 0, wxALIGN_CENTER);
  sizer->Add(_->d12DicePanel, 0, wxALIGN_CENTER);
  SetSizerAndFit(sizer);
}

AllDicePanel::~AllDicePanel()
{/* Empty. */}

int
AllDicePanel::D4() const
{
  return _->d4DicePanel->Num();
}

int
AllDicePanel::D6() const
{
  return _->d6DicePanel->Num();
}

int
AllDicePanel::D8() const
{
  return _->d8DicePanel->Num();
}

int
AllDicePanel::D10() const
{
  return _->d10DicePanel->Num();
}

int
AllDicePanel::D12() const
{
  return _->d12DicePanel->Num();
}

} // namespace roll_calc
