# C语言实现优先队列 | 图解原理与代码实现

> 优先队列（Priority Queue）是一种特殊的队列，队列中的元素以优先级进行排序，优先级高的先出列。

![优先队列 - 例子copy](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/%E4%BC%98%E5%85%88%E9%98%9F%E5%88%97%20-%20%E4%BE%8B%E5%AD%90copy.png)

## 二叉堆

本文使用二叉堆（Binary Heap）实现优先队列。

| 实现   | 获取队首 | 插入     | 删除     |
| ------ | -------- | -------- | -------- |
| 二叉堆 | O(1)     | O(log N) | O(log N) |

二叉堆是一颗完全二叉树（存储结构与二叉树相同，但树中元素只存储在索引低的位置）。二叉堆又可分为大堆（max-heap）和小堆（min-heap），大堆中父节点（parent node）数值**均大于**子节点（child node）数值，小堆则相反，这样可以保证树中最大的元素（或最小）的元素存储在堆顶（根节点）。

![二叉堆 - 例子](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/%E4%BA%8C%E5%8F%89%E5%A0%86%20-%20%E4%BE%8B%E5%AD%90.png)

二叉堆能保证树中最大的元素处在堆顶，这与优先队列要求优先级最高的元素排在队首相似，因此可以使用二叉堆来实现优先队列。

### 初始化

二叉堆中的元素可以存储在数组中，初始化时指定二叉堆的容量（最多能存储的元素个数），同时传入一个函数，用于决定是大堆还是小堆。

![优先队列 - 初始化](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/%E4%BC%98%E5%85%88%E9%98%9F%E5%88%97%20-%20%E5%88%9D%E5%A7%8B%E5%8C%96.png)

以下是初始化代码实现：

```c
//------------------------------------------------------------------------------
// Includes

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//------------------------------------------------------------------------------
// Definitions

typedef int element_t; // 元素类型
typedef struct
{
	bool (*comp)(element_t par, element_t chi); // 比较函数
	element_t *eles;							// 元素存储地址
	int capcity;								// 容量
	int size;									// 存储元素个数
} Priority_Queue_t;

//------------------------------------------------------------------------------
// Functions

/**
 * @brief   
 *          初始化优先队列
 *          
 * @param   capcity 队列容量大小
 * @param   comp    比较函数(用于确保高优先级的元素排在队首)
 *          
 * @date    2023-01-21 created by 吉平.「集」
 *          
 * @return  指向优先队列结构体的指针（返回NULL表示创建失败）
 */
Priority_Queue_t *Priority_Queue_Init(int capcity, bool (*comp)(element_t par, element_t chi))
{
	Priority_Queue_t *pq = NULL;
	pq = (Priority_Queue_t *)calloc(1, sizeof(Priority_Queue_t)); // 申请和0初始化内存空间
	if (pq != NULL)
	{
		// 申请内存空间用于存储元素
		pq->eles = (element_t *)calloc(capcity, sizeof(element_t));
		if (pq->eles != NULL)
		{
			pq->capcity = capcity;
			pq->comp = comp;
		}
		else
		{
			// 申请失败，释放之前申请的内存
			free(pq);
			pq = NULL;
		}
	}

	return pq;
}
```

### 插入操作

在往二叉堆插入新的元素时，需要保证不破坏堆的特性。以大堆为例，通过以下步骤来插入新的元素：

- 第一步：插入一个新的元素到二叉堆末尾，保证二叉堆仍是一颗完全二叉树。

![二叉堆 - 插入操作step1](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/%E4%BA%8C%E5%8F%89%E5%A0%86%20-%20%E6%8F%92%E5%85%A5%E6%93%8D%E4%BD%9Cstep1.png)

- 第二步：比较新元素所在节点与其父节点值的大小，（对于大堆）子节点的值大于父节点时，交换它们的值。

![二叉堆 - 插入操作step2](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/%E4%BA%8C%E5%8F%89%E5%A0%86%20-%20%E6%8F%92%E5%85%A5%E6%93%8D%E4%BD%9Cstep2.png)

- 第三步：重复第二步骤，直至所有节点满足“父节点数值**均大于**子节点”。

![二叉堆 - 插入操作step3](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/%E4%BA%8C%E5%8F%89%E5%A0%86%20-%20%E6%8F%92%E5%85%A5%E6%93%8D%E4%BD%9Cstep3.png)

