---
tags: math
---

# SVD 分解

奇异解分解，本质就是将行空间的一组正交基变换成列
空间里的一组正交基。

$A$的行空间正交基为$\{u_1,u_2,\cdots,u_m\}$，列空间正交基为$\{v_1,v_2,\cdots,v_n\}$，则$A$的奇异值分解为：

$$
A=U\Sigma V^T
$$

其中$\Sigma=\operatorname{diag} \sigma_i$，$\sigma_i$为$A$的奇异值(伸缩因子)

同时找$U$和$V$不好找，但是有

$$
A^TA=V\Sigma^T\Sigma V^T=V\Sigma^2V^T\\
AA^T=U\Sigma^T\Sigma U^T=U\Sigma^2U^T
$$

对比$A^TA=Q\Lambda Q^T$，因此可以根据[[特征空间]]得到$U$和$V$。
