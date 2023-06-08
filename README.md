# Physics Engine

## Description
Minimal physics engine which provide Circle, AABB, OBB, Force Manger, Contact Manager and other tools to create your fist pregame.

## Building
Please use [`premake5`](https://premake.github.io/docs/Using-Premake/) to build our project.
- Ensure `premake5` is installed
- Ensure `premake5` is in the user `PATH`

### Windows
- use next command in root directory:
```
vendor\premake5.exe [PLATFORM]
```
Please check `vendor\premake5.exe --help` to see available platforms.

### Linux
- use next command in root directory:
```
premake5 [MAKE FILE GENERATOR]
```
- run `./build/Core/bin/[CONFIGURATION]/Engine`
- other way to build our project:  use script `./build.sh [ACTION]`

Please `premake5 --help` to see more details

### Mac
Not available now.

## Roadmap

- [x] Rewrite Gvector
- [x] Separate math and structures
- [x] ?? Friction ??
- [x] Abstract class for primitives
- [x] Implement primities
- [ ] Force Managment
- [ ] Collision Manifolds
  - [x] Box vs. Box
  - [ ] Circle vs. Circle
  - [ ] Circle vs. Box 
- [ ] Optimize Collision Detection 
- [ ] build.sh
- [ ] build.bat
- [x] Write documentation 
- [ ] Write wiki
