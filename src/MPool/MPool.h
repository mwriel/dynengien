#ifndef MPOOL_H
#define MPOOL_H

#include <stddef.h>
#define ALIGN_UP(req_size,align) ((req_size + align-1) & ~(align-1))

typedef struct MPool MPool ;

typedef struct ArenaPool ArenaPool ;
typedef struct SlabPool SlabPool ;
typedef struct RingBuffer RingBuffer ;
typedef struct StackPool StackPool ;
typedef struct Pool Pool ;

//public utils
typedef struct {
    size_t obj_size;    // Tamaño de cada objeto
    size_t obj_count;   // Cantidad de objetos
} ObjGroup;



#endif