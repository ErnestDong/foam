---
tags: cli
---
# 什么是 cl-lib

CL 包为 elisp 提供了一系列的 Common Lisp 函数和控制结构，它添加了足够多的功能，使 elisp 编程变得更加方便。但是它也忽略了 Common Lisp 中许多其他的特性，这是出于两方面考虑：某些特性过于复杂，比如 CLOS；某些特性无法在不修改 elisp 解释器的情况下加入 elisp 中，比如大小写不敏感，多值返回等。

cl-lib 之前的名字是 cl，随着新的命名约定的出现，它变成了 cl-lib。如果你使用了一些比较老的包的话，在包加载过程中可能会看到这样的消息：

> Package cl is deprecated

这是由于老包没有使用较新的 cl-lib。cl-lib 中所有的公开名字都使用 cl- 来作为名字前缀。

# cl-lib 的组成

cl-lib 有四个主要的文件：

-   **cl-lib.el** ，它包含了基础的函数，以及关于整个包的信息

-   **cl-extra.el** ，它包含了一些更大更复杂的函数，它被单独分离出来是为了在使用像是 `cl-incf` 之类的简单函数时不需要关注其他东西

-   **cl-seq.el** ，它包含了操作序列的高级函数

-   **cl-macs.el** ，它包含了一些宏，提供了语法扩展

**cl-lib.el** 包含了所有必要的 `autoload` 指令。你只需要 `(require 'cl-lib)` ，在需要使用其他文件内的东西时 `autoload` 会处理好的。

本文主要介绍一些简单的函数和宏。所谓二八定律嘛，一些比较复杂和高级的特性只有在被用到时才会有用，但这种机会对我来说应该没有几次。

# 一些常用的控制结构

以下内容大概列举了几个常用的宏，我会用一些代码来作为示例，并使用实现相同功能的 elisp 代码来进行对比，以体现其优越性。

`cl-loop` 我会放在这一节的最后来介绍，它已经可以称得上是一种 dsl 了。

## cl-incf/cl-decf

这里的 inc 和 dec 取 **increase** 和 **decrease** 的前几个字母，尾字母 `f` 指的是 `formal` 的意思，就像是 `setf` 的 `f` 一样，它们和 `setf` 一样可以接受 `formal` 而不仅仅是变量来作为第一个参数，关于什么是 `formal` 我会在下面给出一些例子。

它们接受一个参数，以及一个可选参数，如果只使用一个参数的话， `cl-incf` 会将变量增加 1，并返回增加后的值； `cl-decf` 则会减去 1，并返回减去后的值。它们会对变量进行修改，用修改过的值来作为变量的新值。

```emacs-lisp
(setq x 1)
(cl-incf x)
=> 2
x
=> 2
(cl-decf x)
=> 1
x
=> 1
(cl-incf x 114513)
=> 114514
(cl-decf x 114495)
=> 19
```

相比于下面这种写法，使用 `cl-incf` 可以少打几个字：

```emacs-lisp
(setq x 1)
(progn (setq x (+ x 1)) x)
;; the better way
(cl-incf x 1)
```

通过下面的代码可以说明 `formal` 是什么意思：

```emacs-lisp
(setq x (list 1 2 3))
(cl-incf (car x))
=> 2
x
=> (2 2 3)
(setq x (vectir 1 2 3))
(cl-incf (aref x 0) 2)
=> 3
x
=> [3 2 3]
```

完整的 `formal` 支持可见于 gnu elisp 文档的 general-variable 一节。这种用法我见的不多。

## cl-psetq

这里的 `p` 是 **parallel** 的意思， `setq` 就是符号设置，psetq 表示平行赋值之意，这是相对于 `setq` 的顺序赋值而言的。使用它可以方便地交换两个变量的值，而不需要中间变量：

```emacs-lisp
(setq x 1)
(setq y 2)
(cl-psetq x y
          y x)
(list x y) => (2 1)
(setq x y
      y x)
(list x y) => (1 1)
```

从上面的代码中我们可以清楚地看出“平行”与“顺序”的区别。下面是一个 `fib` 计算例子：

