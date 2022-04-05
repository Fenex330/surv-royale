# Table of contents

* [About](#About)
* [Building](#Building)
* [Notice](#Notice)
* [Mirrors](#Mirrors)
* [License](#License)
* [Contacts](#Contacts)



### About

**SurvRoyale** is a desktop clone of the popular browser battle royale shooter - [surviv.io](https://surviv.io/), written in C++.
The project is currently in the stage of an early alpha development, so any contribution via pull request or issue is welcome.
At the moment, only Linux and Windows platforms are officially supported. Macos support is planned in the future.



### Building

1. Dependencies: GNU make, GNU parallel (optional), git, C++17 capable compiler, 7zip/tar, SFML>=2.5

2. Clone the repository:
```
    git clone --depth 1 <url from one of the mirrors below>
```

3. Build and install the game
```
    make && make install
```

4. On Windows, execute build-windows.bat instead. The built game will be placed inside "build" directory



### Notice

On Windows, SFML is bundled locally with the project. On Linux and other platforms however, nothing is bundled,
the dependencies are assumed to be installed globally system-wide.

On Windows, the only compiler supported is MinGW (tested winlibs-x86_64-posix-seh-gcc-11.2.0-llvm-14.0.0-mingw-w64msvcrt-9.0.0-r7.7z)
and is assumed that directories for compiler and 7zip executables exist inside PATH variable.
Also, universal C runtime comes pre-installed on Windows 10, but needs to be manually installed on earlier Windows versions.

Windows and Linux builds are provided for download in "Releases" section as self-contained zip archive
and AppImage respectively. For other operating systems, the game needs to be manually built from source.
By default, launching AppImage will run the client, to run the server pass --server option.



### Mirrors

Primary https://github.com/Fenex330/surv-royale.git

Secondary https://notabug.org/Fenex33/surv-royale.git



### License

Distributed under [MIT License](./LICENSE.txt)



### Contacts

For any questions or queries please contact anonimus33@protonmail.com
