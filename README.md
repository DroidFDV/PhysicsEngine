# Physics Engine

## Description
Minimal physics engine which provide Circle, AABB, OBB, Force Manger, Contact Manager and other tools to create your first pregame.

## Building
Please use [`premake5`](https://premake.github.io/docs/Using-Premake/) to build our project.
- Ensure `premake5` is installed
- Ensure `premake5` is in the user `PATH`

### Windows
- Use next command in root directory:
```
vendor\premake5.exe [PLATFORM]
```
Please check `vendor\premake5.exe --help` to see available platforms.

### Linux
- Use next command in root directory:
```
premake5 [MAKE FILE GENERATOR]
```
- Run `./build/Core/bin/[CONFIGURATION]/Engine`
- Other way to build our project:  use script `./build.sh [ACTION]`

Please see `premake5 --help` to more details

### Mac
- Use next command in root directory:
```
premake5 xcode4
```
## Roadmap

- [x] Rewrite Gvector
- [x] Separate math and structures
- [x] ?? Friction ??
- [x] Abstract class for primitives
- [x] Implement primities
- [x] Contact Managment
- [ ] Force Managment
- [ ] Collision Manifolds
  - [x] Box vs. Box
  - [x] Circle vs. Circle
  - [ ] Circle vs. Box 
- [ ] Optimize Collision Detection ?? Grid ??
- [x] Render
- [x] build.sh
- [ ] build.bat
- [x] Write documentation 
- [ ] Write wiki
