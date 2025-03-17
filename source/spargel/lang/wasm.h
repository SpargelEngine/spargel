#pragma once

#include <spargel/base/either.h>
#include <spargel/base/span.h>

namespace spargel::lang {

    enum class WasmModuleParseError {
    };

    class WasmModule {
    public:
    };

    base::Either<WasmModule, WasmModuleParseError> parseWasmModule(base::span<u8> bytes);

}
