---
---

# How to use roviz

The application should be fairly simple to use. On linux, start it by executing:

```text
$ ./build/dev/linux/debug/out/roviz
```

 When you start it up, you can select/create a workspace and a project and then you're already good to go. On the left side, you will find the different items that you can use. Just drag and drop them to the workspace and connect them together. To change the config of an item, right click on it and select `Configure`. If there is no such entry, the item does not have any configs. If you double-click on an item, it will open in the shared window. All items of the same project will open in the same shared window. There you can see the main widget of the item, which is usually an image representing the current output of the item, and the sliders for the trims. If you modify those sliders, you should immediately see an effect on the output image next to it. You can use the three buttons at the top of the shared window to start/pause/stop the items. The difference between a pause and a stop is, that after returning from a pause, the item will just continue with its operation from the point it was before, where as a stop will reset it to its initial state. For example, a video-generator item would just pause the video when you hit pause, but it would start it from the beginning again if you stop it and start it again.

If you're done designing your application, you can switch to the Cmdline backend to run it with the full performance. To do that, run the following (on linux):

```text
$ ./build/cmdline/linux/debug/out/roviz "PATH/TO/YOUR/PROJECT.tpro"
```

In this mode, you won't have any GUI, you don't even need Qt anymore. All you need is a project file that developed within roviz.