```emacs-lisp
(let ((i 0)
      (x 0)
      (y 1))
  (while (< i 10)
    (cl-psetq x y y (+ x y))
    (cl-incf i))
  x)
```

`cl-psetq` 也有一个 `formal` 的版本，叫做 `cl-psetf` ，这里就不详述了。

## cl-flet

`f` 就是 **function** 的意思， `let` 是用来绑定值与符号的 value cell 的， `flet` 则是用来绑定函数与符号 function cell 的。它的定义部分的格式必须是 `(name arglist body ...)` 而不能是其他形式。如果要将通过它定义的函数传递给其他调用时，需要对它使用 `#'` （即 `function` ）而不能用 `'` （ `quote` ）。定义的函数使用静态绑定，因为 Common Lisp 就是静态作用域的语言。

```emacs-lisp
(cl-flet ((a (x) (+ x 1))
          (b (x y) (+ x y)))
  (+ (a 1) (b 2 3)))
=> 7
```

就像 `let` 一样，定义的名字在定义时还是不可见的，以下代码是无法正常工作的：

```emacs-lisp
(cl-flet ((a (ls)
             (if (null ls)
                 0
               (+ 1 (a (cdr ls))))))
  (mapcar #'a '((1 2 3) (2 3 4) (3 4 5))))
=> Debugger entered--Lisp error: (void-function a)
```

这可以通过使用 `cl-label` 解决，它就像是 `letrec` 一样，不过是针对函数的版本。

```emacs-lisp
(cl-labels ((a (ls)
               (if (null ls)
                   0
                 (+ 1 (a (cdr ls))))))
  (mapcar #'a '((1 2 3) (2 3 4) (3 4 5))))
=> (3 3 3)
```

## cl-case

Scheme 中有个类似的结构叫做 `case` ，C 语言中的 Switch 语句也与之类似。它接受一个表达式，对其求值并将得到的值与分支语句中的值比对，相同则进入相应的分支。如果没有分支与之匹配，整个表达式返回 =nil=。

分支的形式是 `(keylist body-forms ...)` ， `keylist` 可以是一个键值，也可以是一个由键值构成的表， `cl-case` 中所有的键值必须是互不相同的。如果键值是 `t` 的话， `cl-case` 会无条件匹配它，这样的语句一般放在表达式的末尾。

```emacs-lisp
(defun swt (x)
  (cl-case x
   (1 (+ x 1))
   (2 (+ x 2))
   ((3 4 5) (+ x 3))
   (t (+ x 100))))

(swt 1) => 2
(swt 2) => 4
(swt 3) => 6
(swt 4) => 7
(swt 5) => 8
(swt 6) => 106
......
```

平时貌似 `cond` 用的比较多，连 `pcase` 都没用什么，更不用说 `cl-case` 了。

## Blocks

文章的开头我提到过，写 `while` 表达式时由于没有局部跳转关键字而不得不手写 `catch/throw` 块。cl-lib 的块扩展解决了这个问题，它提供了静态作用域的非局部退出的机制。与之相关的宏有三个： `cl-block` ， `cl-return-from` 以及 `cl-return` 。通过 `cl-block` 可以建立一个有名字的块，在块内可以通过 `cl-return` 进行跳转，从而直接退出块的执行。

`cl-block` 的使用形式是 `(cl-block name forms ...)` ，如果 `forms` 中没有含 return 的形式的话，它的效果就和 `progn` 是一样的，以最后一个 `form` 的值返回。但是如果存在 `cl-return` 或 `cl-return-from` 的话，它会直接从 `cl-block` 中返回，并以=cl-return= 或 `cl-return-from` 的参数作为返回值。

`block` 看起来和 `catch/throw` 很相似，但它们的机制并不相同。 `block` 的名字是未被求值的符号，不像 `catch` 的名字，它是在运行时被求值得到的 tag。而且 `block` 总是静态作用域的。对于动态作用域的 `catch` ，在 `catch` body 内调用的函数也可以使用 `throw` 来向这个 catch 抛出。但是 `cl-block` 中是不能这样做的， `cl-return-from` 必须出现在 `cl-block` 的 `forms` 里面，不能超出 `block` 的范围。这是它静态性的体现。

