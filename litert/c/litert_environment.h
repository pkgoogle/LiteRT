// Copyright 2024 Google LLC.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef TENSORFLOW_LITE_EXPERIMENTAL_LITERT_C_LITERT_ENVIRONMENT_H_
#define TENSORFLOW_LITE_EXPERIMENTAL_LITERT_C_LITERT_ENVIRONMENT_H_

#include "litert/c/litert_common.h"
#include "litert/c/litert_environment_options.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

LITERT_DEFINE_HANDLE(LiteRtEnvironment);

// Create a LiteRT environment with options.
LiteRtStatus LiteRtEnvironmentCreate(int num_options,
                                     const LiteRtEnvOption* options,
                                     LiteRtEnvironment* environment);

void LiteRtDestroyEnvironment(LiteRtEnvironment environment);

// Get the options that the environment was created with.
LiteRtStatus LiteRtGetEnvironmentOptions(LiteRtEnvironment environment,
                                         LiteRtEnvironmentOptions* options);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // TENSORFLOW_LITE_EXPERIMENTAL_LITERT_C_LITERT_ENVIRONMENT_H_
