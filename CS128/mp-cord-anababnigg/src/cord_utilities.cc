#include "cord_utilities.hpp"

SharedPointer<Cord> SubString(SharedPointer<Cord> curr_cord,
                              unsigned int lower_idx,
                              unsigned int upper_idx) {
  // check for exception
  if (lower_idx < 0 || upper_idx > curr_cord->Length() ||
      lower_idx >= upper_idx) {
    throw std::runtime_error("ERROR: cord outside of bounds");
  }
  // CASES
  // if it's the whole string:
  if (lower_idx == 0 && upper_idx == curr_cord->Length()) {
    return curr_cord;
  }
  // Using Substring
  // nullptr
  if (curr_cord->Left().Get() == nullptr &&
      curr_cord->Right().Get() == nullptr) {
    Cord* cat =
        new Cord(curr_cord->Data().substr(lower_idx, upper_idx - lower_idx));
    return {SharedPointer(cat, kSharedPointerType::kObject)};
  }
  // using split index
  unsigned int split = curr_cord->Left()->Length();
  if (upper_idx <= curr_cord->Left()->Length()) {
    return SubString(curr_cord->Left(), lower_idx, upper_idx);
  }
  if (lower_idx >= curr_cord->Left()->Length()) {
    return SubString(curr_cord->Right(),
                     lower_idx - curr_cord->Left()->Length(),
                     upper_idx - curr_cord->Left()->Length());
  }

  return ConcatCords(SubString(curr_cord->Left(), lower_idx, split),
                     SubString(curr_cord->Right(), 0, upper_idx - split));
}