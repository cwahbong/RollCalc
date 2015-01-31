#ifndef ROLL_CALC__ROLL_CALC_PANEL_H
#define ROLL_CALC__ROLL_CALC_PANEL_H

#include <memory>

#include <wx/button.h>
#include <wx/panel.h>
#include <wx/stattext.h>

namespace roll_calc {

class RollCalcPanel: public wxPanel {
public:
  RollCalcPanel(wxWindow * parent,
                wxWindowID id,
                const wxPoint & pos = wxDefaultPosition,
                const wxSize & size = wxDefaultSize,
                long style = 0,
                const wxString & name = wxPanelNameStr);
  virtual ~RollCalcPanel();

private:
  struct Member;
  std::unique_ptr<Member> _;
};

} // namespace roll_calc

#endif // ROLL_CALC__ROLL_CALC_PANEL_H
