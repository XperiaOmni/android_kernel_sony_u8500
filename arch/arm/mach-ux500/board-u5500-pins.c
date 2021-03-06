/*
 * Copyright (C) ST-Ericsson SA 2011
 *
 * License terms: GNU General Public License (GPL) version 2
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/gpio/nomadik.h>
#include <plat/pincfg.h>

#include "pins-db5500.h"
#include "pins.h"

static pin_cfg_t u5500_pins_default[] = {
	GPIO77_ACCTX_ON		| PIN_SLPM_ALTFUNC,
	GPIO79_ACCSIM_Clk	| PIN_SLPM_ALTFUNC,
	GPIO80_ACCSIM_Da	| PIN_SLPM_ALTFUNC,
	GPIO81_ACCSIM_Reset	| PIN_SLPM_ALTFUNC,
	GPIO82_ACCSIM_DDir	| PIN_SLPM_ALTFUNC,

	/* MSP */
	GPIO32_MSP0_TCK		| PIN_INPUT_PULLDOWN,
	GPIO33_MSP0_TFS		| PIN_INPUT_PULLDOWN,
	GPIO34_MSP0_TXD		| PIN_INPUT_PULLDOWN,
	GPIO35_MSP0_RXD		| PIN_INPUT_PULLDOWN,
	GPIO96_MSP1_TCK		| PIN_INPUT_PULLDOWN,
	GPIO97_MSP1_TFS		| PIN_INPUT_PULLDOWN,
	GPIO98_MSP1_TXD		| PIN_INPUT_PULLDOWN,
	GPIO99_MSP1_RXD		| PIN_INPUT_PULLDOWN,
	GPIO220_MSP2_TCK	| PIN_OUTPUT_LOW,
	GPIO221_MSP2_TFS	| PIN_OUTPUT_LOW,
	GPIO222_MSP2_TXD	| PIN_OUTPUT_LOW,

	/* DISPLAY_ENABLE */
	GPIO226_GPIO        | PIN_OUTPUT_HIGH,

	/* Backlight Enable */
	GPIO224_GPIO		| PIN_OUTPUT_HIGH,

	/* UART0 */
	GPIO28_U0_TXD           | PIN_OUTPUT_HIGH,
	GPIO29_U0_RXD           | PIN_INPUT_PULLUP,

	/* UART3 */
	GPIO165_U3_RXD		| PIN_INPUT_PULLUP,
	GPIO166_U3_TXD		| PIN_OUTPUT_HIGH | PIN_LOWEMI_ENABLED,
	GPIO167_U3_RTSn		| PIN_OUTPUT_HIGH | PIN_LOWEMI_ENABLED,
	GPIO168_U3_CTSn		| PIN_INPUT_PULLUP,

	/* AB5500 */
	GPIO78_IRQn             | PIN_SLPM_NOCHANGE,
	GPIO100_I2C0_SCL        | PIN_INPUT_PULLUP | PIN_SLPM_NOCHANGE,
	GPIO101_I2C0_SDA        | PIN_SLPM_NOCHANGE,

	/* TOUCH_IRQ */
	GPIO179_GPIO	| PIN_INPUT_PULLUP,

	/* SD-CARD detect/levelshifter pins */
	GPIO180_GPIO		| PIN_INPUT_NOPULL,	/* SD_CARD_DETn */
	GPIO227_GPIO		| PIN_OUTPUT_LOW,	/* SD_CARD_CTRL */
	GPIO185_GPIO		| PIN_OUTPUT_LOW,	/* SD_CARD_VSEL */

	/* Display & HDMI HW sync */
	GPIO204_LCD_VSI1	| PIN_INPUT_PULLUP,

	/* TVOUT (connected, but unused) */
	GPIO205_GPIO		| PIN_OUTPUT_LOW,
	GPIO206_GPIO		| PIN_OUTPUT_LOW,
	GPIO207_GPIO		| PIN_OUTPUT_LOW,
	GPIO208_GPIO		| PIN_OUTPUT_LOW,
	GPIO209_GPIO		| PIN_INPUT_PULLDOWN,

	/* Display (connected to NT35560 / TE, but unused) */
	GPIO211_GPIO		| PIN_INPUT_PULLDOWN,

	/* Camera & MMIO XshutDown*/
	GPIO1_GPIO		| PIN_OUTPUT_LOW,
	GPIO2_GPIO		| PIN_OUTPUT_LOW,

	/* USB chip select */
	GPIO76_GPIO		| PIN_OUTPUT_LOW,

	GPIO202_ACCU0_RXD	| PIN_INPUT_PULLUP | PIN_SLPM_NOCHANGE,
	GPIO203_ACCU0_TXD	| PIN_OUTPUT_HIGH | PIN_SLPM_NOCHANGE,

	/* Board Id Identification B5500 or S5500 */
	GPIO0_GPIO		| PIN_INPUT_PULLUP,
	GPIO214_GPIO		| PIN_OUTPUT_LOW,	/* SW_CRASH_INDICATOR */

	/* Touchscreen chip select */
	GPIO186_GPIO		| PIN_OUTPUT_HIGH | PIN_LOWEMI_ENABLED,

	GPIO133_GPIO		| PIN_OUTPUT_LOW,	/* DUALSIMRESETn */
	GPIO187_GPIO		| PIN_OUTPUT_HIGH,	/* Dual SIM CS */

	GPIO163_GPIO		| PIN_INPUT_PULLUP,	/* SERVICEn */

	GPIO223_GPIO		| PIN_INPUT_PULLDOWN,	/* HDMI_INT */
	GPIO225_GPIO		| PIN_OUTPUT_LOW,	/* HDMI_ENABLE */
};

