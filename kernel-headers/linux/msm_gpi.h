/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2017-2021, The Linux Foundation. All rights reserved.
 * Copyright (c) 2023-2024 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef __MSM_GPI_H_
#define __MSM_GPI_H_

#include <linux/types.h>

struct __packed msm_gpi_tre {
	u32 dword[4];
};

enum msm_gpi_tre_type {
	MSM_GPI_TRE_INVALID = 0x00,
	MSM_GPI_TRE_NOP = 0x01,
	MSM_GPI_TRE_DMA_W_BUF = 0x10,
	MSM_GPI_TRE_DMA_IMMEDIATE = 0x11,
	MSM_GPI_TRE_DMA_W_SG_LIST = 0x12,
	MSM_GPI_TRE_GO = 0x20,
	MSM_GPI_TRE_CONFIG0 = 0x22,
	MSM_GPI_TRE_CONFIG1 = 0x23,
	MSM_GPI_TRE_CONFIG2 = 0x24,
	MSM_GPI_TRE_CONFIG3 = 0x25,
	MSM_GPI_TRE_LOCK = 0x30,
	MSM_GPI_TRE_UNLOCK = 0x31,
};

#define MSM_GPI_TRE_TYPE(tre) ((tre->dword[3] >> 16) & 0xFF)

/* Lock TRE */
#define MSM_GPI_LOCK_TRE_DWORD0 (0)
#define MSM_GPI_LOCK_TRE_DWORD1 (0)
#define MSM_GPI_LOCK_TRE_DWORD2 (0)
#define MSM_GPI_LOCK_TRE_DWORD3(link_rx, bei, ieot, ieob, ch) \
	((0x3 << 20) | (0x0 << 16) | (link_rx << 11) | (bei << 10) | \
	(ieot << 9) | (ieob << 8) | ch)

/* Unlock TRE */
#define MSM_GPI_UNLOCK_TRE_DWORD0 (0)
#define MSM_GPI_UNLOCK_TRE_DWORD1 (0)
#define MSM_GPI_UNLOCK_TRE_DWORD2 (0)
#define MSM_GPI_UNLOCK_TRE_DWORD3(link_rx, bei, ieot, ieob, ch) \
	((0x3 << 20) | (0x1 << 16) | (link_rx << 11) | (bei << 10) | \
	(ieot << 9) | (ieob << 8) | ch)

/* DMA w. Buffer TRE */
#ifdef CONFIG_ARM64
#define MSM_GPI_DMA_W_BUFFER_TRE_DWORD0(ptr) ((u32)ptr)
#define MSM_GPI_DMA_W_BUFFER_TRE_DWORD1(ptr) ((u32)(ptr >> 32))
#else
#define MSM_GPI_DMA_W_BUFFER_TRE_DWORD0(ptr) (ptr)
#define MSM_GPI_DMA_W_BUFFER_TRE_DWORD1(ptr) 0
#endif

#define MSM_GPI_DMA_W_BUFFER_TRE_DWORD2(length) (length & 0xFFFFFF)
#define MSM_GPI_DMA_W_BUFFER_TRE_DWORD3(link_rx, bei, ieot, ieob, ch) \
	((0x1 << 20) | (0x0 << 16) | (link_rx << 11) | (bei << 10) | \
	(ieot << 9) | (ieob << 8) | ch)
#define MSM_GPI_DMA_W_BUFFER_TRE_GET_LEN(tre) (tre->dword[2] & 0xFFFFFF)
#define MSM_GPI_DMA_W_BUFFER_TRE_SET_LEN(tre, length) (tre->dword[2] = \
	MSM_GPI_DMA_W_BUFFER_TRE_DWORD2(length))

/* DMA Immediate TRE */
#define MSM_GPI_DMA_IMMEDIATE_TRE_DWORD0(d3, d2, d1, d0) ((d3 << 24) | \
	(d2 << 16) | (d1 << 8) | (d0))
#define MSM_GPI_DMA_IMMEDIATE_TRE_DWORD1(d4, d5, d6, d7) ((d7 << 24) | \
	(d6 << 16) | (d5 << 8) | (d4))
#define MSM_GPI_DMA_IMMEDIATE_TRE_DWORD2(length) (length & 0xF)
#define MSM_GPI_DMA_IMMEDIATE_TRE_DWORD3(link_rx, bei, ieot, ieob, ch) \
	((0x1 << 20) | (0x1 << 16) | (link_rx << 11) | (bei << 10) | \
	(ieot << 9) | (ieob << 8) | ch)
#define MSM_GPI_DMA_IMMEDIATE_TRE_GET_LEN(tre) (tre->dword[2] & 0xF)