在 Common Lisp 中， `defun` 和 `defmacro` 会使用隐含的 `block` 来包住函数体，这样就可以在函数体中直接使用 `cl-return` 了，但是 elisp 中不会这样做。可以使用 `cl-defun` 和 `cl-defmacro` 来创建隐含的 `block` 。隐含 `block` 的还有 `cl-loop` ， `cl-do` ， `cl-dolist` ， `cl-dotimes` 等等。

`cl-return-from` 接受一个名字来作为要返回的块的位置，以及一个可选的返回值来作为 `block` 的值，如果没有返回值的话， `block` 的值为 nil。 `cl-return` 等价于 `cl-return-from nil result)` ，它一般用于隐含了 `block` 的结构中。

`cl-blcok` 所接受的所谓的未求值符号就是裸符号，就像这样：

```emacs-lisp
(cl-block wocao
(+ 1 2)
(setq x 1)
(while (< x 10)
  (cl-incf x)
  (when (= x 5) (cl-return-from wocao x))))
```

上面的 wocao 就是 cl-block 的名字。使用 nil 作为块名字的话就可以直接使用 `cl-return` 了。

## cl-do

Scheme 中有 `do` 这个关键字， `cl-do` 的用法与它很相似，不过与其说是相似，倒不如说 Scheme 中的 `do` 就是从 Common Lisp 里面抄过去的。

`cl-do` 的语法如下：

```emacs-lisp
(cl-do (spec ...) (end-test [result ...]) forms ...)
spec := (var [init [step]])
```

这个控制结构与 C 语言中的 for 循环很相似，for 循环的语法是 `for(初始化; 跳出条件; 更新)` ， `spec` 也是如此。 `spec` 包含 `cl-do` 内变量的名字，初始化和每次循环对变量的更新三部分组成。其中只有变量名是必须的，变量的赋值和更新可以在 form 中完成。不过如果没有初值的话，变量的默认值就是 nil 了。

`end-test` 对应 for 语句中的跳出条件，当 end-test 为真时循环结束，如果 `[result ...]` 不空的话，它就作为 `cl-do` 表达式的值。

`forms` 就是循环过程中执行的代码，对应于 for 循环中的循环体。在循环过程中也可以使用 `cl-return` 直接跳出，因为 `cl-do` 有隐含的 `block` 。

初始化过程中变量是不能相互引用的，因为它们还没有被绑定，就像 `let` 一样，不过 cl-lib 也提供了一个叫做 `cl-do*` 的宏，和 `let*` 作用效果相似。

```emacs-lisp
(cl-do
((a '(1 2 3) (cdr a))
 (b '(4 5 6) (cdr b))
 (c '(7 8 9) (cdr c))
 (d))
((and (null a) (null b) (null c)) d)
(setq d (cons (list (car a) (car b) (car c)) d)))
=> ((3 6 9) (2 5 8) (1 4 7))
```

## cl-loop

第一次使用这个宏时，我被震惊到了，这简直就是实现了一个小语言一样。cl-lib 文档上其他的宏都是简单的描述一下就完了，而它的文档下还有子文档。

cl-loop 的语法大致是这样的：

`(cl-loop name-clause var-clause ... action-clause ...)`

其中的 **name clause** 是可选项，可以赋给 `cl-loop` 的隐含 block 名字，一般来说就来说这个名字是 nil。 **var clause** 指定的是在循环过程中需要绑定的变量。 **action clause** 是在循环过程中需要完成的工作，比如计算，收集或返回值。

上面的描述是很宽泛的，因为 cl-loop 中可选的 clause 实在是太多了。下面描述几种比较常用的 clause。实际上，clause 里面还可以继续细分。如果按照官方文档的顺序来讲的话，那我应该从 for 语句开始。由于 `cl-loop` 实在是有点复杂，我还是再写一篇文章来专门介绍它的用法吧，这里只对几种常用语句进行介绍。

### 简单的 for 循环

```emacs-lisp
for var from exp1 to exp2 by exp3
```

