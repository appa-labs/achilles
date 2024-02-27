# Настройка окружения

Дальше описаны шаги, которые вам нужно предпринять, начать работу над проектом.

Вам нужно будет пройти следующие шаги:

- [Скачивание git репозитория](#git)
- [Установка MVS, ReSharper C++](#install_ide)
- [Отправка решения](#code)

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
- Воспользуйтесь `ssh-keygen` (возможно, вам придется поставить `openssh-client`), затем скопируйте **.pub** ключ:

```shell
>ssh-keygen -t ed25519
Generating public/private ed25519 key pair.
Enter file in which to save the key (C:\Users\Kirill/.ssh/id_ed25519):
# можете ввести любое имя файла или нажать enter,
# в этом случае ssh-keygen создаст файл с именем id_ed25519
>github 

# Обратите внимание, что вы можете не указывать пароль для ключа,
# чтобы не приходилось его потом вводить на каждое действие c ключом
# Это стандартная практика, хотя и не очень безопасная
```
Далее вам необходимо добавить ключ, находящийся в файле с разрешением **.pub** в свой github аккаунт. 

Тут можно почитать [туториал гитхаба](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account), о том как создать и добавить в аккаунт ssh ключ.

<details><summary><a>Как проверить себя?</a></summary>

Проверьте, что ssh соединение установлено:

   ```bash
   >ssh -T git@github.com
   The authenticity of host 'github.com (IP ADDRESS)' can not be established.
   ED25519 key fingerprint is SHA256:+DiY3wvvV6TuJJhbpZisF/zLDA0zPMSvHdkr4UvCOqU.
   Are you sure you want to continue connecting (yes/no)?
   >yes
   Hi USERNAME! You have successfully authenticated, but GitHub does not provide shell access.
   ```
</details>

Если что-то не получилось - обращайтесь в телеграм-чат.

### Клонирование и настройка репозитория

```bash
# Переходим в директорию, где вы хотите разместить репозиторий с проектом
cd <твоя выбранная директория>

# Клонируем репозиторий с https://github.com/appa-labs/Achilles
git clone git@github.com:appa-labs/Achilles.git

# Переходим в директорию склонированного репозитория
cd Achilles

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

## Установка MVS, ReSharper C++ <a id='install_ide'/>

- [Гайд по  установке Microsoft Visual Studio для С++](https://www.youtube.com/watch?v=f9QZQumiC8I) - [ссылка для скачивания](https://visualstudio.microsoft.com/ru/vs/community/)

* [Гайд по установке ReSharper C++](https://www.youtube.com/watch?v=MJJ2GAPg1jE) - [ссылка для скачивания](https://www.jetbrains.com/resharper-cpp/)
<details><summary><a>Если ReSharper показывает подсказки слишком
мелкого шрифта:</a></summary>
 <br>Заходим в <mark style="background-color: LightBlue">Tools > Options > Environment > Fonts and Colors</mark>
  и меняем шрифт для Statement Completion и Find Results Window, в графе show settings for.</br>
</details>

## Отправка решения <a id='code'/>

Для работы в команде мы используем концепцию github flow. Узнать про 
это можно [здесь](https://www.youtube.com/watch?v=43WLFU2LEMs) и [здесь](https://docs.github.com/ru/get-started/using-github/github-flow). 

![](https://lanziani.com/slides/gitflow/images/gitflow_1.png)

> Если в кратце, то вся работа происходит в сторонних ветках созданных для отдельных задач, после решения задачи создается pool request, который, если все хорошо, получает approve и ветку мерджат в main.
