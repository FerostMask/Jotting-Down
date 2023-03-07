# 前言

C语言程序从代码到可执行文件（\*.exe）需要经过预编译、编译、汇编和链接这几个步骤。每当源文件（\*.c）或源文件所包含的头文件（\*.h）做出修改后，我们都需要对这些源文件重新执行上述几个步骤，以使修改效果显现在可执行文件中。

> 通常将预编译、编译和汇编这三个步骤统称为编译。

一个项目中通常有多个源文件，如果只修改其中一个源文件，就对所有源文件重新执行编译、链接步骤，就太浪费时间了。因此十分有必要引入Makefile工具：Makefile工具可以根据文件依赖，自动找出那些需要重新编译和链接的源文件，并对它们执行相应的动作。

![编译链接过程](.\编译链接过程.png)

# 开始前的准备

本文章目的在于帮助你理解和掌握Makefile的编写方法和编写技巧，在开始阅读和动手编写Makefile前，你可能需要准备一下环境。

本篇文章的示例运行在wsl2上（Windows Subsystem for Linux 2），我的系统信息如下：

```shell
gee@JiPing_Desktop:~/workspace/test$ lsb_release -a
No LSB modules are available.
Distributor ID: Ubuntu
Description:    Ubuntu 22.04.1 LTS
Release:        22.04
Codename:       jammy
```

可以看到，我使用Ubuntu系统，且系统发行版本是22.04。如果你是Windows系统，则可以在`启用或关闭 Windows 功能`中点击开启`适用于 Linux 的 Windows 子系统`，并在微软商店中下载和安装Ubuntu系统，以获得与我一致的代码编写环境。

如果你在阅读或实践过程中遇到任何问题，欢迎在评论区中留下你的疑问，我们会尽力尝试解答。

# 从代码编译开始

在开始编写Makefile前，我们先写一段简单的代码，并尝试使用编译工具链将代码变为可执行文件。

## 编写简单的代码

**"main.c"**

```c
#include <stdio.h>

int main(void)
{
        printf("Hello from main!\n");
        return 0;
}
```

## 编译得到可执行文件

编辑完文件后，回到终端，使用编译工具链将代码变为可执行文件：

```shell
gee@JiPing_Desktop:~/workspace/example$ vim main.c
gee@JiPing_Desktop:~/workspace/example$ gcc main.c -o main
gee@JiPing_Desktop:~/workspace/example$ ls
main  main.c
gee@JiPing_Desktop:~/workspace/example$ ./main
Hello from main!
```

可以看到，我们顺利的得到了可执行文件，并且执行结果也符合预期。

> 如果你在执行 `gcc main.c -o main` 时遇到问题，很有可能是没有安装 `gcc` 导致的，在终端中输入 `sudo apt-get install build-essential` 以安装所需的编译工具。

上面所执行的几条命令中，`gcc main.c -o main` 这条命令负责调用编译工具链，将源文件 `main.c` 编译、链接为可执行文件 `main`。这里的GCC(GNU Compiler Collection)就是上文中提及的编译工具链，它是预编译、编译、汇编、链接所使用到的各种工具的集合，它们彼此搭配协作，才最终得到我们所需的可执行文件。

![编写简单的代码并得到可执行文件](.\编写简单的代码并得到可执行文件.png)

你可能同时会好奇上面 `gcc` 命令中的 `-o` 的作用，这是用来指定输出文件的命名的，它随后紧跟的参数就是所要指定的命名，在上面的示例中，我们将输出文件命名指定为了 `main`。

# 动手写简单的Makefile

现在我们已经掌握了将代码编译、链接为可执行文件的方法，是时候开始写最简单的Makefile文件了：

## 编写Makefile并执行make

**"Makefile"**

```makefile
main : main.c
        gcc main.c -o main
```

编写好后回到终端，使用 `make` 来执行Makefile：

```shell
gee@JiPing_Desktop:~/workspace/example$ vim Makefile
gee@JiPing_Desktop:~/workspace/example$ make
make: 'main' is up to date.
```

可以看到Makefile给出了它的处理结果 `make: 'main' is up to date.`，意思是 `main` 已经是最新的了，无需执行任何操作。此时我们的 `main.c` 没有做任何修改，也就是说即使重新编译、链接得到一个新的 `main`，它与旧的 `main` 也不会存在任何的不同，所以Makefile没有执行任何的步骤。

尝试修改 `main.c` 再执行 `make`，看看这次的结果会怎样：

**"main.c"**

```c
#include <stdio.h>

int main(void)
{
        printf("Hello from new main!\n"); // <- 多加了一个new
        return 0;
}
```

回到终端执行 `make`：

```shell
gee@JiPing_Desktop:~/workspace/example$ vim main.c
gee@JiPing_Desktop:~/workspace/example$ make
gcc main.c -o main
gee@JiPing_Desktop:~/workspace/example$ ./main
Hello from new main!
```

可以看到，在修改了 `main.c` 后重新执行 `make`，Makefile会自动地执行 `gcc main.c -o main`，以得到新的可执行文件 `main`。从结果来看，代码中的修改确实反应到了可执行文件上。

## Makefile三要素

那么问题就来了，Makefile中的两行语句分别是什么意思呢？拆解来看，两行语句可以分为三部分，分别是目标文件、依赖文件和执行语句：

![简单Makefile语句解析](.\简单Makefile语句解析.png)

> 延申思考：目标文件、依赖文件和执行语句，三者在Makefile中是否缺一不可？尝试修改目标文件命名再执行make，会得到怎样的结果？

上面的例子中，可执行文件 `main` 就是我们想要获得的目标文件，而 `main` 的生成依赖于源文件 `main.c`，所以将 `main.c` 填写在依赖文件的位置。在发现目标文件不存在，或依赖文件有所修改后，Makefile就会执行下方的执行语句，其任务通常是生成目标文件。

## Makefile中的变量和通配符

回看已经写好的Makefile，会发现其中的内容都是有具体指向的：`main`、`main.c`，试想这样一个场景：我们在文件夹中添加了新的源文件 `src2.c`，并将 `main.c` 重命名为 `entry.c`，同时在 `entry.c` 中调用 `src2.c` 中定义的函数，这时再执行 `make` 会得到怎样的结果？



# 参考链接

- [如何在 Ubuntu 20.04 上安装 GCC(build-essential)](https://developer.aliyun.com/article/766146)

- [linux - What's the meaning of gcc '-c' and gcc '-o'?](https://stackoverflow.com/questions/43164707/whats-the-meaning-of-gcc-c-and-gcc-o)