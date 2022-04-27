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
At the moment, only Linux & Windows platforms are officially supported. MacOS support is unofficial and will be tested for issues
on voluntary basis only.



### Building

1. Satisfy dependencies: GNU parallel (optional), GNU make, git, C++17 capable compiler, 7zip/tar, SFML>=2.5

2. Clone the repository
```
    git clone <mirror url>
```

3. Build and install the game
```
    make
    make install
```

4. On Windows, execute build-windows.bat instead - the built game will be placed inside "build" directory



### Notice

On Windows, SFML is bundled locally with the project. On other platforms however, nothing is bundled,
the dependencies are assumed to be installed globally system-wide.

On Windows, the only compiler supported is [MinGW](https://winlibs.com) and it is assumed that directories for
compiler, git and 7zip executables exist inside PATH variable. Also, universal C runtime comes pre-installed on Windows 10
and later, but needs to be manually installed on earlier Windows versions, if used.

Windows and Linux builds are provided for download in "Releases" section as self-contained zip archive
and AppImage respectively. For other operating systems, the game needs to be built from source.
By default, launching AppImage will run the client, to run the server pass --server option.

On MacOS, you can install the game using Homebrew
```
    xcode-select --install
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    sudo chown -R $(whoami) $(brew --prefix)/*

    brew tap fenex33/surv <mirror url>
    brew update
    brew install surv-royale
```



### Mirrors

- https://github.com/Fenex330/surv-royale.git

- https://codeberg.org/fenex33/surv-royale.git

- https://notabug.org/fenex33/surv-royale.git (read-only)



### License

Distributed under [MIT License](./LICENSE.txt)



### Contacts

For any questions or queries please contact anonimus33@protonmail.com
