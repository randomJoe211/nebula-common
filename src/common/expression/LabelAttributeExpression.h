/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#ifndef COMMON_EXPRESSION_LABELATTRIBUTEEXPRESSION_H_
#define COMMON_EXPRESSION_LABELATTRIBUTEEXPRESSION_H_

#include "common/expression/LabelExpression.h"

namespace nebula {

// label.label
class LabelAttributeExpression final : public Expression {
public:
    explicit LabelAttributeExpression(LabelExpression *lhs = nullptr,
                                      LabelExpression *rhs = nullptr)
        : Expression(Kind::kLabelAttribute) {
        lhs_.reset(lhs);
        rhs_.reset(rhs);
    }

    bool operator==(const Expression &rhs) const override {
        if (rhs.kind() != kind()) {
            return false;
        }
        auto &expr = static_cast<const LabelAttributeExpression&>(rhs);
        return *lhs_ == *expr.lhs_ && *rhs_ == *expr.rhs_;
    }

    const Value& eval(ExpressionContext&) override {
        LOG(FATAL) << "LabelAttributeExpression has to be rewritten";
    }

    const LabelExpression* left() const {
        return lhs_.get();
    }

    const LabelExpression* right() const {
        return rhs_.get();
    }

    std::string toString() const override;

private:
    void writeTo(Encoder&) const override {
        LOG(FATAL) << "LabelAttributeExpression cannot be encoded";
    }

    void resetFrom(Decoder&) override {
        LOG(FATAL) << "LabelAttributeExpression cannot be decoded";
    }

private:
    std::unique_ptr<LabelExpression>    lhs_;
    std::unique_ptr<LabelExpression>    rhs_;
};

}   // namespace nebula

#endif  // COMMON_EXPRESSION_LABELATTRIBUTEEXPRESSION_H_
