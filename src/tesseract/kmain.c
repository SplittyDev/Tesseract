#include <system/typedef.h>
#include <system/system.h>
#include <io/terminal.h>
#include <hardware/gdt.h>
#include <hardware/idt.h>
#include <fs/fat/ff.h>

void init (void) {
  IRQ_OFF;
  init_terminal ();
  init_gdt ();
  init_pic ();
  init_idt ();
  IRQ_ON;
  printf ("Tesseract booted.\n");
  main ();
  while (true) {
  }
}

void main (void) {
  FATFS   fs;
  FIL     file;
  FRESULT fres;

  printf ("Mounting partition... ");
  fres = f_mount (&fs, "", 0);
  if (fres == FR_OK) printf ("OK\n");
  else printf ("FAIL\n");

  printf ("Creating file: test.txt... ");
  fres = f_open (&file, "test.txt", FA_WRITE | FA_CREATE_ALWAYS);
  if (fres == FR_OK) {
    printf ("OK\n");
    uint32_t bw;
    f_write (&file, "Test\r\n", 6, &bw);
    f_close (&file);
  }
  else printf ("FAIL\n");
}
