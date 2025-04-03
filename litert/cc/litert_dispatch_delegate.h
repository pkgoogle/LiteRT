// Copyright 2025 Google LLC.
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

#ifndef ODML_LITERT_LITERT_CC_LITERT_DISPATCH_DELEGATE_H_
#define ODML_LITERT_LITERT_CC_LITERT_DISPATCH_DELEGATE_H_

#include <memory>

#include "litert/c/litert_dispatch_delegate.h"
#include "litert/c/litert_environment_options.h"
#include "tflite/delegates/utils/simple_opaque_delegate.h"  // from @org_tensorflow

namespace litert {

using DispatchDelegateOptionsPtr =
    std::unique_ptr<LiteRtDispatchDelegateOptions,
                    void (*)(LiteRtDispatchDelegateOptions*)>;

using DispatchDelegatePtr = tflite::TfLiteOpaqueDelegateUniquePtr;

DispatchDelegateOptionsPtr CreateDispatchDelegateOptionsPtr(
    LiteRtEnvironmentOptions environment_options);

DispatchDelegatePtr CreateDispatchDelegatePtr(
    LiteRtEnvironmentOptions environment_options,
    DispatchDelegateOptionsPtr&& options);

}  // namespace litert

#endif  // ODML_LITERT_LITERT_CC_LITERT_DISPATCH_DELEGATE_H_
