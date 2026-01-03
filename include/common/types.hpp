#pragma once
#include <string>
#include <iostream>
#include <variant>

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

// use variant to rpz 1 value from many types possible. 1 at each time


}