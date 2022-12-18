# 🔧 Qt Example Plugin

<div align="center">

  [![GitHub license](https://img.shields.io/github/license/Gamer92000/TeamSpeak3-Qt-Plugin-Template.svg)](https://github.com/Gamer92000/TeamSpeak3-Qt-Plugin-Template/blob/main/LICENSE)
  [![GitHub commits](https://badgen.net/github/commits/Gamer92000/TeamSpeak3-Qt-Plugin-Template/main)](https://GitHub.com/Gamer92000/TeamSpeak3-Qt-Plugin-Template/commit/)
  [![Github stars](https://img.shields.io/github/stars/Gamer92000/TeamSpeak3-Qt-Plugin-Template.svg)](https://GitHub.com/Gamer92000/TeamSpeak3-Qt-Plugin-Template/stargazers/)
  [![Renovate](https://img.shields.io/badge/maintained%20with-renovate-brightgreen)](https://github.com/Gamer92000/TeamSpeak3-Qt-Plugin-Template/issues/4)
  <!-- [![Deploy](https://img.shields.io/github/actions/workflow/status/Gamer92000/TeamSpeak3-Qt-Plugin-Template/deploy.yml?branch=*)](https://github.com/Gamer92000/TeamSpeak3-Qt-Plugin-Template/actions/workflows/deploy.yml) -->
  <!-- https://github.com/badges/shields/issues/8736 -->
  <br>
  <h3>If you like this project, please consider giving it a star ⭐️!</h3>
</div>

## 📖 Description

This is a simple example plugin for TeamSpeak. It is meant to be used as a starting point for developing your own plugins. Using CMake, it can be compiled for all supported platforms.

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 📚 Documentation

An outdated documentation for the TeamSpeak Client SDK can be found in the [latest release](https://github.com/TeamSpeak-Systems/ts3client-pluginsdk/releases/tag/23) of the plugin SDK.

This plugin uses the [Qt](https://www.qt.io/) framework. The Qt documentation can be found [here](https://doc.qt.io/).

## 📦 Requirements

To compile this plugin (on Windows), you need the following software installed:

* [Qt =5.12.3](https://www.qt.io/download)
* [CMake >=3.10](https://cmake.org/download/)
* [Visual Studio <=2019 (Toolset v140)](https://visualstudio.microsoft.com/downloads/)

## 🚀 Usage

To create a new plugin based on this example, you can use the button `Use this template` on GitHub. This will create a new repository for you, which you can clone and modify.

### 👶 First steps

First, you need to rename the plugin. To do this, you need to change the following files:

* `CMakeLists.txt`
* `src/definitions.hpp`
* `.github/workflows/deploy.yml`
* `deploy/package.ini`

For Cmake, you also need to point it to the correct Qt installation. To do this, you need to change the following line in `CMakeLists.txt`:

```diff
-# list(APPEND CMAKE_PREFIX_PATH "H:/Qt/5.12.3/msvc2017_64")
+list(APPEND CMAKE_PREFIX_PATH "H:/Qt/5.12.3/msvc2017_64")
```

### 📦 Before Updating

Before publishing a new version of your plugin, don't forget to update the version number of the plugin in the following files:

* `src/definitions.hpp`
* `deploy/package.ini`

## ⚠️ Disclaimer

This plugin is not supported by TeamSpeak Systems GmbH. It is provided as-is and without any warranty. You are free to use it as a starting point for your own plugins, but you are responsible for any issues that may arise from using it.

## 📝 Contributing

If you want to contribute to this project, feel free to open a pull request. I will try to review it as soon as possible.