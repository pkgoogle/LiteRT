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

load("//tflite/experimental/litert/vendors/qualcomm:qualcomm_build_defs.bzl", "litert_cc_bin_with_qnn")

package(
    # copybara:uncomment default_applicable_licenses = ["@org_tensorflow//tensorflow:license"],
    default_visibility = ["//tflite/experimental/litert:__subpackages__"],
)

cc_library(
    name = "apply_plugin",
    srcs = ["apply_plugin.cc"],
    hdrs = ["apply_plugin.h"],
    deps = [
        ":dump",
        ":outstream",
        ":tool_display",
        "//tflite/experimental/litert/c:litert_common",
        "//tflite/experimental/litert/c:litert_logging",
        "//tflite/experimental/litert/c:litert_model",
        "//tflite/experimental/litert/cc:litert_buffer_ref",
        "//tflite/experimental/litert/cc:litert_expected",
        "//tflite/experimental/litert/cc:litert_macros",
        "//tflite/experimental/litert/cc:litert_model",
        "//tflite/experimental/litert/compiler/plugin:compiler_flags",
        "//tflite/experimental/litert/compiler/plugin:compiler_plugin",
        "//tflite/experimental/litert/core/model:model_serialize",
        "//tflite/experimental/litert/core/util:flatbuffer_tools",
        "@com_google_absl//absl/container:flat_hash_set",
        "@com_google_absl//absl/log:absl_check",
        "@com_google_absl//absl/strings:str_format",
        "@com_google_absl//absl/strings:string_view",
        "@com_google_absl//absl/types:span",
    ],
)

cc_test(
    name = "apply_plugin_test",
    srcs = ["apply_plugin_test.cc"],
    data = [
        "//tflite/experimental/litert/test:mlir_test_data",
        "//tflite/experimental/litert/vendors/examples:example_plugin_so",
    ],
    tags = [
        "noasan",
        "nomsan",
        "nosan",
        "notsan",
    ],
    deps = [
        ":apply_plugin",
        "//tflite/experimental/litert/c:litert_common",
        "//tflite/experimental/litert/c:litert_model",
        "//tflite/experimental/litert/c:litert_op_code",
        "//tflite/experimental/litert/cc:litert_buffer_ref",
        "//tflite/experimental/litert/cc:litert_model",
        "//tflite/experimental/litert/core:build_stamp",
        "//tflite/experimental/litert/core:dispatch_op_schema",
        "//tflite/experimental/litert/core/model",
        "//tflite/experimental/litert/test:common",
        "//tflite/experimental/litert/test:matchers",
        "@com_google_absl//absl/log:absl_check",
        "@com_google_absl//absl/strings:string_view",
        "@com_google_googletest//:gtest_main",
    ],
)

# TODO - @lukeboyer: Figure out some selective inclusiion of the data deps, some are very large.
litert_cc_bin_with_qnn(
    name = "apply_plugin_main",
    srcs = ["apply_plugin_main.cc"],
    data = [
        # copybara:uncomment_begin(google-only)
        # "//platforms/darwinn/compiler:compiler_api_wrapper",
        # copybara:uncomment_end
        "//tflite/experimental/litert/vendors/examples:example_plugin_so",
        "//tflite/experimental/litert/vendors/google_tensor/compiler:google_tensor_compiler_plugin_so",
        "//tflite/experimental/litert/vendors/qualcomm/compiler:qnn_compiler_plugin_so",
        "//tflite/experimental/litert/vendors/mediatek/compiler:compiler_plugin_so",
    ],
    export_litert_only = 1,
    include_system = 1,
    linkstatic = 1,
    # copybara:uncomment malloc = "//base:system_malloc",
    tags = [
        "noasan",
        "nobuilder",
        "nomsan",
        "nosan",
    ],
    ungrte = True,
    deps = [
        ":apply_plugin",
        ":outstream",
        "//tflite/experimental/litert/compiler/plugin:compiler_flags",
        "//tflite/experimental/litert/core:build_stamp",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:str_format",
        "@com_google_absl//absl/strings:string_view",
        "@llvm-project//llvm:Support",
    ],
)