/* DMA w. Scatter/Gather List TRE */
#ifdef CONFIG_ARM64
#define MSM_GPI_SG_LIST_TRE_DWORD0(ptr) ((u32)ptr)
#define MSM_GPI_SG_LIST_TRE_DWORD1(ptr) ((u32)(ptr >> 32))
#else
#define MSM_GPI_SG_LIST_TRE_DWORD0(ptr) (ptr)
#define MSM_GPI_SG_LIST_TRE_DWORD1(ptr) 0
#endif
#define MSM_GPI_SG_LIST_TRE_DWORD2(length) (length & 0xFFFF)
#define MSM_GPI_SG_LIST_TRE_DWORD3(link_rx, bei, ieot, ieob, ch) ((0x1 << 20) \
	| (0x2 << 16) | (link_rx << 11) | (bei << 10) | (ieot << 9) | \
	(ieob << 8) | ch)

/* SG Element */
#ifdef CONFIG_ARM64
#define MSM_GPI_SG_ELEMENT_DWORD0(ptr) ((u32)ptr)
#define MSM_GPI_SG_ELEMENT_DWORD1(ptr) ((u32)(ptr >> 32))
#else
#define MSM_GPI_SG_ELEMENT_DWORD0(ptr) (ptr)
#define MSM_GPI_SG_ELEMENT_DWORD1(ptr) 0
#endif
#define MSM_GSI_SG_ELEMENT_DWORD2(length) (length & 0xFFFFF)
#define MSM_GSI_SG_ELEMENT_DWORD3 (0)

/* Config2 TRE  */
#define GPI_CONFIG2_TRE_DWORD0(gr, txp) ((gr << 20) | (txp))
#define GPI_CONFIG2_TRE_DWORD1(txp) (txp)
#define GPI_CONFIG2_TRE_DWORD2 (0)
#define GPI_CONFIG2_TRE_DWORD3(link_rx, bei, ieot, ieob, ch) ((0x2 << 20) | \
	(0x4 << 16) | (link_rx << 11) | (bei << 10) | (ieot << 9) | \
	(ieob << 8) | ch)

/* Config3 TRE */
#define GPI_CONFIG3_TRE_DWORD0(rxp) (rxp)
#define GPI_CONFIG3_TRE_DWORD1(rxp) (rxp)
#define GPI_CONFIG3_TRE_DWORD2 (0)
#define GPI_CONFIG3_TRE_DWORD3(link_rx, bei, ieot, ieob, ch) ((0x2 << 20) \
	| (0x5 << 16) | (link_rx << 11) | (bei << 10) | (ieot << 9) | \
	(ieob << 8) | ch)

/* SPI Go TRE */
#define MSM_GPI_SPI_GO_TRE_DWORD0(flags, cs, command) ((flags << 24) | \
	(cs << 8) | command)
#define MSM_GPI_SPI_GO_TRE_DWORD1 (0)
#define MSM_GPI_SPI_GO_TRE_DWORD2(rx_len) (rx_len)
#define MSM_GPI_SPI_GO_TRE_DWORD3(link_rx, bei, ieot, ieob, ch) ((0x2 << 20) | \
	(0x0 << 16) | (link_rx << 11) | (bei << 10) | (ieot << 9) | \
	(ieob << 8) | ch)

/* SPI Config0 TRE */
#define MSM_GPI_SPI_CONFIG0_TRE_DWORD0(pack, flags, word_size) ((pack << 24) | \
	(flags << 8) | word_size)
#define MSM_GPI_SPI_CONFIG0_TRE_DWORD1(it_del, cs_clk_del, iw_del) \
	((it_del << 16) | (cs_clk_del << 8) | iw_del)
#define MSM_GPI_SPI_CONFIG0_TRE_DWORD2(clk_src, clk_div) ((clk_src << 16) | \
	clk_div)
#define MSM_GPI_SPI_CONFIG0_TRE_DWORD3(link_rx, bei, ieot, ieob, ch) \
	((0x2 << 20) | (0x2 << 16) | (link_rx << 11) | (bei << 10) | \
	(ieot << 9) | (ieob << 8) | ch)

/* UART Go TRE */
#define MSM_GPI_UART_GO_TRE_DWORD0(en_hunt, command) ((en_hunt << 8) | command)
#define MSM_GPI_UART_GO_TRE_DWORD1 (0)
#define MSM_GPI_UART_GO_TRE_DWORD2 (0)
#define MSM_GPI_UART_GO_TRE_DWORD3(link_rx, bei, ieot, ieob, ch) ((0x2 << 20) \
	| (0x0 << 16) | (link_rx << 11) | (bei << 10) | (ieot << 9) | \
	(ieob << 8) | ch)

/* UART Config0 TRE */
#define MSM_GPI_UART_CONFIG0_TRE_DWORD0(pack, hunt, flags, parity, sbl, size) \
	((pack << 24) | (hunt << 16) | (flags << 8) | (parity << 5) | \
	 (sbl << 3) | size)
#define MSM_GPI_UART_CONFIG0_TRE_DWORD1(rfr_level, rx_stale) \
	((rfr_level << 24) | rx_stale)
#define MSM_GPI_UART_CONFIG0_TRE_DWORD2(clk_source, clk_div) \
	((clk_source << 16) | clk_div)
#define MSM_GPI_UART_CONFIG0_TRE_DWORD3(link_rx, bei, ieot, ieob, ch) \
	((0x2 << 20) | (0x2 << 16) | (link_rx << 11) | (bei << 10) | \
	(ieot << 9) | (ieob << 8) | ch)

/* I2C GO TRE */
#define MSM_GPI_I2C_GO_TRE_DWORD0(flags, slave, opcode) \
	((flags << 24) | (slave << 8) | opcode)
#define MSM_GPI_I2C_GO_TRE_DWORD1 (0)
#define MSM_GPI_I2C_GO_TRE_DWORD2(rx_len) (rx_len)
#define MSM_GPI_I2C_GO_TRE_DWORD3(link_rx, bei, ieot, ieob, ch) ((0x2 << 20) | \
	(0x0 << 16) | (link_rx << 11) | (bei << 10) | (ieot << 9) | \
	(ieob << 8) | ch)

/* I2C Config0 TRE */
#define MSM_GPI_I2C_CONFIG0_TRE_DWORD0(pack, t_cycle, t_high, t_low) \
	((pack << 24) | (t_cycle << 16) | (t_high << 8) | t_low)
#define MSM_GPI_I2C_CONFIG0_TRE_DWORD1(inter_delay, noise_rej) \
	((inter_delay << 16) | noise_rej)
#define MSM_GPI_I2C_CONFIG0_TRE_DWORD2(clk_src, clk_div) \
	((clk_src << 16) | clk_div)
#define MSM_GPI_I2C_CONFIG0_TRE_DWORD3(link_rx, bei, ieot, ieob, ch) \
	((0x2 << 20) | (0x2 << 16) | (link_rx << 11) | (bei << 10) | \
	(ieot << 9) | (ieob << 8) | ch)

#ifdef CONFIG_ARM64
#define MSM_GPI_RING_PHYS_ADDR_UPPER(ptr) ((u32)(ptr >> 32))
#else
#define MSM_GPI_RING_PHYS_ADDR_UPPER(ptr) 0
#endif

/* Static GPII here uses bit5 bit4 bit3 bit2 bit1(xxx1 111x) */
#define STATIC_GPII_BMSK (0x1e)
#define STATIC_GPII_SHFT (0x1)
#define GPI_EV_PRIORITY_BMSK (0x1)

#define GSI_SE_ERR(log_ctx, print, dev, x...) do { \
ipc_log_string(log_ctx, x); \
if (print) { \
	if (dev) \
		dev_err((dev), x); \
	else \
		pr_err(x); \
} \
} while (0)

#define GSI_SE_DBG(log_ctx, print, dev, x...) do { \
ipc_log_string(log_ctx, x); \
if (print) { \
	if (dev) \
		dev_dbg((dev), x); \
	else \
		pr_debug(x); \
} \
} while (0)

#define LOCK_TRE_SET		BIT(0)
#define CONFIG_TRE_SET		BIT(1)
#define GO_TRE_SET		BIT(2)
#define DMA_TRE_SET		BIT(3)
#define UNLOCK_TRE_SET		BIT(4)
#define GSI_MAX_TRE_TYPES	(5)

#define GSI_MAX_NUM_TRE_MSGS		(448)
#define GSI_MAX_IMMEDIATE_DMA_LEN	(8)

/* cmds to perform by using dmaengine_slave_config() */
enum msm_gpi_ctrl_cmd {
	MSM_GPI_DEFAULT,
	MSM_GPI_INIT,
	MSM_GPI_CMD_UART_SW_STALE,
	MSM_GPI_CMD_UART_RFR_READY,
	MSM_GPI_CMD_UART_RFR_NOT_READY,
	MSM_GPI_DEEP_SLEEP_INIT,
};

