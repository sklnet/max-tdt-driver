# Tuxbox drivers Makefile
# there are only three targets
#
# make all     - builds all modules
# make install - installs the modules
# make clean   - deletes modules recursively
#
# note that "clean" only works in the current
# directory while "all" and "install" will
# execute from the top dir.

ifeq ($(KERNELRELEASE),)
DRIVER_TOPDIR:=$(shell pwd)
include $(DRIVER_TOPDIR)/kernel.make
else
CCFLAGSY += -D__TDT__ -D__LINUX__ -D__SH4__ -D__KERNEL__ -DMODULE -DEXPORT_SYMTAB

CONFIGFILE := $(DRIVER_TOPDIR)/.config

include $(CONFIGFILE)

ifdef OCTAGON1008
CCFLAGSY+=-DOCTAGON1008
endif

ifdef UFS910
CCFLAGSY += -DUFS910
endif

ifdef CUBEREVO
CCFLAGSY += -DCUBEREVO
endif
ifdef CUBEREVO_MINI
CCFLAGSY += -DCUBEREVO_MINI
endif
ifdef CUBEREVO_MINI2
CCFLAGSY += -DCUBEREVO_MINI2
endif
ifdef CUBEREVO_250HD
CCFLAGSY += -DCUBEREVO_250HD
endif
ifdef CUBEREVO_2000HD
CCFLAGSY += -DCUBEREVO_2000HD
endif
ifdef CUBEREVO_9500HD
CCFLAGSY += -DCUBEREVO_9500HD
endif
ifdef CUBEREVO_MINI_FTA
CCFLAGSY += -DCUBEREVO_MINI_FTA
endif
ifdef TF7700
CCFLAGSY += -DTF7700
endif
ifdef HL101
CCFLAGSY += -DHL101
endif
ifdef VIP1_V2
CCFLAGSY += -DVIP1_V2
endif
ifdef VIP2_V1
CCFLAGSY += -DVIP2_V1
endif
ifdef UFS922
CCFLAGSY+=-DUFS922
endif
ifdef UFC960
CCFLAGSY+=-DUFC960
endif
ifdef UFS912
CCFLAGSY+=-DUFS912
endif
ifdef UFS913
CCFLAGSY+=-DUFS913
endif
ifdef SPARK
CCFLAGSY+=-DSPARK
endif
ifdef SPARK7162
CCFLAGSY+=-DSPARK7162
endif
ifdef FORTIS_HDBOX
CCFLAGSY += -DFORTIS_HDBOX
endif
ifdef ATEVIO7500
CCFLAGSY += -DATEVIO7500
endif
ifdef HS7810A
CCFLAGSY += -DHS7810A
endif
ifdef HS7110
CCFLAGSY += -DHS7110
endif
ifdef ATEMIO520
CCFLAGSY += -DATEMIO520
endif
ifdef ATEMIO530
CCFLAGSY += -DATEMIO530
endif
ifdef HOMECAST5101
CCFLAGSY += -DHOMECAST5101
endif
ifdef ADB_BOX
CCFLAGSY += -DADB_BOX
endif
ifdef IPBOX9900
CCFLAGSY += -DIPBOX9900
endif
ifdef IPBOX99
CCFLAGSY += -DIPBOX99
endif
ifdef IPBOX55
CCFLAGSY += -DIPBOX55
endif
ifdef VITAMIN_HD5000
CCFLAGSY += -DVITAMIN_HD5000
endif
ifneq (,$(findstring 2.6.3,$(KERNELVERSION)))
ccflags-y += $(CCFLAGSY)
else
CFLAGS += $(CCFLAGSY)
endif

export CCFLAGSY

obj-y := avs/
obj-y += multicom/
obj-y += stgfb/
obj-y += player2/
obj-y += boxtype/
obj-y += simu_button/
obj-y += e2_proc/
obj-y += frontends/
obj-y += frontcontroller/
#obj-y += wireless/

ifeq (,$(wildcard $(DRIVER_TOPDIR)/pti_np ))
obj-y += pti/
else
obj-y += pti_np/
endif

obj-y += compcache/
obj-y += bpamem/

ifdef HL101
obj-y += smartcard/
endif

ifdef ADB_BOX
obj-y += smartcard/
obj-y += adb_box_fan/
obj-y += cec_adb_box/
obj-y += dvbt/as102/
endif

ifndef VIP2_V1
ifndef SPARK
ifndef SPARK7162
obj-y += cic/
endif
endif
endif

# Button and Led Driver only needed for old 14W Kathrein Ufs 910 boxes
ifdef UFS910
obj-y += button/
obj-y += led/
endif

ifdef UFS922
obj-y += ufs922_fan/
endif

ifdef HOMECAST5101
obj-y += button_hs5101/
obj-y += player2/linux/drivers/media/dvb/stm/dvb
endif

ifdef UFS912
obj-y += cec/
obj-y += cpu_frequ/
endif

ifdef UFS913
obj-y += cec/
obj-y += cpu_frequ/
endif

ifdef ATEVIO7500
obj-y	+= cec/
obj-y	+= smartcard/
obj-y	+= cpu_frequ/
obj-y	+= sata_switch/
endif

ifdef HS7810A
obj-y += cec/
obj-y += smartcard/
obj-y += cpu_frequ/
endif

ifdef HS7110
obj-y += cec/
obj-y += smartcard/
obj-y += cpu_frequ/
endif

ifdef ATEMIO520
obj-y	+= cec/
obj-y	+= smartcard/
obj-y	+= cpu_frequ/
endif

ifdef ATEMIO530
obj-y	+= cec/
obj-y	+= smartcard/
obj-y	+= cpu_frequ/
endif

ifdef SPARK
obj-y += cec/
obj-y += smartcard/
obj-y += cpu_frequ/
endif

ifdef SPARK7162
obj-y += smartcard/
obj-y += i2c_spi/
obj-y += cpu_frequ/
obj-y += cec/
endif

ifdef OCTAGON1008
obj-y += smartcard/
endif

ifdef FORTIS_HDBOX
obj-y += smartcard/
endif

ifdef IPBOX9900
obj-y += siinfo/
obj-y += rmu/
obj-y += ipbox99xx_fan/
obj-y += smartcard/
obj-y += cpu_frequ/
endif

ifdef IPBOX99
obj-y += siinfo/
obj-y += ipbox99xx_fan/
obj-y += smartcard/
obj-y += cpu_frequ/
endif

ifdef IPBOX55
obj-y += siinfo/
obj-y += smartcard/
obj-y += cpu_frequ/
endif

ifdef CUBEREVO
obj-y += smartcard/
obj-y += cpu_frequ/
endif
ifdef CUBEREVO_MINI2
obj-y += smartcard/
endif
ifdef CUBEREVO_250HD
obj-y += smartcard/
endif
ifdef CUBEREVO_2000HD
obj-y += smartcard/
endif
ifdef CUBEREVO_9500HD
obj-y += smartcard/
endif
ifdef VITAMIN_HD5000
obj-y	+= cec/
obj-y	+= smartcard/
obj-y	+= cpu_frequ/
endif

endif
