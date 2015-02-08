#include "DicePanel.h"

#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/stattext.h>

namespace roll_calc {

struct DicePanel::Member {
  wxSpinCtrl * const diceSpinCtrl;
  wxStaticText * const diceStaticText;

  Member(wxWindow * parent, int dice_type)
  : diceSpinCtrl{new wxSpinCtrl{parent}},
    diceStaticText{new wxStaticText{parent, wxID_ANY, wxString::Format("d%d", dice_type)}}
  {/* Empty. */}
};

DicePanel::DicePanel(
    wxWindow * parent,
    wxWindowID id,
    int dice_type,
    const wxPoint & pos,
    const wxSize & size,
    long style,
    const wxString & name)
: wxPanel{parent, id, pos, size, style, name},
  _{new Member{this, dice_type}}
{
  auto * sizer = new wxGridSizer(2);
  sizer->Add(_->diceSpinCtrl, 0, wxALIGN_CENTER);
  sizer->Add(_->diceStaticText, 0, wxALIGN_CENTER);
  SetSizerAndFit(sizer);
}

DicePanel::~DicePanel()
{/* Empty. */}

int
DicePanel::Num() const
{
  return _->diceSpinCtrl->GetValue();
}

} // namespace roll_calc
