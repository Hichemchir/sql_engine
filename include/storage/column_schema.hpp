#pragma once

#include "common/types.hpp"
#include <string>

namespace sqlengine {

/**
 * Schema def for a table column.
 * COntains metadata about a col:
 * - type
 * - name
 * - constraints (pk, nullable, etc)
 */

struct ColumnSchema {
    std::string name;
    DataType type;
    bool nullable = true;
    bool primary_key = false;

    // Constructor
    ColumnSchema(std::string col_name, DataType col_type)
        : name(std::move(col_name)), type(col_type) {}
    
    ColumnSchema(std::string col_name, DataType col_type, bool is_nullable)
        : name(std::move(col_name)), type(col_type), nullable(is_nullable) {}
    
    ColumnSchema(std::string col_name, DataType col_type, bool is_nullable, bool is_pkey)
        : name(std::move(col_name)), type(col_type), nullable(is_nullable), primary_key(is_pkey) {}
};

}