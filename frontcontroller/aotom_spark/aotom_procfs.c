#include <linux/proc_fs.h>      /* proc fs */
#include <asm/uaccess.h>        /* copy_from_user */
#include <linux/time.h>
#include <linux/kernel.h>
#include "aotom_main.h"

/*
/proc/stb/fp/aotom_led", "w"
/proc/stb/fp/aotom_icon", "w"
*/
/*
 *  /proc/stb/fp
 *             |
 *             +--- aotom (w)
*/

extern int install_e2_procs(char *name, read_proc_t *read_proc, write_proc_t *write_proc, void *data);
extern int remove_e2_procs(char *name, read_proc_t *read_proc, write_proc_t *write_proc);

extern int aotomSetIcon(int which, int on);
extern int aotomSetLed(int which, int on);

// Proc for accessing quick control of aotom
// String format: fxy
// f is "l" (for led) or "i" (for icons)
// x is 0/1 and indicates if the led/icon must be off or on
// y is the led/icon number (between 0 and LASTLED-1 for leds; between 1 and 46, for icons, with y==46, all the icons are set)
static int aotom_write(struct file *file, const char __user *buf,
                           unsigned long count, void *data)
{
  char *page;
  int value;
  int ret = -ENOMEM;

  printk("%s(%ld, ", __FUNCTION__, count);

  page = (char *)__get_free_page(GFP_KERNEL);
  if (page)
  {
    ret = -EFAULT;
    if (copy_from_user(page, buf, count) == 0)
    {
      page[count] = 0;
      printk("%s", page);

      if (count>3) {
        value = (int)simple_strtol(page+2, NULL, 10);
        if (page[0] == 'l') {
          if (page[1] == '0') {
            if ((value>=0)&&(value<LASTLED)) aotomSetLed(value,0);
          }
          else if (page[1] == '1') {
            if ((value>=0)&&(value<LASTLED)) aotomSetLed(value,1);
          }
        }
        else if (page[0] == 'i') {
          if (page[1] == '0') {
            if ((value>=1)&&(value<=46)) aotomSetIcon(value,0);
          }
          else if (page[1] == '1') {
            if ((value>=1)&&(value<=46)) aotomSetIcon(value,1);
          }
        }
      }

      ret = count;
    }
    free_page((unsigned long)page);
  }
  printk(")\n");

  return ret;
}

struct fp_procs
{
  char *name;
  read_proc_t *read_proc;
  write_proc_t *write_proc;
} fp_procs[] =
{
  { "stb/fp/aotom", NULL, aotom_write },
};

void create_proc_fp(void)
{
  int i;

  for(i = 0; i < sizeof(fp_procs)/sizeof(fp_procs[0]); i++)
  {
    install_e2_procs(fp_procs[i].name, fp_procs[i].read_proc,
			fp_procs[i].write_proc, NULL);
  }
}

void remove_proc_fp(void)
{
  int i;

  for(i = sizeof(fp_procs)/sizeof(fp_procs[0]) - 1; i >= 0; i--)
  {
    remove_e2_procs(fp_procs[i].name, fp_procs[i].read_proc,
			fp_procs[i].write_proc);
  }
}

