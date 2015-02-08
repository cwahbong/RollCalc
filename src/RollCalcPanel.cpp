#include "RollCalcPanel.h"

#include "DicePanel.h"
#include "Func.h"
#include "RollCalcOperatorPanel.h"
#include "Util.h"

#include <unordered_map>

#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/textctrl.h>
#include <wx/toolbar.h>


namespace roll_calc {

namespace {

const int ROLL_CALC_BORDER = 10;
const int ROLL_CALC_TEXT_CTRL_WIDTH = 40;

} // namespace

struct RollCalcPanel::Member {
  RollCalcOperatorPanel * operatorPanel;
  wxTextCtrl * destTextCtrl;
  wxStaticText * probStaticText;
  std::map<int, wxSpinCtrl *> diceSpinCtrls;

  wxButton * initCalcButton(wxWindow * parent, wxWindowID id);
  void OnCalcButton(wxCommandEvent & event);

  RollCalcOperatorPanel * initOperatorPanel(wxWindow * parent, wxWindowID id);
  wxStaticText * initProbStaticText(wxWindow * parent, wxWindowID id);

  wxPanel * initAllDicePanel(wxWindow * parent, wxWindowID id);
  wxPanel * initCmpPanel(wxWindow * parent, wxWindowID id);
  wxPanel * initCalcProbPanel(wxWindow * parent, wxWindowID id);

  Member()
  : operatorPanel{NULL},
    destTextCtrl{NULL},
    probStaticText{NULL}
  {/* Empty. */}
};

wxButton *
RollCalcPanel::Member::initCalcButton(
    wxWindow * parent,
    wxWindowID id)
{
  auto * button = new wxButton(parent, id, "Calc");
  button->Bind(wxEVT_BUTTON, &RollCalcPanel::Member::OnCalcButton, this);
  return button;
}

void
RollCalcPanel::Member::OnCalcButton(
    wxCommandEvent & /* event */)
{
  const int d4 = diceSpinCtrls[4]->GetValue();
  const int d6 = diceSpinCtrls[6]->GetValue();
  const int d8 = diceSpinCtrls[8]->GetValue();
  const int d10 = diceSpinCtrls[10]->GetValue();
  const int d12 = diceSpinCtrls[12]->GetValue();
  const std::function<bool (int, int)> op = operatorPanel->GetSelectedOperator();
  const int dest = wxAtoi(destTextCtrl->GetValue());

  const Dice<int, size_t, double> dice = {
    {regular_die<int, double>(4), d4},
    {regular_die<int, double>(6), d6},
    {regular_die<int, double>(8), d8},
    {regular_die<int, double>(10), d10},
    {regular_die<int, double>(12), d12},
  };
  const double prob = probability(
    dice,
    [op, dest](int rolled){
      return op(rolled, dest);
    }
  );

  probStaticText->SetLabel(wxString::Format("%.2f%%", prob));
}

RollCalcOperatorPanel *
RollCalcPanel::Member::initOperatorPanel(
    wxWindow * parent,
    wxWindowID id)
{
  return new RollCalcOperatorPanel(parent, id);
}

wxStaticText *
RollCalcPanel::Member::initProbStaticText(
    wxWindow * parent,
    wxWindowID id)
{
  return new wxStaticText(parent, id, "\%");
}

wxPanel *
RollCalcPanel::Member::initAllDicePanel(
    wxWindow * parent,
    wxWindowID id)
{

  auto * panel = new wxPanel(parent, id);
  auto * sizer = new wxBoxSizer(wxVERTICAL);

  for (const auto & dice: {4, 6, 8, 10, 12}) {
    sizer->Add(new DicePanel(panel, wxID_ANY, dice), 1, wxEXPAND);
  }

  panel->SetSizerAndFit(sizer);
  return panel;
}

wxPanel *
RollCalcPanel::Member::initCmpPanel(
    wxWindow * parent,
    wxWindowID id)
{
  auto * panel = new wxPanel(parent, id);
  auto * sizer = new wxBoxSizer(wxHORIZONTAL);

  operatorPanel = initOperatorPanel(panel, wxID_ANY);
  sizer->Add(operatorPanel, 0, wxALIGN_CENTER);

  destTextCtrl = new wxTextCtrl(panel, wxID_ANY);
  destTextCtrl->SetMinSize(wxSize(ROLL_CALC_TEXT_CTRL_WIDTH, -1));
  sizer->Add(destTextCtrl, 0, wxALIGN_CENTER);

  panel->SetSizerAndFit(sizer);
  return panel;
}

wxPanel *
RollCalcPanel::Member::initCalcProbPanel(
    wxWindow * parent,
    wxWindowID id)
{
  auto * panel = new wxPanel(parent, id);
  auto * sizer = new wxBoxSizer(wxVERTICAL);

  sizer->Add(initCalcButton(panel, wxID_ANY), 0, wxALIGN_CENTER);

  sizer->AddStretchSpacer();

  probStaticText = initProbStaticText(panel, wxID_ANY);
  sizer->Add(probStaticText, 0, wxALIGN_CENTER);

  panel->SetSizerAndFit(sizer);
  return panel;
}

RollCalcPanel::RollCalcPanel(
    wxWindow * parent,
    wxWindowID id,
    const wxPoint & pos,
    const wxSize & size,
    long style,
    const wxString & name)
: wxPanel{parent, id, pos, size, style, name},
  _{new Member{}}
{
  auto * topLevelSizer = new wxBoxSizer(wxHORIZONTAL);

  topLevelSizer->Add(_->initAllDicePanel(this, wxID_ANY),
      0,
      wxEXPAND | wxALL,
      ROLL_CALC_BORDER);

  topLevelSizer->Add(_->initCmpPanel(this, wxID_ANY),
      0,
      wxEXPAND | wxALL,
      ROLL_CALC_BORDER);

  topLevelSizer->Add(_->initCalcProbPanel(this, wxID_ANY),
      0,
      wxEXPAND | wxALL,
      ROLL_CALC_BORDER);

  SetSizerAndFit(topLevelSizer);
}

RollCalcPanel::~RollCalcPanel()
{/* Empty. */}

} // namespace RollCalcPanel