以下是代码实现：

```c
void swap(element_t *a, element_t *b)
{
	element_t temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * @brief   
 *          插入新元素至优先队列
 *          
 * @param   pq  指向优先队列结构体的指针
 * @param   val 插入队列的新元素
 *          
 * @date    2023-01-22 created by 吉平.「集」
 *          
 * @return  true  新元素插入成功
 * @return  false 新元素插入失败
 */
bool Priority_Queue_Push(Priority_Queue_t *pq, element_t val)
{
	bool rev = false; // 返回值
	int new_node = 0; // 新元素所在节点位置
	int par_node = 0; // 新元素父节点所在位置

	// 检查是否有剩余容量
	if (pq != NULL && pq->size < pq->capcity)
	{
		new_node = pq->size;
		par_node = (new_node - 1) / 2; // 计算父节点所在位置，整除为向下取整
		pq->eles[new_node] = val;
		// 父节点存在，且父节点与子节点的值不满足要求时，交换它们的值
		while (new_node != 0 && pq->comp(pq->eles[par_node], pq->eles[new_node]) == false)
		{
			swap(&pq->eles[par_node], &pq->eles[new_node]);
			// 计算新一轮的节点位置
			new_node = par_node;
			par_node = (new_node - 1) / 2;
		}
		pq->size++;
		rev = true;
	}

	return rev;
}
```

测试一下这段代码：

```c
#include <stdio.h>

/**
 * @brief   
 *          获取队首元素
 *          
 * @param   pq 指向优先队列结构体的指针
 *          
 * @date    2023-01-23 created by 吉平.「集」
 *          
 * @return  队首元素，队列中无元素时返回0
 */
element_t Priority_Queue_Top(Priority_Queue_t *pq)
{
	element_t rev = 0;
	if (pq != NULL && pq ->size > 0)
	{
		rev = pq->eles[0];
	}
	return rev;
}

bool comparison(element_t par, element_t chi)
{
	// 父节点的值大于子节点
	return (par > chi) ? true : false;
}

int main(void)
{
	Priority_Queue_t *pq = NULL;
	element_t arr[] = {2, 1, 5, 8, 6, 9};

	pq = Priority_Queue_Init(7, comparison);

	for (int i = 0; i < (sizeof(arr) / sizeof(arr[0])); i++)
	{
		Priority_Queue_Push(pq, arr[i]);
		printf("push: %d, top: %d\n", arr[i], Priority_Queue_Top(pq));
	}

	return 0;
}
```

输出：

```shell
push: 2, top: 2
push: 1, top: 2
push: 5, top: 5
push: 8, top: 8
push: 6, top: 8
push: 9, top: 9
```

### 删除操作

仍然以大堆为例，通过以下操作来删除根节点元素：

- 第一步：交换末尾节点与根节点的数值，删除末尾节点。

![二叉堆 - 删除操作step1](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/%E4%BA%8C%E5%8F%89%E5%A0%86%20-%20%E5%88%A0%E9%99%A4%E6%93%8D%E4%BD%9Cstep1.png)

- 第二步：比较末尾节点（父节点）与左右子节点的数值，父节点数值较小时，交换父节点与子节点的数值，同时保证交换后的父节点数值大于（或等于）两个子节点的数值。

![二叉堆 - 删除操作step2](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/%E4%BA%8C%E5%8F%89%E5%A0%86%20-%20%E5%88%A0%E9%99%A4%E6%93%8D%E4%BD%9Cstep2.png)

- 第三步：重复第二步骤，直至所有节点满足“父节点数值均大于子节点”。

代码实现：

