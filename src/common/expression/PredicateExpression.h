/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#ifndef COMMON_EXPRESSION_PREDICATEEXPRESSIONEXPRESSION_H_
#define COMMON_EXPRESSION_PREDICATEEXPRESSIONEXPRESSION_H_

#include "common/expression/Expression.h"
#include "common/datatypes/Map.h"

namespace nebula {

class PredicateExpression final : public Expression {
    friend class Expression;

public:
    enum class Type : int8_t {
        ALL = 0,
        ANY = 1,
        SINGLE = 2,
        NONE = 3,
    };

    explicit PredicateExpression(const std::string& name = "",
                                 const std::string& innerVar = "",
                                 Expression* collection = nullptr,
                                 Expression* filter = nullptr)
        : Expression(Kind::kPredicate),
          name_(name),
          innerVar_(innerVar),
          collection_(collection),
          filter_(filter) {}

    bool operator==(const Expression& rhs) const override;

    const Value& eval(ExpressionContext& ctx) override;

    std::string toString() const override;

    void accept(ExprVisitor* visitor) override;

    std::unique_ptr<Expression> clone() const override;

    const std::string& name() const {
        return name_;
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

    const Expression* filter() const {
        return filter_.get();
    }

    Expression* filter() {
        return filter_.get();
    }

    void setInnerVar(const std::string& name) {
        innerVar_ = name;
    }

    void setCollection(Expression* expr) {
        collection_.reset(expr);
    }

    void setFilter(Expression* expr) {
        filter_.reset(expr);
    }

    void setOriginString(const std::string& s) {
        originString_ = s;
    }

    std::string makeString() const;

    bool hasOriginString() const {
        return !originString_.empty();
    }

    bool hasInnerVar() const {
        return !innerVar_.empty();
    }

    bool hasFilter() const {
        return filter_ != nullptr;
    }

private:
    const Value& evalExists(ExpressionContext& ctx);

    void writeTo(Encoder& encoder) const override;

    void resetFrom(Decoder& decoder) override;

    static std::unordered_map<std::string, Type> typeMap_;

    std::string name_;
    std::string innerVar_;
    std::unique_ptr<Expression> collection_;
    std::unique_ptr<Expression> filter_;
    std::string originString_;
    Value result_;
};

}   // namespace nebula
#endif   // EXPRESSION_PREDICATEEXPRESSIONEXPRESSION_H_
