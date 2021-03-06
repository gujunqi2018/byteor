/*
 * list.h - double linked list (tailored from Linux)
 *
 * Copyright (c) Linux Kernel
 * Copyright (c) Zhou Peng <p@ctriple.cn>
 */

#ifndef LIST_H
#define LIST_H

#include <stddef.h> /* for size_t, offsetof */

#define container_of(ptr, type, member) ({                \
			const typeof(((type *)0)->member) *__mptr = (ptr);  \
			(type *)((char *)__mptr - offsetof(type,member));   \
		})

struct list_head {
	struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(name) {&(name), &(name)}

#define LIST_HEAD(name)                         \
	struct list_head name = LIST_HEAD_INIT(name)

static inline void INIT_LIST_HEAD(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_add(struct list_head *new,
                              struct list_head *prev,
                              struct list_head *next)
{
	next->prev = new;
	new->next  = next;
	new->prev  = prev;
	prev->next = new;
}

/*
 * list_add -- add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified header.
 * This is good for implementing stacks.
 */
static inline void list_add(struct list_head *new,
                            struct list_head *head)
{
	__list_add(new, head, head->next);
}

/*
 * list_add_tail -- add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
static inline void list_add_tail(struct list_head *new,
                                 struct list_head *head)
{
	__list_add(new, head->prev, head);
}

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_del(struct list_head *prev,
                              struct list_head *next)
{
	next->prev = prev;
	prev->next = next;
}

/*
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty() on entry does not return true after this,
 * the entry is in an undefined state.
 */
static inline void list_del(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	entry->next = NULL;
	entry->prev = NULL;
}

/*
 * list_empty -- tests whether a list is empty
 * @head: the list to test.
 */
static inline int list_empty(const struct list_head *head)
{
	return head->next == head;
}

/*
 * list_entry -- get the struct for this entry
 * @ptr: the &struct list_head pointer.
 * @type: the type of the struct this is embedded in.
 * @member: the name of the list_struct within the struct.
 */
#define list_entry(ptr, type, member)           \
	container_of(ptr, type, member)

/*
 * list_for_each -- iterate over a list
 * @pos: the &struct list_head to use as a loop cursor.
 * @head: the head for your list.
 */
#define list_for_each(pos, head)                            \
	for (pos = (head)->next; pos != (head); pos = pos->next)

/*
 * list_for_each_safe -- iterate over a list safe against
 *                       removal of this entry
 * @pos: the &struct list_head to use as a loop cursor.
 * @n: another &struct list_head to use as temporary storage
 * @head: the head for your list.
 */
#define list_for_each_safe(pos, n, head)                  \
	for (pos = (head)->next, n = pos->next; pos != (head);	\
	     pos = n, n = pos->next)

/*
 * list_for_each_entry -- iterate over list of given type
 * @pos: the type * to use as a loop cursor.
 * @head: the head for your list.
 * @member: the name of the list_struct within the struct.
 */
#define list_for_each_entry(pos, head, member)                    \
	for (pos = list_entry((head)->next, typeof(*pos), member);      \
	     &pos->member != (head);                                    \
	     pos = list_entry(pos->member.next, typeof(*pos), member))

#endif /* LIST_H */
