---
---

# roviz v0.7

## Overview

roviz is a tool, which can simplify the design of computer vision applications. If you want to interpret an image/video stream to e.g. identify objects, people, movement or other things, there are frameworks out there that can help you, most notably [OpenCV](http://opencv.org/). [OpenCV](http://opencv.org/) is great, but it has one big downside: It's not really interactive. That means, that the process to e.g. trying out a new filter always consists of adjusting code, recompiling, restarting the application and at the worst case, you also have to somehow restore the previous state. roviz wants to solve that problem. It builds upon the [itemframework](https://github.com/rdit-ch/itemframework) and provides a Drag-Drop-Adjust interface to manipulate your design.

### Main Features:

 * Graphically create an image processing pipeline
 * Arrange items/filters on the fly
 * Adjust (numerical) parameters on the fly
 * [OpenCV](http://opencv.org/) integration
 * Very easily expandable with plugins
 * Start/stop/pause your application
 * Every item runs in a separate thread
 * Support for sparse data (2D/3D point clouds)
 * Items can be reused
 * Support for GUI-less operation (Cmdline backend)
 * C++ based (Qt 5 is used for GUI handling)

_NOTE: This software is still in its beta-phase. If you find any bugs, please feel free to report them using GitHubs issue tracker. At this stage, API changes are still possible._

<a href="https://shadowigor.github.io/roviz-docs/screenshot.png"><img src="https://shadowigor.github.io/roviz-docs/screenshot.png" alt="Screenshot of the framework in use" width= "800"/></a>

## How it works

If you have a computer vision (or similar) application, you probably have some kind of pipeline that processes the individual frames. With roviz, you will be able to graphically arrange this pipeline and visualize it. This has three big advantages: First, you will better understand your application, because it is in a more structured form. Second, you can change parts of your pipeline while the program is running. If you for example wonder if a canny filter would be a more suited edge-detector than you current sobel filter, you can exchange them on the fly and see the difference within seconds. Third, most of your filters will have some kind of parameters, so we implemented sliders, that allow you to adjust those parameters on the fly as well. If you also had a gaussian blur filter in your project, you could adjust the blur factor with a slider and immediately see the effect it has on the output.

One important aspect of roviz is, that we don't want a tool that does any GUI black magic. The developer needs full control over the individual items. You also need to be able to easily implement your own items, because just using the default items won't be sufficient for most applications. All items are C++ plugins that are easily written. The roviz framework tries to do all kind of input/output and display handling so you don't have to worry about that, but it doesn't mess with your images in any way. Due to the fact that [OpenCV](http://opencv.org/) is supported, writing items is really easy. Mostly, you will only add a couple sliders, call an [OpenCV](http://opencv.org/) function and your plugin is ready. We are trying to include as much items as possible per default, but this is still a work in progress.

## It's not only about computer vision

Most applications are of course more than just computer vision. It is difficult to implement a solution for this problem that suits as many applications as possible. But you can for example create a separate item for the rest of your application that gets fed with the processed image stream. You can also invoke other applications form that item, there are no restrictions. We also tried to provide some more stream variants than just images. We currently have support for point clouds, in case you need sparse data, and messages to transmit simple, arbitrary data. We try to also support other forms of data that are suited for this type of processing and even if we don't support something, it is very easy to implement your own streams.

This program was initially developed to process the images that come from a robot and control it based on this input, so we also wanted to be able to run our software on embedded platforms. This is why we decided to completely remove the need to have Qt available on your system for the items to work. This way, your items are pure C++ and can be reused as-is on embedded platforms. So when you are done developing your application, you can switch to the [Cmdline](howto_backends) backend and use your project as a Qt-less and performance optimized standalone application.

## Installing roviz

First, install the following packages:

 - [git](https://git-scm.com/) (if you compile it from GitHub)
 - A C++ copiler with C++11 support (e.g. g++ 4.7)
 - [Qt 5](https://www.qt.io/)
 - [OpenCV](http://opencv.org/)
 - [tinyxml2](http://www.grinninglizard.com/tinyxml2/)

Then, to build and install roviz, you have to run the following commands:

```text
$ git clone https://github.com/rdit-ch/roviz.git
$ cd roviz
$ ./build.sh
\# ./install.sh
```

You can then run the program with:

```text
$ roviz
```

You can find the documentation and some guides that should help you getting started with roviz here: [https://rdit-ch.github.io/roviz/](https://rdit-ch.github.io/roviz/).

# Future plans

 - Windows/OSX support
 - Multithreaded single items
 - [ROS](http://www.ros.org/) integration
 - Machine learning integration
 - More default items

# License
[GPLv3](https://www.gnu.org/licenses/gpl-3.0.de.html). Contact us if you would like to use it under a different license (e.g. commercial).

# Contact

Rdit.ch  
[contact@rdit.ch](mailto:contact@rdit.ch)
