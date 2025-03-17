
<!-- markdownlint-disable MD041 -->
<p align="left"><img src="https://vulkan.lunarg.com/img/NewLunarGLogoBlack.png" alt="LunarG" width=263 height=113 /></p>
<p align="left">Copyright (c) 2021-2024 LunarG, Inc.</p>

<p align="center"><img src="./images/logo.png" width=400 /></p>

[![Creative Commons][3]][4]

[3]: https://i.creativecommons.org/l/by-nd/4.0/88x31.png "Creative Commons License"
[4]: https://creativecommons.org/licenses/by-nd/4.0/

# Vulkan Profiles Definitions

## Vulkan Profiles List

| Profiles | VP_LUNARG_generated_profile |
|----------|-----------------------------|
| Label | Generated profile |
| Description | Generated profile doing an intersection between profiles: VP_ANDROID_baseline_2021 and VP_LUNARG_desktop_baseline_2022 |
| Version | 1 |
| Required API version | 1.0.68 |
| Required profiles |  |
| Fallback profiles | - |

## Vulkan Profiles Extensions

* :heavy_check_mark: indicates that the extension is defined in the profile
* "X.X Core" indicates that the extension is not defined in the profile but the extension is promoted to the specified core API version that is smaller than or equal to the minimum required API version of the profile
* :x: indicates that the extension is neither defined in the profile nor it is promoted to a core API version that is smaller than or equal to the minimum required API version of the profile

| Profiles | VP_LUNARG_generated_profile |
|----------|-----------------------------|
| **Instance extensions** |
| **Device extensions** |
| [VK_KHR_dedicated_allocation](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VK_KHR_dedicated_allocation.html) | :heavy_check_mark: |
| [VK_KHR_descriptor_update_template](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VK_KHR_descriptor_update_template.html) | :heavy_check_mark: |
| [VK_KHR_external_fence](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VK_KHR_external_fence.html) | :heavy_check_mark: |
| [VK_KHR_external_memory](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VK_KHR_external_memory.html) | :heavy_check_mark: |
| [VK_KHR_external_semaphore](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VK_KHR_external_semaphore.html) | :heavy_check_mark: |
| [VK_KHR_get_memory_requirements2](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VK_KHR_get_memory_requirements2.html) | :heavy_check_mark: |
| [VK_KHR_maintenance1](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VK_KHR_maintenance1.html) | :heavy_check_mark: |
| [VK_KHR_storage_buffer_storage_class](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VK_KHR_storage_buffer_storage_class.html) | :heavy_check_mark: |
| [VK_KHR_swapchain](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VK_KHR_swapchain.html) | :heavy_check_mark: |
| [VK_KHR_variable_pointers](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VK_KHR_variable_pointers.html) | :heavy_check_mark: |

## Vulkan Profile Features

> **NOTE**: The table below only contains features explicitly defined by the corresponding profile. Further features may be supported by the profiles in accordance to the requirements defined in the "Feature Requirements" section of the appropriate version of the Vulkan API Specification.

* :heavy_check_mark: indicates that the feature is defined in the profile (hover over the symbol to view the structure and corresponding extension or core API version where the feature is defined in the profile)
* :warning: indicates that the feature is not defined in the profile but an equivalent feature is (hover over the symbol to view the structure and corresponding extension or core API version where the feature is defined in the profile)
* :x: indicates that neither the feature nor an equivalent feature is defined in the profile

| Profiles | VP_LUNARG_generated_profile |
|----------|-----------------------------|
| **Vulkan 1.0** |
| [depthBiasClamp](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceFeatures.html) | <span title="defined in VkPhysicalDeviceFeatures (Vulkan 1.0)">:heavy_check_mark:</span> |
| [fragmentStoresAndAtomics](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceFeatures.html) | <span title="defined in VkPhysicalDeviceFeatures (Vulkan 1.0)">:heavy_check_mark:</span> |
| [fullDrawIndexUint32](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceFeatures.html) | <span title="defined in VkPhysicalDeviceFeatures (Vulkan 1.0)">:heavy_check_mark:</span> |
| [imageCubeArray](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceFeatures.html) | <span title="defined in VkPhysicalDeviceFeatures (Vulkan 1.0)">:heavy_check_mark:</span> |
| [independentBlend](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceFeatures.html) | <span title="defined in VkPhysicalDeviceFeatures (Vulkan 1.0)">:heavy_check_mark:</span> |
| [robustBufferAccess](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceFeatures.html) | <span title="defined in VkPhysicalDeviceFeatures (Vulkan 1.0)">:heavy_check_mark:</span> |
| [sampleRateShading](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceFeatures.html) | <span title="defined in VkPhysicalDeviceFeatures (Vulkan 1.0)">:heavy_check_mark:</span> |
| [shaderSampledImageArrayDynamicIndexing](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceFeatures.html) | <span title="defined in VkPhysicalDeviceFeatures (Vulkan 1.0)">:heavy_check_mark:</span> |
| [shaderStorageImageArrayDynamicIndexing](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceFeatures.html) | <span title="defined in VkPhysicalDeviceFeatures (Vulkan 1.0)">:heavy_check_mark:</span> |
| [shaderUniformBufferArrayDynamicIndexing](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceFeatures.html) | <span title="defined in VkPhysicalDeviceFeatures (Vulkan 1.0)">:heavy_check_mark:</span> |

## Vulkan Profile Limits (Properties)

> **NOTE**: The table below only contains properties/limits explicitly defined by the corresponding profile. Further properties/limits may be supported by the profiles in accordance to the requirements defined in the "Limit Requirements" section of the appropriate version of the Vulkan API Specification.

* "valueWithRegularFont" indicates that the limit/property is defined in the profile (hover over the value to view the structure and corresponding extension or core API version where the limit/property is defined in the profile)
* "_valueWithItalicFont_" indicates that the limit/property is not defined in the profile but an equivalent limit/property is (hover over the symbol to view the structure and corresponding extension or core API version where the limit/property is defined in the profile)
* "-" indicates that neither the limit/property nor an equivalent limit/property is defined in the profile

| Profiles | VP_LUNARG_generated_profile |
|----------|-----------------------------|
| **Vulkan 1.0** |
| [discreteQueuePriorities (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">2</span> |
| [framebufferColorSampleCounts](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">(VK_SAMPLE_COUNT_1_BIT \| VK_SAMPLE_COUNT_4_BIT)</span> |
| [framebufferDepthSampleCounts](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">(VK_SAMPLE_COUNT_1_BIT \| VK_SAMPLE_COUNT_4_BIT)</span> |
| [framebufferNoAttachmentsSampleCounts](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">(VK_SAMPLE_COUNT_1_BIT \| VK_SAMPLE_COUNT_4_BIT)</span> |
| [framebufferStencilSampleCounts](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">(VK_SAMPLE_COUNT_1_BIT \| VK_SAMPLE_COUNT_4_BIT)</span> |
| [maxBoundDescriptorSets (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">4</span> |
| [maxColorAttachments (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">4</span> |
| [maxComputeSharedMemorySize (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">16384</span> |
| [maxComputeWorkGroupCount (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">(65535,65535,65535)</span> |
| [maxComputeWorkGroupInvocations (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">128</span> |
| [maxComputeWorkGroupSize (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">(128,128,64)</span> |
| [maxDescriptorSetInputAttachments (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">4</span> |
| [maxDescriptorSetSampledImages (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">48</span> |
| [maxDescriptorSetSamplers (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">48</span> |
| [maxDescriptorSetStorageBuffers (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">24</span> |
| [maxDescriptorSetStorageBuffersDynamic (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">4</span> |
| [maxDescriptorSetStorageImages (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">12</span> |
| [maxDescriptorSetUniformBuffers (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">36</span> |
| [maxDescriptorSetUniformBuffersDynamic (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">8</span> |
| [maxDrawIndexedIndexValue (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">4294967294</span> |
| [maxDrawIndirectCount (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">1</span> |
| [maxFragmentCombinedOutputResources (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">8</span> |
| [maxFragmentInputComponents (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">64</span> |
| [maxFragmentOutputAttachments (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">4</span> |
| [maxFramebufferHeight (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">4096</span> |
| [maxFramebufferLayers (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">256</span> |
| [maxFramebufferWidth (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">4096</span> |
| [maxImageArrayLayers (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">256</span> |
| [maxImageDimension1D (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">4096</span> |
| [maxImageDimension2D (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">4096</span> |
| [maxImageDimension3D (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">512</span> |
| [maxImageDimensionCube (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">4096</span> |
| [maxInterpolationOffset (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">0.4375</span> |
| [maxMemoryAllocationCount (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">4096</span> |
| [maxPerStageDescriptorInputAttachments (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">4</span> |
| [maxPerStageDescriptorSampledImages (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">16</span> |
| [maxPerStageDescriptorSamplers (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">16</span> |
| [maxPerStageDescriptorStorageBuffers (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">4</span> |
| [maxPerStageDescriptorStorageImages (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">4</span> |
| [maxPerStageDescriptorUniformBuffers (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">12</span> |
| [maxPerStageResources (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">44</span> |
| [maxPushConstantsSize (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">128</span> |
| [maxSampleMaskWords (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">1</span> |
| [maxSamplerAllocationCount (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">1024</span> |
| [maxSamplerAnisotropy (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">1.0</span> |
| [maxSamplerLodBias (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">0.0</span> |
| [maxStorageBufferRange (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">134217728</span> |
| [maxTexelBufferElements (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">65536</span> |
| [maxTexelOffset (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">7</span> |
| [maxUniformBufferRange (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">16384</span> |
| [maxVertexInputAttributeOffset (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">2047</span> |
| [maxVertexInputAttributes (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">16</span> |
| [maxVertexInputBindingStride (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">2048</span> |
| [maxVertexInputBindings (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">16</span> |
| [maxVertexOutputComponents (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">64</span> |
| [maxViewportDimensions (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">(4096,4096)</span> |
| [maxViewports (max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">1</span> |
| [minInterpolationOffset (min)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">-0.5</span> |
| [minStorageBufferOffsetAlignment (min,pot)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">256</span> |
| [minTexelBufferOffsetAlignment (min,pot)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">256</span> |
| [minTexelOffset (min)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">-8</span> |
| [minUniformBufferOffsetAlignment (min,pot)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">256</span> |
| [mipmapPrecisionBits (bits)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">4</span> |
| [pointSizeGranularity (min,mul)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">1</span> |
| [sampledImageColorSampleCounts](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">(VK_SAMPLE_COUNT_1_BIT \| VK_SAMPLE_COUNT_4_BIT)</span> |
| [sampledImageDepthSampleCounts](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">(VK_SAMPLE_COUNT_1_BIT \| VK_SAMPLE_COUNT_4_BIT)</span> |
| [sampledImageIntegerSampleCounts](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">(VK_SAMPLE_COUNT_1_BIT)</span> |
| [sampledImageStencilSampleCounts](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">(VK_SAMPLE_COUNT_1_BIT \| VK_SAMPLE_COUNT_4_BIT)</span> |
| [standardSampleLocations (exact)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">VK_TRUE</span> |
| [storageImageSampleCounts](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">(VK_SAMPLE_COUNT_1_BIT)</span> |
| [subPixelInterpolationOffsetBits (bits)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">4</span> |
| [subPixelPrecisionBits (bits)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">4</span> |
| [subTexelPrecisionBits (bits)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">4</span> |
| [viewportBoundsRange (min-max)](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPhysicalDeviceLimits.html) | <span title="defined in VkPhysicalDeviceProperties (Vulkan 1.0)">(-8192,8191)</span> |

## Vulkan Profile Queue Families

* "valueWithRegularFont" indicates that the queue family property is defined in the profile (hover over the value to view the structure and corresponding extension or core API version where the queue family property is defined in the profile)
* "_valueWithItalicFont_" indicates that the queue family property is not defined in the profile but an equivalent queue family property is (hover over the symbol to view the structure and corresponding extension or core API version where the queue family property is defined in the profile)
* "-" indicates that neither the queue family property nor an equivalent queue family property is defined in the profile
* Empty cells next to the properties of a particular queue family definition section indicate that the profile does not have a corresponding queue family definition

| Profiles | VP_LUNARG_generated_profile |
|----------|-----------------------------|

## Vulkan Profile Formats

> **NOTE**: The table below only contains formats and properties explicitly defined by the corresponding profile. Further formats and properties may be supported by the profiles in accordance to the requirements defined in the "Required Format Support" section of the appropriate version of the Vulkan API Specification.

* "valueWithRegularFont" indicates that the format property is defined in the profile (hover over the value to view the structure and corresponding extension or core API version where the format property is defined in the profile)
* "_valueWithItalicFont_" indicates that the format property is not defined in the profile but an equivalent format property is (hover over the symbol to view the structure and corresponding extension or core API version where the format property is defined in the profile)
* "-" indicates that neither the format property nor an equivalent format property is defined in the profile
* Empty cells next to the properties of a particular format definition section indicate that the profile does not have a corresponding format definition

| Profiles | VP_LUNARG_generated_profile |
|----------|-----------------------------|
| **VK_FORMAT_A2B10G10R10_UINT_PACK32** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_A2B10G10R10_UNORM_PACK32** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_A8B8G8R8_SINT_PACK32** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_A8B8G8R8_SNORM_PACK32** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_A8B8G8R8_SRGB_PACK32** |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_A8B8G8R8_UINT_PACK32** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_A8B8G8R8_UNORM_PACK32** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_B10G11R11_UFLOAT_PACK32** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_B8G8R8A8_SRGB** |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_B8G8R8A8_UNORM** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_D16_UNORM** |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_D32_SFLOAT** |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_E5B9G9R9_UFLOAT_PACK32** |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R16G16B16A16_SFLOAT** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R16G16B16A16_SINT** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R16G16B16A16_SNORM** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| **VK_FORMAT_R16G16B16A16_UINT** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R16G16_SFLOAT** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R16G16_SINT** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R16G16_SNORM** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| **VK_FORMAT_R16G16_UINT** |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R16_SFLOAT** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R16_SINT** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R16_SNORM** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| **VK_FORMAT_R16_UINT** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R16_UNORM** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| **VK_FORMAT_R32G32B32A32_SFLOAT** |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R32G32B32A32_SINT** |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R32G32B32A32_UINT** |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R32G32_SFLOAT** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R32G32_SINT** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R32G32_UINT** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R32_SFLOAT** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R32_SINT** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R32_UINT** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R8G8B8A8_SINT** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R8G8B8A8_SNORM** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R8G8B8A8_SRGB** |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R8G8B8A8_UINT** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R8G8B8A8_UNORM** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R8G8_SINT** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R8G8_SNORM** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R8G8_UINT** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R8G8_UNORM** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R8_SINT** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R8_SNORM** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R8_UINT** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| **VK_FORMAT_R8_UNORM** |
| [bufferFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT \| VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)</span> |
| [linearTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |
| [optimalTilingFeatures](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFormatProperties3.html) | <span title="defined in VkFormatProperties (Vulkan 1.0)">(VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT \| VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT \| VK_FORMAT_FEATURE_BLIT_SRC_BIT \| VK_FORMAT_FEATURE_BLIT_DST_BIT \| VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT \| VK_FORMAT_FEATURE_TRANSFER_SRC_BIT \| VK_FORMAT_FEATURE_TRANSFER_DST_BIT)</span> |

## Vulkan Profile Video Profiles

The table below lists the video profiles (or class of video profiles) that any profile defines requirements for.
Video profile names take the following form:
> `"(General|[<codec>] <category>) [([<subsampling>] [<bits>])] [<codecSpecificProfileInfo>]"`
* "General" refers to general requirements for all video profiles.
* `<category>` is the category of the video profile requirements (e.g. "Decode" or "Encode").
* `<codec>` identifies the specific codec (e.g. H.264, H.265, AV1) the requirements apply to. If not indicated, the requirements apply to all supported video profiles falling in the specified category.
* `<subsampling>` indicates the chroma subsampling (e.g. 4:2:0, 4:2:2, 4:4:4, or monochrome). If not indicated, the requirements apply to all supported chroma subsampling modes.
* `<bits>` indicates the luma and chroma bit depth (e.g. 8-bit, 10-bit, or e.g. 10:8-bit for mixed bit depths). If not indicated, the requirements apply to all supported bit depths. Partial, luma-only or chroma-only "wildcard" requirements are indicated with an asterisk in place of the corresponding bit depth (e.g. 10:\*-bit or \*:8-bit).
* `<codecSpecificProfileInfo>` indicates additional codec-specific video profile information (e.g. "Main", "High"). If not indicated, the requirements apply to all video profiles of the codec.
* :heavy_check_mark: indicates that the profile defines requirements for the video profile (or class of video profiles)
* :x: indicates that that the profile does not define requirements for the video profile (or class of video profiles)

| Profiles | VP_LUNARG_generated_profile |
|----------|-----------------------------|
