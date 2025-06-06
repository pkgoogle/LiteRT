/* Copyright 2022 The TensorFlow Authors. All Rights Reserved.

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

#import <XCTest/XCTest.h>

#include "tflite/delegates/gpu/common/tasks/select_v2_test_util.h"
#include "tflite/delegates/gpu/metal/kernels/test_util.h"

@interface SelectV2MetalTest : XCTestCase
@end


@implementation SelectV2MetalTest {
  tflite::gpu::metal::MetalExecutionEnvironment exec_env_;
}

- (void)testSelectV2Test {
  auto status = SelectV2Test(&exec_env_);
  XCTAssertTrue(status.ok(), @"%s", std::string(status.message()).c_str());
}

- (void)testSelectV2BatchTest {
  auto status = SelectV2BatchTest(&exec_env_);
  XCTAssertTrue(status.ok(), @"%s", std::string(status.message()).c_str());
}

- (void)testSelectV2ChannelsTest {
  auto status = SelectV2ChannelsTest(&exec_env_);
  XCTAssertTrue(status.ok(), @"%s", std::string(status.message()).c_str());
}

- (void)testSelectV2ChannelsBatchTest {
  auto status = SelectV2ChannelsBatchTest(&exec_env_);
  XCTAssertTrue(status.ok(), @"%s", std::string(status.message()).c_str());
}

- (void)testSelectV2BroadcastTrueTest {
  auto status = SelectV2BroadcastTrueTest(&exec_env_);
  XCTAssertTrue(status.ok(), @"%s", std::string(status.message()).c_str());
}

- (void)testSelectV2BroadcastElseTest {
  auto status = SelectV2BroadcastFalseTest(&exec_env_);
  XCTAssertTrue(status.ok(), @"%s", std::string(status.message()).c_str());
}

- (void)testSelectV2BroadcastBothTest {
  auto status = SelectV2BroadcastBothTest(&exec_env_);
  XCTAssertTrue(status.ok(), @"%s", std::string(status.message()).c_str());
}

- (void)testSelectV2ChannelsBroadcastElseTest {
  auto status = SelectV2ChannelsBroadcastFalseTest(&exec_env_);
  XCTAssertTrue(status.ok(), @"%s", std::string(status.message()).c_str());
}

@end
