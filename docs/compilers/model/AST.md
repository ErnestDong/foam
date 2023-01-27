---
tags: compilers
---

# AST

抽象语法树 (Abstract Syntax Tree)是源代码语法结构的一种抽象表示。它以树状的形式表现编程语言的语法结构，树上的每个节点都表示源代码中的一种结构。

![示例](https://upload.wikimedia.org/wikipedia/commons/thumb/c/c7/Abstract_syntax_tree_for_Euclidean_algorithm.svg/400px-Abstract_syntax_tree_for_Euclidean_algorithm.svg.png)

抽象语法树实际上只是一个解析树(parse tree)的一个精简版本。在编译器设计的语境中，"AST" 和 "语法树"(syntax tree)是可以互换的。精简之处在于：

- AST 不含有语法细节，比如冒号、括号、分号
- AST 会压缩单继承节点
- 操作符会变成内部节点，不再会以叶子节点出现在树的末端。
