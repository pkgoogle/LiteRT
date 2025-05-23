# Description:
#   BenchmarkModel Android harness for Firebase Test Lab.

load("@build_bazel_rules_android//android:rules.bzl", "android_binary")
load("//tflite:build_def.bzl", "tflite_jni_binary")
load("//tflite:special_rules.bzl", "tflite_hexagon_nn_skel_libraries")

package(
    # copybara:uncomment default_applicable_licenses = ["@org_tensorflow//tensorflow:license"],
    default_visibility = ["//visibility:private"],
    licenses = ["notice"],
)

android_binary(
    name = "benchmark_model_firebase",
    srcs = glob([
        "src/**/*.java",
    ]),
    custom_package = "org.tensorflow.lite.benchmark.firebase",
    manifest = "AndroidManifest.xml",
    multidex = "native",
    # In some platforms we don't have an Android SDK/NDK and this target
    # can't be built. We need to prevent the build system from trying to
    # use the target in that case.
    tags = ["manual"],
    deps = [
        ":hexagon_libs",
        ":tensorflowlite_benchmark_firebase_native",
    ],
)

tflite_jni_binary(
    name = "libtensorflowlite_benchmark_firebase.so",
    srcs = glob([
        "jni/**/*.cc",
        "jni/**/*.h",
    ]),
    deps = [
        "//tflite/java/jni",
        "//tflite/tools/benchmark:benchmark_tflite_model_lib",
    ],
)

cc_library(
    name = "tensorflowlite_benchmark_firebase_native",
    srcs = ["libtensorflowlite_benchmark_firebase.so"],
    visibility = ["//visibility:private"],
)

cc_library(
    name = "hexagon_libs",
    srcs = select({
        "@org_tensorflow//tensorflow:android_arm64": [
            "//tflite/delegates/hexagon/hexagon_nn:libhexagon_interface.so",
        ] + tflite_hexagon_nn_skel_libraries(),
        "@org_tensorflow//tensorflow:android_arm": [
            "//tflite/delegates/hexagon/hexagon_nn:libhexagon_interface.so",
        ] + tflite_hexagon_nn_skel_libraries(),
        "//conditions:default": [],
    }),
    visibility = ["//visibility:private"],
)
