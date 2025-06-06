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

load("//tflite/experimental/litert/build_common:tfl_model_gen.bzl", "tfl_model_gen")

package(
    # copybara:uncomment default_applicable_licenses = ["@org_tensorflow//tensorflow:license"],
    default_visibility = [
        # copybara:uncomment "@org_tensorflow//third_party/mediapipe/calculators/tensor:__subpackages__",
        # copybara:uncomment "@org_tensorflow//third_party/odml/litert:__subpackages__",
        "//tflite/experimental/litert:__subpackages__",
    ],
)

tfl_model_gen(
    name = "mlir_test_data",
    srcs = glob(["testdata/*.mlir"]),
)

filegroup(
    name = "tflite_test_data",
    srcs = glob(["testdata/*.tflite"]),
)

cc_library(
    name = "common",
    testonly = 1,
    srcs = [
        "common.cc",
    ],
    hdrs = [
        "common.h",
    ],
    deps = [
        "//tflite:framework",
        "//tflite/c:c_api_opaque",
        "//tflite/c:common",
        "//tflite/core:cc_api_stable",
        "//tflite/experimental/litert/c:litert_common",
        "//tflite/experimental/litert/c:litert_logging",
        "//tflite/experimental/litert/cc:litert_expected",
        "//tflite/experimental/litert/cc:litert_model",
        "//tflite/experimental/litert/cc:litert_model_predicates",
        "//tflite/experimental/litert/core:filesystem",
        "//tflite/experimental/litert/core/model:model_buffer",
        "//tflite/experimental/litert/core/util:flatbuffer_tools",
        "//tflite/kernels:builtin_ops",
        "@com_google_absl//absl/base:core_headers",
        "@com_google_absl//absl/log:check",
        "@com_google_absl//absl/strings:string_view",
        "@com_google_absl//absl/synchronization",
        "@local_tsl//tsl/platform",
    ],
)

cc_library(
    name = "simple_model",
    testonly = 1,
    hdrs = [
        "testdata/simple_model_test_vectors.h",
    ],
    data = [
        "testdata/simple_model.tflite",
    ],
    deps = [
        "//tflite/experimental/litert/c:litert_model",
        "//tflite/experimental/litert/cc:litert_layout",
    ],
)

cc_library(
    name = "simple_model_npu",
    testonly = 1,
    srcs = [],
    hdrs = [
        "testdata/simple_model_test_vectors.h",
    ],
    data = [
        "testdata/simple_model_google_tensor.bin",
        "testdata/simple_model_mtk.bin",
        "testdata/simple_model_npu.tflite",
        "testdata/simple_model_qualcomm.bin",
    ],
    deps = [
        "//tflite/experimental/litert/c:litert_model",
        "//tflite/experimental/litert/cc:litert_layout",
    ],
)

cc_library(
    name = "simple_cascade_model_npu",
    testonly = 1,
    srcs = [],
    hdrs = [
        "testdata/simple_model_test_vectors.h",
    ],
    data = [
        "testdata/simple_cascade_model_npu.tflite",
        "testdata/simple_model_google_tensor.bin",
        "testdata/simple_model_mtk.bin",
        "testdata/simple_model_qualcomm.bin",
    ],
    deps = [
        "//tflite/experimental/litert/c:litert_model",
        "//tflite/experimental/litert/cc:litert_layout",
    ],
)

cc_library(
    name = "test_models",
    hdrs = ["test_models.h"],
    deps = [
        "@com_google_absl//absl/strings:string_view",
        "@com_google_absl//absl/types:span",
    ],
)

cc_library(
    name = "matchers",
    testonly = True,
    hdrs = ["matchers.h"],
    deps = [
        "//tflite/experimental/litert/c:litert_common",
        "//tflite/experimental/litert/cc:litert_expected",
        "@com_google_absl//absl/strings:string_view",
        "@com_google_googletest//:gtest",
    ],
)

cc_test(
    name = "matchers_test",
    srcs = ["matchers_test.cc"],
    deps = [
        ":matchers",
        "//tflite/experimental/litert/c:litert_common",
        "//tflite/experimental/litert/cc:litert_expected",
        "@com_google_googletest//:gtest_main",
    ],
)

# Use this library if you want to enforce an OSS environment for your test.
cc_library(
    name = "matchers_oss",
    testonly = True,
    hdrs = ["matchers.h"],
    defines = ["LITERT_DEFINE_GTEST_STATUS_PRINTER"],
    tags = ["avoid_dep"],
    deps = [
        "//tflite/experimental/litert/c:litert_common",
        "//tflite/experimental/litert/cc:litert_expected",
        "@com_google_absl//absl/strings:str_format",
        "@com_google_absl//absl/strings:string_view",
        "@com_google_googletest//:gtest",
    ],
)

exports_files(srcs = [
    "testdata/mobilenet_v2_1.0_224.tflite",
    "testdata/simple_model_google_tensor.bin",
    "testdata/simple_model_mtk.bin",
    "testdata/simple_model_qualcomm.bin",
])