从字面意思上这个语句是很好理解的，从 exp1 到 exp2，步长是 exp3：

```emacs-lisp
(cl-loop
 for x from 0 to 10 by 2
 sum x)
=> 30 ; 0 + 2 + 4 + 6 + 8 + 10
```

循环可以从小到大，也可以从大到小，还可以限制是小于还是小于等于：

```emacs-lisp
(cl-loop
 for x from 10 downto 1
 collect x)
=>
(10 9 8 7 6 5 4 3 2 1)

(cl-loop
 for x from 10 above 1
 collect x)
=>
(10 9 8 7 6 5 4 3 2)

(cl-loop
 for x from 0 below 10
 collect x)
=>
(0 1 2 3 4 5 6 7 8 9)
```

### 类 foreach 遍历

```emacs-lisp
for var in list by function
```

其中的 `by function` 部分是可以省略的，它的默认值是 `cdr` ，表示顺着表完成遍历，通过 `by` 语句可以改变这个默认行为。

```emacs-lisp
(cl-loop
 for x in '(1 2 () 3)
 collect (if (numberp x) x 0))
=> (1 2 0 3)
```

还有一种 `in-ref` 的用法，var 在这里就是类似于 C++ 中的引用，对 var 进行的修改操作会反应到表上。不过需要使用可以操作 `formal` 的 cl 函数，比如 `setf` `incf` 等。

```emacs-lisp
(setq x (list 2 3 4 5 6 7))
(cl-loop
for a in-ref x by 'cddr
do
(setf a (+ a 1)))
x => (3 3 5 5 7 7)
```

还有一个 `on` 关键字，这时 x 的值就是剩余的表而不是每一个表中的元素：

```emacs-lisp
(cl-loop for x on '(1 2 3 4) collect x)
        ⇒ ((1 2 3 4) (2 3 4) (3 4) (4))
```

### 一些迭代语句

`repeat integer` ，表示重复 n 次：

```emacs-lisp
(cl-loop repeat 10 sum 1) => 10
```

`while condition` ，当 condition 为 nil 时循环终止。 `until condition` 与其相反，当条件为真时循环终止。

`always` 和 `never` 表示全为真或全为假，如果有不满足的项，cl-loop 会停止并返回 nil，就像这样：

```emacs-lisp
  (cl-loop
   for x to 10
   always (> x -1))
  => t

  (cl-loop
   for x in '(1 3 4 5 7 9)
   always (cl-oddp x))
  => nil
```

`thereis condition` 当条件不为 nil 时就退出循环，表示“存在”或“找到了”的意思。

### 积累器

上面我们已经使用过一些积累器了，那就是 `sum` ， `collect` 。它们的作用是把一些值收集起来，作为 `cl-loop` 表达式的值。如果没有中途的中断， `cl-loop` 会使用收集得到的值来作为表达式的值。这里列举一下几个常用的积累器。

-   `collect` 表示将值收入结果中，得到的表的顺序与迭代顺序一致

-   `append` 表示将表并入结果中

-   `sum` 表示将数字加入结果中

-   `maximize` 表示使用最大值作为结果值

-   `minimize` 表示使用最小值作为结果值

这里对上面没有使用过的积累器做个介绍：

```emacs-lisp
(cl-loop
for x to 100
maximize x into a
minimize x into b
finally return (list a b))
=> (100 0)

(cl-loop
 for x on '(1 2 3)
 append x)
=> (1 2 3 2 3 3)
```

上面用到了另一种语句，即 `finally return` ，如果没有其他的显式 return 的话，就使用它的值作为 `cl-loop` 的返回值。

上面介绍的只是 `cl-loop` 功能的一小部分，更多内容请见于官方文档。

# 一些数学函数

说来也怪，elisp 没有提供一些非常简单基础的数学函数，比如判断正负，判断奇偶之类的。 `cl-lib` 中提供了这些函数：

-   `cl-plusp` 判断数字是否为正数

-   `cl-minusp` 判断数字是否为负数

-   `cl-oddp` 判断数字是否为奇数

-   `cl-evenp` 判断数字是否为偶数

