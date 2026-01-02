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

Table* Catalog::get_table(const std::string& table_name) {
    if (!table_exists(table_name)) return nullptr;
    Table* tbl_ptr = tables_[table_name].get();
    return tbl_ptr;
}

bool Catalog::create_table(const std::string& table_name, const std::vector<std::string>& column_names) {
    if (table_exists(table_name)) {
        std::cerr << "Error: table " << table_name << " already exists" << std::endl;
        return false;
    }

    // Create a unique ptr and move ownership
    auto tbl_ptr = std::make_unique<Table>(table_name, column_names);
    tables_[table_name] = std::move(tbl_ptr);

    std::cout << "Table " << table_name << " created successfully" << std::endl;
    return true;
}

bool Catalog::drop_table(const std::string& table_name) {
    if (!table_exists(table_name)) return false;
    tables_.erase(table_name);
    return true;
}

std::vector<std::string> Catalog::list_tables() const {
    std::vector<std::string> ls_tbl;

    for (const auto& table : tables_) {
        ls_tbl.push_back(table.first);
    }

    return ls_tbl;
}

void Catalog::display_catalog() const {
    std::cout << "\nDATABASE CATALOG:" << std::endl;
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;

    if (tables_.empty()) {
        std::cout << " (no tables)" << std::endl;
        return;
    }

    std::cout << "Tables (" << tables_.size() << "):" << std::endl;
    for (const auto& [name, table] : tables_) {
        std::cout << "Table name: " << name << std::endl;
    }
}
