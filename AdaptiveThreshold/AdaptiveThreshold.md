# 自适应阈值二值化C语言代码实现

> 本文重点关注自适应阈值二值化代码实现

### 应用背景

光照不均匀的场景，大津法计算得到的阈值，用于二值化的效果并不理想。尝试自适应阈值二值化或许可以得到效果更好的二值化图像。

### 效果对比

| 从上至下分别是原图[^1]、灰度图、大津法二值化结果、自适应阈值二值化结果[^2] |
| ------------------------------------------------------------ |
| ![Snipaste_2022-12-20_22-52-00](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/Snipaste_2022-12-20_22-52-00.bmp) |
| ![colorful2gray](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/colorful2gray.bmp) |
| ![binary_otsu](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/binary_otsu.bmp) |
| ![binary_adpative](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/binary_adpative.bmp) |

可以看到大津法二值化和自适应二值化有各自的特点。大津法二值化比较准确的区分了前景和背景；自适应二值化保留了较多细节。

### 代码实现

自适应阈值二值化C语言实现：[^3]

```C
#include "stdlib.h"

/**
 * @brief:   获取积分图像
 *           
 * @param:   *gray_img  灰度图像数组首地址
 * @param:   *sum       保存积分图像数组的首地址
 * @param:   width      灰度图像宽度
 * @param:   height     灰度图像高度
 *           
 * @date:    2022-12-20 created by 吉平.「集」
 */
void integral(uint8_t *gray_img, int *sum, int width, int height)
{
	for (int y = 0; y < height; y++)
	{
		// 获取行指针
		gray_t *input_row_ptr = &gray_img[y * width];
		int *output_row_ptr = &sum[(y + 1) * width + 1]; // 积分图像比原始图像行和列都要多1

		// 计算积分图像
		for (int x = 0; x < width; x++)
		{
			output_row_ptr[x] = 0;															// 清零
			output_row_ptr[x] = output_row_ptr[x - 1] + input_row_ptr[x];					// 0 + s_{y,x-1} + a_{x,y}
			output_row_ptr[x] += output_row_ptr[x - width] - output_row_ptr[x - width - 1]; // 当前列和
		}
	}
}

/**
 * @brief:   自适应阈值二值化
 *           
 * @param:   *gray_img  灰度图像数组首地址
 * @param:   width      灰度图像宽度
 * @param:   height     灰度图像高度
 *           
 *           @note 二值化会直接作用在原灰度图像上
 *           
 * @date:    2022-12-20 created by 吉平.「集」
 */
void adaptive_threshold_binaryzation(uint8_t *gray_img, int width, int height)
{
	// 自适应阈值取n*n范围的像素计算局部最优阈值，这里计算合适的n的取值
	int S = (width > height ? width : height)/8;
	// T是一个可调参数，影响阈值（进而影响二值化效果）
	float T = 0.15;

	// 定义变量保存n*n框选的图像范围及像素数量
	int s2 = S/2;
	int x1, y1, x2, y2, count;

	// 申请内存空间用于保存积分图像，积分图像比原始图像多一行一列
	int *sum = NULL;
	sum = (int *)calloc((width + 1) * (height + 1), sizeof(int)); // 申请内存空间，并对申请到的空间做零初始化

	// 确认是否申请到了内存空间
	if(sum != NULL)
	{
		integral(gray_img, sum, width, height); // 计算和获取积分图像

		// 外层循环用于遍历图像的每一行
		for (int y = 0; y < height; y++)
		{
			// 计算y轴上的框选范围
			y1 = y - s2;
			y2 = y + s2;

			// 避免框选到图像外的像素点
			y1 = y1 < 0 ? 0 : y1;
			y2 = y2 > (height - 1) ? (height - 1) : y2;

			// 获取灰度图像和积分图像的行指针（可以理解为单行图像的首个像素的地址）
			gray_t *row_ptr = &gray_img[y * width];
			int *y1_ptr = &sum[y1 * width];
			int *y2_ptr = &sum[y2 * width];

			// 内层循环用于遍历图像的每一列
			for (int x = 0; x < width; x++)
			{
				// 计算x轴上的框选范围
				x1 = x - s2;
				x2 = x + s2;

				// 避免框选到图像外的像素点
				x1 = x1 < 0 ? 0 : x1;
				x2 = x2 > (width - 1) ? (width - 1) : x2;

				// 计算框选的像素点的个数
				count = (x2 - x1) * (y2 - y1);

				// 计算局部阈值
				int summation = y2_ptr[x2] + y1_ptr[x1] - y1_ptr[x2] - y2_ptr[x1]; // 利用积分图快速求区域和
				uint8_t threshold = summation / count;

				// 二值化
				row_ptr[x] = ((int)(row_ptr[x] * count) > (int)(summation * (1.f - T))) ? 255 : 0;
			}
		}

		free(sum); // 释放申请的内存空间
	}
	else
	{
		// do nothing
	}
}
```

### 参考链接

[自适应阈值二值化算法](https://www.cnblogs.com/polly333/p/7269153.html)

[积分图像](https://mangoroom.cn/opencv/integral-image.html)

[Integral images in OpenCV](https://aishack.in/tutorials/integral-images-opencv/)

### 脚注

[^1]:[Two People On Mountain Cliff · Free Stock Photo ](https://www.pexels.com/photo/two-people-on-mountain-cliff-1647962/)
[^2]:转灰度和二值化用了 [@Kyatto](https://github.com/KyattoCat) 制作的图形上位机 [Mi-UpperMachine](https://github.com/KyattoCat/Mi-UpperMachine)
[^3]:代码主要参考的是[自适应阈值二值化算法](https://www.cnblogs.com/polly333/p/7269153.html)

> 本文作者：吉平. 「集」，如有侵权，请联系我。

![Jotting-Down_logo](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/Jotting-Down_logo.png)