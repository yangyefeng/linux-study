    #include <stdio.h>
    #include <glib.h>
    #include <glib/gprintf.h>

    struct map {
        int key;
        char *value;
    } m[10] = {
        {0,"zero"},
        {1,"one"},
        {2,"two"},
        {3,"three"},
        {4,"four"},
        {5,"five"},
        {6,"six"},
        {7,"seven"},
        {8,"eight"},
        {9,"nine"},
    };
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
        g_printf(fmt, *(gint*)key, (gchar*)value);
        
        return FALSE;
    }

    static void
    test_avl_tree(void)
    {
        GTree *tree;
        gint i;

    // GTree* g_tree_new(GCompareFunc key_compare_func);
        tree = g_tree_new(myCompare);
        
    // void g_tree_insert(GTree *tree, gpointer key, gpointer value);
        for (i = 0; i < sizeof(m)/sizeof(m[0]); i++)
            g_tree_insert(tree, &m[i].key, m[i].value);

    // void g_tree_foreach(GTree *tree, GTraverseFunc func, gpointer user_data);
        g_printf("Now the tree:\n");
        g_tree_foreach(tree, myTraverse, "Key:\t%d\t\tVaule:\t%s\n");
    // gint g_tree_nnodes(GTree *tree);
        g_printf("The tree should have '%d' items now.\t\tResult: %d.\n", 10, g_tree_nnodes(tree));
    // gint g_tree_height(GTree *tree);
        g_printf("The height of tree is '%d' now.\n", g_tree_height(tree));

    // void g_tree_replace(GTree *tree, gpointer key, gpointer value);
        g_tree_replace(tree, &m[3].key, "3333");
        g_printf("Now the vaule of '%d' should be '3333' now.\n", m[3].key);
        g_tree_foreach(tree, myTraverse, "Key:\t%d\t\tVaule:\t%s\n");

        gchar *tmp = NULL;
    // gpointer g_tree_lookup(GTree *tree, gconstpointer key);
        g_printf("Now the vaule of '%d' should be '%s' now[lookup].\n",
                m[3].key,
                (tmp = (gchar *)g_tree_lookup(tree, &m[3].key)) != NULL ? tmp : NULL);

    // gboolean g_tree_remove(GTree *tree, gconstpointer key);
        gboolean b = g_tree_remove(tree, &m[3].key);
        g_printf("The key '%d' has %sbeen found and removed now.\n", m[3].key, b ? "" : "NOT");

    // gpointer g_tree_search(GTree *tree, GCompareFunc search_func, gconstpointer user_data);
        g_printf("Now the vaule which should be removed of '%d' should be '%s' now[search].\n",
                m[3].key,
                (tmp = (gchar *)g_tree_search(tree, mySearch, &m[3].key)) != NULL ? tmp : NULL);

        g_printf("Now the tree look like:\n");
        g_tree_foreach(tree, myTraverse, "Key:\t%d\t\tVaule:\t%s\n");

    // void g_tree_destroy(GTree *tree);
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
