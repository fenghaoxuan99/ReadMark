# 笔记



model_train     = model.train()设置训练模式
```python
  # 设置模型为训练模式
model.train()

# 训练循环
for data, target in train_loader:
    optimizer.zero_grad()  # 清除梯度
    output = model(data)   # 前向传播
    loss = loss_fn(output, target)  # 计算损失
    loss.backward()  # 反向传播
    optimizer.step()  # 更新权重
 ```

model_train = model_train.cuda() 将模型或张量转移到 GPU

param.requires_grad = False：这行代码将每个参数的 **requires_grad** 属性设置为 False。在 PyTorch 中，requires_grad 是一个布尔值，
指示该参数是否需要在反向传播中计算梯度。如果设置为 False，则在反向传播时，这些参数的梯度不会被计算，从而在优化过程中不会更新它们的值。
### freeze_model 冻结模型参数
```python
 def freeze_backbone(self):
        for param in self.features.parameters():
            param.requires_grad = False

    def Unfreeze_backbone(self):
        for param in self.features.parameters():
            param.requires_grad = True
```  

## 余弦退火学习率调整（Cosine Annealing Learning Rate Scheduler）--学习率衰减策略。
它模仿了物理上的退火过程，通过模拟余弦函数的周期性变化来逐渐降低学习率，从而帮助模型在训练过程中更好地收敛。

基本原理
余弦退火的基本思想是在训练的预设周期内，按照余弦函数的形式逐渐降低学习率。这种方法可以**让学习率在训练初期较快地
减小，然后在训练后期更加平缓地降低**，模仿了金属退火时温度逐渐降低的过程。

### 余弦退火学习率公式
余弦退火学习率的计算公式通常如下：

其中：

lr 是当前的学习率。
lr_max 是学习率的最大值，通常是初始学习率。
lr_min 是学习率的最小值。
T 是当前的周期数或迭代次数。
T_max 是预设的周期总数或总迭代次数。
### 特点
周期性: 学习率按照余弦函数的周期性变化，有助于模型在训练过程中避免陷入局部最小值。
平滑性: 学习率的变化更加平滑，减少了训练过程中的不稳定性。
适应性: 可以根据训练的进度动态调整学习率，使模型在不同阶段有不同的学习效率。
### 应用场景
余弦退火学习率调整广泛应用于各种深度学习任务中，特别是在以下场景：
需要预热的模型: 某些模型在训练初期可能需要较高的学习率以快速收敛到一个合理的解空间。
训练周期较长: 对于需要长时间训练的模型，余弦退火可以帮助模型在训练后期更细致地调整权重。
避免过拟合: 通过逐渐降低学习率，模型可以减少对训练数据的过拟合。
### 实现示例
在实际的深度学习框架中，如 PyTorch，可以使用 torch.optim.lr_scheduler.CosineAnnealingLR 来实现余弦退火学习率调整：
```python
import torch.optim as optim
from torch.optim.lr_scheduler import CosineAnnealingLR

optimizer = optim.SGD(model.parameters(), lr=0.1)
scheduler = CosineAnnealingLR(optimizer, T_max=10)

for epoch in range(num_epochs):
    train(...)
    validate(...)

    scheduler.step()
```
在每个 epoch 结束时调用 scheduler.step() 来更新学习率。
### 注意事项
采用以较低学习率逐渐增大至较高学习率的方式实现网络训练的“热身”阶段，称为 warm up stage。
(二)、为什么使用Warmup?
由于刚开始训练时,模型的权重(weights)是随机初始化的，此时若选择一个较大的学习率,可能带来模型的不稳定(振荡)，选择Warmup预热学习率的方式，
可以使得开始训练的几个epoches或者一些steps内学习率较小,在预热的小学习率下，模型可以慢慢趋于稳定,等模型相对稳定后再选择预先设置的学习率进行训
练,使得模型收敛速度变得更快，模型效果更佳。
Example：Resnet论文中使用一个110层的ResNet在cifar10上训练时，先用0.01的学习率训练直到训练误差低于80%(大概训练了400个steps)，然后
使用0.1的学习率进行训练。
余弦函数中随着x的增加余弦值首先缓慢下降，然后加速下降，再次缓慢下降。这种下降模式能和学习率配合，以一种十分有效的计算方式来产生很好的效果


## param_groups
optimizer.param_groups： 是一个list，其中的元素为字典；

optimizer.param_groups[0]：长度为7的字典，包括
[‘params’, ‘lr’, ‘betas’, ‘eps’, ‘weight_decay’, ‘amsgrad’, ‘maximize’]这7个参数；

下面用的Adam优化器创建了一个optimizer变量：

```python
from tqdm import tqdm

# assume
dataset_num = 100000
batch_size = 8
epoch = 1
d_loss = 1.2345
g_loss = 1.2345

pbar = tqdm(range(int(dataset_num / batch_size)))

for i in pbar:
    epoch += 1
    d_loss += 1.2345
    g_loss += 1.2345
    pbar.set_description('Epoch: %i' % epoch)
    pbar.set_postfix(d_loss=format(d_loss,'.3f'), g_loss=format(g_loss,'.3f'))
```

