# EyeTracking V2

In this project I will re-write the existing [Software Engineering](https://github.com/xsoophx/SoftwareEngineering)
Project in C++.

The Architecture will be slightly changed and optimized, further information about this project will be added on the go.

## Config File :wrench:

The new config file is adapted and improved. While
the [old configfile](https://github.com/xsoophx/SoftwareEngineering/blob/master/cfg.json) contained some impossible
state, the new one is substituting this with meaningful state. See the following example:

```json
{
  "general": {
    "fullscreen": true,
    "width": 1920,
    "height": 1080,
    "selectionMenuEnabled": true,
    "activatedTool": null,
    "masterPath": "masterPath",
    "exportPath": "exportPath",
    "imagePath": "imagePath"
  }
}
```

The JSON snippet shows the properties __"fullscreen"__ and __"width / height"__, as well as __"selectionMenuEnabled"__
and __"activatedTool"__, which are pairs of impossible state.

These settings can now be expressed through the properties __"displayMode"__ and __"activatedTool"__. See the following
examples:

__1. Fullscreen is enabled, Bubble View is activated:__

```json
{
  "general": {
    "displayMode": "fullScreen",
    "activatedTool": "bubbleView",
    "masterPath": "masterPath",
    "exportPath": "exportPath",
    "imagePath": "imagePath"
  }
}
```

__2. Display Mode is specified by width and height, Selection Menu is implicitly enabled:__

```json
{
  "general": {
    "displayMode": {
      "width": 1920,
      "height": 1080
    },
    "masterPath": "masterPath",
    "exportPath": "exportPath",
    "imagePath": "imagePath"
  }
}
```

