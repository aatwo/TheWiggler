# TheWiggler

This is a small Qt / QML / C++  application that moves your mouse to prevent screensavers and auto locking. It is moderately configurable via a QML UI. 

See the **releases** page to download a ready to run version.

Currently, it builds on both **Windows** and **macOS** and releases for both can be found on the release page (so far I've only tested it on Windows 10 and macOS High Sierra 10.13).

# Build instructions

Qt is the main dependency and can be downloaded for free from https://www.qt.io. 

- For Windows users you will also need Visual Studio 2017 installed if you are using the latest Qt release (5.14.2).
- For macOS users you will need XCode which the Qt installer should prompt you to install if it is missing.

Once the dependencies are installed you should be able to open the project in Qt Creator and run / build it.

Currently, the build has only been tested on Windows 10 and macOS High Sierra 10.13.

# Deployment instructions

Once you have built a release version of the application you may wish to deploy so it can be run on other machines by collecting all the shared library dependencies.

# Windows deployment

For Windows deployment you can use the `windeployqt.exe` which is found in the Qt install directory. For example:

```
C:/Qt/5.14.0/msvc2016_64/bin/windeployqt.exe
```

Simply run this tool using the following parameters:

```
./windeployqt.exe {path-to-build-folder}\TheWiggler.exe --qmldir {path-to-repo-root}\TheWiggler
```
	
This will copy all the dependencies required to run `TheWiggler.exe` on any machine into the folder containing `TheWiggler.exe`.

# macOS deployment

For OSX deployment you can use the `macdeployqt` tool found in the Qt install directory. For example:

```
$HOME/Qt/5.14.2/clang_64/bin/macdeployqt
```
	
Simply run this tool using the following parameters:

```
./macdeployqt {path-to-build-folder}\TheWiggler.app -qmldir={path-to-repo-root}\TheWiggler
```
	
This will pack your `.app` file with all the required Qt framework dependencies required to run the app on any machine.
