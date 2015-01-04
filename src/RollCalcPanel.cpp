#include "RollCalcPanel.h"

#include "RollCalcFunc.h"
#include "RollCalcOperatorPanel.h"
#include "RollCalcUtil.h"

#include <unordered_map>

#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/textctrl.h>
#include <wx/toolbar.h>


namespace roll_calc {

namespace {

const int ROLL_CALC_BORDER = 10;

enum {
  ROLL_CALC_PANEL_CALC_BUTTON = wxID_HIGHEST + 1,
  ROLL_CALC_PANEL_D4_SPIN_CTRL,
  ROLL_CALC_PANEL_D6_SPIN_CTRL,
  ROLL_CALC_PANEL_D8_SPIN_CTRL,
  ROLL_CALC_PANEL_D10_SPIN_CTRL,
  ROLL_CALC_PANEL_D12_SPIN_CTRL,
  ROLL_CALC_PANEL_OPERATOR_PANEL,
  ROLL_CALC_PANEL_DEST_TEXT_CTRL,
  ROLL_CALC_PANEL_PROB_TEXT,
};

wxWindowID
GetDieSpinCtrlId(int die)
{
  const std::unordered_map<int, wxWindowID> umap = {
    {4, ROLL_CALC_PANEL_D4_SPIN_CTRL},
    {6, ROLL_CALC_PANEL_D6_SPIN_CTRL},
    {8, ROLL_CALC_PANEL_D8_SPIN_CTRL},
    {10, ROLL_CALC_PANEL_D10_SPIN_CTRL},
    {12, ROLL_CALC_PANEL_D12_SPIN_CTRL},
  };

  return umap.at(die);
}

wxPanel *
newDiePanel(wxWindow * parent, wxWindowID id, int die)
{
  auto * panel = new wxPanel(parent, id);
  panel->SetBackgroundColour(wxColor(255,255,0));
  auto * topSizer = new wxGridSizer(1);
  {
    auto * sizer = new wxGridSizer(2);
    {
      sizer->Add(new wxSpinCtrl(panel, GetDieSpinCtrlId(die)), 0, wxALIGN_CENTER);
      sizer->Add(new wxStaticText(panel, wxID_ANY, wxString::Format("d%d", die)), 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
    }
    topSizer->Add(sizer, 0, wxALIGN_CENTER);
  }
  panel->SetSizerAndFit(topSizer);
  return panel;
}

wxPanel *
newDicePanel(wxWindow * parent, wxWindowID id)
{

  auto * panel = new wxPanel(parent, id);
  auto * sizer = new wxBoxSizer(wxVERTICAL);

  for (const auto & die: {4, 6, 8, 10, 12}) {
    sizer->Add(newDiePanel(panel, wxID_ANY, die), 1, wxEXPAND);
  }

  panel->SetSizerAndFit(sizer);
  return panel;
}

wxPanel *
newCmpPanel(wxWindow * parent, wxWindowID id)
{
  auto * panel = new wxPanel(parent, id);
  panel->SetBackgroundColour(wxColor(255,0,255));
  auto * sizer = new wxBoxSizer(wxHORIZONTAL);
  {
    sizer->Add(new RollCalcOperatorPanel(panel, ROLL_CALC_PANEL_OPERATOR_PANEL), 0, wxALIGN_CENTER);

    auto * destTextCtrl = new wxTextCtrl(panel, ROLL_CALC_PANEL_DEST_TEXT_CTRL);
    sizer->Add(destTextCtrl, 0, wxALIGN_CENTER);
  }
  panel->SetSizer(sizer);
  return panel;
}

wxPanel *
newCalcProbPanel(wxWindow * parent, wxWindowID id)
{
  auto * panel = new wxPanel(parent, id);
  panel->SetBackgroundColour(wxColor(0,255,255));
  {
    auto * sizer = new wxBoxSizer(wxVERTICAL);
    {
      sizer->Add(new wxButton(panel, ROLL_CALC_PANEL_CALC_BUTTON, "Calc"), 0, wxALIGN_CENTER);
      sizer->AddStretchSpacer();
      sizer->Add(new wxStaticText(panel, ROLL_CALC_PANEL_PROB_TEXT, "%"), 0, wxALIGN_CENTER);
    }
    panel->SetSizerAndFit(sizer);
  }
  return panel;
}

void
initLayout(wxWindow * window)
{
  auto * topLevelSizer = new wxGridSizer(3);
  {
    topLevelSizer->Add(newDicePanel(window, wxID_ANY),
        1,
        wxEXPAND | wxALL,
        ROLL_CALC_BORDER);
    topLevelSizer->Add(newCmpPanel(window, wxID_ANY),
        1,
        wxEXPAND | wxALL,
        ROLL_CALC_BORDER);
    topLevelSizer->Add(newCalcProbPanel(window, wxID_ANY),
        1,
        wxEXPAND | wxALL,
        ROLL_CALC_BORDER);
  }
  window->SetSizerAndFit(topLevelSizer);
}

void
bindEvents(wxWindow * window)
{
  window->Bind(
      wxEVT_BUTTON,
      [window](wxCommandEvent & /* event */){
        auto * text = FindWxWindowById<wxStaticText *>(ROLL_CALC_PANEL_PROB_TEXT, window);
        if (text) {
          // call calc_prob and set the text label;
          // XXX check NULL return value by FindWxWindowByID
          int d4 = FindWxWindowById<wxSpinCtrl *>(ROLL_CALC_PANEL_D4_SPIN_CTRL, window)->GetValue();
          int d6 = FindWxWindowById<wxSpinCtrl *>(ROLL_CALC_PANEL_D6_SPIN_CTRL, window)->GetValue();
          int d8 = FindWxWindowById<wxSpinCtrl *>(ROLL_CALC_PANEL_D8_SPIN_CTRL, window)->GetValue();
          int d10 = FindWxWindowById<wxSpinCtrl *>(ROLL_CALC_PANEL_D10_SPIN_CTRL, window)->GetValue();
          int d12 = FindWxWindowById<wxSpinCtrl *>(ROLL_CALC_PANEL_D12_SPIN_CTRL, window)->GetValue();
          std::function<bool (int, int)> op = FindWxWindowById<RollCalcOperatorPanel *>(ROLL_CALC_PANEL_OPERATOR_PANEL, window)->GetSelectedOperator();

          wxString destStr = FindWxWindowById<wxTextCtrl *>(ROLL_CALC_PANEL_DEST_TEXT_CTRL, window)->GetValue();
          int dest = wxAtoi(destStr);

          double prob = Prob(d4, d6, d8, d10, d12, [op, dest](int rolled){ return op(rolled, dest); });

          text->SetLabel(wxString::Format("%d + %d + %d + %d + %d = %.2f%%", d4, d6, d8, d10, d12, prob));
        } else {
          // ERROR HANDLING
        }
      },
      ROLL_CALC_PANEL_CALC_BUTTON
  );
}

} // namespace

RollCalcPanel::RollCalcPanel(
  wxWindow * parent,
  wxWindowID id,
  const wxPoint & pos,
  const wxSize & size,
  long style,
  const wxString & name
)
: wxPanel{parent, id, pos, size, style, name}
{
  initLayout(this);
  bindEvents(this);
}

RollCalcPanel::~RollCalcPanel()
{/* Empty. */}

} // namespace RollCalcPanel
