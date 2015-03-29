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

.global gdt_flush
gdt_flush:
  mov $0x10, %ax
  mov %ax, %ds
  mov %ax, %es
  mov %ax, %fs
  mov %ax, %gs
  mov %ax, %ss
  jmp $0x8, $gdt_flush2
gdt_flush2:
  ret

.extern idt_handle_general
.global isr_wrapper

isr_wrapper:
  pusha
  push %ds
  push %es
  push %fs
  push %gs
  mov $0x10, %ax
  mov %ax, %ds
  mov %ax, %es
  mov %ax, %fs
  mov %ax, %gs
  mov %esp, %eax
  push %eax
  mov $idt_handle_general, %eax
  call *%eax
  pop %eax
  pop %gs
  pop %fs
  pop %es
  pop %ds
  popa
  add $8, %esp
  iret

.macro isr num
  .global isr\num
  isr\num:
    cli
		pushl $0
		pushl $\num
		jmp isr_wrapper
.endm

.macro exc num
	.global exc\num
	exc\num:
    cli
		pushl $\num
		jmp isr_wrapper
.endm

.macro irq dummy num
  .global irq\dummy
  irq\dummy:
    cli
    pushl $0
    pushl $\num
    jmp isr_wrapper
.endm

# Exceptions
isr 0
isr 1
isr 2
isr 3
isr 4
isr 5
isr 6
isr 7
exc 8
isr 9
exc 10
exc 11
exc 12
exc 13
exc 14
isr 15
isr 16
isr 17
isr 18
isr 19
isr 20
isr 21
isr 22
isr 23
isr 24
isr 25
isr 26
isr 27
isr 28
isr 29
isr 30
isr 31

# IRQs
irq 0   32
irq 1   33
irq 2   34
irq 3   35
irq 4   36
irq 5   37
irq 6   38
irq 7   39
irq 8   40
irq 9   41
irq 10  42
irq 11  43
irq 12  44
irq 13  45
irq 14  46
irq 15  47

.section .bss
.space 8192
stack_top:
