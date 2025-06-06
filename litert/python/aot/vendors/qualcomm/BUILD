# Copyright 2025 Google LLC.
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

load("@org_tensorflow//tensorflow:pytype.default.bzl", "pytype_strict_contrib_test", "pytype_strict_library")

package(
    # copybara:uncomment default_applicable_licenses = ["@org_tensorflow//tensorflow:license"],
    default_visibility = ["//litert:litert_python_internal_users"],
)

pytype_strict_library(
    name = "qualcomm_backend",
    srcs = ["qualcomm_backend.py"],
    deps = [
        ":target",
        "//litert/python/aot/core:components",
        "//litert/python/aot/core:types",
        "//litert/python/aot/vendors:import_vendor",
    ],
)

pytype_strict_library(
    name = "target",
    srcs = ["target.py"],
    deps = ["//litert/python/aot/core:types"],
)

pytype_strict_contrib_test(
    name = "qualcomm_backend_test",
    srcs = ["qualcomm_backend_test.py"],
    deps = [
        ":qualcomm_backend",
        ":target",
        "@absl_py//absl/testing:absltest",
        "//litert/python/aot/core:components",
        "//litert/python/aot/core:test_common",
        "//litert/python/aot/core:types",
    ],
)
