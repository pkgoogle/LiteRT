# Copyright 2024 Google LLC.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

package(
    # copybara:uncomment default_applicable_licenses = ["@org_tensorflow//tensorflow:license"],
    default_visibility = ["//tflite/experimental/litert/vendors/qualcomm/compiler:__subpackages__"],
)

cc_library(
    name = "qnn_tensor",
    srcs = ["qnn_tensor.cc"],
    hdrs = ["qnn_tensor.h"],
    tags = [
        # Don't build/test in OS until qnn is available.
        "nobuilder",
    ],
    deps = [
        "@com_google_absl//absl/log:absl_check",
        "@com_google_absl//absl/types:span",
        # copybara:uncomment "@org_tensorflow//third_party/qairt/latest:qnn_lib_headers",
        "//tflite/experimental/litert/c:litert_common",
        "//tflite/experimental/litert/c:litert_logging",
        "//tflite/experimental/litert/c:litert_model",
        "//tflite/experimental/litert/cc:litert_expected",
        "//tflite/experimental/litert/cc:litert_macros",
        "//tflite/experimental/litert/cc:litert_model",
        "//tflite/experimental/litert/vendors/qualcomm:common",
    ],
)

cc_test(
    name = "qnn_tensor_test",
    srcs = ["qnn_tensor_test.cc"],
    data = [
        "//tflite/experimental/litert/test:mlir_test_data",
        "//tflite/experimental/litert/test:tflite_test_data",
    ],
    tags = [
        # Don't build/test in OS until qnn is available.
        "nobuilder",
        "no_oss",
    ],
    deps = [
        ":qnn_tensor",
        "@com_google_googletest//:gtest_main",
        "@com_google_absl//absl/types:span",
        # copybara:uncomment "@org_tensorflow//third_party/qairt/latest:qnn_lib_headers",
        "//tflite/experimental/litert/c:litert_model",
        "//tflite/experimental/litert/cc:litert_model",
        "//tflite/experimental/litert/test:common",
        "//tflite/experimental/litert/test:matchers",
        "//tflite/experimental/litert/test:test_models",
    ],
)

cc_library(
    name = "qnn_op",
    srcs = ["qnn_op.cc"],
    hdrs = ["qnn_op.h"],
    tags = [
        # Don't build/test in OS until qnn is available.
        "nobuilder",
    ],
    deps = [
        # copybara:uncomment "@org_tensorflow//third_party/qairt/latest:qnn_lib_headers",
        "//tflite/experimental/litert/c:litert_common",
        "//tflite/experimental/litert/c:litert_model",
        "//tflite/experimental/litert/c:litert_op_code",
        "//tflite/experimental/litert/cc:litert_model",
    ],
)

cc_test(
    name = "qnn_op_test",
    srcs = ["qnn_op_test.cc"],
    data = ["//tflite/experimental/litert/test:mlir_test_data"],
    tags = [
        # Don't build/test in OS until qnn is available.
        "nobuilder",
        "no_oss",
    ],
    deps = [
        ":qnn_op",
        "@com_google_googletest//:gtest_main",
        "@com_google_absl//absl/strings",
        # copybara:uncomment "@org_tensorflow//third_party/qairt/latest:qnn_lib_headers",
        "//tflite/experimental/litert/c:litert_common",
        "//tflite/experimental/litert/test:common",
        "//tflite/experimental/litert/test:matchers",
    ],
)

cc_test(
    name = "op_compatibility_test",
    srcs = ["op_compatibility_test.cc"],
    data = ["//tflite/experimental/litert/test:mlir_test_data"],
    tags = [
        # Don't build/test in OS until qnn is available.
        "nobuilder",
        "no_oss",
    ],
    deps = [
        ":qnn_op",
        "@com_google_googletest//:gtest_main",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:str_format",
        "@com_google_absl//absl/strings:string_view",
        # copybara:uncomment "@org_tensorflow//third_party/qairt/latest:qnn_lib_headers",
        "//tflite/experimental/litert/test:common",
        "//tflite/experimental/litert/test:matchers",
    ],
)
