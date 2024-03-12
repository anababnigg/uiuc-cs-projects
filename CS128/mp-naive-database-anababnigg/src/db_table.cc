#include "db_table.hpp"

const unsigned int kRowGrowthRate = 2;

// >> HELPER FUNCTIONS <<
void DbTable::AddColumnHelper() {
  row_col_capacity_ *= kRowGrowthRate;
  for (auto& [key, value] : rows_) {
    void** nrow = new void*[row_col_capacity_];
    for (unsigned int i = 0; i < row_col_capacity_; i++) {
      nrow[i] = value[i];
    }
    delete[] value;
    rows_.at(key) = nrow;
  }
}

// >> MAIN FUNCTIONS <<
// (MAIN) AddColumn
void DbTable::AddColumn(const std::pair<std::string, DataType>& col_desc) {
  // resizing + updating to row_col_capacity * 2.
  if (col_descs_.size() == row_col_capacity_) {
    AddColumnHelper();
  }
  // pushback to col_descs_
  col_descs_.push_back(col_desc);
  //"for every data row mapped by rows_":
  for (auto& [key, value] : rows_) {
    switch (col_desc.second) {
    // do i need static cast void??
    case (DataType::kString):
      value[col_descs_.size() - 1] = static_cast<void*>(new std::string(""));
      break;
    case (DataType::kInt):
      value[col_descs_.size() - 1] = static_cast<void*>(new int(0));
      break;
    case (DataType::kDouble):
      value[col_descs_.size() - 1] = static_cast<void*>(new double(0.0));
      break;
    }
  }
}

// (MAIN) DeleteColumnByIdx
void DbTable::DeleteColumnByIdx(unsigned int col_idx) {
  // checking for exceptions:
  if (col_idx >= col_descs_.size()) {
    throw std::out_of_range("EXCEPTION: out of range");
  }
  if (col_descs_.size() == 1 && !rows_.empty()) {
    throw std::runtime_error(
        "EXCEPTION: any table with at least one row must have at least one "
        "column.");
  }
  // "for every mapped row in rows_":
  for (auto& [key, value] : rows_) {
    switch (col_descs_.at(col_idx).second) {
    case (DataType::kString):
      delete static_cast<std::string*>(value[col_idx]);
      break;
    case (DataType::kInt):
      delete static_cast<int*>(value[col_idx]);
      break;
    case (DataType::kDouble):
      delete static_cast<double*>(value[col_idx]);
      break;
    }
    // shifts all elements w indexes greater than col_idx down by one?
    for (unsigned int i = col_idx; i + 1 < col_descs_.size(); i++) {
      value[i] = value[i + 1];
    }
  }
  // erase :3
  col_descs_.erase(col_descs_.begin() + col_idx);
}

// (MAIN) AddRow
// i have no idea if this works, following same structure as before
void DbTable::AddRow(const std::initializer_list<std::string>& col_data) {
  // 1) handling exceptions:
  if (col_data.size() != col_descs_.size()) {
    throw std::invalid_argument(
        "EXCEPTION: items in col_data must be equal to number of columns in "
        "table");
  }
  // 2)
  void** nrow = new void*[row_col_capacity_];
  rows_.insert({next_unique_id_, nrow});
  // need to factor in next_uniuqe id??
  unsigned int iter = 0;
  for (const std::string& data : col_data) {
    switch (col_descs_.at(iter).second) {
    case (DataType::kString):
      rows_.at(next_unique_id_)[iter] =
          static_cast<void*>(new std::string(data));
      break;
    case (DataType::kInt):
      rows_.at(next_unique_id_)[iter] =
          static_cast<void*>(new int(std::stoi(data)));
      break;
    case (DataType::kDouble):
      rows_.at(next_unique_id_)[iter] =
          static_cast<void*>(new double(std::stod(data)));
      break;
    }
    iter++;
  }
  next_unique_id_++;
}

// (MAIN) DeleteRowByID
void DbTable::DeleteRowById(unsigned int id) {
  // exception checking
  if (!rows_.contains(id)) {
    throw std::invalid_argument("EXCEPTION: row with id does not exist");
  }
  // for loop
  for (unsigned int i = 0; i < col_descs_.size(); i++) {
    switch (col_descs_.at(i).second) {
    case (DataType::kString):
      delete static_cast<std::string*>(rows_.at(id)[i]);
      break;
    case (DataType::kInt):
      delete static_cast<int*>(rows_.at(id)[i]);
      break;
    case (DataType::kDouble):
      delete static_cast<double*>(rows_.at(id)[i]);
      break;
    }
  }
  delete[] rows_.at(id);
  rows_.erase(id);
}

// >> CONSTRUCTORS / DESTRUCTORS <<
// (COPY CONSTRUCTOR)
DbTable::DbTable(const DbTable& rhs) { *this = rhs; }

// (COPY ASSIGNMENT OPERATOR)
DbTable& DbTable::operator=(const DbTable& rhs) {
  if (this != &rhs) {
    // clear
    for (unsigned int i = 0; i < next_unique_id_; i++) {
      if (rows_.contains(i)) {
        DeleteRowById(i);
      }
    }
    col_descs_.clear();
    //  deep copy
    col_descs_ = rhs.col_descs_;
    next_unique_id_ = rhs.next_unique_id_;
    row_col_capacity_ = rhs.row_col_capacity_;
    // deep copy rows
    for (auto [key, value] : rhs.rows_) {
      void** crow = new void*[row_col_capacity_];
      rows_.insert({key, crow});
      for (unsigned int i = 0; i < col_descs_.size(); i++) {
        switch (col_descs_[i].second) {
        case (DataType::kString):
          rows_.at(key)[i] = static_cast<void*>(
              new std::string(*(static_cast<std::string*>(value[i]))));
          break;
        case (DataType::kInt):
          rows_.at(key)[i] =
              static_cast<void*>(new int(*(static_cast<int*>(value[i]))));
          break;
        case (DataType::kDouble):
          rows_.at(key)[i] =
              static_cast<void*>(new double(*(static_cast<double*>(value[i]))));
          break;
        }
      }
    }
  }
  return *this;
}

// (DESTRUCTOR)
DbTable::~DbTable() {
  for (unsigned int i = 0; i < next_unique_id_; i++) {
    if (rows_.contains(i)) {
      DeleteRowById(i);
    }
  }
  col_descs_.clear();
}

// (OSSTREAM)
std::ostream& operator<<(std::ostream& os, const DbTable& table) {
  for (unsigned int i = 0; i < table.col_descs_.size(); i++) {
    os << table.col_descs_.at(i).first;
    switch (table.col_descs_.at(i).second) {
    case (DataType::kString):
      os << "(std::string)";
      break;
    case (DataType::kInt):
      os << "(int)";
      break;
    case (DataType::kDouble):
      os << "(double)";
      break;
    }
    if (i != table.col_descs_.size() - 1) {
      os << ", ";
    }
  }
  os << std::endl;
  for (auto [key, value] : table.rows_) {
    for (unsigned int n = 0; n < table.col_descs_.size(); n++) {
      switch (table.col_descs_.at(n).second) {
      case (DataType::kString):
        os << *(static_cast<std::string*>(value[n]));
        break;
      case (DataType::kInt):
        os << *(static_cast<int*>(value[n]));
        break;
      case (DataType::kDouble):
        os << *(static_cast<double*>(value[n]));
        break;
      }
      if (n != table.col_descs_.size() - 1) {
        os << ", ";
      }
    }
    os << std::endl;
  }
  return os;
}
