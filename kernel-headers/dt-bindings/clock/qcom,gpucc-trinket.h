/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2023, Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _DT_BINDINGS_CLK_QCOM_GPU_CC_TRINKET_H
#define _DT_BINDINGS_CLK_QCOM_GPU_CC_TRINKET_H

/* GPU_CC clocks */
#define GPU_CC_AHB_CLK						0
#define GPU_CC_CRC_AHB_CLK					1
#define GPU_CC_CX_GFX3D_CLK					2
#define GPU_CC_CX_GFX3D_SLV_CLK					3
#define GPU_CC_CX_GMU_CLK					4
#define GPU_CC_CX_SNOC_DVM_CLK					5
#define GPU_CC_CXO_AON_CLK					6
#define GPU_CC_CXO_CLK						7
#define GPU_CC_GMU_CLK_SRC					8
#define GPU_CC_GX_GFX3D_CLK					9
#define GPU_CC_GX_GFX3D_CLK_SRC					10
#define GPU_CC_HLOS1_VOTE_GPU_SMMU_CLK				11
#define GPU_CC_PLL0						12
#define GPU_CC_PLL1						13
#define GPU_CC_SLEEP_CLK					14
#define GPU_CC_CX_APB_CLK					15

/* GPU_CC resets */
#define GPUCC_GPU_CC_CX_BCR					0
#define GPUCC_GPU_CC_GFX3D_AON_BCR				1
#define GPUCC_GPU_CC_GMU_BCR					2
#define GPUCC_GPU_CC_GX_BCR					3
#define GPUCC_GPU_CC_XO_BCR					4

#endif
