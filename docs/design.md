# Spargel XXX Language

XXX = shading/scripting/...

## Examples

```
// this is a comment

// # The Module System
//
// foo/
//   a.xxx <-+ <--- current file
//   b.xxx <-+- module `foo`
//   c.xxx <-+
//   bar/
//     d.xxx <- module `foo/bar`
//   baz/
import bar // module bar is resolved in the compiler args
// compiler --module bar=/path/to/build/dir/foo/bar/bar.xxxmod

// defining a function
def main() // this line has indentation 0
    // this line has indentation 4, which is larger than that of the last line
    // so a block starts

    // there is no need for semicolon
    print("hello") // calling a function

    if 1 + 1 > 2 then
        // a new block!
        print("1 + 1 > 2")
    else
        print("1 + 1 <= 2")

    // it is equivalent to the following
    if { 1 + 1 > 2 } then { // note the block between if and else
        print("1 + 1 > 2")
    } else {
        print("1 + 1 <= 2")
    }

    // what is a block?
    // it should be understood as a function!

    // a nested definition
    def my_if_else(cond, succ, fail)
        // pattern matching
        match cond()
            // special syntax
            true => succ()
            false => fail()

def fib(n: nat)
    match n
        0 => 0
        1 => 0
        n => fib(n - 1) + fib(n - 2)

struct VertexInput
    @shader.location(0)
    position: vec2(float)
    @shader.location(1)
    color: vec4(float)

struct RasterInput
    @shader.position
    position: vec3(float)
    color: vec4(float)

@shader(stage: vertex)
def vertex_shader(@shader.input input: VertexInput,
                  @shader.vertex_id vid: uint,
                  @shader.instance_id iid: uint,
                  @shader.binding(group: 0, location: 0) viewport: &float2)
    var pos = input.position / ( viewport / 2.0 )
    RasterInput { // position: &mut vec3(float), color: &mut vec4(float)
        position = vec3(float)(pos)
        color = input.color
    }

@shader(stage = pixel)
def pixel_shader(@shader.input input: RasterInput)
    input.color
```
