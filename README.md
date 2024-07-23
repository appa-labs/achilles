# Achilles Game Engine

Achilles is a 2D light weight game engine developed using C++ and [SFML](https://github.com/SFML/SFML).

## Table of Contents

- [Description](#description)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)

## Description

Achilles Game Engine is a 2D game engine that provides a framework for developing platformer games. The engine includes features such as physics simulation, collision detection, and rendering. It is designed to be easy to use and flexible, allowing developers to create custom game mechanics and content.

## Installation

To install achilles, follow this [steps](https://github.com/appa-labs/achilles/blob/main/docs/SETUP.md) or quick start with the following commands in your bazel WORKSPACE file:

```WORKSPACE
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "achilles",
    remote = "https://github.com/appa-labs/achilles.git",
)
```

## Usage

To make game using achilles, you need to create a new class that inherits from `Engine` class and implement some pure virtual functions, see example [here](https://github.com/appa-labs/achilles/tree/main/example).

## Examples

Here are some screenshots from Achilles Game:

![Example 1](https://github.com/appa-labs/achilles/blob/media/physics_record_1.gif)

## Contributing

Contributions are welcome! If you would like to contribute, please follow these guidelines:

- Submit bug reports or feature requests by creating an issue on the GitHub repository.
- Fork the repository, make your changes, and submit a pull request for review.
- Follow the coding style and conventions used in the project.

## License

Achilles Game is distributed under the MIT License. See the [LICENSE](https://github.com/appa-labs/Achilles/blob/main/LICENSE) file for more information.
