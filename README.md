# Quakaster SDK
I originally started this project out as a very small side project, but eventually, it got to the point
where good ol' fashioned move fast and break shit approach no longer became sustainable. Plus, a lot of it was
written by ChatGPT (I'm a college kid with what I think is a neat approach to rendering that I want to test out ASAP).
From now on, I plan to actually write the code for real this time. Yes, big ask, I know.


## Easy-to-use modular game engine
Quakaster, as the name implies, is meant to be heavily inspired by the Quake engine. Obviously, the Quake engine was not built with modern design patterns like Entity-Component systems, which
of course limited the performance of the engine.

It also has the added benefit that it uses a module system (not really but kind of) that allows developers to
include certain feature sets into their own DLLs. The way I'll go about this is by compiling each module into
LLVM, and whomever uses the SDK can define some macros in their build system to build their own instance of
the Quakaster DLL.

## Efficiency, Efficiency, Efficiency, and Efficiency.

The engine is being built on top of Vulkan and EnTT, which are both among some of the most performant in
their respective categories. Game worlds are usually the most expensive part of the scene, so I have a novel
approach to upping the ante when it comes to high-performance code. It's a novel idea without a patent, so
I won't get too in-depth, but I will tell you the benefits you shuold expect from the engine:

- Less memory usage
- Built-in occlusion and frustum culling.
- Built from the ground up with newer technologies (such as an ECS)


