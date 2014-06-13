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
 *             +--- aotom_led (w)
 *             |
 *             +--- aotom_icon (w)
*/

extern int install_e2_procs(char *name, read_proc_t *read_proc, write_proc_t *write_proc, void *data);
extern int remove_e2_procs(char *name, read_proc_t *read_proc, write_proc_t *write_proc);

extern int aotomSetIcon(int which, int on);
extern int aotomSetLed(int which, int on);

// Proc for activating main leds
// String format: xy
// x is 0/1 and indicates if the led must be off or on
// y is the led number (between 0 and LASTLED-1)
static int aotom_led_write(struct file *file, const char __user *buf,
                           unsigned long count, void *data)
{
  char *page;
  long led;
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
      led = simple_strtol(page, NULL, 10);
      if ((led>=0)&&(led<LASTLED)) {
        aotomSetLed((int)led,0);
      }
      else if ((led>=10)&&(led<(10+LASTLED))) {
        aotomSetLed((int)led-10,1);
      }
      ret = count;
    }
    free_page((unsigned long)page);
  }
  printk(")\n");

  return ret;
}

// Proc file for activating icons
// String format: xy
// x is 0/1 and indicates if the icon must be off or on
// y is the led number (between 1 and 46). If y==46, all the icons are set.
static int aotom_icon_write(struct file *file, const char __user *buf,
                           unsigned long count, void *data)
{
  char *page;
  long icon;
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

      icon = simple_strtol(page, NULL, 10);
      if ((icon>=1)&&(icon<=46)) {
        aotomSetIcon((int)icon,0);
      }
      else if ((icon>=101)&&(icon<=146)) {
        aotomSetIcon((int)icon-100,1);
      }
      ret = count;
    }
    free_page((unsigned long)page);
  }
  printk(")\n");

  return ret;
}


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
  { "stb/fp/aotom_led", NULL, aotom_led_write },
  { "stb/fp/aotom_icon", NULL, aotom_icon_write },
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

