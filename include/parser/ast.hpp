#pragma once

#include <string>
#include <vector>
#include <memory>
#include <common/types.hpp>
#include "parser/token.hpp"

namespace sqlengine {

/**
 * COMPARISON OPERATOR : in WHERE clauses
 */

enum class ComparisonOp {
    EQUAL,
    NOT_EQUAL,
    LESS_THAN,
    LESS_EQUAL,
    GREATER_THAN,
    GREATER_EQUAL
};

// Convert ComparisonOp to string representation
inline std::string comparison_op_to_string(ComparisonOp& op) {
    switch (op) {
        case ComparisonOp::EQUAL: return "=";
        case ComparisonOp::NOT_EQUAL: return "!=";
        case ComparisonOp::LESS_THAN: return "<";
        case ComparisonOp::LESS_EQUAL: return "<=";
        case ComparisonOp::GREATER_THAN: return ">";
        case ComparisonOp::GREATER_EQUAL: return ">=";

        default:
            return "UNKOWN";
    }
}

/**
 * LOGICAL OPERATOR : combining conditions
 */

enum class LogicalOp {
    AND,
    OR,
    NOT
};

// Convert LogicalOp to string representation
inline std::string logical_op_to_string(LogicalOp& op) {
    switch (op) {
        case LogicalOp::AND: return "AND";
        case LogicalOp::OR: return "OR";
        case LogicalOp::NOT: return "NOT";

        default:
            return "UNKNOWN";
    }
}

/**
 * BASE AST NODE : abstract base class
 * ASTNode:
 *  Base class for all AST nodes
 */







} // namespace sqlengine