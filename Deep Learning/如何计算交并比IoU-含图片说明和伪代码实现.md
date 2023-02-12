# 交并比的定义

IoU(Intersection over Union)即交并比，定义为两个矩形框的交集面积除以并集面积。

![交并比定义_1](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/%E4%BA%A4%E5%B9%B6%E6%AF%94%E5%AE%9A%E4%B9%89_1.png)

所以计算交并比问题，可以转化为计算矩形框交集面积和并集面积问题。

# 计算矩形框交集面积

两个矩形框交集部分为规整的矩形，可以用矩形长乘以宽计算得到面积：

![计算交集面积-1](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/%E8%AE%A1%E7%AE%97%E4%BA%A4%E9%9B%86%E9%9D%A2%E7%A7%AF-1.png)

矩形框的宽和高分别通过x轴坐标和y轴坐标计算获得：`w = x_min - x_max`、`h = y_max - y_min`，难点在于获取两个方向上的坐标值，以x轴为例：

![交集面积-获取x轴上的坐标-1](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/%E4%BA%A4%E9%9B%86%E9%9D%A2%E7%A7%AF-%E8%8E%B7%E5%8F%96x%E8%BD%B4%E4%B8%8A%E7%9A%84%E5%9D%90%E6%A0%87-1(1).png)

![交集面积-获取x轴上的坐标-2](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/%E4%BA%A4%E9%9B%86%E9%9D%A2%E7%A7%AF-%E8%8E%B7%E5%8F%96x%E8%BD%B4%E4%B8%8A%E7%9A%84%E5%9D%90%E6%A0%87-2(1).png)

![交集面积-获取x轴上的坐标-3](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/%E4%BA%A4%E9%9B%86%E9%9D%A2%E7%A7%AF-%E8%8E%B7%E5%8F%96x%E8%BD%B4%E4%B8%8A%E7%9A%84%E5%9D%90%E6%A0%87-3(1).png)

图中`x_min`和`x_max`为需要获取的坐标值，根据矩形框位置不同，坐标值来源不同：图一中`x_min`是红色框的`x_left`（边框左边点x轴坐标值），图二和图三中则是绿色框的`x_left`。

但不管哪种情况，`x_min`始终来源于两个框的`x_left`，再仔细观察发现，`x_min`始终是两个`x_left`中靠右（值较大）的那个，所以对于`x_min`，可以通过比较`x_left`获得。对于`x_max`也是相同的，它始终是两个`x_right`中靠左（值较小）的那个。再看y轴上需要获取的坐标，可以发现与x轴坐标是类似的：

![交集面积-获取y轴上的坐标(强迫症犯了坐标同一条线单图版)](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/%E4%BA%A4%E9%9B%86%E9%9D%A2%E7%A7%AF-%E8%8E%B7%E5%8F%96y%E8%BD%B4%E4%B8%8A%E7%9A%84%E5%9D%90%E6%A0%87(%E5%BC%BA%E8%BF%AB%E7%97%87%E7%8A%AF%E4%BA%86%E5%9D%90%E6%A0%87%E5%90%8C%E4%B8%80%E6%9D%A1%E7%BA%BF%E5%8D%95%E5%9B%BE%E7%89%88).png)

对于`y_min`，始终是两个`y_top`中靠下（值较大）的那个；对于`y_max`，始终是两个`y_bottom`中靠上（值较小）的那个。

所以给定两个框的坐标，求它们交集部分坐标及面积的方法如下：

```python
# 传入参数 | bbox_red：红色框坐标 | bbox_green：绿色框坐标
# 注释：坐标格式为(x_left, y_top, x_right, y_bottom)（voc格式坐标，即边框左上角点坐标和右下角点坐标）
def get_IoU(bbox_red, bbox_green):
    # 步骤一：获取交集部分坐标
    ix_min = max(bbox_red[0], bbox_green[0]) # 两个 x_left 中[靠右]的那个
    iy_min = max(bbox_red[1], bbox_green[1]) # 两个 y_top 中[靠下]的那个
    ix_max = min(bbox_red[2], bbox_green[2]) # 两个 x_right 中[靠左]的那个
    iy_max = min(bbox_red[3], bbox_green[3]) # 两个 y_bottom 中[靠上]的那个
    
    # 步骤二：计算交集部分的宽和高
    # 注：可能出现宽度或高度为负数的情况，此时两个框没有交集，交并比为0
    iw = max(ix_max - ix_min, 0.0)
    ih = max(iy_max - iy_min, 0.0)
    
    # 步骤三：计算交集部分面积
    inters = iw * ih
```