```c
/**
 * @brief   
 *          优先队列删除队首元素
 *          
 * @param   pq 指向优先队列结构体的指针
 *          
 * @date    2023-01-23 created by 吉平.「集」
 *          
 * @return  true  队首元素删除成功
 * @return  false 队首元素删除失败
 */
bool Priority_Queue_Pop(Priority_Queue_t *pq)
{
	bool rev = false;
	bool l_cond = false;
	bool r_cond = false;
	int pos = 0;
	int l_pos = 0;
	int r_pos = 0;

	// 判断是否有元素能够删除
	if (pq != NULL && pq->size > 0)
	{
		swap(&pq->eles[pos], &pq->eles[pq->size - 1]);
		pq->size--; // 删除元素

		while (pos < pq->size - 1)
		{
			l_pos = pos * 2 + 1;
			r_pos = pos * 2 + 2;

			// 子节点存在时判断数值是否满足要求
			l_cond = (l_pos < pq->size) ? pq->comp(pq->eles[pos], pq->eles[l_pos]) : true;
			r_cond = (r_pos < pq->size) ? pq->comp(pq->eles[pos], pq->eles[r_pos]) : true;

			if (l_cond == true && r_cond == true)
			{
				break; // 两个子节点均满足条件，退出循环
			}
			else if (l_cond == false && r_cond == true)
			{
				swap(&pq->eles[pos], &pq->eles[l_pos]); // 只有左子节点不满足条件，与其交换数值
				pos = l_pos;
			}
			else if (l_cond == true && r_cond == false)
			{
				swap(&pq->eles[pos], &pq->eles[r_pos]); // 只有右子节点不满足条件，与其交换数值
				pos = r_pos;
			}
			else
			{
				// 两个子节点均不满足条件，挑选一个交换后数值仍满足要求的节点进行交换
				if (pq->comp(pq->eles[l_pos], pq->eles[r_pos]) == true)
				{
					swap(&pq->eles[pos], &pq->eles[l_pos]);
					pos = l_pos;
				}
				else
				{
					swap(&pq->eles[pos], &pq->eles[r_pos]);
					pos = r_pos;
				}
			}
		}

		rev = true;
	}

	return rev;
}
```

在主函数中添加一段测试代码：

```c
	for (int i = 0; i < (sizeof(arr) / sizeof(arr[0])); i++)
	{
		printf("top: %d\n", Priority_Queue_Top(pq));
		Priority_Queue_Pop(pq);
	}
```

输出：

```shel
top: 9
top: 8
top: 6
top: 5
top: 2
top: 1
```

输出符合预期。

## 完整代码

**"Priority_Queue.h"**

```c
#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

//------------------------------------------------------------------------------
// Includes
#include <stdbool.h>
//------------------------------------------------------------------------------
// Definitions

typedef int element_t; // 元素类型

typedef struct
{
	bool (*comp)(element_t par, element_t chi); // 比较函数
	element_t *eles;							// 元素存储地址
	int capcity;								// 容量
	int size;									// 存储元素个数
} Priority_Queue_t;

//------------------------------------------------------------------------------
// Function declarations

element_t Priority_Queue_Top(Priority_Queue_t *pq);
bool Priority_Queue_Push(Priority_Queue_t *pq, element_t val);
bool Priority_Queue_Pop(Priority_Queue_t *pq);
Priority_Queue_t *Priority_Queue_Init(int capcity, bool (*comp)(element_t par, element_t chi));

#endif

//------------------------------------------------------------------------------
// End of file
```

**"Priority_Queue.c"**

