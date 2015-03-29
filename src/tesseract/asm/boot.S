.section multiboot
#define MB_ALIGN    1 << 0
#define MB_MEMINFO  1 << 1
#define MB_MAGIC    0x1BADB002
#define MB_FLAGS    MB_ALIGN | MB_MEMINFO
#define MB_CHECKSUM -(MB_MAGIC + MB_FLAGS)

.align 4
.int  MB_MAGIC
.int  MB_FLAGS
.int  MB_CHECKSUM

# Vesa
#.int  0x00000000
#.int  0x00000000
#.int  0x00000000
#.int  0x00000000
#.int  0x00000000
#.int  0x00000000
#.int  0
#.int  0
#.int  24

.section .text
.extern init
.global _start

_start:
  mov $stack_top, %esp
  cli
  call init
  jmp _stop

_stop:
  cli
  hlt
  jmp _stop

.section .bss
.space 8192
stack_top:
