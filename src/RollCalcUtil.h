#ifndef ROLL_CALC__ROLL_CALC_UTIL_H
#define ROLL_CALC__ROLL_CALC_UTIL_H

#include <wx/window.h>

namespace roll_calc {

template <class W>
W
FindWxWindowById(int id, const wxWindow * parent = 0)
{
  auto * window = wxWindow::FindWindowById(id, parent);
  return dynamic_cast<W>(window);
}

} // namespace roll_calc

#endif // ROLL_CALC__ROLL_CALC_UTIL_H
