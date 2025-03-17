
#include <spargel/base/logging.h>
#include <spargel/base/panic.h>

//
#include <combaseapi.h>
#include <d3d12.h>
#include <d3dcommon.h>
#include <dxgi1_3.h>
#include <winerror.h>

#define CHECK_RESULT(expr)                                                \
    do {                                                                  \
        HRESULT result = expr;                                            \
        if (FAILED(result)) {                                             \
            spargel_log_fatal(#expr " failed with result = %ld", result); \
            spargel_panic_here();                                         \
        }                                                                 \
    } while (0)

int main() {
    ID3D12Debug* debug;
    CHECK_RESULT(D3D12GetDebugInterface(IID_PPV_ARGS(&debug)));
    debug->EnableDebugLayer();

    // Use `CreateDXGIFactory2` to enable debugging.
    // `CreateDXGIFactory2` creates a DXGI 1.3 factory.
    IDXGIFactory3* factory;
    CHECK_RESULT(CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&factory)));

    u32 adapter_id = 0;
    IDXGIAdapter* adapter;
    CHECK_RESULT(factory->EnumAdapters(adapter_id, &adapter));

    DXGI_ADAPTER_DESC adapter_desc;
    adapter->GetDesc(&adapter_desc);
    spargel_log_info("adapter: %ls", adapter_desc.Description);

    ID3D12Device* device;
    CHECK_RESULT(D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&device)));

    ID3D12CommandQueue* queue;
    D3D12_COMMAND_QUEUE_DESC queue_desc;
    queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    queue_desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    queue_desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queue_desc.NodeMask = 0;

    CHECK_RESULT(device->CreateCommandQueue(&queue_desc, IID_PPV_ARGS(&queue)));

    return 0;
}
