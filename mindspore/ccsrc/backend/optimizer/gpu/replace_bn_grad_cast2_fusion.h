/**
 * Copyright 2020 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MINDSPORE_CCSRC_BACKEND_OPTIMIZER_GPU_REPLACE_BN_GRAD_CAST2_FUSION_H_
#define MINDSPORE_CCSRC_BACKEND_OPTIMIZER_GPU_REPLACE_BN_GRAD_CAST2_FUSION_H_

#include <memory>
#include "backend/optimizer/common/optimizer.h"

namespace mindspore {
namespace opt {
class ReplaceBNGradCast2Fusion : public PatternProcessPass {
 public:
  explicit ReplaceBNGradCast2Fusion(bool multigraph = true) : PatternProcessPass("replace_grad_cast2", multigraph) {
    dy_ = std::make_shared<Var>();
    x_ = std::make_shared<Var>();
    scale_ = std::make_shared<Var>();
    mean_ = std::make_shared<Var>();
    var_ = std::make_shared<Var>();
    dx_ = std::make_shared<Var>();
    bn_scale_ = std::make_shared<Var>();
    bn_bias_ = std::make_shared<Var>();
    index_ = std::make_shared<Var>();
  }
  ~ReplaceBNGradCast2Fusion() override = default;
  const BaseRef DefinePattern() const override;
  const AnfNodePtr Process(const FuncGraphPtr &, const AnfNodePtr &, const EquivPtr &) const override;

 private:
  VarPtr dy_;
  VarPtr x_;
  VarPtr scale_;
  VarPtr mean_;
  VarPtr var_;
  VarPtr dx_;
  VarPtr bn_scale_;
  VarPtr bn_bias_;
  VarPtr index_;
};
}  // namespace opt
}  // namespace mindspore
#endif  // MINDSPORE_CCSRC_BACKEND_OPTIMIZER_GPU_REPLACE_BN_GRAD_CAST2_FUSION_H_
