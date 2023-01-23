
//------------------------------------------------------------------------------
// Includes
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Priority_Queue.h"
//------------------------------------------------------------------------------
// Definitions

//------------------------------------------------------------------------------
// Function declarations

//------------------------------------------------------------------------------
// Global variables

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

	for (int i = 0; i < (sizeof(arr) / sizeof(arr[0])); i++)
	{
		printf("top: %d\n", Priority_Queue_Top(pq));
		Priority_Queue_Pop(pq);
	}

	return 0;
}

//------------------------------------------------------------------------------
// End of file
