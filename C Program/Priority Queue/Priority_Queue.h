
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