static UX500_PINS(db5500_kp_pins,
	/* Keypad */
	GPIO128_KP_I0	| PIN_INPUT_PULLUP | PIN_SLPM_INPUT_PULLUP,
	GPIO130_KP_I1	| PIN_INPUT_PULLUP | PIN_SLPM_INPUT_PULLUP,
	GPIO132_KP_I2	| PIN_INPUT_PULLUP | PIN_SLPM_INPUT_PULLUP,
	GPIO134_KP_I3	| PIN_INPUT_PULLUP | PIN_SLPM_INPUT_PULLUP,
	GPIO137_KP_O4	| PIN_INPUT_PULLUP | PIN_SLPM_OUTPUT_LOW,
	GPIO139_KP_O5	| PIN_INPUT_PULLUP | PIN_SLPM_OUTPUT_LOW,
);

static UX500_PINS(db5500_pins_sdi0,
	/* SDI0 (eMMC) */
	GPIO5_MC0_DAT0		| PIN_INPUT_PULLUP,
	GPIO6_MC0_DAT1		| PIN_INPUT_PULLUP,
	GPIO7_MC0_DAT2		| PIN_INPUT_PULLUP,
	GPIO8_MC0_DAT3		| PIN_INPUT_PULLUP,
	GPIO9_MC0_DAT4		| PIN_INPUT_PULLUP,
	GPIO10_MC0_DAT5		| PIN_INPUT_PULLUP,
	GPIO11_MC0_DAT6		| PIN_INPUT_PULLUP,
	GPIO12_MC0_DAT7		| PIN_INPUT_PULLUP,
	GPIO13_MC0_CMD		| PIN_INPUT_PULLUP,
	GPIO14_MC0_CLK		| PIN_OUTPUT_LOW,
);

static UX500_PINS(db5500_pins_sdi1,
	/* SDI1 (SD-CARD) */
	GPIO191_MC1_DAT0	| PIN_INPUT_PULLUP,
	GPIO192_MC1_DAT1	| PIN_INPUT_PULLUP,
	GPIO193_MC1_DAT2	| PIN_INPUT_PULLUP,
	GPIO194_MC1_DAT3	| PIN_INPUT_PULLUP,
	GPIO195_MC1_CLK		| PIN_OUTPUT_LOW,
	GPIO196_MC1_CMD		| PIN_INPUT_PULLUP,
	GPIO197_MC1_CMDDIR	| PIN_OUTPUT_HIGH,
	GPIO198_MC1_FBCLK	| PIN_INPUT_PULLDOWN,
	GPIO199_MC1_DAT0DIR	| PIN_OUTPUT_HIGH,
);

static UX500_PINS(db5500_pins_sdi2,
	/* SDI2 (eMMC) */
	GPIO16_MC2_CMD		| PIN_INPUT_PULLUP,
	GPIO17_MC2_CLK		| PIN_OUTPUT_LOW,
	GPIO23_MC2_DAT0		| PIN_INPUT_PULLUP,
	GPIO19_MC2_DAT1		| PIN_INPUT_PULLUP,
	GPIO24_MC2_DAT2		| PIN_INPUT_PULLUP,
	GPIO20_MC2_DAT3		| PIN_INPUT_PULLUP,
	GPIO25_MC2_DAT4		| PIN_INPUT_PULLUP,
	GPIO21_MC2_DAT5		| PIN_INPUT_PULLUP,
	GPIO26_MC2_DAT6		| PIN_INPUT_PULLUP,
	GPIO22_MC2_DAT7		| PIN_INPUT_PULLUP
);