enum msm_gpi_cb_event {
	/* These events are hardware generated events */
	MSM_GPI_QUP_NOTIFY,
	MSM_GPI_QUP_ERROR, /* global error */
	MSM_GPI_QUP_CH_ERROR, /* channel specific error */
	MSM_GPI_QUP_FW_ERROR, /* unhandled error */
	/* These events indicate a software bug */
	MSM_GPI_QUP_PENDING_EVENT,
	MSM_GPI_QUP_EOT_DESC_MISMATCH,
	MSM_GPI_QUP_SW_ERROR,
	MSM_GPI_QUP_MAX_EVENT,
};

struct msm_gpi_error_log {
	u32 routine;
	u32 type;
	u32 error_code;
};

struct msm_gpi_cb {
	enum msm_gpi_cb_event cb_event;
	u64 status;
	u64 timestamp;
	u64 count;
	struct msm_gpi_error_log error_log;
};

struct dma_chan;

struct gpi_client_info {
	/*
	 * memory for msm_gpi_cb is released after callback, clients shall
	 * save any required data for post processing after returning
	 * from callback
	 */
	void (*callback)(struct dma_chan *chan,
			 struct msm_gpi_cb const *msm_gpi_cb,
			 void *cb_param);
	void *cb_param;
};

/*
 * control structure to config gpi dma engine via dmaengine_slave_config()
 * dma_chan.private should point to msm_gpi_ctrl structure
 */
struct msm_gpi_ctrl {
	enum msm_gpi_ctrl_cmd cmd;
	union {
		struct gpi_client_info init;
	};
};

enum msm_gpi_tce_code {
	MSM_GPI_TCE_SUCCESS = 1,
	MSM_GPI_TCE_EOT = 2,
	MSM_GPI_TCE_EOB = 4,
	MSM_GPI_TCE_UNEXP_ERR = 16,
};

/*
 * gpi specific callback parameters to pass between gpi client and gpi engine.
 * client shall set async_desc.callback_parm to msm_gpi_dma_async_tx_cb_param
 */
struct msm_gpi_dma_async_tx_cb_param {
	u32 length;
	enum msm_gpi_tce_code completion_code; /* TCE event code */
	u32 status;
	struct __packed msm_gpi_tre imed_tre;
	void *userdata;
};

struct gsi_tre_info {
	struct msm_gpi_tre lock_t;
	struct msm_gpi_tre go_t;
	struct msm_gpi_tre config_t;
	struct msm_gpi_tre dma_t;
	struct msm_gpi_tre unlock_t;
	u8 flags;
};

struct gsi_tre_queue {
	u32 msg_cnt;
	u32 unmap_msg_cnt;
	u32 freed_msg_cnt;
	dma_addr_t dma_buf[GSI_MAX_NUM_TRE_MSGS];
	void *virt_buf[GSI_MAX_NUM_TRE_MSGS];
	u32 len[GSI_MAX_NUM_TRE_MSGS];
	atomic_t irq_cnt;
};

struct gsi_xfer_param {
	struct dma_async_tx_descriptor *desc;
	struct msm_gpi_dma_async_tx_cb_param cb;
	struct dma_chan *ch;
	struct scatterlist *sg; /* lock, cfg0, go, TX, unlock */
	dma_addr_t sg_dma;
	struct msm_gpi_ctrl ev;
	struct gsi_tre_info tre;
	struct gsi_tre_queue tre_queue;
	spinlock_t multi_tre_lock; /* multi tre spin lock */
	void (*cb_fun)(void *ptr); /* tx or rx cb */
};

struct gsi_common {
	u8 protocol;
	struct completion *xfer;
	struct device *dev;
	void *dev_node;
	struct gsi_xfer_param tx;
	struct gsi_xfer_param rx;
	void *ipc;
	bool req_chan;
	bool err; /* For every gsi error performing gsi reset */
	int *protocol_err; /* protocol specific error*/
	void (*ev_cb_fun)(struct dma_chan *ch, struct msm_gpi_cb const *cb_str, void *ptr);
};

/* Client drivers of the GPI can call this function to dump the GPI registers
 * whenever client met some scenario like timeout, error in GPI transfer mode.
 */
void gpi_dump_for_geni(struct dma_chan *chan);
void gpi_update_multi_desc_flag(struct dma_chan *chan, bool is_multi_descriptor, int num_msgs);
int geni_gsi_common_request_channel(struct gsi_common *gsi);
int gsi_common_prep_desc_and_submit(struct gsi_common *gsi, int segs, bool tx_chan, bool skip_cb);
int gsi_common_fill_tre_buf(struct gsi_common *gsi, bool tx_chan);
void gsi_common_clear_tre_indexes(struct gsi_tre_queue *gsi_q);
#endif
