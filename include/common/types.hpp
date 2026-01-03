#pragma once
#include <string>
#include <iostream>
#include <variant>
#include <cstdint>

namespace sqlengine {

//SQL types

 enum class DataType {
    INTEGER,
    REAL,
    TEXT,
    BOOLEAN,
    NULL_TYPE
 };

// convert datatype to string representation (inline --> request to do it at compile time)
inline std::string data_type_to_string(DataType type) {
    switch(type) {
        case DataType::INTEGER: return "INTEGER";
        case DataType::REAL: return "REAL";
        case DataType::TEXT: return "TEXT";
        case DataType::BOOLEAN: return "BOOLEAN";
        case DataType::NULL_TYPE: return "NULL";
    }
    return "UNKNOWN";
}

/** Use variant to rpz 1 value from many types possible. 1 at each time. Monostate --> null type,
 *  because variant needs at least 1 valid value.
 * Design pattern = factory methods for type safety.
 * Static method to create object, not constructor
 * */ 


class Value {
public:
    static Value make_integer(int64_t val) {
        Value v;
        v.type_ = DataType::INTEGER;
        v.data_ = val;
        return v;
    }

private:
    DataType type_;
    std::variant<std::monostate, int64_t, double, std::string, bool> data_;
};

}