/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#ifndef COMMON_EXPRESSION_REDUCEEXPRESSIONEXPRESSION_H_
#define COMMON_EXPRESSION_REDUCEEXPRESSIONEXPRESSION_H_

#include "common/expression/Expression.h"

namespace nebula {

class ReduceExpression final : public Expression {
    friend class Expression;

public:
    explicit ReduceExpression(const std::string& accumulator = "",
                              Expression* initial = nullptr,
                              const std::string& innerVar = "",
                              Expression* collection = nullptr,
                              Expression* mapping = nullptr)
        : Expression(Kind::kReduce),
          accumulator_(accumulator),
          initial_(initial),
          innerVar_(innerVar),
          collection_(collection),
          mapping_(mapping) {}

    bool operator==(const Expression& rhs) const override;

    const Value& eval(ExpressionContext& ctx) override;

    std::string toString() const override;

    void accept(ExprVisitor* visitor) override;

    std::unique_ptr<Expression> clone() const override;

    const std::string& accumulator() const {
        return accumulator_;
    }

    const Expression* initial() const {
        return initial_.get();
    }

    Expression* initial() {
        return initial_.get();
    }

    const std::string& innerVar() const {
        return innerVar_;
    }

    const Expression* collection() const {
        return collection_.get();
    }

    Expression* collection() {
        return collection_.get();
    }

    const Expression* mapping() const {
        return mapping_.get();
    }

    Expression* mapping() {
        return mapping_.get();
    }

    void setAccumulator(const std::string& name) {
        accumulator_ = name;
    }

    void setInitial(Expression* expr) {
        initial_.reset(expr);
    }

    void setInnerVar(const std::string& name) {
        innerVar_ = name;
    }

    void setCollection(Expression* expr) {
        collection_.reset(expr);
    }

    void setMapping(Expression* expr) {
        mapping_.reset(expr);
    }

    void setOriginString(const std::string& s) {
        originString_ = s;
    }

    std::string makeString() const;

    bool hasOriginString() const {
        return !originString_.empty();
    }

private:
    void writeTo(Encoder& encoder) const override;

    void resetFrom(Decoder& decoder) override;

    std::string accumulator_;
    std::unique_ptr<Expression> initial_;
    std::string innerVar_;
    std::unique_ptr<Expression> collection_;
    std::unique_ptr<Expression> mapping_;
    std::string originString_;
    Value result_;
};

}   // namespace nebula
#endif   // EXPRESSION_REDUCEEXPRESSIONEXPRESSION_H_
