# Copyright 2023 The TensorFlow Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ==============================================================================
# Description:
#  Holds the tests for the native layer of the app.

package(
    # copybara:uncomment default_applicable_licenses = ["@org_tensorflow//tensorflow:license"],
    licenses = ["notice"],
)

cc_test(
    name = "latency_benchmark_test",
    srcs = ["latency_benchmark_test.cc"],
    data = [
        "//tflite/delegates/utils/experimental/sample_stable_delegate:tensorflowlite_sample_stable_delegate",
        "//tflite/tools/delegates/experimental/stable_delegate:test_sample_stable_delegate_settings.json",
        "@tflite_mobilenet_float//:mobilenet_v1_1.0_224.tflite",
    ],
    deps = [
        "//tflite/acceleration/configuration:configuration_fbs",
        "//tflite/delegates/utils/experimental/stable_delegate:tflite_settings_json_parser",
        "//tflite/tools/benchmark/experimental/delegate_performance/android/proto:delegate_performance_cc_proto",
        "//tflite/tools/benchmark/experimental/delegate_performance/android/src/main/native:latency_benchmark",
        "@com_google_googletest//:gtest_main",
        "@flatbuffers",
    ],
)

cc_test(
    name = "accuracy_benchmark_test",
    srcs = ["accuracy_benchmark_test.cc"],
    data = [
        "//tflite/delegates/utils/experimental/sample_stable_delegate:tensorflowlite_sample_stable_delegate",
        "//tflite/delegates/utils/experimental/stable_delegate:test_xnnpack_settings.json",
        "//tflite/tools/delegates/experimental/stable_delegate:test_sample_stable_delegate_settings.json",
    ],
    deps = [
        "//tflite/acceleration/configuration:configuration_fbs",
        "//tflite/delegates/utils/experimental/stable_delegate:tflite_settings_json_parser",
        "//tflite/experimental/acceleration/mini_benchmark:embedded_mobilenet_validation_model",
        "//tflite/experimental/acceleration/mini_benchmark:mini_benchmark_test_helper",
        "//tflite/tools/benchmark/experimental/delegate_performance/android/src/main/native:accuracy_benchmark",
        "//tflite/tools/benchmark/experimental/delegate_performance/android/src/main/native:status_codes",
        "@com_google_googletest//:gtest_main",
        "@flatbuffers",
    ],
)
