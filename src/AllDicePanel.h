#ifndef ROLL_CALC__ALL_DICE_PANEL_H
#define ROLL_CALC__ALL_DICE_PANEL_H

#include <memory>

#include <wx/panel.h>

namespace roll_calc {

class AllDicePanel: public wxPanel {
public:
  AllDicePanel(
      wxWindow * parent,
      wxWindowID id,
      const wxPoint & pos = wxDefaultPosition,
      const wxSize & size = wxDefaultSize,
      long style = 0,
      const wxString & name = wxPanelNameStr);
  virtual ~AllDicePanel();

  int D4() const;
  int D6() const;
  int D8() const;
  int D10() const;
  int D12() const;

private:
  struct Member;
  std::unique_ptr<Member> _;
};

} // namespace roll_calc

#endif // ROLL_CALC__ALL_DICE_PANEL_H
