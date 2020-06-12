#pragma once

#include <memory>

#include "date.h"
#include "utils.h"

using namespace std;

class Node {
public:
    virtual bool Evaluate(const Date& date, const string& value) const = 0;
};

class EmptyNode : public Node {
    bool Evaluate(const Date& date, const string& value) const override;
};

class DateComparisonNode : public Node {

public:
    DateComparisonNode(const Comparison& cmp, const Date& date);
    bool Evaluate(const Date& date, const string& value) const override;

private:
    const Comparison cmp_;
    const Date date_;
};

class EventComparisonNode : public Node {

public:
    EventComparisonNode(const Comparison& cmp, const string& value);
    bool Evaluate(const Date& date, const string& value) const override;

private:
    const Comparison cmp_;
    const string value_;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation& logical_operation, shared_ptr<Node> left, shared_ptr<Node> right);
    bool Evaluate(const Date& date, const string& value) const override;

private:
    LogicalOperation logical_operation_;
    shared_ptr<Node> left_;
    shared_ptr<Node> right_;
};
