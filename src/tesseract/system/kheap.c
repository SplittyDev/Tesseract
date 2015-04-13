#include <stdlib/stdio.h>
#include <system/kheap.h>
#include <system/typedef.h>

int init_kheap (kheap_t *heap, uint32_t bsize) {
  heap->fblock = 0;
  heap->bsize = bsize;
  return 1;
}

int kheap_addblock (kheap_t *heap, uintptr_t addr, uint32_t size) {
  kheapblock_t  *b;
  uint32_t       x;
  uint32_t      *stack;
  uint32_t       stacksz;
  uint32_t       slotres;

  b = (kheapblock_t *)addr;
  b->next = heap->fblock;
  heap->fblock = b;

  b->size = size;
  size = size - sizeof(kheapblock_t);
  b->max = size / (heap->bsize);
  stacksz = b->max * 4;

  uint32_t tmp = stacksz / heap->bsize;
  slotres = tmp * heap->bsize < stacksz ? tmp + 1 : tmp;
  b->top = slotres;

  stack = (uint32_t *)&b[1];
  for (x = slotres; x < b->max; ++x)
    stack[x] = x * heap->bsize;

  return 1;
}

void *kheap_alloc (kheap_t *heap, uint32_t size) {
  kheapblock_t  *b;
  uintptr_t      ptr;
  uint32_t      *stack;

  if (size > heap->bsize)
    return 0;

  for (b = heap->fblock; b; b = b->next) {
    if (b->top != b->max) {
      stack = (uint32_t *)&b[1];
      ptr = stack[b->top++];
      ptr = (uintptr_t)&b[1] + ptr;
      return (void *)ptr;
    }
  }

  return 0;
}

void kheap_free (kheap_t *heap, void *dest) {
  kheapblock_t  *b;
  uintptr_t      ptr;
  uint32_t      *stack;

  ptr = (uintptr_t)dest;
  for (b = heap->fblock; b; b = b->next) {
    if (ptr > (uintptr_t)b && ptr < ((uintptr_t)b + b->size))
      break;
  }

  if (!b)
    printf ("\n*** [FATAL] Heap corrupted!\n");
    return;

  stack = (uint32_t *)&b[1];

  stack[--b->top] = ptr - (uintptr_t)&b[1];
  return;
}
