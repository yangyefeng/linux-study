    #include <stdio.h>
    #include <glib.h>
    #include <glib/gprintf.h>
typedef int(*pf)(int,int);
GTree *tree;
GSList *list[10];
int add(int a,int b)
{
 return a+b;
}
int sub(int a,int b)
{
 return a-b;
}

    struct map {
        int key;
      //  int (*value)(int a,int b);
	GSList *list;
    }; 
/*m[10] = {
        {0,add},
        {1,add},
        {2,add},
        {3,sub},
        {4,add},
        {5,add},
        {6,add},
        {7,add},
        {8,add},
        {9,add},
    };
*/
struct map m[10];
void init_map(void)
{
	
        int i;
        for(i=0;i<10;i++) 
	{
		m[i].key=i;
                m[i].list=list[i];

	}
	

}
add_list_node(int t,pf g_pf)
{
    	//int (*tmp)(int a,int b) = NULL;
        GSList *list_temp;
	int sum;
   	 list_temp = g_tree_lookup(tree, &m[t].key); 
	 list_temp = g_slist_append(list_temp, g_pf);
	//printf("%d\n",sum);
        GSList *iterator = NULL;

    for (iterator = list_temp; iterator; iterator = iterator->next) {
        printf("%d ", iterator->data);
    }


}
    typedef struct map map;

    static gint
    myCompare(gconstpointer p1, gconstpointer p2)
    {
        const char *a = p1;
        const char *b = p2;

        return *a - *b;
    }

    static gint
    mySearch(gconstpointer p1, gconstpointer p2)
    {
        return myCompare(p1, p2);
    }

    static gint
    myTraverse(gpointer key, gpointer value, gpointer fmt)
    {
     //   g_printf(fmt, *(gint*)key, (int)(*value)(1,2));
        
        return FALSE;
    }

    static void
    test_avl_tree(void)
    {
        
        gint i;
	int sum;
 	int (*tmp)(int a,int b) = NULL;

    // GTree* g_tree_new(GCompareFunc key_compare_func);
        tree = g_tree_new(myCompare);
        
    // void g_tree_insert(GTree *tree, gpointer key, gpointer value);
        init_map();
        for (i = 0; i < sizeof(m)/sizeof(m[0]); i++)
            g_tree_insert(tree, &m[i].key, m[i].list);

    // void g_tree_foreach(GTree *tree, GTraverseFunc func, gpointer user_data);
        g_printf("Now the tree:\n");
 //	tmp = g_tree_lookup(tree, &m[3].key);  //查找树的关键值
//	g_printf("Now the vaule of '%d' should be '%d' now[lookup].\n",m[3].key,
 //               tmp(8,4));
        add_list_node(1,add(5,3));//给某个消息添加处理函数
        for (i = 0; i < sizeof(m)/sizeof(m[0]); i++)
	{
        	//sum=m[i].value(2,3);
        	
	}
        g_tree_destroy(tree);
    }

    int
    main(void)
    {
        printf("BEGIN:\n************************************************************\n");

        test_avl_tree();

        printf("\n************************************************************\nDONE\n");

        return 0;
    }
