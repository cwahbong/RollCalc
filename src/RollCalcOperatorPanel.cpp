#include "RollCalcOperatorPanel.h"

#include <unordered_map>
#include <vector>

#include <wx/bitmap.h>
#include <wx/tglbtn.h>
#include <wx/sizer.h>

namespace roll_calc {

namespace {

enum {
  ROLL_CALC_OPERATOR_PANEL_GT = wxID_HIGHEST + 1,
  ROLL_CALC_OPERATOR_PANEL_GE,
  ROLL_CALC_OPERATOR_PANEL_EQ,
  ROLL_CALC_OPERATOR_PANEL_NE,
  ROLL_CALC_OPERATOR_PANEL_LT,
  ROLL_CALC_OPERATOR_PANEL_LE,
};

wxBitmap
GetBitmap(wxWindowID id)
{
  const static std::unordered_map<int, wxBitmap> umap = {
    {ROLL_CALC_OPERATOR_PANEL_GT, wxBitmap(32, 32)},
    {ROLL_CALC_OPERATOR_PANEL_GE, wxBitmap(32, 32)},
    {ROLL_CALC_OPERATOR_PANEL_EQ, wxBitmap(32, 32)},
    {ROLL_CALC_OPERATOR_PANEL_NE, wxBitmap(32, 32)},
    {ROLL_CALC_OPERATOR_PANEL_LT, wxBitmap(32, 32)},
    {ROLL_CALC_OPERATOR_PANEL_LE, wxBitmap(32, 32)},
  };

  return umap.at(id);
}

std::function<bool (int, int)>
GetOperator(wxWindowID id)
{
  const static std::unordered_map<wxWindowID, std::function<bool (int, int)>> umap = {
    {ROLL_CALC_OPERATOR_PANEL_GT, std::greater<int>()},
    {ROLL_CALC_OPERATOR_PANEL_GE, std::greater_equal<int>()},
    {ROLL_CALC_OPERATOR_PANEL_EQ, std::equal_to<int>()},
    {ROLL_CALC_OPERATOR_PANEL_NE, std::not_equal_to<int>()},
    {ROLL_CALC_OPERATOR_PANEL_LT, std::less<int>()},
    {ROLL_CALC_OPERATOR_PANEL_LE, std::less_equal<int>()},
  };

  return umap.at(id);
}

} // namespace

struct RollCalcOperatorPanel::Member {
  wxToggleButton * selected;

  Member()
  : selected{NULL}
  {/* Empty. */}

  wxToggleButton *
  newOperatorButton(wxWindow * parent, wxWindowID id)
  {
    wxToggleButton * button = new wxBitmapToggleButton(parent, id, GetBitmap(id));
    parent->Bind(
        wxEVT_COMMAND_TOGGLEBUTTON_CLICKED,
        [this](wxCommandEvent & event) {
          if (selected) {
            selected->SetValue(false);
          }
          auto * newSelected = dynamic_cast<wxToggleButton *>(event.GetEventObject());
          newSelected->SetValue(true);
          selected = newSelected;
        },
        button->GetId());
    return button;
  }
};

RollCalcOperatorPanel::RollCalcOperatorPanel(
  wxWindow * parent,
  wxWindowID id,
  const wxPoint & pos,
  const wxSize & size,
  long style,
  const wxString & name
)
: wxPanel{parent, id, pos, size, style, name},
  _{new Member{}}
{
  const std::vector<wxWindowID> buttonIds = {
    ROLL_CALC_OPERATOR_PANEL_GT,
    ROLL_CALC_OPERATOR_PANEL_GE,
    ROLL_CALC_OPERATOR_PANEL_EQ,
    ROLL_CALC_OPERATOR_PANEL_NE,
    ROLL_CALC_OPERATOR_PANEL_LT,
    ROLL_CALC_OPERATOR_PANEL_LE,
  };

  auto * sizer = new wxGridSizer(2);
  for (auto buttonId: buttonIds) {
    sizer->Add(
        _->newOperatorButton(this, buttonId),
        wxALIGN_CENTER);
  }
  SetSizerAndFit(sizer);
}

RollCalcOperatorPanel::~RollCalcOperatorPanel()
{/* Empty. */}

std::function<bool (int, int)>
RollCalcOperatorPanel::GetSelectedOperator() const
{
  if (!_->selected) {
    return [](int, int){ return false; };
  }
  return GetOperator(_->selected->GetId());
}

} // namespace roll_calc