-   `cl-digit-char-p` 判断字符是否为合法的数字符号

上面的函数都很简单，但 `cl-digit-char-p` 需要提一下，它在默认情况下仅对十进制数进行判断，但是它还可以接受一个 `radix` 参数来判断其他进制的数。=radix= 的范围是 2 - 16。

## 数值函数

一些数学函数，诸如最大公因数和最小公倍数的求取在 elisp 中是没有的，cl-lib 提供了一些数值函数：

-   `cl-gcd` ，求数字中的最大公因数，就像这样： `(cl-gcd 1 3 6 60)`

-   `cl-lcm` ，求数字中的最小公倍数，就像这样： `(cl-lcm 100 200 250)`

-   `cl-isqrt` ，它接受一个整数，返回小于它平方根的最大整数， `(cl-isqrt 99)` 得到 9

接下来是一系列取整函数，即上取整，下取整，截断，取整等等。这些函数在 elisp 中也没有。

-   `cl-floor` ，即下取整。接受一个数字，返回由整数和小数组成的表。例如： `(cl-floor 1.6) => (1 0.6)` ， `(cl-floor -1.2) => (-2 0.8)`

-   `cl-ceiling` ，即上取整，得到由整数和小数组成的表。 `(cl-ceiling 1.7) => (2 -0.3)` ， `(cl-ceiling -1.3) => (-1 -0.3)`

-   `cl-truncate` ，即趋零截断， `(cl-truncate 1.5) => (1 0.5)` ， `(cl-truncate -1.6) => (-1 -0.6)` 。elisp 中也有 `truncate` 函数，但它只返回整数部分

-   `cl-round` ，即四舍五入， `(cl-round 1.5) => (2 -0.5)` ， `(cl-round 1.4) => (1 0.4)` ， `(cl-round -1.6) => (-2 0.4)` ， `(cl-round -1.4) => (-1 0.4)`

其实，上面的四个函数还可以接受一个参数作为 `divisor` ，有点麻烦，这里就不多讲了。

`cl-parse-integer` 可以将字符串解析为整数，就像这样：

```emacs-lisp
(cl-parse-integer "123") => 123
(cl-parse-integer "123" :radix 11) => 146
```

elisp 有一个叫做 `string-to-number` 的函数，功能与之相似，但提供的选项没有它多。

## 随机函数

elisp 中已经有了一个随机函数，叫做 `random` 。据文档所说，cl-random 的实现采用了 [addictive-congruential](https://en.wikipedia.org/wiki/ACORN_(PRNG)) 算法，可以产生比许多操作系统提供的生成器更好的随机数。

`cl-random` 接受一个数字作为随机数的范围，并返回在该范围内的非负数字，如果这个数字是整数，那么随机数也是整数，如果是浮点数那么随机数也是浮点数。

它还接受一个可选参数 `state` ，它应该是一个 `random-state` 对象。 `cl-random` 会修改这个对象的状态（它用来记录随机数的信息，以得到下一个随机数）。如果 `state` 参数被忽略了， `cl-random` 会使用内部的 `cl--random-state` ，它是默认的 `random-state` 对象。

由于 `cl--random-state` 被所有的 elisp 程序共用，要想得到两个相同的随机数序列的话，仅仅使用 `cl-random` 是不可能的，这里可以使用 `cl-make-random-state` 来复制 `state` ：

```emacs-lisp
(setq ss1 (cl-make-random-state t))
(setq ss2 (cl-make-random-state ss1))
(cl-random 100 ss1) => 78
(cl-random 100 ss2) => 78
```

使用相同的 `state object` 就会产生相同的随机值。

如果没有参数的话， `cl-make-random-state` 会复制 `cl--random-state` 并返回复制的对象，如果参数是一个 `state object` 的话，它会复制这个对象并返回。如果参数是 `t` ，这个函数会以时间和日期作为种子返回一个新的对象。 `state` 参数也可以是一个整数，函数会以整数作为种子来产生新的对象。

`state object` 是一个可打印的对象，也就是说将它保存到文件中的话还可以再次读取，并再次产生和上次相同的随机数序列。这样对于某些工作是很方便的。
