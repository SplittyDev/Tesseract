.section multiboot
#define MB_ALIGN    1 << 0
#define MB_MEMINFO  1 << 1
#define MB_GRAPHICS 1 << 2
#define MB_MAGIC    0x1BADB002
#define MB_FLAGS    MB_ALIGN | MB_MEMINFO
#define MB_CHECKSUM -(MB_MAGIC + MB_FLAGS)

.align 4
.int  MB_MAGIC
.int  MB_FLAGS
.int  MB_CHECKSUM
.int  0x00000000  # load_addr
.int  0x00000000  # load_end_addr
.int  0x00000000  # bss_end_addr
.int  0x00000000  # entry_addr
.int  0x00000000  # mode (0 = LFB)
.int  0           # width
.int  0           # height
.int  32          # depth

.section .text
.extern init
.global _start

_start:
  mov $stack_top, %esp
  push %ebx
  call init

_stop:
  cli
  hlt
  jmp _stop

.global gdt_flush
gdt_flush:
  mov $0x10, %ax
  mov %ax, %ds
  mov %ax, %es
  mov %ax, %fs
  mov %ax, %gs
  mov %ax, %ss
  ljmp $0x8, $gdt_flush2
  ret
gdt_flush2:
  ret

.section .bss
.space 8192
stack_top:
