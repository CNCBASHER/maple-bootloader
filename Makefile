PROG=	dfu
SRCS=	usb.c usb_callbacks.c usb_descriptor.c main.c hardware.c dfu.c \
	usb_regs.c \
	usb_int.c \
	usb_init.c \
	usb_core.c \
	usb_mem.c

CFLAGS+=	-Istm32_lib

include ../../toolchain/mchck.mk
