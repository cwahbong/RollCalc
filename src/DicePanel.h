#ifndef ROLL_CALC__DICE_PANEL_H
#define ROLL_CALC__DICE_PANEL_H

#include <memory>

#include <wx/panel.h>

namespace roll_calc {

class DicePanel: public wxPanel {
public:
  DicePanel(
      wxWindow * parent,
      wxWindowID id,
      int dice_type,
      const wxPoint & pos = wxDefaultPosition,
      const wxSize & size = wxDefaultSize,
      long style = 0,
      const wxString & name = wxPanelNameStr);
  virtual ~DicePanel();

  int Num() const;

private:
  struct Member;
  std::unique_ptr<Member> _;
};

} // namespace roll_calc

#endif // ROLL_CALC__DICE_PANEL_H
