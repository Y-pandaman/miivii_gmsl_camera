# Changelog
All notable changes to this project will be documented in this file.

## [Unreleased]
## [1.0.0] - 2020-07-14
- Adapted for Jetpack 4.4 GA
- refactor for better performance 

## [0.1.4] - 2019-08-07
- Fixed bugs in cameras_opencv_demo.cpp when set fmt as YUYV results program crash.
- Added version number support in both dynamic libs and header file.
- Removed redundant outputs.

## [0.1.3] - 2019-06-18
- Change the directory structure for easy management.

## [0.1.2] - 2019-04-13
- Adjust folder structure to adapt C++ Project Standard.
- Optimize user compilation methods
  
## [0.1.1] - 2019-04-09

### Changed

- Added timestamp interface in SDK and usage in example.cpp.
- Modified make logic. 

## [0.1.0] - 2019-03-08

### Changed

- Rewrote the SDK so that it no longer depends on Nv header files.
- Modified example.cpp.
- Modified folder structure.

## [0.0.5] - 2019-02-20
### Changed
- Add example launch command in README.md.

## [0.0.4] - 2019-02-16
### Changed
- S2-pro compatible.

## [0.0.3] - 2019-01-17
### Added
- R5 synchronize support

### Changed
- Use CV Display instead of EGLRender.
### Fixed
- Camera frozen in long time test.

## [0.0.2] - 2018-12-20

### Removed
- Removed SDK alone with example.

## [0.0.1] - 2018-12-18
### Added
- Added control of multi-window parameters. 
- Fix a build problem on build.sh script. 
### Changed
- Make install path changed to /lib/
- Simplify code structure.
- Replace multi-media framework to xavier compatible.
