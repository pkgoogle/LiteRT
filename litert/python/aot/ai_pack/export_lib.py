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
"""Utility functions for exporting models to AI pack format."""

import itertools
import os
import pathlib

from litert.python.aot.core import common
from litert.python.aot.core import types
from litert.python.aot.vendors import fallback_backend
from litert.python.aot.vendors.qualcomm import target as qnn_target

# TODO: b/407453529 - Add unittests.


# TODO: b/407453529 - Use templating libraries like jinja2 to generate this.
_AI_PACK_MANIFEST = """<!-- AiPackManifest.xml -->

<?xml version="1.0" encoding="utf-8"?>
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:dist="http://schemas.android.com/apk/distribution">

  <dist:module
      dist:type="ai-pack">
    <dist:fusing dist:include="true" />
    <dist:delivery>
      <dist:install-time />
    </dist:delivery>
  </dist:module>

</manifest>
"""

_DEVICE_TARGETING_CONFIGURATION = """<config:device-targeting-config
    xmlns:config="http://schemas.android.com/apk/config">
{device_groups}
</config:device-targeting-config>"""

_DEVICE_GROUP_TEMPLATE = """    <config:device-group name="{device_group_name}">
{device_selectors}
    </config:device-group>"""

_DEVICE_SELECTOR_TEMPLATE = """        <config:device-selector>
            <config:system-on-chip manufacturer="{soc_man}" model="{soc_model}"/>
        </config:device-selector>"""


def _export_model_files_to_ai_pack(
    compiled_models: types.CompiledModels,
    ai_pack_dir: pathlib.Path,
    ai_pack_name: str,
    litert_model_name: str,
):
  """Exports the model tflite files to the AI pack directory structure."""
  model_export_dir = ai_pack_dir / ai_pack_name
  os.makedirs(model_export_dir, exist_ok=True)
  for backend, model in compiled_models.models_with_backend:
    backend_id = backend.target_id
    if backend_id == fallback_backend.FallbackBackend.id():
      backend_id = 'other'
    group_name = 'model#group_' + backend_id
    export_dir = model_export_dir / group_name
    os.makedirs(export_dir, exist_ok=True)
    model_export_path = export_dir / (litert_model_name + common.DOT_TFLITE)
    if not model.in_memory:
      model.load()
    model.save(model_export_path, export_only=True)


def _write_ai_pack_manifest(ai_pack_dir: pathlib.Path):
  """Writes the AndroidManifest.xml file."""
  manifest_path = ai_pack_dir / 'AndroidManifest.xml'
  manifest_path.write_text(_AI_PACK_MANIFEST)


def _build_targeting_config(compiled_targets: list[types.Target]) -> str:
  """Builds device-targeting-config in device_targeting_configuration.xml."""
  device_groups = []
  for target in compiled_targets:
    device_group = _target_to_ai_pack_info(target)
    if device_group:
      device_groups.append(device_group)
  device_groups = '\n'.join(device_groups)
  return _DEVICE_TARGETING_CONFIGURATION.format(device_groups=device_groups)


def _target_to_ai_pack_info(target: types.Target) -> str | None:
  """Builds the device group used in device_targeting_configuration.xml."""
  if isinstance(target, qnn_target.Target):
    group_name = str(target)
    selector = _process_qnn_target(target)
    device_selectors = [
        _DEVICE_SELECTOR_TEMPLATE.format(soc_man=man, soc_model=model)
        for man, model in selector
    ]
    device_selectors = '\n'.join(device_selectors)
    device_group = _DEVICE_GROUP_TEMPLATE.format(
        device_group_name=group_name, device_selectors=device_selectors
    )
    return device_group
  elif isinstance(target, fallback_backend.FallbackTarget):
    # Don't need to have device selector for fallback target.
    return None
  else:
    # TODO: b/407453529 - Support MTK targets.
    print('unsupported target ', target)
    return None


# TODO: b/407453529 - Auto-generate this function from CSVs.
def _process_qnn_target(target: qnn_target.Target) -> list[tuple[str, str]]:
  """Returns the list of (manufacturer, model) for the given QNN target."""
  # Play cannot distinguish between Qualcomm and QTI for now.
  manufacturer = ['Qualcomm', 'QTI']

  match target.soc_model:
    case qnn_target.SocModel.V79:
      models = ['SM8750']
    case qnn_target.SocModel.V75:
      models = ['SM8650']
    case qnn_target.SocModel.V73:
      models = [
          'SM8635',
          'SM8550',
          'SM7675',
          'SM7550',
          'SM7435',
          'SM6450',
          'QCM8550LA',
          'QCM8550LE',
      ]
    case qnn_target.SocModel.V69:
      models = [
          'SM8475',
          'SM8450',
          'SM7475',
          'SM7450',
          'SM7425',
          'SXR2230P',
          'SXR2250P',
      ]
    case _:
      models = []
  return list(itertools.product(manufacturer, models))


def _write_targeting_config(
    compiled_models: types.CompiledModels, ai_pack_dir: pathlib.Path
) -> None:
  """Writes device_targeting_configuration.xml for the given compiled models."""
  compiled_targets = [
      x.target for x, _ in compiled_models.models_with_backend
  ]
  targeting_config = _build_targeting_config(compiled_targets=compiled_targets)

  targeting_config_path = ai_pack_dir / 'device_targeting_configuration.xml'
  targeting_config_path.write_text(targeting_config)


def export(
    compiled_models: types.CompiledModels,
    ai_pack_dir: pathlib.Path | str,
    ai_pack_name: str,
    litert_model_name: str,
) -> None:
  """Exports the compiled models to AI pack format.

  This function will export the compiled models to corresponding directory
  structure:

  {ai_pack_dir}/
    AndroidManifest.xml
    device_targeting_configuration.xml
    {ai_pack_name}/
      model#group_target_1/
        {litert_model_name}.tflite
      model#group_target_2/
        {litert_model_name}.tflite
      model#group_target_3/
        {litert_model_name}.tflite
      model#group_other/
        {litert_model_name}.tflite

  Args:
    compiled_models: The compiled models to export.
    ai_pack_dir: The directory to export the AI pack to.
    ai_pack_name: The name of the AI pack.
    litert_model_name: The name of the model in the litert format.
  """
  if isinstance(ai_pack_dir, str):
    ai_pack_dir = pathlib.Path(ai_pack_dir)

  ai_pack_dir.mkdir(parents=True, exist_ok=True)

  _export_model_files_to_ai_pack(
      compiled_models=compiled_models,
      ai_pack_dir=ai_pack_dir,
      ai_pack_name=ai_pack_name,
      litert_model_name=litert_model_name,
  )
  _write_ai_pack_manifest(ai_pack_dir=ai_pack_dir)
  _write_targeting_config(
      compiled_models=compiled_models, ai_pack_dir=ai_pack_dir
  )