```c
//------------------------------------------------------------------------------
// Includes
#include <stdlib.h>
#include <string.h>
#include "Priority_Queue.h"

//------------------------------------------------------------------------------
// Functions

static void swap(element_t *a, element_t *b)
{
	element_t temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * @brief   
 *          获取队首元素
 *          
 * @param   pq 指向优先队列结构体的指针
 *          
 * @date    2023-01-23 created by 吉平.「集」
 *          
 * @return  队首元素，队列中无元素时返回0
 */
element_t Priority_Queue_Top(Priority_Queue_t *pq)
{
	element_t rev = 0;
	if (pq != NULL && pq ->size > 0)
	{
		rev = pq->eles[0];
	}
	return rev;
}

/**
 * @brief   
 *          插入新元素至优先队列
 *          
 * @param   pq  指向优先队列结构体的指针
 * @param   val 插入队列的新元素
 *          
 * @date    2023-01-22 created by 吉平.「集」
 *          
 * @return  true  新元素插入成功
 * @return  false 新元素插入失败
 */
bool Priority_Queue_Push(Priority_Queue_t *pq, element_t val)
{
	bool rev = false; // 返回值
	int new_node = 0; // 新元素所在节点位置
	int par_node = 0; // 新元素父节点所在位置

	// 检查是否有剩余容量
	if (pq != NULL && pq->size < pq->capcity)
	{
		new_node = pq->size;
		par_node = (new_node - 1) / 2; // 计算父节点所在位置，整除为向下取整
		pq->eles[new_node] = val;
		// 父节点存在，且父节点与子节点的值不满足要求时，交换它们的值
		while (new_node != 0 && pq->comp(pq->eles[par_node], pq->eles[new_node]) == false)
		{
			swap(&pq->eles[par_node], &pq->eles[new_node]);
			// 计算新一轮的节点位置
			new_node = par_node;
			par_node = (new_node - 1) / 2;
		}
		pq->size++;
		rev = true;
	}

	return rev;
}

/**
 * @brief   
 *          优先队列删除队首元素
 *          
 * @param   pq 指向优先队列结构体的指针
 *          
 * @date    2023-01-23 created by 吉平.「集」
 *          
 * @return  true  队首元素删除成功
 * @return  false 队首元素删除失败
 */
bool Priority_Queue_Pop(Priority_Queue_t *pq)
{
	bool rev = false;
	bool l_cond = false;
	bool r_cond = false;
	int pos = 0;
	int l_pos = 0;
	int r_pos = 0;

	// 判断是否有元素能够删除
	if (pq != NULL && pq->size > 0)
	{
		swap(&pq->eles[pos], &pq->eles[pq->size - 1]);
		pq->size--; // 删除元素

		while (pos < pq->size - 1)
		{
			l_pos = pos * 2 + 1;
			r_pos = pos * 2 + 2;

			// 子节点存在时判断数值是否满足要求
			l_cond = (l_pos < pq->size) ? pq->comp(pq->eles[pos], pq->eles[l_pos]) : true;
			r_cond = (r_pos < pq->size) ? pq->comp(pq->eles[pos], pq->eles[r_pos]) : true;

			if (l_cond == true && r_cond == true)
			{
				break; // 两个子节点均满足条件，退出循环
			}
			else if (l_cond == false && r_cond == true)
			{
				swap(&pq->eles[pos], &pq->eles[l_pos]); // 只有左子节点不满足条件，与其交换数值
				pos = l_pos;
			}
			else if (l_cond == true && r_cond == false)
			{
				swap(&pq->eles[pos], &pq->eles[r_pos]); // 只有右子节点不满足条件，与其交换数值
				pos = r_pos;
			}
			else
			{
				// 两个子节点均不满足条件，挑选一个交换后数值仍满足要求的节点进行交换
				if (pq->comp(pq->eles[l_pos], pq->eles[r_pos]) == true)
				{
					swap(&pq->eles[pos], &pq->eles[l_pos]);
					pos = l_pos;
				}
				else
				{
					swap(&pq->eles[pos], &pq->eles[r_pos]);
					pos = r_pos;
				}
			}
		}

		rev = true;
	}

	return rev;
}

/**
 * @brief   
 *          初始化优先队列
 *          
 * @param   capcity 队列容量大小
 * @param   comp    比较函数(用于确保高优先级的元素排在队首)
 *          
 * @date    2023-01-21 created by 吉平.「集」
 *          
 * @return  指向优先队列结构体的指针（返回NULL表示创建失败）
 */
Priority_Queue_t *Priority_Queue_Init(int capcity, bool (*comp)(element_t par, element_t chi))
{
	Priority_Queue_t *pq = NULL;
	pq = (Priority_Queue_t *)calloc(1, sizeof(Priority_Queue_t)); // 申请和0初始化内存空间
	if (pq != NULL)
	{
		// 申请内存空间用于存储元素
		pq->eles = (element_t *)calloc(capcity, sizeof(element_t));
		if (pq->eles != NULL)
		{
			pq->capcity = capcity;
			pq->comp = comp;
		}
		else
		{
			// 申请失败，释放之前申请的内存
			free(pq);
			pq = NULL;
		}
	}

	return pq;
}

//------------------------------------------------------------------------------
// End of file
```

## 参考链接

- [什么是优先队列？](https://blog.csdn.net/hyb612/article/details/90620517)

- [Data Structures Tutorials - Max Heap with an exaple](http://btechsmartclass.com/data_structures/max-heap.html)

- [Priority Queue Data Structure](https://www.programiz.com/dsa/priority-queue)

> 本文作者：吉平. 「集」，如有侵权请联系。

![Jotting-Down_logo](https://ferost-myphotos.oss-cn-shenzhen.aliyuncs.com/Jotting-Down_logo.png)
