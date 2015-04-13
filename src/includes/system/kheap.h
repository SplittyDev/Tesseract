#ifndef __kheap__
#define __kheap__

#include <system/typedef.h>

typedef struct kheapblock {
  struct kheapblock *next;
  uint32_t           top;
  uint32_t           max;
  uintptr_t          size;
} kheapblock_t;

typedef struct kheap {
  kheapblock_t      *fblock;
  uint32_t           bsize;
} kheap_t;

void init_kheap (kheap_t *, uint32_t);
int kheap_addblock (kheap_t *, uintptr_t, uint32_t);
void *kheap_alloc (kheap_t *, uint32_t);
void kheap_free (kheap_t *, void *);

#endif
