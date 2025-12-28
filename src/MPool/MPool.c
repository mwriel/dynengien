#include "MPool.h"
#include <stdalign.h>
#include <stdatomic.h>
#include <stddef.h>
#include <stdlib.h>

#include <stdint.h>
#include <stdbool.h>

typedef struct block block ;
typedef struct block{
    bool used;
    block* next;
} block;

typedef struct vblock vblock ;
typedef struct vblock{
    bool used;
    size_t size;
    vblock* next;
} vblock;
typedef struct ArenaPool {
    //start of the pool pointer
    char * pool;
    //total size of the pool used to calculate space aviable from specific pointer
    size_t psize;

    // current aviable addr to write from
    // INITIALIZE as pool + psize to start from the top and last aviable space should be after pool
    // OPTIONALY can be initialize as pool if you want to start from the bottom
    char* aviable;
}ArenaPool ;//if the ArenaPool is part of the pool it serves as header, not recomended if it will be reused
//if on stack it is normal behavior for reusing, if used as header do not free, start from whatever whas the original start after header

typedef struct SlabPool {
    char* pool;
    size_t psize;
    size_t bsize;
    block* next; // if null there are no aviable blocks;

}SlabPool ;
typedef struct RingBuffer {
    //need to study how a ring buffer works
    char* pool;
    size_t psize;
}RingBuffer ;
typedef struct StackPool {
    //not sure but this is a normal pool with variable sized blocks but fifo
    char* pool;
    size_t psize;
    //FIFO HEAD
    vblock* head;
} StackPool ;

typedef struct Pool{
    //same as stack pool just used in diferent functions
    char* pool;
    size_t psize;
    
    vblock* head;
}Pool ;







Pool* createPool(size_t size, size_t align){
    if (align<1) {
        //default align
        align=alignof(max_align_t);
    }
    size_t poolsize=ALIGN_UP(sizeof(Pool),align);
    size_t total=poolsize;
    total+= ALIGN_UP(size,align);
    
    size_t node_size = ALIGN_UP(sizeof(vblock), align);
    //aproximate how many nodes one might need, later could be a better aproximation buy for normal pools with no defined block size this is all i came up for now
    total+= ALIGN_UP(node_size*(int)sizeof(int)/size,align);

    char* pool;
    pool = (char*) malloc(total);
    if (pool==NULL) {
        //TODO make a log for the error
        return NULL;
    }

    Pool * return_pool=(Pool*)pool;
    return_pool->psize=total;
    return_pool->pool=pool;
    return_pool->head=(vblock* )(pool + poolsize);
    return_pool->head->next=NULL;
    return_pool->head->used=false;
    return_pool->head->size=total-poolsize-node_size;
    return return_pool;


}

size_t calculate_pool_size(int groups_count, ObjGroup groups[],size_t align) {
    
    size_t total = ALIGN_UP(sizeof(Pool), align);  // Espacio para la estructura del pool
    
    // Calcular espacio para nodos (1 por objeto)
    size_t node_size = ALIGN_UP(sizeof(vblock), align);
    
    // Calcular espacio para los objetos
    for (int i = 0; i < groups_count; i++) {
        size_t aligned_size = ALIGN_UP(groups[i].obj_size, align);
        total += aligned_size * groups[i].obj_count;
        
        total += node_size*groups[i].obj_count;
    }
    //total += node_size * groups_count*obj_count;  // Espacio para todos los nodos

    return total;
}
//while the other pool types are done this function should be good for testing
Pool* createExplicitPool(size_t align,int groups_count, ObjGroup groups[]){
    if (align<1) {
        //default align
        align=alignof(max_align_t);
    }
    size_t poolsize=ALIGN_UP(sizeof(Pool),align);
    size_t total=poolsize;
    
    size_t node_size = ALIGN_UP(sizeof(vblock), align);
    //using explicit function
    total=calculate_pool_size(groups_count,groups,align);

    char* pool;
    pool = (char*) malloc(total);

    Pool * return_pool=(Pool*)pool;
    return_pool->psize=total;
    return_pool->pool=pool;
    return_pool->head=(vblock* )(pool + poolsize);
    return_pool->head->next=NULL;
    return_pool->head->used=false;
    return_pool->head->size=total-poolsize-node_size;


}