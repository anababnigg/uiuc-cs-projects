#include "cord.hpp"

#include <stdexcept>

#include "cord_utilities.hpp"

// >> CONSTRUCTOR <<
Cord::Cord(std::string_view sv) {
  // check for exception
  if (sv.empty()) {
    throw std::runtime_error("ERROR: SV is empty");
  }
  // set data and make deep copy of data:
  data_ = new char[sv.size() + 1];
  for (size_t i = 0; i < sv.size(); i++) {
    data_[i] = sv.at(i);
  }
  data_[sv.size()] = '\0';  // null terminator
  length_ = static_cast<unsigned int>(sv.size());
  left_ = nullptr;
  right_ = nullptr;
}

// >> DESTRUCTOR <<
Cord::~Cord() { delete data_; }

// >> MAIN METHODS <<
// ToString
SharedPointer<char> Cord::ToString() const {
  char* final = new char[length_ + 1];
  int index = 0;
  ToStringHelper(final, index);
  final[length_] = '\0';
  return SharedPointer<char>{final, kSharedPointerType::kArray};
}

// Recursive helper:
void Cord::ToStringHelper(char* final, int& index) const {
  // if leaf node:
  if (data_ != nullptr) {
    for (unsigned int i = 0; i < length_; i++) {
      final[index++] = data_[i];
    }
    return;
  }
  // call recursion
  left_.Get()->ToStringHelper(final, index);
  right_.Get()->ToStringHelper(final, index);
}

// >> FRIEND <<
SharedPointer<Cord> ConcatCords(SharedPointer<Cord> left_cord,
                                SharedPointer<Cord> right_cord) {
  // check for exception
  if (left_cord.Get() == nullptr || right_cord.Get() == nullptr) {
    throw std::runtime_error("ERROR: Cord is empty");
  }
  // concatenation
  Cord* cat = new Cord;
  cat->left_ = left_cord;
  cat->right_ = right_cord;
  cat->length_ = left_cord.Get()->length_ + right_cord.Get()->length_;

  return {cat, kSharedPointerType::kObject};
}
