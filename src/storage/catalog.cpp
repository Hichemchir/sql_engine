#include <string>
#include <unordered_map>
#include <memory>
#include <optional>
#include <vector>
#include "storage/table.hpp"
#include "storage/catalog.hpp"

bool Catalog::table_exists(const std::string& table_name) const {
    if (tables_.find(table_name) != tables_.end()) return true;
    return false;
}

bool Catalog::create_table(const std::string& table_name, const std::vector<std::string>& column_names) {
}

Table* Catalog::get_table(const std::string& table_name) {
    
}
