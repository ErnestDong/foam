---
tags: algorithm, math
---
# P&NP

P 就是能在多项式时间内解决的问题，NP 就是能在多项式时间验证答案(certificate)正确与否的问题。$P \subseteq NP$，是否是真子集有待证明或证伪

判定一个问题 A 是否是 P/NP 问题，可以采用一种多项式时间的 reduction 算法转化为 B，B 如果是 P/NP 问题，那么 A 也是 P/NP 问题

## P 问题与 NP 问题的定义

- 字母表 $\Sigma$：符号的有限集合，如 $\{ 0,1 \}$
- 语言 $L$：$\Sigma$ 上的符号组成的串的集合
  - 语言可以有并交补，也可以有连结，即两个分属不同语言的串连起来
  - 语言的闭包是 $L^*=\{\epsilon\}\bigcup L\bigcup L^2\bigcup\cdots$
  - 可以把问题 Q 定义看作在语言上 $L=\{ x\in \Sigma^*: Q(x)=1 \}$，$\Sigma^*$是所有串构成的语言
- 算法 $A$ 结果为 0 (拒绝)或 1 (接受)，输入

P 问题的定义借助以上概念，形式化为 $P=\{L \subseteq \{ 0,1 \}^*: \exists A, \forall x \in L, A(x)=1 \}$
NP 问题的定义则是 $NP=\{x \in \{ 0,1 \}^*: \exists y, \left\vert y \right\vert =O(\left\vert x \right\vert ^c)\And A(x,y)=1 \}$

## NP 完全问题 NPC

reduction 提供了一种形式方法，证明一个问题在一个多项式时间因子内至少与另一个问题一样难，记作 $L_1\le_pL_2$。
NPC 类问题满足 $(L\in NP)\And(\forall L'\in NP,L'\le_PL)$。如果只满足后一个则称 L 是 NP-hard 的
