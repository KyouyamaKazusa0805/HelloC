#pragma warning (disable: 6031)

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node
{
	int data; // 数据域。
	struct node *next; // 指针域。
};

void visit(struct node *);
void printNewLine(void);

struct node *create(int);
struct node *getIndexOf(struct node *, int);
void traverse(struct node *, void (*)(struct node *), void (*)(void));
void insert(struct node *, int, struct node *);
void append(struct node *, struct node *);
int getLength(struct node);
struct node *removeAt(struct node *, int);
struct node *removeTail(struct node *);
void dispose(struct node *);

int main(void)
{
	struct node *pHead = create(5);
	if (pHead == NULL)
	{
		printf("分配内存失败。");
		return 0;
	}

	int length = getLength(*pHead);
	printf("%d\n", length);

	traverse(pHead, &visit, &printNewLine);

	removeAt(pHead, 2);

	traverse(pHead, &visit, &printNewLine);

	struct node *newNode = malloc(sizeof(struct node));
	if (newNode != NULL)
	{
		newNode->data = 12;
		insert(pHead, 3, newNode);

		traverse(pHead, &visit, &printNewLine);
	}

	//traverse(pHead, &visit, &printNewLine);

	//getIndexOf(pHead, 3)->data = 2;

	//traverse(pHead, &visit, &printNewLine);
}

void visit(struct node *node)
{
	printf("%d ", node->data);
}

void printNewLine(void)
{
	putchar('\n');
}

// 释放链表使用的内存空间。
void dispose(struct node *list)
{
	// TODO: q 没有初始化。
	struct node *p = list, *q = p;
	while (p->next)
	{
		p = p->next;
		free(q);
		q = q->next;
	}
}

// 获取链表的长度。
int getLength(struct node head)
{
	int count = 1;
	struct node *p = head.next;
	while (p->next)
	{
		count++;
		p = p->next;
	}

	return count;
}

// 删除最后一个节点。
struct node *removeTail(struct node *list)
{
	int length = getLength(*list);
	struct node *pTail = getIndexOf(list, length - 2);
	struct node *returnNode = pTail->next;

	pTail->next = NULL;
	return returnNode;
}

// 删除中间某个节点，由索引指定。
struct node *removeAt(
	struct node *list,
	int index
)
{
	struct node *p, *q, *r;
	q = getIndexOf(list, index - 1);
	p = q->next;
	r = q->next->next;

	q->next = r;
	return p;
}

// 将某个节点追加到指定链表里。
void append(
	struct node *list,
	struct node *pNode
)
{
	struct node *p = list;
	while (p->next)
	{
		p = p->next;
	}

	p->next = pNode;
	pNode->next = NULL;
}

// 插入某个节点到指定列表里。
void insert(
	struct node *list,
	int index,
	struct node *pNode
)
{
	struct node *p = getIndexOf(list, index);
	struct node *q = p->next;
	p->next = pNode;
	pNode->next = q;
}

// 遍历列表。
void traverse(
	struct node *list,
	void (*visitor)(struct node *),
	void (*onEnding)(void)
)
{
	struct node *p = list;
	while (p->next)
	{
		(*visitor)(p);

		p = p->next;
	}

	(*onEnding)();
}

// 取出指定索引（下标）的节点信息，
// 返回当前要查找节点的地址。
struct node *getIndexOf(
	struct node *list,
	int index
)
{
	struct node *p = list;
	for (int i = 0; i < index; i++)
	{
		p = p->next;
	}

	return p;
}

// 创建指定节点数的链表，并返回头节点地址。
struct node *create(int count)
{
	struct node *head = malloc(sizeof(struct node));
	if (!head)
	{
		return NULL;
	}

	head->data = 1;
	head->next = NULL;
	struct node *tail = head;
	for (int i = 0; i < count; i++)
	{
		struct node *p;
		do
			p = malloc(sizeof(struct node));
		while (!p);

		p->data = 0;
		p->next = NULL;

		tail->next = p;
		tail = p;
	}

	return head;
}