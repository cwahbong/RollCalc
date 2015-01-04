#ifndef ROLL_CALC__ROLL_CALC_OPERATOR_PANEL_H
#define ROLL_CALC__ROLL_CALC_OPERATOR_PANEL_H

#include <functional>
#include <memory>

#include <wx/panel.h>

namespace roll_calc {

class RollCalcOperatorPanel: public wxPanel {
public:
  RollCalcOperatorPanel(wxWindow * parent,
                        wxWindowID id,
                        const wxPoint & pos = wxDefaultPosition,
                        const wxSize & size = wxDefaultSize,
                        long style = 0,
                        const wxString & name = wxPanelNameStr);
  virtual ~RollCalcOperatorPanel();

  std::function<bool (int, int)> GetSelectedOperator() const;

private:
  struct Member;
  std::unique_ptr<Member> _;
};

} // namespace roll_calc

#endif // ROLL_CALC__ROLL_CALC_OPERATOR_PANEL_H
