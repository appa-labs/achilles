# Настройка окружения

Дальше описаны шаги, которые вам нужно предпринять, начать работу над проектом.

Вам нужно будет пройти следующие шаги:

- [Скачивание git репозитория](#git)
- [Установка bazel, компиляторов, clang-tidy, clang-format](#install)
- [Настройка IDE](#ide)
- [Запуск проекта из консоли](#build)

---

## Скачивание git репозитория <a id='git'/>

Вся работа над проектом происходит через git репозиторий. Для начала нужно
его получить, скачать и настроить доступ.
О том, что такое гит, и как вообще с ним работать, рассказывают тут -- [лекции про
гит](https://yadi.sk/i/YUe3SJYo11EChA).

### Установка необходимого

Нам нужно установить ssh-keygen (если его нет) и git.
С некоторой вероятностью они уже стоят, проверить можно так:

```shell
git --version
ssh-keygen --help
```

Если же нет, то устанавливаем: [git](https://git-scm.com/download/win)

### Создание ssh-ключа

Можно почитать [туториал гитхаба](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account) о том как создать и добавить в аккаунт ssh ключ.

Если что-то не получилось - обращайтесь в телеграм-чат.

### Клонирование и настройка репозитория

```bash
# Переходим в директорию, где вы хотите разместить репозиторий с проектом
cd <твоя выбранная директория>

# Клонируем репозиторий с https://github.com/repo_name
git clone git@github.com:repo_name.git

# Переходим в директорию склонированного репозитория
cd 2D_Engine

# Настраиваем гит так, чтобы он знал нас "в лицо"
git config --local user.name "<твой логин с github.com>"
git config --local user.email "<твой email с github.com>"

```

<details><summary><a>Как проверить себя?</a></summary>

Проверьте, что git настроен корректно (находясь в внутри репозитория):

   ```bash
   > git status
   On branch main
   Your branch is up to date with 'origin/main'.

   nothing to commit, working tree clean
   ```
 (ветка может быть другая)
</details>

## Установка bazel, компиляторов, clang-tidy, clang-format <a id='install'/>

 **bazel**

* [ссылка для скачивания](https://docs.bazel.build/versions/3.2.0/install-windows.html)
* [настройка](https://www.youtube.com/watch?v=LlMX7faTQ-M)

<details><summary><a>Как проверить себя?</a></summary>

Проверьте, что bazel установлен корректно (находясь в внутри репозитория):

   ```bash
   > bazel
   Usage: bazel <command> <options> ...

   Available commands:
   analyze-profile     Analyzes build profile data.
   aquery              Analyzes the given targets and queries the action graph.
   build               Builds the specified targets.
   canonicalize-flags  Canonicalizes a list of bazel options.
   clean               Removes output files and optionally stops the server.
   coverage            Generates code coverage report for specified test targets.
   ...
   bazel help info-keys
                   Displays a list of keys used by the info command.
   ```
 (Предупреждения в начале это нормально)
</details>

## Установка и настройка IDE <a id='ide'/>

Настройте VS Code
      - Смотрите [Гайд по настройке VSCode](docs/VSCode.md)



### Запуск проекта из консоли <a id='build'/>

Все действия нужно производить из консоли, аналогично тому, как вы настраивали ключи и git.

Быстрый запуск:

```bash
# Скачать sfml
sudo apt install -y libsfml-dev
# Cобрать
bazel buld <path-to-build-file>:<pocket-name>

# Собрать и запустить
bazel run <path-to-build-file>:<pocket-name>
```

