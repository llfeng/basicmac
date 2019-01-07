# Copyright (C) 2016-2019 Semtech (International) AG. All rights reserved.
#
# This file is subject to the terms and conditions defined in file 'LICENSE',
# which is part of this source code package.

# ------------------------------------------------
# Family: Development Boards

ifneq (,$(filter nucleo_l073rz,$(FAMILIES)))
    MCU		:= stm32l0
    LD_SCRIPTS	+= $(BL)/src/arm/stm32lx/ld/STM32L0xxZ.ld
    DEFS	+= -DSTM32L0 -DSTM32L073xx
    DEFS	+= -DCFG_nucleo_board
    OOCFGS	+= nucleo-l0.cfg
endif

ifneq (,$(filter nucleo_l053r8,$(FAMILIES)))
    MCU		:= stm32l0
    LD_SCRIPTS	+= $(BL)/src/arm/stm32lx/ld/STM32L05xx8.ld
    DEFS	+= -DSTM32L0 -DSTM32L053xx
    DEFS	+= -DCFG_nucleo_board
    OOCFGS	+= nucleo-l0.cfg
endif

ifneq (,$(filter sx1272mbed,$(FAMILIES)))
    DEFS	+= -DCFG_sx1272mbed
endif

ifneq (,$(filter sx1276mbed,$(FAMILIES)))
    DEFS	+= -DCFG_sx1276mbed
endif

ifneq (,$(filter b_l072z_lrwan1,$(FAMILIES)))
    MCU		:= stm32l0
    LD_SCRIPTS	+= $(BL)/src/arm/stm32lx/ld/STM32L0xxZ.ld
    DEFS	+= -DSTM32L0 -DSTM32L072xx
    DEFS	+= -DCFG_b_l072Z_lrwan1_board
    DEFS	+= -DBRD_IMPL_INC='"brd_devboards.h"'
    OOCFGS	+= nucleo-l0.cfg
    BL_BRD	:= B-L072Z-LRWAN1
endif
