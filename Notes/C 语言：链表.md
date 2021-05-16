# 链表

## 介绍

创建数组时，我们会直接分配出所有我们需要的内存。但是对于链表，我们每次只分配出一个**节点**（node） 的内存。链表使用指针将各个节点组合到一起，这样就形成了一个连一个的链式的结构，这就是**链表**（Linked List）。

链表的每个”单元“称为节点，其由俩部分组成：

![图 1](https://i.loli.net/2021/05/14/8fqQpa6DVwCsMGO.png "图1")

## 链表基本构造

在实现链表之前，其定义部分基本如下：

```c
struct node
{
    int data; // 数据域。
    struct node *next; //指针域。
};
```

数据域存储此节点的信息，而指针域则存储下一节点的地址，**而最后一个节点的指针域则一般为 `NULL`**。现在，有如下链表：

![图 2](https://i.loli.net/2021/05/14/t1pdfBLGiIRoyw6.png "图 2")

若要取用数据，有以下俩种方法可供参考：

```c
int d = p.next->data;
int d = (*p.next).data;
// p 的变量类型为 'struct node'，
// 取用的值为p所指向的节点的下一个节点的数据。
```

> **Tips:** `p.next` 与 `p->next` 的区别
>
> 假设我们有 `struct node *p;`，那么：
>
> * `p->next` 指的是 `p` 的下一节点的地址；
> * `p.next` 指的是当 `p` 被 `struct node p` 定义时，才有所需要的意义：指 `p` 的指针域所指向的地址。 

## Part 1：创建及初始化链表

```C
struct node *create(int count)
```

创建一个链表并初始化，首先要知道所需要的长度，那么头节点的指针是必须知道的。定义一个头节点同时分配内存：`struct node *head = malloc(sizeof(struct node *));`。考虑到内存分配失败的情况，此时返回 `NULL` 值。

```c
if(head == NULL)
{
    return NULL; // 在主函数里，调用时，若分配失败，打印一条信息。
}
```

分配内存之后，初始化其值，这里统一为 0，同时为了区分头节点与其他节点，把头节点的值赋值为 1。

### 初始化头节点

```c
head->data = 1;
head->next = NULL;  // 如果只创建 1 个的话，头节点即尾节点。
```

### 初始化其他节点

> 为初始化其他节点，且保持 ‘秩序’，先定义一个“游标”为 `tail`。

```c
struct node *tail = head;
for(int i = 0; i < count; i++) // 'head' 已经有一个节点了，for 初始化其他节点。
{
    struct node *p, *q;
    do
    {
        q = malloc(sizeof(struct node));
	} while(q == NULL);
    p = q;
    
    p->data = 0;
    p->next = NULL;
    
    tail->next = p; // 连接到下一个节点。第一轮循环把 'head' 和第二个节点连接了，所以直接返回 'head'。
    tail = p; // 新节点当尾巴。
}
```

最后函数体只需返回 `head` 即可，即 `return head;`。

值得注意的是，链表的初始化主要有一下几点：

1. 创建节点，分配内存；
2. 尾巴后移：将最新创建的节点赋给游标；
3. 连接节点：将上一节点的指针域指向下一节点，即 `p->next = q;`。


## Part 2：遍历链表、读取指定节点

### 链表的遍历

```c
void traverse(struct person *list)
```

为了实现遍历链表，然后输出，显然我们依旧需要一个游标节点。遍历过程大致分为两步：

1. 输出当前节点数据；
2. 游标前移，当节点指针域为 `NULL` 时停止。	

```c
struct node *p = list;
while(p->next != NULL)
{
    printf("%d ", p->data);
    p = p->next;
}
printf("\n"); // 以上为函数体。
```

### 读取链表指定节点

```c
struct node *getIndexOf(struct node *list, int index)
```

同样的道理，使用游标，游标不断前移，直到到索引处，函数返回该节点的地址即可。

```c
struct node *p = list;

// 对这一段，i = 0 的话，那么 index = 3 时，
// 指向的就是第四个节点。
for (int i = 1; i < index; i++)
{
    p = p->next;
}
return p;
```

作为一个可选项，如果 `index = 1` 或者 0 的话，根据需要，可以直接返回头节点的地址，即 `return list`。

## Part 3:  插入节点、获取链表长度

### 插入节点

![图 3](https://i.loli.net/2021/05/15/pwznIvqLkNgjKxs.png "图 3")

插入节点，分为俩种情况，一种插入在中段，另一种则是插入在两端。

> 待插入节点记为 `pNode`。

### 在中间部分插入节点

```c
void insert(struct node *list, int index, struct node *pNode)
```

> `index` 为待插入位置的前一个节点的索引。

这个过程我们需要做两件事：

1. 删除 `p`、`q` 之间的关系，连接 `p` 与 `n`；
2. 连接 `n` 与 `q`。

代码实现如下：

```c
struct node *p = getIndexOf(list, index);
struct node *q = p->next;
p->next = pNode;
pNode->next = q;
```

### 在两端插入节点

事实上，无论是在链表前端还是在后端插入节点，其原理，都是相似的。

当在前端插入时，我们只需将待插入节点 `pNode` 的指针域指向头节点，即可。在后端插入时，把之前最后节点的指针域指向新节点，同时新节点的指针域为 `NULL`。

```c
void appendHead(struct node *list, struct node *pNode) // 在头节点前添加节点。

// 则有
pNode->next = list;
```

```c
void appendTail(struct node *list, struct node *pNode) // 向尾部追加。

// 则有
struct node *p = list;
while(p->next != NULL)
{
    p = p->next;
}
p->next = pNode;
pNode->next = NULL;
```

### 获取链表长度

``` c
int getLength(struct node *head*)
```

原理很简单，从头开始，遍历一遍，记录节点个数即可。

```c
int count = 1;
struct node *p = head.next;
while(p->next != NULL)
{
    count++;
    p = p->next;
}
return count;
```

## Part 4：删除节点

对于 `p`、`r`、`q` 三个连续的节点，此时我们想删除 `r` 节点。

![图 4](https://i.loli.net/2021/05/15/BgYrfkCERGOFlvU.png "图 4")


这个过程主要包括：**找到 `p` 节点的地址、找到 `r` 节点的地址、最后连接 `p`、`r`**（即 `p->next = r`）。

```c
struct node *removeAt(struct node *list, int index)
    
// 则有
struct node *p, *q, *r;
p = getIndexOf(list, index - 1);
q = p->next;
r = p->next->next;

p->next = r;
return q; // 返回被删除节点的地址。
```

但同插入节点类似，删除节点也要考虑到两端的问题。

删除头节点时，只需将头节点地址存储下来待返回，将返回值指向第二个节点。

```c
struct node *removeHead(struct node *list)

// 则有
struct node *returnNode = list;
returnNode = list->next;
free(list);
return returnNode;
```

删除尾部节点，只需找到尾部节点地址，然后将上一节点指针域指向NULL。

```c
struct node *removeTail(struct node *list)

// 则有
// 这里我们使用上面自定义的函数操作。
int length = getLength(*list);
struct node *pTail = getIndexOf(list, length - 1);
struct node *returnNode = pTail->next;
pTail->next = NULL;
return returnNode;
```


## Part 5：释放内存

释放内存就比较简单了，只需要有一个游标前移，同时删除节点空间。

```c
void dispose(struct node *list)
```

```c
struct node *p = list, *q; //q 作为游标。
q = p;
while(p != NULL)
{
    p = p->next; // 前移。
    free(q);
    q = q->next;   
}
```

## 完

最后，需要说明的是，虽然文中并没有提到基础**增删改查**中的**改**，但这一操作所需原理已经解释。改本质上即找到所需修改节点的地址，然后修改数据。所以，利用 `getIndexOf` 函数即可。
