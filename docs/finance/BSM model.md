---
tags: 衍生品
---
# BSM 模型

## [[随机过程]]

## 股价的分布

股价服从对数正态分布 即$\ln S_T/S_0$ 服从$N((\mu-\sigma^2/2)T,\sigma^2T$

$mu$ 是每年的期望收益率，S 的期望为 $S_0e^{\mu T}$ 方差为 $S_0^2e^{2\mu T}(e^{\sigma^{2T}}-1)$

T 时间内的收益率服从 $N(\mu-\sigma^2/2,\sigma^2/T)$

expected value of Stock 是 $S_0e^{\mu T}$ ，
$\ln E(S_T/S_0) = \mu$

expected return on Stock 是 $\mu-\sigma^2/2$，$E(\ln (S_T/S_0) ) =\mu - \sigma^2/2$ 因为 $\Delta t$ 内的价格累计不是线性的 经济学解释是 $\mu$ 是收益率的算术平均值，微小时间段上价格的变动。 总区间的收益是几何平均的 $\mu-\sigma^2/2$

## 股价的波动率

$\tau$ 年标准差 s 估计的波动率为$\hat{s}/\sqrt{\tau}$

此外也会用 ARCH/GARCH/EWMA 模型估计波动率

## 假设

衍生品当成荣誉证券，可以被基础证券复制

- Stock price follows brownie
- Constant volatility
- Short selling of stocks are allowed
- No transaction cost or taxes, and stocks are perfectly divisible
- No dividends paid during the life of derivative
- No riskless arbitrage opportunity
- Stocks are continuously traded
- Constant riskless interest rate

## 动态复制

买入 $\Delta$ 股票和期权使组合无风险

股价 S 服从几何布朗运动，衍生品 G 服从，

对组合$\Pi=\Delta S -G$ 求导，利用公式

$d\Pi=\Delta dS - dG=$ 没有随机性的某个值，求得$\Delta$;，瞬时是无风险的

无套利情况下 $d\Pi=-G_tdt-\sigma^2S^2G_{SS}dt/2=r\Pi dt$

又$\Pi=\Delta S+G$，可以得到

$rG=G_t+rG_SS+\frac{1}{2}\sigma^2S^2G_{SS}$

用[[衍生品#希腊值]]表示为

$r\Pi=\Theta+rS\Delta+\frac{1}{2}\sigma^2S^2\Gamma$

## 欧式看涨看跌期权的定价

已知欧式期权满足$G=\max{S_T-K}$ ，代入可以得到针对欧式期权的 BS 公式：

$$c=S_0N(d_1)-Ke^{-rT}N(d_2)$$

$$p=Ke^{-rT}N(-d_2)-S_0N(-d_1)$$

where $d_1=\frac{\ln(S_0/K)+(r+\sigma^2/2)T}{\sigma\sqrt{T}}$ $d_2=d_1-\sigma\sqrt{T}$

可以看出衍生品相当于买了 $N(d_{1})$ 一份股票和 $N(d_{2})$ 的 $K$，这也说明了衍生品相对于“荣誉证券”

无股息下的美式期权 call option 等于欧式期权价格，但是 put option 没有解析式

$N(d_{2})$是风险中性世界里面执行期权的概率

<https://zhuanlan.zhihu.com/p/38293827>
<https://www.zhihu.com/column/p/38294971>
