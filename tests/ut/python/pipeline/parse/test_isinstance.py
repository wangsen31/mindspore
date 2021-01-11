# Copyright 2021 Huawei Technologies Co., Ltd
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ============================================================================
""" test instance"""
import numpy as np
import pytest

import mindspore.nn as nn
from mindspore import Tensor
from mindspore import context

context.set_context(mode=context.GRAPH_MODE, save_graphs=True)


def test_isinstance():
    class Net(nn.Cell):
        def __init__(self):
            super(Net, self).__init__()
            self.int_member = 1
            self.float_member = 1.0
            self.bool_member = True
            self.string_member = "abcd"
            self.tensor_member = Tensor(np.arange(4))
            self.tuple_member = (1, 1.0, True, "abcd", self.tensor_member)
            self.list_member = list(self.tuple_member)

        def construct(self, x, y):
            is_int = isinstance(self.int_member, int)
            is_float = isinstance(self.float_member, float)
            is_bool = isinstance(self.bool_member, bool)
            is_string = isinstance(self.string_member, str)
            is_tensor_const = isinstance(self.tensor_member, Tensor)
            is_tensor_var = isinstance(x, Tensor)
            is_tuple_const = isinstance(self.tuple_member, tuple)
            is_tuple_var = isinstance((x, 1, 1.0, y), tuple)
            is_list_const = isinstance(self.list_member, list)
            is_list_var = isinstance([x, 1, 1.0, y], list)
            is_list_or_tensor = isinstance([x, y], (Tensor, list))
            is_int_or_float_or_tensor_or_tuple = isinstance(x, (Tensor, tuple, int, float))
            float_is_int = isinstance(self.float_member, int)
            bool_is_string = isinstance(self.bool_member, str)
            tensor_is_tuple = isinstance(x, tuple)
            tuple_is_list = isinstance(self.tuple_member, list)
            return is_int, is_float, is_bool, is_string, is_tensor_const, is_tensor_var, \
                   is_tuple_const, is_tuple_var, is_list_const, is_list_var, \
                   is_int_or_float_or_tensor_or_tuple, is_list_or_tensor, \
                   float_is_int, bool_is_string, tensor_is_tuple, tuple_is_list

    net = Net()
    x = Tensor(np.arange(4))
    y = Tensor(np.arange(5))
    assert net(x, y) == (True,) * 12 + (False,) * 4


def test_isinstance_not_supported():
    class Net(nn.Cell):
        def __init__(self):
            super(Net, self).__init__()
            self.value = (11, 22, 33, 44)

        def construct(self):
            return isinstance(self.value, None)

    net = Net()
    with pytest.raises(TypeError) as err:
        net()
    assert "The type 'None' is not supported for 'isinstance'" in str(err.value)