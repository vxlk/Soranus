#pragma once

#ifdef DEBUG_UNDEFINED_FROM_WRAP_PYTHON_H
#  def _DEBUG // Don't let Python force the debug library just because we're debugging.
#endif