#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif


static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x31e3170f, "module_put" },
	{ 0x585db2cc, "try_module_get" },
	{ 0x92997ed8, "_printk" },
	{ 0xde80cd09, "ioremap" },
	{ 0x425364b1, "__register_chrdev" },
	{ 0xb19b445, "ioread8" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x9bdbb0da, "__pci_register_driver" },
	{ 0xdf1ac593, "pci_unregister_driver" },
	{ 0x541a6db8, "module_layout" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("pci:v000010ECd0000C821sv*sd*bc*sc*i*");

MODULE_INFO(srcversion, "ADEF44726D3C76141D46F0B");
