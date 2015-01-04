#include "RollCalcFrame.h"

#include "RollCalcPanel.h"


namespace roll_calc {

RollCalcFrame::RollCalcFrame()
  : wxFrame{NULL, wxID_ANY, "RollCalc"}
{
  new RollCalcPanel(this, wxID_ANY);
  Fit();
  SetMinSize(GetSize());
}

RollCalcFrame::~RollCalcFrame()
{/* Empty. */}

} // namespace roll_calc
