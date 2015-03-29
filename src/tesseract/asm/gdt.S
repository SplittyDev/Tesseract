.global gdt_flush
.extern gdt_ptr

gdt_flush:
  lgdt (gdt_ptr)
  mov $0x10, %ax
  mov %ax, %ds
  mov %ax, %es
  mov %ax, %fs
  mov %ax, %gs
  mov %ax, %ss
  jmp $0x08, $gdt_flush2

gdt_flush2:
  ret
