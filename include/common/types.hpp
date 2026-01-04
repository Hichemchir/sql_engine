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
private:
    DataType type_;
    std::variant<std::monostate, int64_t, double, std::string, bool> data_;

public:
    static Value make_integer(int64_t val) {
        Value v;
        v.type_ = DataType::INTEGER;
        v.data_ = val;
        return v;
    }

    static Value make_real(double val) {
        Value v;
        v.type_ = DataType::REAL;
        v.data_ = val;
        return v;
    }

    static Value make_text(std::string txt) {
        Value v;
        v.type_ = DataType::TEXT;
        v.data_ = txt;
        return v;
    }

    static Value make_boolean(bool val) {
        Value v;
        v.type_ = DataType::BOOLEAN;
        v.data_ = val;
        return v;
    }

    static Value make_null() {
        Value v;
        v.type_ = DataType::NULL_TYPE;
        v.data_ = std::monostate{};
        return v;
    }

    // getters
    DataType type() const { return type_; }
    bool is_null() const { return type_ == DataType::NULL_TYPE; }
    
    int64_t as_integer() const {
        return std::get<int64_t>(data_);
    }
    double as_real() const {
        return std::get<double>(data_);
    }
    const std::string& as_text() const {
        return std::get<std::string>(data_);
    }
    bool as_boolean() const {
        return std::get<bool>(data_);
    }

    // convert value to string for display
    std::string to_string() const {
        if (is_null()) {
            return "NULL";
        }
        switch (type_) {
            case DataType::INTEGER:
                return std::to_string(as_integer());
            case DataType::REAL: {
                char buf[64];
                snprintf(buf, sizeof(buf), "%.2f", as_real());
                return std::string(buf);
            }
            case DataType::TEXT:
                return as_text();
            case DataType::BOOLEAN:
                return as_boolean() ? "true" : "false";
            default:
                return "NULL";
        }
    }
    
};

}