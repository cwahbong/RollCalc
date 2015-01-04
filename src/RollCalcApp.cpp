#include <wx/app.h>

#include "RollCalcFrame.h"

namespace roll_calc {

class RollCalcApp: public wxApp
{
public:
  virtual bool OnInit();
};

bool
RollCalcApp::OnInit()
{
  if (!wxApp::OnInit()) {
    return false;
  }

  auto * frame = new RollCalcFrame();
  frame->Show(true);

  return true;
}

} // namespace roll_calc

// This implements the main function.
IMPLEMENT_APP(roll_calc::RollCalcApp);