# Fork of "apply_plugin_main" without the "ungrte" so this tool can be used as part of larger
# integration test pipelines with example_plugin.
cc_binary(
    name = "apply_plugin_main_for_test",
    testonly = 1,
    srcs = ["apply_plugin_main.cc"],
    data = [
        "//tflite/experimental/litert/vendors/examples:example_plugin_so",
    ],
    linkstatic = 1,
    tags = [
        "noasan",
        "nomsan",
        "nosan",
    ],
    deps = [
        ":apply_plugin",
        ":outstream",
        "//tflite/experimental/litert/compiler/plugin:compiler_flags",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:str_format",
        "@llvm-project//llvm:Support",
    ],
)

cc_library(
    name = "tool_display",
    srcs = ["tool_display.cc"],
    hdrs = ["tool_display.h"],
    deps = [
        ":outstream",
        "@com_google_absl//absl/strings:str_format",
        "@com_google_absl//absl/strings:string_view",
    ],
)

cc_test(
    name = "tool_display_test",
    srcs = ["tool_display_test.cc"],
    data = ["//tflite/experimental/litert/test:mlir_test_data"],
    deps = [
        ":tool_display",
        "@com_google_absl//absl/strings:str_format",
        "@com_google_absl//absl/strings:string_view",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "dump",
    srcs = ["dump.cc"],
    hdrs = ["dump.h"],
    deps = [
        "//tflite/experimental/litert/c:litert_model",
        "//tflite/experimental/litert/c:litert_op_code",
        "//tflite/experimental/litert/compiler/plugin:compiler_plugin",
        "//tflite/experimental/litert/core/model",
        "@com_google_absl//absl/strings:str_format",
        "@com_google_absl//absl/strings:string_view",
    ],
)

cc_test(
    name = "dump_test",
    srcs = ["dump_test.cc"],
    data = ["//tflite/experimental/litert/test:mlir_test_data"],
    deps = [
        ":dump",
        "//tflite/experimental/litert/core/model",
        "//tflite/experimental/litert/test:common",
        "@com_google_absl//absl/strings:string_view",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "outstream",
    hdrs = ["outstream.h"],
    deps = [
        "//tflite/experimental/litert/c:litert_logging",
        "@com_google_absl//absl/strings:string_view",
    ],
)

cc_library(
    name = "benchmark_litert_model",
    srcs = ["benchmark_litert_model.cc"],
    hdrs = ["benchmark_litert_model.h"],
    deps = [
        "//tflite/c:c_api_types",
        "//tflite/c:common",
        "//tflite/experimental/litert/c:litert_common",
        "//tflite/experimental/litert/c:litert_logging",
        "//tflite/experimental/litert/cc:litert_compilation_options",
        "//tflite/experimental/litert/cc:litert_compiled_model",
        "//tflite/experimental/litert/cc:litert_environment",
        "//tflite/experimental/litert/cc:litert_model",
        "//tflite/experimental/litert/cc:litert_tensor_buffer",
        "//tflite/tools:utils",
        "//tflite/tools/benchmark:benchmark_model_lib",
        "//tflite/tools/benchmark:benchmark_params",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/types:span",
    ],
)

cc_test(
    name = "benchmark_litert_model_test",
    srcs = ["benchmark_litert_model_test.cc"],
    data = [
        "//tflite/experimental/litert/test:testdata/mobilenet_v2_1.0_224.tflite",
    ],
    env = {
        "ASAN_OPTIONS": "detect_odr_violation=0",
    },
    tags = [
        "manual",
        "notap",
        "requires-gpu-nvidia",
    ],
    deps =
        [
            ":benchmark_litert_model",
            "@com_google_googletest//:gtest_main",
            # copybara:uncomment_begin(google-only)
            # "@org_tensorflow//third_party/odml/infra/ml_drift_delegate/litert:ml_drift_cl_accelerator",  # buildcleaner: keep
            # copybara:uncomment_end
            "//tflite/core/c:c_api_types",
            "//tflite/tools/benchmark:benchmark_model_lib",
            "//tflite/tools/benchmark:benchmark_params",
        ],
)

# We create a library for benchmark_main.cc to faciliate the creation of a
# customized benchmark model binary that only needs linking with extra
# dependency, e.g., enabling creating of benchmark binaries with a custom
# delegate provider.
cc_library(
    name = "benchmark_model_main",
    srcs = [
        "benchmark_litert_model_main.cc",
    ],
    deps = [
        ":benchmark_litert_model",
        "//tflite/c:c_api_types",
        "//tflite/tools:logging",
    ],
)
