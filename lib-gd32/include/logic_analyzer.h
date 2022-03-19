/**
 * @file logic_analyzer.h
 *
 */
/* Copyright (C) 2022 by Arjan van Vught mailto:info@gd32-dmx.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "gd32.h"

namespace logic_analyzer {

static void init() {
#if defined (LOGIC_ANALYZER)
# if defined (LOGIC_ANALYZER_CH0_GPIO_PINx)
	rcu_periph_clock_enable(LOGIC_ANALYZER_CH0_RCU_GPIOx);
#  if !defined (GD32F4XX)
	gpio_init(LOGIC_ANALYZER_CH0_GPIOx, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LOGIC_ANALYZER_CH0_GPIO_PINx);
#  else
	gpio_mode_set(LOGIC_ANALYZER_CH0_GPIOx, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LOGIC_ANALYZER_CH0_GPIO_PINx);
	gpio_output_options_set(LOGIC_ANALYZER_CH0_GPIOx, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LOGIC_ANALYZER_CH0_GPIO_PINx);
#  endif
# endif
# if defined (LOGIC_ANALYZER_CH1_GPIO_PINx)
	rcu_periph_clock_enable(LOGIC_ANALYZER_CH1_RCU_GPIOx);
#  if !defined (GD32F4XX)
	gpio_init(LOGIC_ANALYZER_CH1_GPIOx, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LOGIC_ANALYZER_CH1_GPIO_PINx);
#  else
	gpio_mode_set(LOGIC_ANALYZER_CH1_GPIOx, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LOGIC_ANALYZER_CH1_GPIO_PINx);
	gpio_output_options_set(LOGIC_ANALYZER_CH1_GPIOx, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LOGIC_ANALYZER_CH1_GPIO_PINx);
#  endif
# endif
# if defined (LOGIC_ANALYZER_CH2_GPIO_PINx)
	rcu_periph_clock_enable(LOGIC_ANALYZER_CH2_RCU_GPIOx);
#  if !defined (GD32F4XX)
	gpio_init(LOGIC_ANALYZER_CH2_GPIOx, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LOGIC_ANALYZER_CH2_GPIO_PINx);
#  else
	gpio_mode_set(LOGIC_ANALYZER_CH2_GPIOx, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LOGIC_ANALYZER_CH2_GPIO_PINx);
	gpio_output_options_set(LOGIC_ANALYZER_CH2_GPIOx, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LOGIC_ANALYZER_CH2_GPIO_PINx);
#  endif
# endif
# if defined (LOGIC_ANALYZER_CH3_GPIO_PINx)
	rcu_periph_clock_enable(LOGIC_ANALYZER_CH3_RCU_GPIOx);
#  if !defined (GD32F4XX)
	gpio_init(LOGIC_ANALYZER_CH3_GPIOx, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LOGIC_ANALYZER_CH3_GPIO_PINx);
#  else
	gpio_mode_set(LOGIC_ANALYZER_CH3_GPIOx, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LOGIC_ANALYZER_CH3_GPIO_PINx);
	gpio_output_options_set(LOGIC_ANALYZER_CH3_GPIOx, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LOGIC_ANALYZER_CH3_GPIO_PINx);
#  endif
# endif
# if defined (LOGIC_ANALYZER_CH4_GPIO_PINx)
	rcu_periph_clock_enable(LOGIC_ANALYZER_CH4_RCU_GPIOx);
#  if !defined (GD32F4XX)
	gpio_init(LOGIC_ANALYZER_CH4_GPIOx, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LOGIC_ANALYZER_CH4_GPIO_PINx);
#  else
	gpio_mode_set(LOGIC_ANALYZER_CH4_GPIOx, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LOGIC_ANALYZER_CH4_GPIO_PINx);
	gpio_output_options_set(LOGIC_ANALYZER_CH4_GPIOx, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LOGIC_ANALYZER_CH4_GPIO_PINx);
#  endif
# endif
# if defined (LOGIC_ANALYZER_CH5_GPIO_PINx)
	rcu_periph_clock_enable(LOGIC_ANALYZER_CH5_RCU_GPIOx);
#  if !defined (GD32F4XX)
	gpio_init(LOGIC_ANALYZER_CH5_GPIOx, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LOGIC_ANALYZER_CH5_GPIO_PINx);
#  else
	gpio_mode_set(LOGIC_ANALYZER_CH5_GPIOx, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LOGIC_ANALYZER_CH5_GPIO_PINx);
	gpio_output_options_set(LOGIC_ANALYZER_CH5_GPIOx, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LOGIC_ANALYZER_CH5_GPIO_PINx);
#  endif
# endif
# if defined (LOGIC_ANALYZER_CH6_GPIO_PINx)
	rcu_periph_clock_enable(LOGIC_ANALYZER_CH6_RCU_GPIOx);
#  if !defined (GD32F4XX)
	gpio_init(LOGIC_ANALYZER_CH6_GPIOx, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LOGIC_ANALYZER_CH6_GPIO_PINx);
#  else
	gpio_mode_set(LOGIC_ANALYZER_CH6_GPIOx, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LOGIC_ANALYZER_CH6_GPIO_PINx);
	gpio_output_options_set(LOGIC_ANALYZER_CH6_GPIOx, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LOGIC_ANALYZER_CH6_GPIO_PINx);
#  endif
# endif
# if defined (LOGIC_ANALYZER_CH7_GPIO_PINx)
	rcu_periph_clock_enable(LOGIC_ANALYZER_CH7_RCU_GPIOx);
#  if !defined (GD32F4XX)
	gpio_init(LOGIC_ANALYZER_CH7_GPIOx, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LOGIC_ANALYZER_CH7_GPIO_PINx);
#  else
	gpio_mode_set(LOGIC_ANALYZER_CH7_GPIOx, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LOGIC_ANALYZER_CH7_GPIO_PINx);
	gpio_output_options_set(LOGIC_ANALYZER_CH7_GPIOx, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LOGIC_ANALYZER_CH7_GPIO_PINx);
#  endif
# endif
#endif
}

static void ch0_clear() {
#if defined (LOGIC_ANALYZER_CH0_GPIO_PINx)
	GPIO_BC(LOGIC_ANALYZER_CH0_GPIOx) = LOGIC_ANALYZER_CH0_GPIO_PINx;
#endif
}

static void ch0_set() {
#if defined (LOGIC_ANALYZER_CH0_GPIO_PINx)
	GPIO_BOP(LOGIC_ANALYZER_CH0_GPIOx) = LOGIC_ANALYZER_CH0_GPIO_PINx;
#endif
}

static void ch1_clear() {
#if defined (LOGIC_ANALYZER_CH1_GPIO_PINx)
	GPIO_BC(LOGIC_ANALYZER_CH1_GPIOx) = LOGIC_ANALYZER_CH1_GPIO_PINx;
#endif
}

static void ch1_set() {
#if defined (LOGIC_ANALYZER_CH1_GPIO_PINx)
	GPIO_BOP(LOGIC_ANALYZER_CH1_GPIOx) = LOGIC_ANALYZER_CH1_GPIO_PINx;
#endif
}

static void ch2_clear() {
#if defined (LOGIC_ANALYZER_CH2_GPIO_PINx)
	GPIO_BC(LOGIC_ANALYZER_CH2_GPIOx) = LOGIC_ANALYZER_CH2_GPIO_PINx;
#endif
}

static void ch2_set() {
#if defined (LOGIC_ANALYZER_CH2_GPIO_PINx)
	GPIO_BOP(LOGIC_ANALYZER_CH2_GPIOx) = LOGIC_ANALYZER_CH2_GPIO_PINx;
#endif
}

static void ch3_clear() {
#if defined (LOGIC_ANALYZER_CH3_GPIO_PINx)
	GPIO_BC(LOGIC_ANALYZER_CH3_GPIOx) = LOGIC_ANALYZER_CH3_GPIO_PINx;
#endif
}

static void ch3_set() {
#if defined (LOGIC_ANALYZER_CH3_GPIO_PINx)
	GPIO_BOP(LOGIC_ANALYZER_CH3_GPIOx) = LOGIC_ANALYZER_CH3_GPIO_PINx;
#endif
}

//
static void ch4_clear() {
#if defined (LOGIC_ANALYZER_CH4_GPIO_PINx)
	GPIO_BC(LOGIC_ANALYZER_CH4_GPIOx) = LOGIC_ANALYZER_CH4_GPIO_PINx;
#endif
}

static void ch4_set() {
#if defined (LOGIC_ANALYZER_CH4_GPIO_PINx)
	GPIO_BOP(LOGIC_ANALYZER_CH4_GPIOx) = LOGIC_ANALYZER_CH4_GPIO_PINx;
#endif
}

static void ch5_clear() {
#if defined (LOGIC_ANALYZER_CH5_GPIO_PINx)
	GPIO_BC(LOGIC_ANALYZER_CH5_GPIOx) = LOGIC_ANALYZER_CH5_GPIO_PINx;
#endif
}

static void ch5_set() {
#if defined (LOGIC_ANALYZER_CH5_GPIO_PINx)
	GPIO_BOP(LOGIC_ANALYZER_CH5_GPIOx) = LOGIC_ANALYZER_CH5_GPIO_PINx;
#endif
}

static void ch6_clear() {
#if defined (LOGIC_ANALYZER_CH6_GPIO_PINx)
	GPIO_BC(LOGIC_ANALYZER_CH6_GPIOx) = LOGIC_ANALYZER_CH6_GPIO_PINx;
#endif
}

static void ch6_set() {
#if defined (LOGIC_ANALYZER_CH6_GPIO_PINx)
	GPIO_BOP(LOGIC_ANALYZER_CH6_GPIOx) = LOGIC_ANALYZER_CH6_GPIO_PINx;
#endif
}

static void ch7_clear() {
#if defined (LOGIC_ANALYZER_CH7_GPIO_PINx)
	GPIO_BC(LOGIC_ANALYZER_CH7_GPIOx) = LOGIC_ANALYZER_CH7_GPIO_PINx;
#endif
}

static void ch7_set() {
#if defined (LOGIC_ANALYZER_CH7_GPIO_PINx)
	GPIO_BOP(LOGIC_ANALYZER_CH7_GPIOx) = LOGIC_ANALYZER_CH7_GPIO_PINx;
#endif
}

}  // namespace logic_analyzer

#ifndef LOGIC_ANALYZER_H_
#define LOGIC_ANALYZER_H_

#endif /* LOGIC_ANALYZER_H_ */
