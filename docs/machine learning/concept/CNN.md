---
tags: DeepLearning
---
# CNN

## 卷积

![CNN](https://raw.githubusercontent.com/ErnestDong/ml-in-erm/main/lib/cnn.jpeg)

$$(f*g)(t)=\int_{\mathbb{R}^n}f(\tau)g(t-\tau)\mathrm{d}\tau$$

## 池化

增强稳健性

## 代码

```python
class CNN(nn.Module):
    def __init__(self) -> None:
        super(CNN, self).__init__()
        self.conv = nn.Sequential(
            nn.Conv1d(48, 20, 3,padding=2, stride=1),
            # 输入特征48个1维指标，20个卷积核，每个核大小为3，左右各补两个，每次滑动一格
            nn.Tanh(),
            nn.AvgPool1d(3),
            # 池化采用取平均值，卷积扫出来是三个（2+1+2=5，5-2=3），20层
        )
        self.fc = nn.Sequential(
            nn.Linear(20, 7),
            # 20 层转化为 7 维
            nn.ReLU(),
            nn.Softmax(dim=1),
        )

    def forward(self, x):
        out = self.conv(x)
        out = out.view(out.size(0), -1)
        out = self.fc(out)
        return out
```

## 扩展

1. AlexNet：CNN 开山之作，重点是防止过拟合
2. ResNet：只有训练得好才走网络，否则不走。拟合残差函数 $h(x)-x$
