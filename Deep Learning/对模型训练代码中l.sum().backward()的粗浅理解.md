在**动手学深度学习 3.2 线性回归的从零开始实现**中有这样的代码：

```python
import torch
import random
import numpy as np

true_w = torch.tensor([2, -3.4])
true_b = 4.2

# 生成样本和标签
def synthetic_data(w, b, num_examples):
	X = torch.normal(0, 1, (num_examples, len(w)))
	y = torch.matmul(X, w) + b
	y += torch.normal(0, 0.01, y.shape)
	return X, y.reshape((-1, 1))

features, labels = synthetic_data(true_w, true_b, 1000)

def data_iter(batch_size, features, labels):
	num_examples = len(features) # 获取样本数量
	indices = list(range(num_examples)) # 生成数列，数字指向样本
	# 打乱样本读取顺序
	random.shuffle(indices)
	for i in range(0, num_examples, batch_size):
		batch_indices = torch.tensor(indices[i: min(i+batch_size, num_examples)])
		yield features[batch_indices], labels[batch_indices]

# 初始化权重和偏置
w = torch.normal(0, 0.01, size=(2,1), requires_grad=True)
b = torch.zeros(1, requires_grad=True)

# 定义模型
def linreg(X, w, b):
	return torch.matmul(X, w) + b

# 定义损失函数
def squred_loss(y_hat, y):
	return (y_hat - y.reshape(y_hat.shape)) ** 2 / 2

# 定义优化算法
def sgd(params, lr, batch_size):
	with torch.no_grad():
		for param in params:
			param -= lr * param.grad / batch_size # 多个样本的梯度取平均值，不至于一次迈出多个梯度
			param.grad.zero_() # 清空梯度

# 训练
lr = 0.03
num_epochs = 3 # 迭代次数
batch_size = 10
net = linreg
loss = squred_loss

# 训练模型
for epoch in range(num_epochs):
	for X, y in data_iter(batch_size, features, labels):
		l = loss(net(X, w, b), y) # 计算损失函数
		l.sum().backward() # 计算各个参数的梯度
		sgd([w, b], lr, batch_size) # 更新参数
```

之前一直想不明白训练模型时计算反向传播为什么要写成`l.sum().backward()`，现在重看之前的篇章，终于看明白了。

模型训练过程的数学表达如下：
$$
(\mathbf{w},b) \leftarrow (\mathbf{w},b) - \frac{\eta}{|\mathcal{B}|} \sum_{i \in \mathcal{B}} \partial_{(\mathbf{w},b)} l^{(i)}(\mathbf{w},b).
$$

>  很好理解，损失函数`loss`用于量化目标的实际值与真实值的差异，差异越小，模型越精准。如何更新权重w和偏置b使得损失函数递减就是模型训练要解决的问题，为此可以求损失函数关于权重w和偏置b的偏导数（即当权重w和偏置b为某一值时损失函数变化率的最佳近似，或者更通俗的讲，当权重w和偏置b向前迈出极小的一步时（+0.000001），损失函数的值会如何变化（升高或降低多少）），然后在损失函数递减的方向上更新权重和偏置（向前迈步损失升高就后退，反之前进）。

也可以写作：
$$
\begin{aligned} \mathbf{w} &\leftarrow \mathbf{w} -   \frac{\eta}{|\mathcal{B}|} \sum_{i \in \mathcal{B}} \partial_{\mathbf{w}} l^{(i)}(\mathbf{w}, b) = \mathbf{w} - \frac{\eta}{|\mathcal{B}|} \sum_{i \in \mathcal{B}} \mathbf{x}^{(i)} \left(\mathbf{w}^\top \mathbf{x}^{(i)} + b - y^{(i)}\right),\\ b &\leftarrow b -  \frac{\eta}{|\mathcal{B}|} \sum_{i \in \mathcal{B}} \partial_b l^{(i)}(\mathbf{w}, b)  = b - \frac{\eta}{|\mathcal{B}|} \sum_{i \in \mathcal{B}} \left(\mathbf{w}^\top \mathbf{x}^{(i)} + b - y^{(i)}\right). \end{aligned}
$$

`l.sum()`其实就对应着公式中的：
$$
z \leftarrow \sum_{i \in \mathcal{B}} l^{(i)}(\mathbf{w},b)
$$
接下来用z表示`l.sum()`，写成这样方便看懂如何求导：
$$
z \leftarrow l^{(1)}(\mathbf{w},b) +l^{(2)}(\mathbf{w},b) + \dots + l^{(\mathcal{B})}(\mathbf{w},b)
$$
这时对z求关于权重w和偏置b的偏导数，也就是`l.sum().backward()`：
$$
\partial_{(\mathbf{w},b)}z = \partial_{(\mathbf{w},b)}(l^{(1)}(\mathbf{w},b) +l^{(2)}(\mathbf{w},b) + \dots + l^{(\mathcal{B})}(\mathbf{w},b))
$$
其实就是相加函数求导，对每项单独求导即可：
$$
\partial_{(\mathbf{w},b)}z = \partial_{(\mathbf{w},b)}l^{(1)}(\mathbf{w},b) + \partial_{(\mathbf{w},b)}l^{(2)}(\mathbf{w},b) + \dots + \partial_{(\mathbf{w},b)} l^{(\mathcal{B})}(\mathbf{w},b)
$$
接着再把求和符号变回去：
$$
\partial_{(\mathbf{w},b)}z = \sum_{i \in \mathcal{B}} \partial_{(\mathbf{w},b)} l^{(i)}(\mathbf{w},b)
$$
就得到了一开始模型训练过程数学表达中的后半部分，接着把`l.sum().backward()`的结果（保存至权重和偏置的梯度grad中了）带入到优化算法`sgd`对应的代码中`param -= lr * param.grad / batch_size`，就得到了完整的数学表达：
$$
(\mathbf{w},b) \leftarrow (\mathbf{w},b) - \frac{\eta}{|\mathcal{B}|} \sum_{i \in \mathcal{B}} \partial_{(\mathbf{w},b)} l^{(i)}(\mathbf{w},b).
$$
附上笔记：

![IMG_2077](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/IMG_2077.jpg)

![IMG_2078](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/IMG_2078.jpg)

![IMG_2079](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/IMG_2079.jpg)

> 本文作者：吉平. 「集」，如有侵权请联系。

![Jotting-Down_logo](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/Jotting-Down_logo.png)