static UX500_PINS(db5500_pins_sdi3,
	/* SDI3 (SDIO) */
	GPIO171_MC3_DAT0	| PIN_INPUT_PULLUP | PIN_LOWEMI_ENABLED,
	GPIO172_MC3_DAT1	| PIN_INPUT_PULLUP | PIN_LOWEMI_ENABLED,
	GPIO173_MC3_DAT2	| PIN_INPUT_PULLUP | PIN_LOWEMI_ENABLED,
	GPIO174_MC3_DAT3	| PIN_INPUT_PULLUP | PIN_LOWEMI_ENABLED,
	GPIO175_MC3_CMD		| PIN_INPUT_PULLUP | PIN_LOWEMI_ENABLED,
	GPIO176_MC3_CLK		| PIN_OUTPUT_LOW,
);

static UX500_PINS(u5500_pins_i2c1,
	GPIO3_I2C1_SCL		| PIN_INPUT_NOPULL | PIN_LOWEMI_ENABLED,
	GPIO4_I2C1_SDA		| PIN_INPUT_NOPULL | PIN_LOWEMI_ENABLED,
);

static UX500_PINS(u5500_pins_i2c2,
	GPIO218_I2C2_SCL	| PIN_INPUT_NOPULL | PIN_LOWEMI_ENABLED,
	GPIO219_I2C2_SDA	| PIN_INPUT_NOPULL | PIN_LOWEMI_ENABLED,
);

static UX500_PINS(u5500_pins_i2c3,
	GPIO177_I2C3_SCL	| PIN_INPUT_NOPULL | PIN_LOWEMI_ENABLED,
	GPIO178_I2C3_SDA	| PIN_INPUT_NOPULL | PIN_LOWEMI_ENABLED,
);

static UX500_PINS(u5500_pins_spi3,
	GPIO188_SPI3_RXD	| PIN_INPUT_PULLUP,
	GPIO189_SPI3_TXD	| PIN_OUTPUT_LOW | PIN_LOWEMI_ENABLED,
	GPIO190_SPI3_CLK	| PIN_OUTPUT_LOW | PIN_LOWEMI_ENABLED,
);

/* USB */
static UX500_PINS(u5500_pins_usb,
	GPIO74_USB_NXT 	| PIN_INPUT_NOPULL	| PIN_SLPM_INPUT_PULLDOWN,
	GPIO72_USB_STP	| PIN_OUTPUT_HIGH 	| PIN_SLPM_OUTPUT_HIGH,
	GPIO75_USB_XCLK	| PIN_INPUT_NOPULL	| PIN_SLPM_INPUT_PULLDOWN,
	GPIO73_USB_DIR 	| PIN_INPUT_NOPULL	| PIN_SLPM_INPUT_PULLDOWN,
	GPIO71_USB_DAT7	| PIN_INPUT_NOPULL	| PIN_SLPM_INPUT_PULLDOWN,
	GPIO70_USB_DAT6	| PIN_INPUT_NOPULL	| PIN_SLPM_INPUT_PULLDOWN,
	GPIO69_USB_DAT5	| PIN_INPUT_NOPULL	| PIN_SLPM_INPUT_PULLDOWN,
	GPIO68_USB_DAT4	| PIN_INPUT_NOPULL	| PIN_SLPM_INPUT_PULLDOWN,
	GPIO67_USB_DAT3	| PIN_INPUT_NOPULL	| PIN_SLPM_INPUT_PULLDOWN,
	GPIO66_USB_DAT2	| PIN_INPUT_NOPULL	| PIN_SLPM_INPUT_PULLDOWN,
	GPIO65_USB_DAT1	| PIN_INPUT_NOPULL	| PIN_SLPM_INPUT_PULLDOWN,
	GPIO64_USB_DAT0	| PIN_INPUT_NOPULL	| PIN_SLPM_INPUT_PULLDOWN,
);

static struct ux500_pin_lookup u5500_pins[] = {
	PIN_LOOKUP("nmk-i2c.1", &u5500_pins_i2c1),
	PIN_LOOKUP("nmk-i2c.2", &u5500_pins_i2c2),
	PIN_LOOKUP("nmk-i2c.3", &u5500_pins_i2c3),
	PIN_LOOKUP("spi3", &u5500_pins_spi3),
	PIN_LOOKUP("db5500_kp", &db5500_kp_pins),
	PIN_LOOKUP("ab5500-usb.0", &u5500_pins_usb),
	PIN_LOOKUP("sdi0", &db5500_pins_sdi0),
	PIN_LOOKUP("sdi1", &db5500_pins_sdi1),
	PIN_LOOKUP("sdi2", &db5500_pins_sdi2),
	PIN_LOOKUP("sdi3", &db5500_pins_sdi3),
};

void __init u5500_pins_init(void)
{
	nmk_config_pins(u5500_pins_default, ARRAY_SIZE(u5500_pins_default));
	ux500_pins_add(u5500_pins, ARRAY_SIZE(u5500_pins));
}

/* Stub function to make board-ux500-cg2900.c compile within a U5500 configuration */
int pins_for_u9500(void)
{
	return 0;
}
