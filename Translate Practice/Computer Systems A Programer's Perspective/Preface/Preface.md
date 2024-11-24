# Preface

This book (known as CS:APP) is for computer scientists, computer engineers, and others who want to be able to write better programs by learning what is going on "under the hood" of a computer system.

本书（简称 CS:APP）的目标读者是计算机科学家、计算机工程师，以及任何想要通过学习计算机系统背后运行原理以写出更好程序的人。

> 本书（简称 CS:APP）的主要读者是计算机科学家、计算机工程师，以及那些想通过学习计算机系统的内在运作而能够写出更好程序的人。

Our aim is to explain the enduring concepts underlying all computer systems, and to show you the concrete ways that these ideas affect the correctness, performance, and utility of your application programs. Many systems books are written from a builder's perspective, describing how to implement the hardware or the systems software, including the operating system, compiler, and network interface. This book is written from a programmer's perspective, describing how application programmers can use their knowledge of a system to write better programs. Of course, learning what a system is supposed to do provides a good first step in learning how to build one, so this book also serves as a valuable introduction to those who go on to implement systems hardware and software. Most systems books also tend to focus on just one aspect of the system, for example, the hardware architecture, the operating system, the compiler, or the network. This book spans all of these aspects, with the unifying theme of a programmer's perspective.

我们的目标是解释计算机系统背后的长久概念，以及向你展示这些概念具体如何影响应用程序的正确性、性能和实用性的。其他的系统类书籍都是以构建者的角度来写的，描述如何实现硬件或系统软件，包括操作系统、编译器和网络接口。而本书是以程序员的角度来写的，讲述应用程序员如何通过他们对系统的了解来写出更好的程序。当然，认识一个计算机系统应该做些什么，是学习如何构建一个计算机系统很好出发点，所以对于那些希望进一步实现系统软硬件的人来说，本书也是一本很有价值的介绍性读物。绝大多数系统书籍都倾向聚焦于计算机系统的某个方面，例如：硬件架构、操作系统、编译器或网络。本书将以程序员的视角通过统一的风格来讲述上述所有方面的内容。

> 我们的目的是解释所有计算机系统的本质概念，并向你展示这些概念是如何实实在在地影响应用程序的正确性、性能和实用性的。而本书是从程序员的角度来写的，讲述应用程序员如何能够利用系统知识来编写出更好的程序。当然，学习一个计算机系统应该做些什么，是学习如何构建一个计算机系统的很好的出发点，所以，对于希望继续学习系统软硬件实现的人来说，本书也是一本很有价值的介绍性读物。大多数系统书籍还倾向于重点关注系统的某一个方面，比如：硬件架构、操作系统、编译器或者网络。本书则以程序员的视角统一覆盖了上述所有方面的内容。

If you study and learn the concepts in this book, you will be on your way to becoming the rare power programmer who knows how things work and how to fix them when they break. You will be able to write programs that make better use of the capabilities provided by the operating system and systems software, that operate correctly across a wide range of operating conditions and run-time parameters, that run faster, and that avoid the flaws that make programs vulnerable to cyberattack. You will be prepared to delve deeper into advanced topics such as compilers, computer architecture, operating systems, embedded systems, networking, and cybersecurity.

当你真正开始了解本书中的概念，你将逐渐成为罕见的大神，知晓程序背后的运行原理，并在错误发生时懂得如何修复它们。你所编写的代码能更大程度的发挥操作系统和系统软件所提供的能力，使你的程序能在庞杂的运行环境下正确工作，使其运行得更快，且避免程序出现容易受到网络攻击得缺陷。同时，你需要做好深入探究的准备，研究像编译器、计算机体系架构、操作系统、嵌入式系统、网络和网络安全这样的高级话题。

> 如果你研究和领会了这本书里的概念，你将开始成为极少数的"牛人"，这些"牛人"知道事情是如何运作的，也知道当事情出现故障时如何修复。你写的程序将能够更好地利用操作系统和系统软件提供的功能，对各种操作条件和运行时参数都能正确操作，运行起来更快，并能避免出现使程序容易受到网络攻击的缺陷。同时，你也要做好更深入探究的准备，研究像编译器、计算机体系结构、操作系统、嵌入式系统、网络互联和网络安全这样的高级题目。

## Assumptions about the Reader's Background

This book focuses on systems that execute x86-64 machine code. x86-64 is the latest in an evolutionary path followed by Intel and its competitors that started with the 8086 microprocessor in 1978. Due to the naming conventions used by Intel for its microprocessor line, this class of microprocessors is  referred to colloquially as "x86." As semiconductor technology has evolved to allow more transistors to be integrated onto a single chip, these processors have progressed greatly in their computing power and their memory capacity. As part of this progression, they have gone from operating on 16-bit words, to 32-bit words with the introduction of IA32 processors, and most recently to 64-bit words with x86-64.

这本书聚焦于执行 x86-64 机器代码的系统。x86-64 是由 Intel 及其竞争对手最新研发的架构，其成果最早可以追溯到1978年的8086微处理器。根据 Intel 对其微处理器产品线的命名习惯，这一类微处理器通常俗称为“x86”。随着半导体技术的逐步发展，目前单个芯片上能够集成的晶体管变得越来越多，随之带来的就是这些处理器在计算性能和存储容量上的巨大提升。作为这一演变进程的一部分，处理器经历了从最开始的处理 16 位字，逐步转变到引入 32 位字处理的 IA32，再到最近处理 64 位字的 x86-64。

> 本书的重点是执行 x86-64 机器代码的系统。对英特尔及其竞争对手而言，x86-64 是他们自 1978 年起，以8086 微处理器为代表，不断进化的最新成果。按照英特尔微处理器产品线的命名规则，这类微处理器俗称为 “x86”。随着半导体技术的演进，单芯片上集成了更多的晶体管，这些处理器的计算能力和内存容量有了很大的增长。在这个过程中，它们从处理 16 位字，发展到引人 IA32 处理器处理 32 位字，再到最近的 x86-64 处理 64 位字。

We consider how these machines execute C programs on Linux. Linux is one of a number of operating systems having their heritage in the Unix operating system developed originally by Bell Laboratories. Other members of this class of operating systems include Solaris, FreeBSD, and MacOS X. In recent years, these operating systems have maintained a high level of compatibility through the efforts of the Posix and Standard Unix Specification standardization efforts. Thus, the material in this book applies almost directly to these "Unix-like" operating systems.

我们将探究这些机器如何在 Linux 上运行 C 程序。Linux 是众多类 Unix 系统中的一员，这类系统的设计继承自最早由贝尔实验室研发的 Unix 系统。其它同类的操作系统有 Solaris、FreeBSD 以及 MacOS X 等等。通过 Posix 和标准 Unix 规范的标准化努力，最近几年这些类 Unix 操作系统保持了高度兼容性。因此，这本书的绝大多数内容直接适用这些类 Unix 操作系统。

> 我们考虑的是这些机器如何在 Linux 操作系统上运行 C 语言程序。Linux 是众多继承自最初由贝尔实验室开发的 Unix 的操作系统中的一种。这类操作系统的其他成员包括 Solaris、FreeBSD 和 Mac OSX。近年来，由于 Posix 和标准 Unix 规范的标准化努力，这些操作系统保持了高度兼容性。因此，本书内容几乎直接适用于这些“类 Unix”操作系统。