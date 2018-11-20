#include <glib.h>

void display_list(GSList *list)
{
    GSList *iterator = NULL;

    for (iterator = list; iterator; iterator = iterator->next) {
        printf("%s ", (char*)iterator->data);
    }
    printf("/n");
}

int my_str_cmp(gconstpointer str1, gconstpointer str2)
{
    return strcmp(str1, str2);
}

int main(int argc, char *argv[])
{
    GSList *list = NULL;

    /*
     * 这里没有调用创建链表的函数，只需要声明一个指向GSList结构体的指针，
     * g_slist_append函数返回指向链表首部的指针，所以一定要保存这个指针
     */
    printf("Creat single list:/n");
    list = g_slist_append(list, "one");
    list = g_slist_append(list, "two");
    list = g_slist_append(list, "three");
    display_list(list);

    /*
     * 在链表首部加入，复杂度是O(1)，记得要保存函数返回的指针
     */
    printf("Add at head of list:/n");
    list = g_slist_prepend(list, "first");
    list = g_slist_prepend(list, "second");
    list = g_slist_prepend(list, "third");
    display_list(list);

    /*
     * 在链表的指定位置插入一个节点
     */
    printf("Insert at index 1, 2, 3:/n");
    list = g_slist_insert(list, "1", 1);
    list = g_slist_insert(list, "2", 2);
    list = g_slist_insert(list, "3", 3);
    display_list(list);

    /*
     * 向链表中插入节点并排序，这里我传入了一个用于排序链表元素的比较函数，
     * 这个函数只是简单的调用了strcmp。这里可以直接到strcmp作为第三个参数
     * 传给g_slist_insert_sorted
     */
    printf("Insert sorted:/n");
    list = g_slist_insert_sorted(list, "ONE", my_str_cmp);
    list = g_slist_insert_sorted(list, "TWO", my_str_cmp);
    list = g_slist_insert_sorted(list, "THREE", my_str_cmp);
    display_list(list);

    /*
     * 反转链表
     */
    printf("Reverse the list:/n");
    list = g_slist_reverse(list);
    display_list(list);

    /*
     * 删除链表，如果list为NULL的话，g_slist_free函数会直接返回
     */
    g_slist_free(list);
    return 0;
}

