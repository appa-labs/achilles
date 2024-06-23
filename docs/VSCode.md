# Небольшой гайд по настройке VSCode + Bazel

1) поставить VS Code, WSL (инструкция в [docs/SETUP.md](docs/SETUP.md))
2) поставить в WSL `cmake`, `clang` и всё, что нужно, с помощью команды: `sudo apt install build-essential gdb cmake clang clang-format clang-tidy`
3) установить в VS Code расширения:
   - C/C++ Extension Pack (автор — Microsoft), WSL (Microsoft),
   - CMake (twxs),
   - CMake Tools (Microsoft),
   - Clang-Format (Xaver Hellauer)
4) установить bazel, следуя инструкциям на официальном сайте