/* Copyright 2021 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include <cstdint>
#include <functional>
#include <limits>
#include <memory>
#include <random>

#include <gtest/gtest.h>
#include "tflite/delegates/xnnpack/quantized_fully_connected_tester.h"
#include "tflite/delegates/xnnpack/xnnpack_delegate.h"

namespace tflite {
namespace xnnpack {

TEST(UnsignedQuantizedFullyConnected, 1D) {
  std::unique_ptr<TfLiteDelegate, decltype(&TfLiteXNNPackDelegateDelete)>
      xnnpack_delegate(TfLiteXNNPackDelegateCreate(nullptr),
                       TfLiteXNNPackDelegateDelete);

  std::random_device random_device;
  auto rng = std::mt19937(random_device());
  auto zero_point_rng = std::bind(std::uniform_int_distribution<int32_t>(
                                      std::numeric_limits<uint8_t>::min(),
                                      std::numeric_limits<uint8_t>::max()),
                                  std::ref(rng));
  auto filter_zero_point_rng = std::bind(
      std::uniform_int_distribution<int32_t>(100, 150), std::ref(rng));
  auto channels_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 9), std::ref(rng));
  const auto input_channels = channels_rng();
  const auto output_channels = channels_rng();

  QuantizedFullyConnectedTester()
      .InputZeroPoint(zero_point_rng())
      .FilterZeroPoint(filter_zero_point_rng())
      .OutputZeroPoint(zero_point_rng())
      .InputShape({input_channels})
      .InputChannels(input_channels)
      .OutputChannels(output_channels)
      .Test(xnnpack_delegate.get());
}

TEST(UnsignedQuantizedFullyConnected, 1DKeepDims) {
  std::unique_ptr<TfLiteDelegate, decltype(&TfLiteXNNPackDelegateDelete)>
      xnnpack_delegate(TfLiteXNNPackDelegateCreate(nullptr),
                       TfLiteXNNPackDelegateDelete);

  std::random_device random_device;
  auto rng = std::mt19937(random_device());
  auto zero_point_rng = std::bind(std::uniform_int_distribution<int32_t>(
                                      std::numeric_limits<uint8_t>::min(),
                                      std::numeric_limits<uint8_t>::max()),
                                  std::ref(rng));
  auto filter_zero_point_rng = std::bind(
      std::uniform_int_distribution<int32_t>(100, 150), std::ref(rng));
  auto channels_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 9), std::ref(rng));
  const auto input_channels = channels_rng();
  const auto output_channels = channels_rng();

  QuantizedFullyConnectedTester()
      .InputZeroPoint(zero_point_rng())
      .FilterZeroPoint(filter_zero_point_rng())
      .OutputZeroPoint(zero_point_rng())
      .InputShape({input_channels})
      .InputChannels(input_channels)
      .OutputChannels(output_channels)
      .KeepDims(true)
      .Test(xnnpack_delegate.get());
}

TEST(UnsignedQuantizedFullyConnected, 2D) {
  std::unique_ptr<TfLiteDelegate, decltype(&TfLiteXNNPackDelegateDelete)>
      xnnpack_delegate(TfLiteXNNPackDelegateCreate(nullptr),
                       TfLiteXNNPackDelegateDelete);

  std::random_device random_device;
  auto rng = std::mt19937(random_device());
  auto zero_point_rng = std::bind(std::uniform_int_distribution<int32_t>(
                                      std::numeric_limits<uint8_t>::min(),
                                      std::numeric_limits<uint8_t>::max()),
                                  std::ref(rng));
  auto filter_zero_point_rng = std::bind(
      std::uniform_int_distribution<int32_t>(100, 150), std::ref(rng));
  auto batch_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 5), std::ref(rng));
  auto channels_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 9), std::ref(rng));
  const auto batch = batch_rng();
  const auto input_channels = channels_rng();
  const auto output_channels = channels_rng();

  QuantizedFullyConnectedTester()
      .InputZeroPoint(zero_point_rng())
      .FilterZeroPoint(filter_zero_point_rng())
      .OutputZeroPoint(zero_point_rng())
      .InputShape({batch, input_channels})
      .InputChannels(input_channels)
      .OutputChannels(output_channels)
      .Test(xnnpack_delegate.get());
}

TEST(UnsignedQuantizedFullyConnected, 2DKeepDims) {
  std::unique_ptr<TfLiteDelegate, decltype(&TfLiteXNNPackDelegateDelete)>
      xnnpack_delegate(TfLiteXNNPackDelegateCreate(nullptr),
                       TfLiteXNNPackDelegateDelete);

  std::random_device random_device;
  auto rng = std::mt19937(random_device());
  auto zero_point_rng = std::bind(std::uniform_int_distribution<int32_t>(
                                      std::numeric_limits<uint8_t>::min(),
                                      std::numeric_limits<uint8_t>::max()),
                                  std::ref(rng));
  auto filter_zero_point_rng = std::bind(
      std::uniform_int_distribution<int32_t>(100, 150), std::ref(rng));
  auto batch_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 5), std::ref(rng));
  auto channels_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 9), std::ref(rng));
  const auto batch = batch_rng();
  const auto input_channels = channels_rng();
  const auto output_channels = channels_rng();

  QuantizedFullyConnectedTester()
      .InputZeroPoint(zero_point_rng())
      .FilterZeroPoint(filter_zero_point_rng())
      .OutputZeroPoint(zero_point_rng())
      .InputShape({batch, input_channels})
      .InputChannels(input_channels)
      .OutputChannels(output_channels)
      .KeepDims(true)
      .Test(xnnpack_delegate.get());
}

TEST(UnsignedQuantizedFullyConnected, 3D) {
  std::unique_ptr<TfLiteDelegate, decltype(&TfLiteXNNPackDelegateDelete)>
      xnnpack_delegate(TfLiteXNNPackDelegateCreate(nullptr),
                       TfLiteXNNPackDelegateDelete);

  std::random_device random_device;
  auto rng = std::mt19937(random_device());
  auto zero_point_rng = std::bind(std::uniform_int_distribution<int32_t>(
                                      std::numeric_limits<uint8_t>::min(),
                                      std::numeric_limits<uint8_t>::max()),
                                  std::ref(rng));
  auto filter_zero_point_rng = std::bind(
      std::uniform_int_distribution<int32_t>(100, 150), std::ref(rng));
  auto shape_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 5), std::ref(rng));
  auto channels_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 9), std::ref(rng));
  const auto batch = shape_rng();
  const auto width = shape_rng();
  const auto input_channels = channels_rng();
  const auto output_channels = channels_rng();

  QuantizedFullyConnectedTester()
      .InputZeroPoint(zero_point_rng())
      .FilterZeroPoint(filter_zero_point_rng())
      .OutputZeroPoint(zero_point_rng())
      .InputShape({batch, width, input_channels})
      .InputChannels(input_channels)
      .OutputChannels(output_channels)
      .Test(xnnpack_delegate.get());
}

TEST(UnsignedQuantizedFullyConnected, 3DReshape) {
  std::unique_ptr<TfLiteDelegate, decltype(&TfLiteXNNPackDelegateDelete)>
      xnnpack_delegate(TfLiteXNNPackDelegateCreate(nullptr),
                       TfLiteXNNPackDelegateDelete);

  std::random_device random_device;
  auto rng = std::mt19937(random_device());
  auto zero_point_rng = std::bind(std::uniform_int_distribution<int32_t>(
                                      std::numeric_limits<uint8_t>::min(),
                                      std::numeric_limits<uint8_t>::max()),
                                  std::ref(rng));
  auto filter_zero_point_rng = std::bind(
      std::uniform_int_distribution<int32_t>(100, 150), std::ref(rng));
  auto shape_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 5), std::ref(rng));
  auto channels_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 9), std::ref(rng));
  const auto batch = shape_rng();
  const auto width = shape_rng();
  const auto input_channels = channels_rng();
  const auto output_channels = channels_rng();

  QuantizedFullyConnectedTester()
      .InputZeroPoint(zero_point_rng())
      .FilterZeroPoint(filter_zero_point_rng())
      .OutputZeroPoint(zero_point_rng())
      .InputShape({batch, width, input_channels})
      .InputChannels(width * input_channels)
      .OutputChannels(output_channels)
      .Test(xnnpack_delegate.get());
}

TEST(UnsignedQuantizedFullyConnected, 3DKeepDims) {
  std::unique_ptr<TfLiteDelegate, decltype(&TfLiteXNNPackDelegateDelete)>
      xnnpack_delegate(TfLiteXNNPackDelegateCreate(nullptr),
                       TfLiteXNNPackDelegateDelete);

  std::random_device random_device;
  auto rng = std::mt19937(random_device());
  auto zero_point_rng = std::bind(std::uniform_int_distribution<int32_t>(
                                      std::numeric_limits<uint8_t>::min(),
                                      std::numeric_limits<uint8_t>::max()),
                                  std::ref(rng));
  auto filter_zero_point_rng = std::bind(
      std::uniform_int_distribution<int32_t>(100, 150), std::ref(rng));
  auto shape_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 5), std::ref(rng));
  auto channels_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 9), std::ref(rng));
  const auto batch = shape_rng();
  const auto width = shape_rng();
  const auto input_channels = channels_rng();
  const auto output_channels = channels_rng();

  QuantizedFullyConnectedTester()
      .InputZeroPoint(zero_point_rng())
      .FilterZeroPoint(filter_zero_point_rng())
      .OutputZeroPoint(zero_point_rng())
      .InputShape({batch, width, input_channels})
      .InputChannels(input_channels)
      .OutputChannels(output_channels)
      .KeepDims(true)
      .Test(xnnpack_delegate.get());
}

TEST(UnsignedQuantizedFullyConnected, 4D) {
  std::unique_ptr<TfLiteDelegate, decltype(&TfLiteXNNPackDelegateDelete)>
      xnnpack_delegate(TfLiteXNNPackDelegateCreate(nullptr),
                       TfLiteXNNPackDelegateDelete);

  std::random_device random_device;
  auto rng = std::mt19937(random_device());
  auto zero_point_rng = std::bind(std::uniform_int_distribution<int32_t>(
                                      std::numeric_limits<uint8_t>::min(),
                                      std::numeric_limits<uint8_t>::max()),
                                  std::ref(rng));
  auto filter_zero_point_rng = std::bind(
      std::uniform_int_distribution<int32_t>(100, 150), std::ref(rng));
  auto shape_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 5), std::ref(rng));
  auto channels_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 9), std::ref(rng));
  const auto batch = shape_rng();
  const auto height = shape_rng();
  const auto width = shape_rng();
  const auto input_channels = channels_rng();
  const auto output_channels = channels_rng();

  QuantizedFullyConnectedTester()
      .InputZeroPoint(zero_point_rng())
      .FilterZeroPoint(filter_zero_point_rng())
      .OutputZeroPoint(zero_point_rng())
      .InputShape({batch, height, width, input_channels})
      .InputChannels(input_channels)
      .OutputChannels(output_channels)
      .Test(xnnpack_delegate.get());
}

TEST(UnsignedQuantizedFullyConnected, 4DKeepDims) {
  std::unique_ptr<TfLiteDelegate, decltype(&TfLiteXNNPackDelegateDelete)>
      xnnpack_delegate(TfLiteXNNPackDelegateCreate(nullptr),
                       TfLiteXNNPackDelegateDelete);

  std::random_device random_device;
  auto rng = std::mt19937(random_device());
  auto zero_point_rng = std::bind(std::uniform_int_distribution<int32_t>(
                                      std::numeric_limits<uint8_t>::min(),
                                      std::numeric_limits<uint8_t>::max()),
                                  std::ref(rng));
  auto filter_zero_point_rng = std::bind(
      std::uniform_int_distribution<int32_t>(100, 150), std::ref(rng));
  auto shape_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 5), std::ref(rng));
  auto channels_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 9), std::ref(rng));
  const auto batch = shape_rng();
  const auto height = shape_rng();
  const auto width = shape_rng();
  const auto input_channels = channels_rng();
  const auto output_channels = channels_rng();

  QuantizedFullyConnectedTester()
      .InputZeroPoint(zero_point_rng())
      .FilterZeroPoint(filter_zero_point_rng())
      .OutputZeroPoint(zero_point_rng())
      .InputShape({batch, height, width, input_channels})
      .InputChannels(input_channels)
      .OutputChannels(output_channels)
      .KeepDims(true)
      .Test(xnnpack_delegate.get());
}

TEST(UnsignedQuantizedFullyConnected, NoBias) {
  std::unique_ptr<TfLiteDelegate, decltype(&TfLiteXNNPackDelegateDelete)>
      xnnpack_delegate(TfLiteXNNPackDelegateCreate(nullptr),
                       TfLiteXNNPackDelegateDelete);

  std::random_device random_device;
  auto rng = std::mt19937(random_device());
  auto zero_point_rng = std::bind(std::uniform_int_distribution<int32_t>(
                                      std::numeric_limits<uint8_t>::min(),
                                      std::numeric_limits<uint8_t>::max()),
                                  std::ref(rng));
  auto filter_zero_point_rng = std::bind(
      std::uniform_int_distribution<int32_t>(100, 150), std::ref(rng));
  auto batch_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 5), std::ref(rng));
  auto channels_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 9), std::ref(rng));
  const auto batch = batch_rng();
  const auto input_channels = channels_rng();
  const auto output_channels = channels_rng();

  QuantizedFullyConnectedTester()
      .InputZeroPoint(zero_point_rng())
      .FilterZeroPoint(filter_zero_point_rng())
      .OutputZeroPoint(zero_point_rng())
      .InputShape({batch, input_channels})
      .InputChannels(input_channels)
      .OutputChannels(output_channels)
      .NoBias()
      .Test(xnnpack_delegate.get());
}

TEST(UnsignedQuantizedFullyConnected, ReluActivation) {
  std::unique_ptr<TfLiteDelegate, decltype(&TfLiteXNNPackDelegateDelete)>
      xnnpack_delegate(TfLiteXNNPackDelegateCreate(nullptr),
                       TfLiteXNNPackDelegateDelete);

  std::random_device random_device;
  auto rng = std::mt19937(random_device());
  auto zero_point_rng = std::bind(std::uniform_int_distribution<int32_t>(
                                      std::numeric_limits<uint8_t>::min(),
                                      std::numeric_limits<uint8_t>::max()),
                                  std::ref(rng));
  auto filter_zero_point_rng = std::bind(
      std::uniform_int_distribution<int32_t>(100, 150), std::ref(rng));
  auto batch_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 5), std::ref(rng));
  auto channels_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 9), std::ref(rng));
  const auto batch = batch_rng();
  const auto input_channels = channels_rng();
  const auto output_channels = channels_rng();

  QuantizedFullyConnectedTester()
      .InputZeroPoint(zero_point_rng())
      .FilterZeroPoint(filter_zero_point_rng())
      .OutputZeroPoint(0)
      .InputShape({batch, input_channels})
      .InputChannels(input_channels)
      .OutputChannels(output_channels)
      .ReluActivation()
      .Test(xnnpack_delegate.get());
}

TEST(UnsignedQuantizedFullyConnected, Relu6Activation) {
  std::unique_ptr<TfLiteDelegate, decltype(&TfLiteXNNPackDelegateDelete)>
      xnnpack_delegate(TfLiteXNNPackDelegateCreate(nullptr),
                       TfLiteXNNPackDelegateDelete);

  std::random_device random_device;
  auto rng = std::mt19937(random_device());
  auto zero_point_rng = std::bind(std::uniform_int_distribution<int32_t>(
                                      std::numeric_limits<uint8_t>::min(),
                                      std::numeric_limits<uint8_t>::max()),
                                  std::ref(rng));
  auto filter_zero_point_rng = std::bind(
      std::uniform_int_distribution<int32_t>(100, 150), std::ref(rng));
  auto batch_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 5), std::ref(rng));
  auto channels_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 9), std::ref(rng));
  const auto batch = batch_rng();
  const auto input_channels = channels_rng();
  const auto output_channels = channels_rng();

  QuantizedFullyConnectedTester()
      .InputZeroPoint(zero_point_rng())
      .FilterZeroPoint(filter_zero_point_rng())
      .OutputZeroPoint(0)
      .InputShape({batch, input_channels})
      .InputChannels(input_channels)
      .OutputChannels(output_channels)
      .Relu6Activation()
      .Test(xnnpack_delegate.get());
}

TEST(UnsignedQuantizedFullyConnected, ReluMinus1To1Activation) {
  std::unique_ptr<TfLiteDelegate, decltype(&TfLiteXNNPackDelegateDelete)>
      xnnpack_delegate(TfLiteXNNPackDelegateCreate(nullptr),
                       TfLiteXNNPackDelegateDelete);

  std::random_device random_device;
  auto rng = std::mt19937(random_device());
  auto zero_point_rng = std::bind(std::uniform_int_distribution<int32_t>(
                                      std::numeric_limits<uint8_t>::min(),
                                      std::numeric_limits<uint8_t>::max()),
                                  std::ref(rng));
  auto filter_zero_point_rng = std::bind(
      std::uniform_int_distribution<int32_t>(100, 150), std::ref(rng));
  auto batch_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 5), std::ref(rng));
  auto channels_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 9), std::ref(rng));
  const auto batch = batch_rng();
  const auto input_channels = channels_rng();
  const auto output_channels = channels_rng();

  QuantizedFullyConnectedTester()
      .InputZeroPoint(zero_point_rng())
      .FilterZeroPoint(filter_zero_point_rng())
      .OutputZeroPoint(zero_point_rng())
      .InputShape({batch, input_channels})
      .InputChannels(input_channels)
      .OutputChannels(output_channels)
      .ReluMinus1To1Activation()
      .Test(xnnpack_delegate.get());
}

TEST(UnsignedQuantizedFullyConnected, MultiThreading) {
  TfLiteXNNPackDelegateOptions delegate_options =
      TfLiteXNNPackDelegateOptionsDefault();
  delegate_options.num_threads = 2;
  std::unique_ptr<TfLiteDelegate, decltype(&TfLiteXNNPackDelegateDelete)>
      xnnpack_delegate(TfLiteXNNPackDelegateCreate(&delegate_options),
                       TfLiteXNNPackDelegateDelete);

  std::random_device random_device;
  auto rng = std::mt19937(random_device());
  auto zero_point_rng = std::bind(std::uniform_int_distribution<int32_t>(
                                      std::numeric_limits<uint8_t>::min(),
                                      std::numeric_limits<uint8_t>::max()),
                                  std::ref(rng));
  auto filter_zero_point_rng = std::bind(
      std::uniform_int_distribution<int32_t>(100, 150), std::ref(rng));
  auto batch_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 5), std::ref(rng));
  auto channels_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 9), std::ref(rng));
  const auto batch = batch_rng();
  const auto input_channels = channels_rng();
  const auto output_channels = channels_rng();

  QuantizedFullyConnectedTester()
      .InputZeroPoint(zero_point_rng())
      .FilterZeroPoint(filter_zero_point_rng())
      .OutputZeroPoint(zero_point_rng())
      .InputShape({batch, input_channels})
      .InputChannels(input_channels)
      .OutputChannels(output_channels)
      .Test(xnnpack_delegate.get());
}

}  // namespace xnnpack
}  // namespace tflite
