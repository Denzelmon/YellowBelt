#include "node.h"

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date &date) : cmp_(cmp), date_(date) {}

EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string &value) : cmp_(cmp), value_(value) {}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& logical_operation,
        shared_ptr<Node> left, shared_ptr<Node> right) : logical_operation_(logical_operation), left_(left), right_(right) {}


// Evaluate functions
bool EmptyNode::Evaluate(const Date &date, const string &value) const { return true; } // ??

template <class T>
bool Compare(const Comparison& cmp, const T& left, const T& right) {
    switch (cmp) {
        case Comparison::Less: return left < right;
        case Comparison::LessOrEqual: return left <= right;
        case Comparison::Equal: return left == right;
        case Comparison::Greater: return left > right;
        case Comparison::GreaterOrEqual: return left >= right;
        case Comparison::NotEqual: return left != right;
    }
}

bool DateComparisonNode::Evaluate(const Date &date, const string &value) const {
    return Compare(cmp_, date, date_);
}

bool EventComparisonNode::Evaluate(const Date &date, const string &value) const {
    return Compare(cmp_, value, value_);
}

bool LogicalOperationNode::Evaluate(const Date &date, const string &value) const {
    if (logical_operation_ == LogicalOperation::Or) {
        return left_->Evaluate(date, value) || right_->Evaluate(date, value);
    } else {
        return left_->Evaluate(date, value) && right_->Evaluate(date, value);
    }
}
