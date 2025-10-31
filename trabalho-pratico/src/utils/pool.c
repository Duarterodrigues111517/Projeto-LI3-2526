#include "utils/pool.h"
/*
*   pool struct:
*       -> blocks:: array of pointers to each block memory (array of linked lists)
*       -> block_size:: defines the number of items that each memory block supports
*       -> item_size:: defines the size of each item present in the block
*       -> block_number:: stores the number of blocks currently allocated
*   Considerations: 
*       -> Each block has a capacity
*       -> Blocks are defined as linked lists
*       -> The blocks array grows over time 
*/
struct pool{
    GPtrArray*   blocks;
    size_t       item_size;
    int          block_length;
    int          last_block_items;
};


pool_t* pool_init(int block_length, size_t item_size){
    pool_t* new_pool = malloc (sizeof(pool_t));
    new_pool->blocks = g_ptr_array_new ();
    new_pool->item_size = item_size;
    new_pool->block_length = block_length;
    new_pool->last_block_items = 0;
    return new_pool;
}

void* pool_insert_item(pool_t* pool, size_t item_size){
    if(pool->last_block_items == pool->block_length){
        //need to allocate a new block
        void* new_block = malloc (pool->block_length * item_size);
        g_ptr_array_add (pool->blocks, new_block);
        pool->last_block_items = 0;
    }
    //insert item in the last block
    void* last_block = g_ptr_array_index (pool->blocks, pool->blocks->len - 1);
    void* item_position = (char*)last_block + (pool->last_block_items * item_size);
    pool->last_block_items += 1;
    return item_position;
}


int pool_free(pool_t* pool){
    for(unsigned int i = 0; i < pool->blocks->len; i++){
        void* block = g_ptr_array_index (pool->blocks, i);
        free (block);
    }
    g_ptr_array_free (pool->blocks, TRUE);
    free (pool);
    return 0;
}