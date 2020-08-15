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

#include <memory>
#include "tools/converter/parser/onnx/onnx_elu_parser.h"

namespace mindspore {
namespace lite {
STATUS OnnxEluParser::Parse(const onnx::GraphProto &onnx_graph, const onnx::NodeProto &onnx_node, schema::CNodeT *op) {
  MS_LOG(DEBUG) << "onnx EluParser";
  std::unique_ptr<schema::EluT> attr(new schema::EluT());
  for (const auto &onnx_node_attr : onnx_node.attribute()) {
    const auto& attribute_name = onnx_node_attr.name();
    if (attribute_name == "alpha") {
      attr->alpha = onnx_node_attr.f();
    }
  }
  if (op != nullptr) {
    op->primitive = std::make_unique<schema::PrimitiveT>();
    op->primitive->value.type = schema::PrimitiveType_Elu;
    op->primitive->value.value = attr.release();
  }
  return RET_OK;
}

OnnxNodeRegistrar g_onnxEluParser("Elu", new OnnxEluParser());
}  // namespace lite
}  // namespace mindspore

