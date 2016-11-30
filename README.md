# roviz v0.5

## Overview

roviz is a tool, which can simplify the design of computer vision applications. If you want to interpret a video stream to e.g. identify objects, people, movement or other things, there are frameworks out there that can help you, most notably [OpenCV](http://opencv.org/). [OpenCV](http://opencv.org/) is great, but it has one big downside: It's not really interactive. That means, that the process to e.g. try out a new filter always consists of adjusting code, recompiling, restarting the application and at the worst case, you also have to somehow restore the previous state. roviz wants to solve that problem. It builds upon the [itemframework](https://github.com/rdit-ch/itemframework) and provides a Drag-Drop-Adjust interface to manipulate your design.

### Main Features:

 * Change items on the fly
 * Adjust (numerical) parameters on the fly
 * [OpenCV](http://opencv.org/) integration
 * Start/stop/pause your application
 * Every item runs in a separate thread
 * Support for sparse data (point clouds)
 * Items can be reused
 * C++ based (Qt5 is used for GUI handling)

_NOTE: This software is still in its beta-phase. If you find any bugs, please feel free to report them using GitHubs issue tracker._

<a href="./screenshot.png"><img src="./screenshot.png" alt="Screenshot of the framework in use" width= "800"/></a>

## Getting started

To build the project, you have to run the following commands:

```
$ ./update_deps.sh
$ qmake
$ make
```

NOTE: You need to have git and at least Qt 5.5 installed on your system.

You can then run the program with (assuming you run it on a linux machine):

```
$ ./build/linux/release/roviz
```

If you would like to create your own plugins, you can build the documentation by running doxygen in the root folder.

```
$ doxygen
```

You can then look at the documentation of the PortableItem class, which is the main class that is used for developing plugins. If you don't want to build the documentation, you can also find all the basic information in 'usercore/include/portable/portable_item.h'. To create a new project based on a template, you can use the 'new_project.sh' script.

```
$ ./new_project CLASS_NAME
```

You can also look at the default items if you need some inspiration. They are located at 'plugins/'.

## How it works

If you have a computer vision (or similar) application, you probably have some kind of pipeline that processes the individual frames. With roviz, you will be able to graphically arrange this pipeline and visualize it. This has three big advantages: First, you will better understand your application, because it is in a more structured form. Second, you can change parts of your pipeline while the program is running. If you for example wonder if a canny filter would be a more suited edge-detector than you current sobel filter, you can exchange them on the fly and see the difference within seconds. Third, most of your filters will have some kind of parameters, so we implemented sliders, that allow you to adjust those parameters on the fly as well. If you also had a gaussian blur filter in your project, you could adjust the blur factor with a slider and immediately see the effect it has on the output.

One important aspect of roviz is, that we don't want a tool that does any GUI black magic. The developer needs full control over the individual items. You also need to be able to easily implement your own items, because just using the default items won't be sufficient for most applications. All items are C++ plugins that are easily written. The roviz framework tries to do all kind of input/output and display handling so you don't have to worry about that, but it doesn't mess with your images in any way. Due to the fact that [OpenCV](http://opencv.org/) is supported, writing items is really easy. As an example, to implement the gaussian blur item, you only have to add 6 lines of code to the standard template! For [OpenCV](http://opencv.org/) functions, this number will always be more or less the same and we are currently working on it to include as many [OpenCV](http://opencv.org/) items as possible by default.

## It's not only about computer vision

Most applications are of course more than just computer vision. It is difficult to implement a solution for this problem that suits as many applications as possible. But you can for example create a separate item for the rest of your application that gets fed with the processed image stream. You can also invoke other applications form that item, there are no restrictions. We also tried to provide some more stream variants than just images. We currently have support for point clouds, in case you need sparse data, and messages to transmit simple, arbitrary data. We try to also support other forms of data that are suited for this type of processing and even if we don't support something, it is very easy to implement your own streams with the power of the [itemframework](https://github.com/rdit-ch/itemframework).

This program was initially developed to process the images that come from a robot and control it based on this input, so we also wanted to be able to run our software on embedded platforms. This is why we decided to completely remove the need to have Qt available on your system for the items to work. This way, your items are pure C++ and can be reused as-is on embedded platforms. In the future, we intend to develop a stripped down, non-interactive version of the roviz framework that will run on embedded platforms and can reuse the items and applications you designed with the interactive version.

# License

[GPLv3](https://www.gnu.org/licenses/gpl-3.0.de.html). Contact us if you would like to use it under a different license (e.g. commercial).

# Contact

Rdit.ch  
[contact@rdit.ch](mailto:contact@rdit.ch)
