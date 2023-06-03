# Readme.md

## Description
Minimal physics engine which provide Circle, AABB, OBB and tools to detect and solve their collisions.

## Build
We are provide a `premake5` tool to build our project.

### Windows
In root directory use:
```
vendor\premake5.exe [PLATFORM]
```
Check ```vendor\premake5.exe --help``` to see available platforms to option `[PLATFORM]`.

### Linux
In root directory use: 
```
premake5 gmake2
```
then in directory build use make.  Or use script `./build.sh` and run `./build/Core/bin/[CONFIGURATION]/Engine`.

### Mac
Not available now.

# Roadmap

- [x] Rewrite Gvector
- [x] Separate math and structures
- [ ] ?? Friction ??
- [x] Abstract class for primitives
- [x] Implement primities
- [ ] Force Managment
- [ ] Collision Manifolds
- [ ] Optimize Collision Detection 
- [ ] build.sh
- [ ] build.bat
- [ ] Write documentation 
- [ ] Write wiki
