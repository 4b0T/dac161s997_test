#pragma once

#include <stdint.h>

void sysclk_cfg(void);

static inline uint32_t sysclk_get_mclk_hz(void) { return 8000000u; }
static inline uint32_t sysclk_get_smclk_hz(void) { return 8000000u; }
static inline uint32_t sysclk_get_aclk_hz(void) { return 32768u; }