![交集面积-获取x轴和y轴上的坐标](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/%E4%BA%A4%E9%9B%86%E9%9D%A2%E7%A7%AF-%E8%8E%B7%E5%8F%96x%E8%BD%B4%E5%92%8Cy%E8%BD%B4%E4%B8%8A%E7%9A%84%E5%9D%90%E6%A0%87.png)

# 计算矩形框并集面积

计算交并比还需要两个矩形框的并集面积，计算方法为绿色框面积+红色框面积-交集面积：

![并集面积-并集面积的计算1](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/%E5%B9%B6%E9%9B%86%E9%9D%A2%E7%A7%AF-%E5%B9%B6%E9%9B%86%E9%9D%A2%E7%A7%AF%E7%9A%84%E8%AE%A1%E7%AE%971.png)

原因及组合方法如下，由于重复累加了交集面积，所以末尾减掉其中一块交集面积：

![并集面积-并集面积的计算2](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/%E5%B9%B6%E9%9B%86%E9%9D%A2%E7%A7%AF-%E5%B9%B6%E9%9B%86%E9%9D%A2%E7%A7%AF%E7%9A%84%E8%AE%A1%E7%AE%972.png)

# 计算交并比的代码实现

最后将交集面积除以并集面积即可得到交并比：

```python
# 传入参数 | bbox_red：红色框坐标 | bbox_green：绿色框坐标
# 注释：坐标格式为(x_left, y_top, x_right, y_bottom)（voc格式坐标，即边框左上角点坐标和右下角点坐标）
def get_IoU(bbox_red, bbox_green):
    # 步骤一：获取交集部分坐标
    ix_min = max(bbox_red[0], bbox_green[0]) # 两个 x_left 中[靠右]的那个
    iy_min = max(bbox_red[1], bbox_green[1]) # 两个 y_top 中[靠下]的那个
    ix_max = min(bbox_red[2], bbox_green[2]) # 两个 x_right 中[靠左]的那个
    iy_max = min(bbox_red[3], bbox_green[3]) # 两个 y_bottom 中[靠上]的那个
    
    # 步骤二：计算交集部分的宽和高
    # 注：可能出现宽度或高度为负数的情况，此时两个框没有交集，交并比为0
    iw = max(ix_max - ix_min, 0.0)
    ih = max(iy_max - iy_min, 0.0)
    
    # 步骤三：计算交集部分面积
    inters = iw * ih
    
    # 步骤四：计算两个框的面积
    # area = w * h = (x_right - x_left) * (y_bottom - y_top)
    red_area = (bbox_red[2] - bbox_red[0]) * (bbox_red[3] - bbox_red[1]) 
    green_area = (bbox_green[2] - bbox_green[0]) * (bbox_green[3] - bbox_green[1]) 
    
    # 步骤五：计算并集面积
    uni = red_area + green_area - inters # 红色框面积 + 绿色框面积 - 交集面积
    
    # 步骤六：计算和返回交并比
    overlaps = inters / uni
    return overlaps
```

# 代码测试

有交集的情况：

```python
if __name__ == '__main__':
	bbox_red = [2, 3, 9, 10]
	bbox_green = [1, 2, 7, 8]
	print('r&g: ', get_IoU(bbox_red, bbox_green)) # 计算红色框与绿色框的交并比
	print('self: ', get_IoU(bbox_green, bbox_green)) # 计算边框完全重合时的交并比
```

![代码测试-1](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/%E4%BB%A3%E7%A0%81%E6%B5%8B%E8%AF%95-1.png)

输出：

```shell
r&g:  0.4166666666666667
self:  1.0
```

没有交集的情况：

```python
if __name__ == '__main__':
	bbox_red = [9, 3, 16, 10]
	bbox_green = [1, 2, 7, 8]
	print('none: ', get_IoU(bbox_red, bbox_green))
```

![代码测试-2](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/%E4%BB%A3%E7%A0%81%E6%B5%8B%E8%AF%95-2.png)

输出：

```shell
none:  0.0
```

# 参考链接

[目标检测番外篇(1)_IoU](https://zhuanlan.zhihu.com/p/47189358)

[【Batch IOU】IOU计算的简单理解](https://zhuanlan.zhihu.com/p/424241927)

[目标检测之 IoU](https://blog.csdn.net/u014061630/article/details/82818112)

> 本文作者：吉平. 「集」，如有侵权请联系。

![Jotting-Down_logo](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/Jotting-Down_logo.png)
