// Copyright (C) 2016-2019 Semtech (International) AG. All rights reserved.
// Copyright (C) 2014-2016 IBM Corporation. All rights reserved.
//
// This file is subject to the terms and conditions defined in file 'LICENSE',
// which is part of this source code package.

#ifndef _hal_hpp_
#define _hal_hpp_

#ifdef HAL_IMPL_INC
#include HAL_IMPL_INC
#endif

/*
 * initialize hardware (IO, SPI, TIMER, IRQ).
 */
void hal_init (void* bootarg);

/*
 * set watchdog counter (in 2s units)
 */
void hal_watchcount (int cnt);

/*
 * drive radio RX/TX pins (0=rx, 1=tx, -1=off [initial]).
 */
void hal_pin_rxtx (s1_t val);

/*
 * control radio RST pin (0=low, 1=high, 2=floating)
 */
void hal_pin_rst (u1_t val);

/*
 * set DIO0/1/2 interrupt mask
 */
#define HAL_IRQMASK_DIO0 (1<<0)
#define HAL_IRQMASK_DIO1 (1<<1)
#define HAL_IRQMASK_DIO2 (1<<2)
void hal_irqmask_set (int mask);

/*
 * drive radio NSS pin (on=low, off=high).
 */
void hal_spi_select (int on);

/*
 * perform 8-bit SPI transaction with radio.
 *   - write given byte 'outval'
 *   - read byte and return value
 */
u1_t hal_spi (u1_t outval);

/*
 * disable all CPU interrupts.
 *   - might be invoked nested
 *   - will be followed by matching call to hal_enableIRQs()
 */
void hal_disableIRQs (void);

/*
 * enable CPU interrupts.
 */
void hal_enableIRQs (void);

/*
 * put system and CPU in low-power mode, sleep until target time / interrupt.
 *   - return 0 if target time is close
 *   - otherwise sleep until target time / interrupt and return non-zero
 */
#define HAL_SLEEP_EXACT		0
#define HAL_SLEEP_APPROX	1
#define HAL_SLEEP_FOREVER	2
u1_t hal_sleep (u1_t type, u4_t targettime);

/*
 * disable deeper sleep modes.
 *   - might be invoked nested
 *   - will be followed by matching call to hal_enableSleep()
 */
#define HAL_SLEEP_MEDIUM	0
#define HAL_SLEEP_DEEP		1
void hal_disableSleep (u1_t kind);

/*
 * enable deeper sleep modes.
 */
void hal_enableSleep (u1_t kind);

/*
 * return 32-bit system time in ticks.
 */
u4_t hal_ticks (void);

/*
 * return 64-bit system time in ticks.
 */
u8_t hal_xticks (void);

/*
 * return subticks (1/1024th tick)
 */
s2_t hal_subticks (void);

/*
 * busy-wait until specified timestamp (in ticks) is reached.
 */
void hal_waitUntil (u4_t time);

/*
 * get current battery level
 */
u1_t hal_getBattLevel (void);

/*
 * set current battery level
 */
void hal_setBattLevel (u1_t level);

/*
 * perform fatal failure action.
 *   - called by assertions
 *   - action could be HALT or reboot
 */
void hal_failed (void);

#ifdef CFG_powerstats
/*
 * ***EXPERIMENTAL***
 *
 * retrieve HAL runtime statistics
 */
typedef struct {
    uint32_t run_ms;			// running
    uint32_t sleep1_ms;			// normal sleep
    uint32_t sleep2_ms;			// medium sleep
    uint32_t sleep3_s;			// deep sleep
    uint32_t rx_ms, tx_ms;		// rx/tx time
} hal_statistics;
void hal_stats_get (hal_statistics* stats);
void hal_stats_consume (hal_statistics* stats);
#endif

#ifdef CFG_DEBUG

void hal_debug_str (const char* str);
void hal_debug_led (int val);

#endif

typedef struct {
    uint32_t blversion;
    uint32_t version;
    uint32_t crc;
    uint32_t flashsz;
} hal_fwi;

void hal_fwinfo (hal_fwi* fwi);

u1_t* hal_joineui (void);
u1_t* hal_deveui (void);
u1_t* hal_nwkkey (void);
u1_t* hal_appkey (void);
u1_t* hal_serial (void);
u4_t  hal_region (void);
u4_t  hal_hwid (void);
u4_t  hal_unique (void);

void hal_reboot (void);

#endif // _hal_hpp_
