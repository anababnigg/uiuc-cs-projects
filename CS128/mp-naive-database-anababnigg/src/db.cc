#include "db.hpp"
// >> HELPER FUNCTIONS <<
// do i need any helpers ? :3

// >> MAIN FUNCTIONS <<
// (MAIN): CreateTable
void Database::CreateTable(const std::string& table_name) {
  tables_.insert({table_name, new DbTable()});
}

// (MAIN) DropTable
void Database::DropTable(const std::string& table_name) {
  if (!tables_.contains(table_name)) {
    throw std::invalid_argument("table_name does not exist in tables_");
  }
  delete tables_.at(table_name);
  tables_.erase(table_name);  // erase is special case, does this need anything?
}

// (MAIN) GetTable
DbTable& Database::GetTable(const std::string& table_name) {
  return *(tables_.at(table_name));
}

// >> CONSTRUCTORS / DESTRUCTORS <<
// (COPY CONSTRUCTOR)
Database::Database(const Database& rhs) { *this = rhs; }

// (COPY ASSIGNMENT OPERATOR)
Database& Database::operator=(const Database& rhs) {
  if (this == &rhs) {
    return *this;
  }
  // clear
  for (auto [key, value] : tables_) {
    delete value;
  }
  tables_.clear();
  // deep copy policy
  for (auto [key, value] : rhs.tables_) {
    tables_.insert({key, new DbTable(*value)});
  }
  return *this;
}

// (DESTRUCTOR)
Database::~Database() {
  for (auto [key, value] : tables_) {
    delete value;
  }
  tables_.clear();
}
