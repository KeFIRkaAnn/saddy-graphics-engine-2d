# Saddy 

Saddy is an open-source crossplatform 2D graphic engine, based on OpenGL, which can be used for creating simple games.

## Download

* **15.02.15** Saddy 1.5-alpha released!

A pre-built engine for Win32 Microsoft Visual C++2010 can be downloaded from here:

[saddy-1.5](https://sourceforge.net/projects/saddyengine/files/?source=navbar)

Note that you must have MSVC2010 redistributable files installed. Also you need to install Freetype library. This is just alpha release, so most of executables are not built. This is not a stable release, they will be built in next release.

* **19.10.14** Saddy 1.4 released!

You can download pre-built engine, demos and docs (Win32-MSVC version) from following pages:

[docs-1.4](https://dl.dropboxusercontent.com/u/5039908/docs-1.4.zip) 

[saddy-1.4](https://dl.dropboxusercontent.com/u/5039908/saddy-1.4.zip)

Changelog :

  * Resource loading has been fully remade to be independent from time of loading.
  * Switched to serializing to JSON for both resources and in-game screens, implemented simple serialization for all basic types
  * Marshalling has been fully remade. Old namespaces "config" and "marshal" has been replaced with "resource" and "db",
  * Resource reloading has been merged with the core.
  * Instead of just editing in-game screens in IFace Editor, now you could edit a simple database and even define objects with custom properties. Also, new version supports dialogue editing and editing ways for physic-based applications.

* **17.02.14** Saddy 1.1-BETA released!

You can download pre-built engine, demos and docs (Win32-MSVC version) from following pages:

[docs-1.1](https://dl.dropboxusercontent.com/u/5039908/docs-1.1-beta.zip) 

[saddy-1.1](https://dl.dropboxusercontent.com/u/5039908/saddy-1.1-beta.zip)

* **26.08.13** Saddy 1.0-BETA released!

## Our Goals

Our main goal is to create tiny graphic engine, which can be used to create a small native 2D games.
  * We want to provide a simple engine, which can be built with NO external dependencies at all. That's right. You don't need to download and build anything to build a source of main page
  * We do, however, use a 3rdparty libraries, like tpunit++ or format, but they are either linked statically, or moved to plugins.
  * We want to provide an easy-to-use toolchain to satisfy simple most basic needs for  creating a simple game.
  * We rely on established and well-known technologies, such as OpenGL, MSVC or GCC.
  * This is project done for fun and powered by it.   

## Supported platforms

Currently, we support a following platforms.

  * Windows, using Microsoft Visual C++ 2010 (x86, x64)
  * Windows, using MinGW (x86/x64)
  * Ubuntu (x86/x64)
  * OpenSUSE (x86/x64)
  * ArchLinux (x86 only)  

However, we cannot provide binary builds for all of those platforms, only guarantee, that built source will work.

## Developers

  * Mamontov Dmitry - leader and current maintainer of project.
  * Alexander Sokolov - programmed core engine
  * Andrey Ryaskov -  programmed windows gui wrapper.
  * Victor Grigoriev - contributed to core engine development
  * Dmitry Kolesov - contributed to core engine development

## Run into a problem? Don't know where to start?

You can write directly to maintainer in Twitter
(https://twitter.com/ahiddenseeker) and we will reply as fast as we can.
