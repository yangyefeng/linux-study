

    #include <stdio.h>
    #include <string.h>
    #include <glib.h>
    #include <time.h>
    #include <assert.h>

    #define TIMES 20
    static void free_data(gpointer hash_data)
    {
        g_free(hash_data);
        hash_data = NULL;
    }
    int add(int a,int b)
{ 
   return a+b;
        

}

    void print_key_value(gpointer key, gpointer value ,gpointer user_data)
    {
        printf("%4s -------------------->%s\n",(char*)key,(char*)value);
    }

    int hash_test_2()
    {
         GHashTable* dictionary = NULL;
         dictionary = g_hash_table_new_full(g_str_hash,g_str_equal,free_data,free_data);

         if(dictionary == NULL)
         {
             fprintf(stderr,"create hash table failed\n");
             return -1;
         }

         srandom(time(NULL));

         int i = 0;
         int ret = 0;
         char key[64] ;
         char value[64] ;
         for(i = 0; i< TIMES;i++)
         {
             snprintf(key,sizeof(key),"%d",i);
             snprintf(value,sizeof(value), "%d", random());
             
             char* key_in_hash = strdup(key);
             char* value_in_hash = strdup(value);

             if( value_in_hash == NULL || key_in_hash == NULL)
             {
                 ret = -2;
                 fprintf(stderr,"key or value malloc failed\n");
                 goto exit;
             }

             if(strcmp(key_in_hash,"10") == 0)
             {
                 printf("before insert key(10) address(%p) : value(%s) address(%p)\n",key_in_hash,value_in_hash,value_in_hash);
             }
             g_hash_table_insert(dictionary, key_in_hash,value_in_hash);

         }

        g_hash_table_foreach(dictionary,print_key_value,NULL);
        printf("there are %d records in dictory\n",(unsigned int) g_hash_table_size(dictionary));

        char* key_10 = NULL;
        char* value_10 = NULL; 
        ret = g_hash_table_lookup_extended(dictionary,"10",(void **)&key_10, (void **)&value_10);
        if(ret==FALSE)
        {
            fprintf(stderr, "can not the key 10\n");
            goto exit;
        }
        else
        {
            fprintf(stderr,"In dictionary, key(%s) address(%p) : value (%s) address(%p)\n",key_10,key_10,value_10,value_10);
        }

        char* key_10_new = strdup("10");
        char* value_10_new = strdup("new 10 value");

        g_hash_table_replace(dictionary,key_10_new,value_10_new);


        ret = g_hash_table_lookup_extended(dictionary,"10",(void **)&key_10,(void**)&value_10);
        if(ret == FALSE)
        {
            fprintf(stderr, "found failed after modify\n");
            
        }
        else
            printf("After replace In dictionary, key(%s) address(%p) : value (%s) address(%p)\n",key_10,key_10,value_10,value_10);
        
        g_hash_table_remove(dictionary,"10");
        value_10 = g_hash_table_lookup(dictionary,"10");
        assert(value_10 == NULL);

        ret = 0;
    exit:
        g_hash_table_destroy(dictionary);
        return ret;
    }

    int main()
    {
         hash_test_2();
    }


