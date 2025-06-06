/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

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
#include "tflite/delegates/nnapi/acceleration_test_util.h"

namespace tflite {

const char* const NnapiAccelerationTestParams::acceleration_test_config_ =
    R"(
## Every Test can be allowlisted or denylisted using a regexp on its test_id

## Test_id
#
# The test_id is test_suite_name / test_name, this differs from the
# name used by the build because of the / separator instead of .
# Parameterized tests names are composed by the base test name / test / ordinal
# the ordinal is the position in the list of parameters generated by the
# cardinal product of all the different parameter sets

# Denylist/Allowlist
# To denylist an element simply add - before the test_id regex

## Rules evaluation
#
# Rules are checked in order, the first matching completes the browsing
# This can be useful to put more specific rules first and generic default
# ones below

## Test Arguments
#
# The test can be parameterized with the minimum Android SDK version
# to apply the acceleration validation for.
# If omitted will use 27

#test-id,min-android-sdk-version

# activations_test
FloatActivationsOpTest/Softmax[13]D,29
QuantizedActivationsOpTest/Softmax[13]D.+nt8,29
FloatActivationsOpTest/Softmax\dD
QuantizedActivationsOpTest/Softmax\dD.+nt8
FloatActivationsOpTest/LogSoftmax,29
FloatActivationsOpTest/PRelu,29
LogisticOpTest/LogisticOpTest/Sigmoid(.+nt8)?/\d+
LogisticOpTest/LogisticOpTest/Sigmoid/\d+
TanhOpTest/TanhOpTest/Tanh(.+nt8)?/\d+,29
FloatActivationsOpTest/Elu,30
FloatActivationsOpTest/Relu
FloatActivationsOpTest/Relu1
FloatActivationsOpTest/Relu6
FloatActivationsOpTest/HardSwish
FloatActivationsOpTest/LeakyRelu,29
QuantizedActivationsOpTest/HardSwish
QuantizedActivationsOpTest/HardSwishBias
-QuantizedActivationsOpTest/Relu.?Int16
QuantizedActivationsOpTest/Relu.*
-QuantizedActivationsOpTest/LeakyReluInt16,30
QuantizedActivationsOpTest/LeakyRelu.*,30
QuantizedActivationsOpTest/Relu.+nt8
QuantizedActivationsOpTest/PRelu,29
QuantizedActivationsOpTest/PReluSameShapes,29
QuantizedActivationsOpTest/PReluInt8.+,30
PReluOpTest/.*,29


# add_test
FloatAddOpModel/.+
QuantizedAddOpModel/QuantizedTestsNoActivation.+nt8
QuantizedAddOpModel/QuantizedVariousInputShapes.+
QuantizedAddOpModel/QuantizedWithScalarBroadcast.+nt8
QuantizedAddOpModel/QuantizedWithMixedBroadcas.+nt8

# arg_min_max_test
# Only tests with ConstantAxis && OutputType == TensorType_INT32
# (element 4 and 6 in the test parameter list)
# Supported only from NNAPI 1.2
ArgMinMaxOpTest/ArgMinMaxOpTest/Get.+ArgFloat/[46],29
ArgMinMaxOpTest/ArgMinMaxOpTest/Get.+Arg.+nt8/[46],29
ArgMinMaxOpTest/ArgMinMaxOpTest/Get.+ArgInt/[46],29
ArgMinMaxOpTest/ArgMinMaxOpTest/Get.+ArgMulDimensions/[46],29
ArgMinMaxOpTest/ArgMinMaxOpTest/Get.+ArgNegativeAxis/[46],29
ArgMinMaxOpTest/ArgMinMaxOpTest/Get.+ArgOutput64/[46],29

# basic_rnn_test
RnnOpTest/BlackBoxTest

# batch_matmul_test
# broadcasting is not supported
-BatchMatMulOpTest/BatchMatMulOpTest/.+Broadcast.+
BatchMatMulOpTest/BatchMatMulOpTest/.+,1000006
QuantizedBatchMatMulOpTest/QuantizedBatchMatMulOpTest/SimpleTestQuantizedInt8/.+,1000006

# batch_to_space_nd_test
BatchToSpaceNDOpTest/SimpleConstTest.*
BatchToSpaceNDOpTest/BatchOneConstTest.*

# bidirectional_sequence_lstm_test
# Only test with non quantized weights
LSTMOpTest/LSTMOpTest/BlackBoxTestNoCifgNoPeepholeNoProjectionNoClipping/0,29
# Only test with non quantized weights
LSTMOpTest/LSTMOpTest/BlackBoxTestMergedOutput/0,29
LSTMOpTest/BlackBoxTestNoCifgNoPeepholeNoProjectionNoClippingReverse,29
LSTMOpTest/BlackBoxTestWithCifgWithPeepholeNoProjectionNoClipping,29
LSTMOpTest/BlackBoxTestWithCifgWithPeepholeNoProjectionNoClippingReversed,29
LSTMOpTest/BlackBoxTestWithPeepholeWithProjectionNoClipping,29
LSTMOpTest/BlackBoxTestWithPeepholeWithProjectionNoClippingBatchMajor,29
# Only test with non quantized weights
LSTMOpTest/LSTMOpTest/BlackBoxTestWithAuxInputZeroAuxWeight/0,29
QuantizationOrNot/LSTMOpTest/BlackBoxTestNoCifgNoPeepholeNoProjectionNoClipping/0,29
QuantizationOrNot/LSTMOpTest/BlackBoxTestMergedOutput/0,29
QuantizationOrNot/LSTMOpTest/BlackBoxTestWithAuxInputZeroAuxWeight/0,29
LSTMOpTest/LSTMOpTest/BlackBoxTestWithAuxInput/0,29

# cast_test
CastOpModel/CastFloatToIn32
CastOpModel/CastInt32ToFloat,29
CastOpModel/CastFloatToUInt8,29
CastOpModel/CastUInt8ToFloat,29
CastOpModel/CastInt32ToUInt8,29
CastOpModel/CastUInt8ToInt32,29

# comparisons_test
ComparisonsTest/.+,29

# concatenation_test
ConcatenationOpTest/ThreeDimensionalOneInput
ConcatenationOpTest/OneTrivialInput
ConcatenationOpTest/TwoDimensionalOneInput
ConcatenationOpTest/TwoInputsTwoAxesNegativeAxes
ConcatenationOpTest/TwoInputsTwoAxesNegativeAxesNonQuantized
ConcatenationOpTest/FourInputs
ConcatenationOpTest/FourInputsQuantizedUint8
ConcatenationOpTest/FourInputsQuantizedInt8
ConcatenationOpTest/ThreeDimensionalNonQuantizedOneInput
ConcatenationOpTest/OneTrivialNonQuantizedInput
ConcatenationOpTest/TwoDimensionalNonQuantizedOneInput
ConcatenationOpTest/FourInputsQuantizedMixedRange,29
ConcatenationOpTest/FourInputsQuantizedMixedRangeClampingLogic,29

# conv_test
-ConvolutionOpTest/ConvolutionOpTest.SimplePerTensorTest/.+
ConvolutionOpTest/ConvolutionOpTest.SimpleTestFloatWithDilation/.+,29
ConvolutionOpTest/ConvolutionOpTest.SimpleTestLargeIrregularQuantized/.+,29
ConvolutionOpTest/ConvolutionOpTest.SimpleTestQuantizedOutputMultiplierGreaterThan1/.+,29
ConvolutionOpTest/ConvolutionOpTest.SimpleTestQuantizedWithDilation/.+,29
ConvolutionOpTest/ConvolutionOpTest.SimplePerChannelTest/.+,29
ConvolutionOpTest/ConvolutionOpTest.SimpleTestQuantizedGrouped/.+,29
ConvolutionOpTest/ConvolutionOpTest/.+Hybrid.+,29/
ConvolutionOpTest/ConvolutionOpTest/.+/\d+


# depthwise_conv_test
.+ConvolutionOpTest/.+/\d+,29

# dequantize_test
DequantizeOpTest/Uint8
DequantizeOpTest/Int8,30

# depth_to_space_test
DepthToSpaceOpModel/Float32
DepthToSpaceOpModel/UInt8
DepthToSpaceOpModel/int8

# div_test
-FloatDivOpTest/WithBroadcast5D
FloatDivOpTest/.+

# elementwise_test
ElementWise/Abs,29
ElementWise/Sin,29
ElementWise/Log,29
ElementWise/Sqrt,29
ElementWise/Rsqrt,29
ElementWise/LogicalNot,29

# embedding_lookup_test
EmbeddingLookupOpTest/SimpleTest

# exp_test
ExpOpTest/FloatTest,29

# expand_dims_test
# Only constant tensors models
ExpandDimsOpTest/.+/1,29

# fill_test
FillOpTest/FillOpTest/FillInt32/0,30
FillOpTest/FillOpTest/FillFloat/0,30
FillOpTest/FillOpTest/FillFloatInt32Dims/0,30

# floor_test
FloorOpTest/.+

# fully_connected_test
FloatFullyConnectedOpTest/FloatFullyConnectedOpTest/SimpleTest/\d+
FloatFullyConnectedOpTest/FloatFullyConnectedOpTest/SimpleTest2/\d+
QuantizedFullyConnectedOpTest/QuantizedFullyConnectedOpTest/SimpleTestQuantized.+nt8/\d+,29
QuantizedFullyConnectedOpTest/QuantizedFullyConnectedOpTest/SimpleTestSingleBatchQuantizedInt8/\d+,29
QuantizedFullyConnectedOpTest/SimpleTestQuantizedOutputMultiplierGreaterThan1Uint8/\d+,29
QuantizedFullyConnectedOpTest/SimpleTestQuantizedOutputMultiplierGreaterThan1Int8/\d+,29
HybridFullyConnectedOpTest/SimpleTestQuantizedUint8,29
HybridFullyConnectedOpTest/SimpleTestQuantizedInt8,29
HybridAsymmetricInputFullyConnectedOpTest.SimpleTestQuantizedUint8,29
FloatFullyConnectedOpTest/FloatFullyConnectedOpTest/SimpleTest4DInput/\d+
QuantizedFullyConnectedOpTest/QuantizedFullyConnectedOpTest/SimpleTest4dInputQuantizedUint8/\d+
QuantizedFullyConnectedOpTest/QuantizedFullyConnectedOpTest/SimpleTest4dInputQuantizedOutputMultiplierGreaterThan1Uint8/\d+,29
FloatFullyConnectedOpTest/FloatFullyConnectedOpTest/BlackBoxTest/\d+
FloatFullyConnectedOpTest/SimpleTestNoBias

# gather_test
GatherOpTest/Shuffle,29
GatherOpTest/Test1DInput1DIndex,29
GatherOpTest/Test2DIndexWith2DResult,29
FloatGatherOpTest/Duplicate,29
FloatGatherOpTest/Slice,29
FloatGatherOpTest/Axis1,29
FloatGatherOpTest/Axis1Slice,29
FloatGatherOpTest/LastAxis,29
TypesGatherOpTest/Float32Int32,29
TypesGatherOpTest/Int32Int32,29
TypesGatherOpTest/Uint8Int32,29
TypesGatherOpTest/Int8Int32,29
-TypesGatherOpTest/.*Int16.*

# hashtable_lookup_test
# All test excepted the string one should be accelerated
-HashtableLookupOpTest/TestString
HashtableLookupOpTest/.+

# l2norm_test
L2NormOpTest/.+,29

# local_response_norm_test
LocalResponseNormOpTest/.+

# logical_test
LogicalTest/.+,29

# lsh_projection_test
-LSHProjectionOpTest2/Sparse3DInputs
LSHProjectionOpTest2/Sparse1DInputs,29
LSHProjectionOpTest2/.+

# Before the lstm because of clashing with matchers
# unidirectional_sequence_lstm_test
NoCifgNoPeepholeNoProjectionNoClippingUnidirectionalLstmTest/LstmBlackBoxTest,29
CifgPeepholeNoProjectionNoClippingUnidirectionalLstmTest/NonLayerNormLstmBlackBoxTest,29
# Only the two tests above, disabling all possible matches from the lstm tests
# coming after
-.+UnidirectionalLstmTest/.+

# lstm_test
-LstmOpTest/InvalidTypes
# Float
Parameterized/LstmOpTest.+/0,29
Parameterized/LstmOpTest.+/1,29
Parameterized/LstmOpTest.+/2,29
Parameterized/LstmOpTest.+/3,29
# HybridUint8
Parameterized/LstmOpTest.+/4,29
Parameterized/LstmOpTest.+/5,29
Parameterized/LstmOpTest.+/6,29
Parameterized/LstmOpTest.+/7,29
# HybridInt8
-Parameterized/LstmOpTest.+/8
-Parameterized/LstmOpTest.+/9
-Parameterized/LstmOpTest.+/10
-Parameterized/LstmOpTest.+/11

# maximum_minimum_test
MaxMinOpTest/.+nt8Test,29
MaximumOpTest/.+,29

# mirror_pad_test
MirrorPadTest/.+,1000007

# mul_test
FloatMulOpTest/.+

# neg_test
-NegOpModel/.+Int64
NegOpModel/.+,29

# pack_test
# int32 and uint8 are supported since NNAPI FL6
PackOpTest/Int32.+,1000006
PackOpTestInt/1/.+,1000006
# PACK along last axis is supported since NNAPI FL6
PackOpTest/FloatThreeInputsDifferentAxis,1000006
PackOpTest/FloatThreeInputsNegativeAxis,1000006
PackOpTestInt/0/ThreeInputsDifferentAxis,1000006
PackOpTestInt/0/ThreeInputsNegativeAxis,1000006
# f32 and int8 are supported since NNAPI 1.3 by decomposition
PackOpTest/Float.+,30
PackOpTestInt/0/.+,30

# pad_test
-PadOpTest/TooManyDimensions
-PadOpTest/UnequalDimensions
-PadOpTest/InvalidPadValue
# Zero height or width is not supported
-PadOpTest/Zero.+ConstImageStyleTest
# Dynamic tensors are not supported
-.*Pad.*OpTest/.+Dynamic.*Test
-QuantizedPad.*OpTest/.+ZeroNotInQuantizationRange
# 16-bit tests are not supported
-QuantizedPadOpTest/.*Int16.*
QuantizedPadOpTest/.+,29
QuantizedPadV2OpTest/.+,29
PadOpTest/.+,29

# pooling_test
FloatPoolingOpTest/L2PoolActivationRelu.*,29
FloatPoolingOpTest/.+
# Image is too big
-QuantizedPoolingOpTest/AveragePoolImageSize17
# Int16 unsupported
-QuantizedPoolingOpTest/SymmetricAveragePool16
QuantizedPoolingOpTest/.+
QuantizedUInt8PoolingOpTest/.+

# pow_test
-PowOpModel/Simple
-PowOpModel/NegativeAndZeroValue
-PowOpModel/BroadcastTest
-PowOpModel/IntSingleIntegerExponentTest
PowOpModel/.+,29

# quant_basic_lstm_test
QuantizedLstmTest/BasicQuantizedLstmTest/29

# quantized_lstm op test
# Temporary disabled due to b/188515203
//IntegerLstmOpTest/NoCifg_NoPeephole_Projection_LayerNorm,30

# quantize_test
QuantizeOpTest/UINT8,29
QuantizeOpTest/UInt8UInt8.+,29
QuantizeOpTest/Int8Int8.+,30
QuantizeOpTest/INT8,30

# rank

# reduce_test
-Dynamic.+(Mean|Sum|Prod|Max|Min)OpTest/.+
-ConstUint8SumOpTest/.+
ConstUint8(Max|Min)OpTest/.+,29
ConstUint8(Mean)OpTest/.+,29
-ConstInt8(Max|Min)OpTest/.+,29
ConstInt8MeanOpTest/.+,29
-ConstMeanOpTest.*/.+Int16
ConstMeanOpTest.*/.+,29
-MeanOpTestQuantized.*/.+Int16
MeanOpTestQuantized.*/.+,29
ConstFloat(Sum|Prod|Max|Min)OpTest/NotKeepDims,29
ConstFloat(Sum|Prod|Max|Min)OpTest/KeepDims,29
ConstFloat(Mean|Any)OpTest/NotKeepDims
ConstFloat(Mean|Any)OpTest/KeepDims
ConstFloat(Sum|Prod|Max|Min)OpTest/ScalarAxis,29

# reshape_test
# Acceleration would be only for the test with shape being a constant tensor or
# as hardcoded options.
ReshapeOpTest/[01]/InvalidShape
ReshapeOpTest/[01]/RegularShapes
ReshapeOpTest/[01]/WithStretchDimension
# int32 is supported since NNAPI FL6
ReshapeOpTest/3/InvalidShape,1000006
ReshapeOpTest/3/RegularShapes,1000006
ReshapeOpTest/3/WithStretchDimension,1000006

# resize_bilinear_test
// align_corners & half_pixel_centers are not implemented in NNAPI before API 30
ResizeBilinearOpTest/ResizeBilinearOpTest.+HalfPixelCenters.*/0,30
// Only models with constant size tensor are accelerated
ResizeBilinearOpTest/ResizeBilinearOpTest/.+/0,29

# resize_nearest_neighbor_test
// align_corners & half_pixel_centers are not implemented in NNAPI before API 30
ResizeNearestNeighborOpTest/ResizeNearestNeighborOpTest.+AlignCorners.*/0,30
ResizeNearestNeighborOpTest/ResizeNearestNeighborOpTest.+HalfPixelCenters.*/0,30
// 16-bit tests are not supported
-ResizeNearestNeighborOpTest.+Int16/.+
// Only models with constant size tensor are accelerated
ResizeNearestNeighborOpTest/ResizeNearestNeighborOpTest/.+/0,29

# reverse_test
-ReverseOpTest/Int64.+
-ReverseOpTest/Int16.+
ReverseOpTest/.+,1000007

# select_test
-SelectOpTest/SelectBool
-SelectOpTest.SelectInt16
-SelectOpTest/RankZero.+
-SelectOpTest/RankOne.+
SelectOpTest/.+,29

# slice_test
-SliceOpTest/SliceOpTest/IndexInt64/.+
-SliceOpTest/SliceOpTest/SliceString/.+
-SliceOpTest/SliceOpTest/SliceInt64/.+
-SliceOpTest/SliceOpTest/SliceBool/.+
-SliceOpTest/SliceOpTest/SliceInt16/.+
-SliceOpTest/SliceOpTest/SliceInt64StaticOutput/.*
# Only constant tensors
SliceOpTest/SliceOpTest/.+/0,29

# softmax_test
SoftmaxOpTest/CompareWithTFminiBetaEq1
SoftmaxOpTest/CompareWithTFminiBetaNotEq1

# space_to_depth_test
SpaceToDepthOpModel/Float32
SpaceToDepthOpModel/Uint8
SpaceToDepthOpModel/int8

# split_test
-SplitOpTest/SplitOpTest/.+Int8/.+
# Only accelerated when axis is a constant tensor
SplitOpTest/SplitOpTest/.+/0,29

# split_v_test
# NNAPI does not support int16
-SplitVOpTypedTest/3/.+
# NNAPI does not support zero-sized slice
-SplitVOpTypedTest/.+OneDimensional2
# Only accelerated when both split_sizes and axis are constant
SplitVOpTypedTest/.+/ConstSplits.+,30

# squared_difference_test
FloatSquaredDifferenceOpTest/.+,28
(Integer|Quantized)SquaredDifferenceOpTest/.+,30

# squeeze_test
FloatSqueezeOpTest/.+,29

# sub_test
-FloatSubOpModel/WithBroadcast5D
FloatSubOpModel/.+
-QuantizedSubOpModel/.+Int16
-QuantizedSubOpModel/.+Int8
QuantizedSubOpModel/.+

# svdf_test
SVDFOpTest/BlackBoxTestRank1
SVDFOpTest/BlackBoxTestRank2

# tile_test
-TileTest/TileTest/Int64.+/.+
-TileTest/TileTest/Boolean.+/.+
-TileTest/TileTest/String.+/.+
# Const tensor only
TileTest/TileTest/.+/0,29

# topk_v2_test
-TopKV2OpTest/TopKV2OpTest/.+Int64/.+
# Const tensor only
TopKV2OpTest/TopKV2OpTest/.+/0,29

# transpose_test
# death test
-TransposeTest/Test6DInputTensor
-TransposeTest/5DDividedIntoTwo2Ds.*
-TransposeTest/Complex5DTest.*
-TransposeTest/.+DynamicTensor
-TransposeTest/TestRefOps4DInt16
TransposeTest/.+

# transpose_conv_test
-TransposeConvOpTest/TransposeConvOpTest.SimpleTestQuantizedPerChannel16x8/.+
TransposeConvOpTest/TransposeConvOpTest..*Bias.*/0,29
# Const tensor only
TransposeConvOpTest/TransposeConvOpTest/.+/0,29

# unidirectional_sequence_rnn_test
UnidirectionalRNNOpTest/BlackBoxTest,29
UnidirectionalRNNOpTest.TimeMajorBlackBoxTest,29

# unpack_test
# Unpacking along the last axis is not supported
-UnpackOpTest/.+/ThreeOutputsAxisOne
-UnpackOpTest/.+/ThreeOutputsNegativeAxisOne
-UnpackOpTest/.+/ThreeDimensionsOutputs
# Unpacking 5D tensor is not supported
-UnpackOpTest/.+/FiveDimensionsOutputs
# Unpacking a vector to scalar is not supported
-UnpackOpTest/.+/VectorToScalar
# float, int8, uint8 only
UnpackOpTest/(0|2|3)/.+,30
)";

}  // namespace tflite
