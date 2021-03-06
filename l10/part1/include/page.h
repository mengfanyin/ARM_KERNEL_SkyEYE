#ifndef     __PAGE_H__
#define     __PAGE_H__


#include "arch/asm.h"
#include "list.h"

#define  PAGE_NUM   (MEM_SIZE / 4096)
/* 32MB max order */
#define  MAX_ORDER  13
#define PAGE_SHIFT 12
#define PAGE_SIZE (1 << PAGE_SHIFT)

#include "slab.h"

struct page {
    /* dummy */
    unsigned long phy_addr;
    unsigned long flag;
    /* 表示该页所在的order */
    int order;
    /* 用于实现伙伴算法 */
    struct list_head pg_lst;
    /* 指明该页属于哪个slab分配器 */
    struct kmem_cache *cachep;
};

struct buddy_node {
    unsigned long free_num;
    struct list_head node_head[MAX_ORDER];
};


struct page* get_page_by_phyaddr(unsigned long phy_addr);
unsigned long get_phyaddr_by_page(struct page *pg);
void * alloc_pages(int order);
struct page * __alloc_page(int order);
void __free_pages(struct page *page, int order);
unsigned long get_phyaddr_by_page(struct page *pg);
struct page* get_page_by_phyaddr(unsigned long phy_addr);
void free_pages(void *addr, int order);
void test_buddy(void);

#define alloc_page() alloc_pages(0)
#define free_page(addr) free_pages(addr, 0)

#endif
