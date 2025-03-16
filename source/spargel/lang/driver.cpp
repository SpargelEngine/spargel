#include <stdio.h>

#include <spargel/base/command_line.h>
#include <spargel/base/string.h>
#include <spargel/base/string_view.h>
#include <spargel/lang/syntax.h>
#include <spargel/resource/directory.h>
#include <spargel/resource/resource.h>

using spargel::base::CommandLine;
using spargel::base::string;
using spargel::base::string_view;
using spargel::lang::Lexer;
using spargel::resource::ResourceId;
using spargel::resource::ResourceManagerDirectory;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "error: no input file\n");
        return 1;
    }

    CommandLine cmd(argc, argv);

    ResourceManagerDirectory resource_manager(".");
    auto blob = resource_manager.open(ResourceId(string(argv[1])));
    if (!blob.hasValue()) {
        fprintf(stderr, "error: cannot open `%s`\n", argv[1]);
        return 1;
    }
    auto source = string_view((char*)blob.value()->mapData(), (char*)blob.value()->mapData() + blob.value()->size());

    if (cmd.hasSwitch("lex")) {
        Lexer lexer(source);
    }

    return 0;
}
