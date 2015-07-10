/* exynos_drm.h
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 * Authors:
 *	Inki Dae <inki.dae@samsung.com>
 *	Joonyoung Shim <jy0922.shim@samsung.com>
 *	Seung-Woo Kim <sw0312.kim@samsung.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */

#ifndef _UAPI_EXYNOS_DRM_H_
#define _UAPI_EXYNOS_DRM_H_

#include <drm/drm.h>

/**
 * User-desired buffer creation information structure.
 *
 * @size: user-desired memory allocation size.
 *	- this size value would be page-aligned internally.
 * @flags: user request for setting memory type or cache attributes.
 * @handle: returned a handle to created gem object.
 *	- this handle will be set by gem module of kernel side.
 */
struct drm_exynos_gem_create {
	uint64_t size;
	unsigned int flags;
	unsigned int handle;
};

/**
 * A structure for getting buffer offset.
 *
 * @handle: a pointer to gem object created.
 * @pad: just padding to be 64-bit aligned.
 * @offset: relatived offset value of the memory region allocated.
 *	- this value should be set by user.
 */
struct drm_exynos_gem_map_off {
	unsigned int handle;
	unsigned int pad;
	uint64_t offset;
};

/**
 * A structure for mapping buffer.
 *
 * @handle: a handle to gem object created.
 * @pad: just padding to be 64-bit aligned.
 * @size: memory size to be mapped.
 * @mapped: having user virtual address mmaped.
 *	- this variable would be filled by exynos gem module
 *	of kernel side with user virtual address which is allocated
 *	by do_mmap().
 */
struct drm_exynos_gem_mmap {
	unsigned int handle;
	unsigned int pad;
	uint64_t size;
	uint64_t mapped;
};

/**
 * A structure to gem information.
 *
 * @handle: a handle to gem object created.
 * @flags: flag value including memory type and cache attribute and
 *	this value would be set by driver.
 * @size: size to memory region allocated by gem and this size would
 *	be set by driver.
 */
struct drm_exynos_gem_info {
	unsigned int handle;
	unsigned int flags;
	uint64_t size;
};

/**
 * A structure for user connection request of virtual display.
 *
 * @connection: indicate whether doing connetion or not by user.
 * @extensions: if this value is 1 then the vidi driver would need additional
 *	128bytes edid data.
 * @edid: the edid data pointer from user side.
 */
struct drm_exynos_vidi_connection {
	unsigned int connection;
	unsigned int extensions;
	uint64_t edid;
};

/* memory type definitions. */
enum e_drm_exynos_gem_mem_type {
	/* Physically Continuous memory and used as default. */
	EXYNOS_BO_CONTIG	= 0 << 0,
	/* Physically Non-Continuous memory. */
	EXYNOS_BO_NONCONTIG	= 1 << 0,
	/* non-cachable mapping and used as default. */
	EXYNOS_BO_NONCACHABLE	= 0 << 1,
	/* cachable mapping. */
	EXYNOS_BO_CACHABLE	= 1 << 1,
	/* write-combine mapping. */
	EXYNOS_BO_WC		= 1 << 2,
	EXYNOS_BO_MASK		= EXYNOS_BO_NONCONTIG | EXYNOS_BO_CACHABLE |
					EXYNOS_BO_WC
};

struct drm_exynos_g2d_get_ver {
	__u32	major;
	__u32	minor;
};

struct drm_exynos_g2d_cmd {
	__u32	offset;
	__u32	data;
};

enum drm_exynos_g2d_buf_type {
	G2D_BUF_USERPTR = 1 << 31,
};

enum drm_exynos_g2d_event_type {
	G2D_EVENT_NOT,
	G2D_EVENT_NONSTOP,
	G2D_EVENT_STOP,		/* not yet */
};

struct drm_exynos_g2d_userptr {
	unsigned long userptr;
	unsigned long size;
};

struct drm_exynos_g2d_set_cmdlist {
	__u64					cmd;
	__u64					cmd_buf;
	__u32					cmd_nr;
	__u32					cmd_buf_nr;

	/* for g2d event */
	__u64					event_type;
	__u64					user_data;
};

struct drm_exynos_g2d_exec {
	__u64					async;
};

enum drm_exynos_ops_id {
	EXYNOS_DRM_OPS_SRC,
	EXYNOS_DRM_OPS_DST,
	EXYNOS_DRM_OPS_MAX,
};

struct drm_exynos_sz {
	__u32	hsize;
	__u32	vsize;
};

struct drm_exynos_pos {
	__u32	x;
	__u32	y;
	__u32	w;
	__u32	h;
};

enum drm_exynos_flip {
	EXYNOS_DRM_FLIP_NONE = (0 << 0),
	EXYNOS_DRM_FLIP_VERTICAL = (1 << 0),
	EXYNOS_DRM_FLIP_HORIZONTAL = (1 << 1),
	EXYNOS_DRM_FLIP_BOTH = EXYNOS_DRM_FLIP_VERTICAL |
			EXYNOS_DRM_FLIP_HORIZONTAL,
};

enum drm_exynos_degree {
	EXYNOS_DRM_DEGREE_0,
	EXYNOS_DRM_DEGREE_90,
	EXYNOS_DRM_DEGREE_180,
	EXYNOS_DRM_DEGREE_270,
};

enum drm_exynos_planer {
	EXYNOS_DRM_PLANAR_Y,
	EXYNOS_DRM_PLANAR_CB,
	EXYNOS_DRM_PLANAR_CR,
	EXYNOS_DRM_PLANAR_MAX,
};

/**
 * A structure for ipp supported property list.
 *
 * @version: version of this structure.
 * @ipp_id: id of ipp driver.
 * @count: count of ipp driver.
 * @writeback: flag of writeback supporting.
 * @flip: flag of flip supporting.
 * @degree: flag of degree information.
 * @csc: flag of csc supporting.
 * @crop: flag of crop supporting.
 * @scale: flag of scale supporting.
 * @blending: flag of blending supporting.
 * @dithering: flag of dithering supporting.
 * @colorfill: flag of colorfill supporting.
 * @refresh_min: min hz of refresh.
 * @refresh_max: max hz of refresh.
 * @crop_min: crop min resolution.
 * @crop_max: crop max resolution.
 * @scale_min: scale min resolution.
 * @scale_max: scale max resolution.
 */
struct drm_exynos_ipp_prop_list {
	__u32	version;
	__u32	ipp_id;
	__u32	count;
	__u32	writeback;
	__u32	flip;
	__u32	degree;
	__u32	csc;
	__u32	crop;
	__u32	scale;
	__u32	blending;
	__u32	dithering;
	__u32	colorfill;
	__u32	refresh_min;
	__u32	refresh_max;
	struct drm_exynos_sz	crop_min;
	struct drm_exynos_sz	crop_max;
	struct drm_exynos_sz	scale_min;
	struct drm_exynos_sz	scale_max;
};

/**
 * A structure for ipp config.
 *
 * @ops_id: property of operation directions.
 * @flip: property of mirror, flip.
 * @degree: property of rotation degree.
 * @fmt: property of image format.
 * @sz: property of image size.
 * @pos: property of image position(src-cropped,dst-scaler).
 */
struct drm_exynos_ipp_config {
	__u32	ops_id;
	__u32	flip;
	__u32	degree;
	__u32	fmt;
	struct drm_exynos_sz	sz;
	struct drm_exynos_pos	pos;
};

enum drm_exynos_ipp_cmd {
	IPP_CMD_NONE,
	IPP_CMD_M2M,
	IPP_CMD_WB,
	IPP_CMD_OUTPUT,
	IPP_CMD_MAX,
};

/* define of color range */
enum drm_exynos_color_range {
	COLOR_RANGE_LIMITED,	/* Narrow: Y(16 to 235), Cb/Cr(16 to 240) */
	COLOR_RANGE_FULL,	/* Wide: Y/Cb/Cr(0 to 255), Wide default */
};

/* define of blending operation */
enum drm_exynos_ipp_blending {
	IPP_BLENDING_NO,
	/* [0, 0] */
	IPP_BLENDING_CLR,
	/* [Sa, Sc] */
	IPP_BLENDING_SRC,
	/* [Da, Dc] */
	IPP_BLENDING_DST,
	/* [Sa + (1 - Sa)*Da, Rc = Sc + (1 - Sa)*Dc] */
	IPP_BLENDING_SRC_OVER,
	/* [Sa + (1 - Sa)*Da, Rc = Dc + (1 - Da)*Sc] */
	IPP_BLENDING_DST_OVER,
	/* [Sa * Da, Sc * Da] */
	IPP_BLENDING_SRC_IN,
	/* [Sa * Da, Sa * Dc] */
	IPP_BLENDING_DST_IN,
	/* [Sa * (1 - Da), Sc * (1 - Da)] */
	IPP_BLENDING_SRC_OUT,
	/* [Da * (1 - Sa), Dc * (1 - Sa)] */
	IPP_BLENDING_DST_OUT,
	/* [Da, Sc * Da + (1 - Sa) * Dc] */
	IPP_BLENDING_SRC_ATOP,
	/* [Sa, Sc * (1 - Da) + Sa * Dc ] */
	IPP_BLENDING_DST_ATOP,
	/* [-(Sa * Da), Sc * (1 - Da) + (1 - Sa) * Dc] */
	IPP_BLENDING_XOR,
	/* [Sa + Da - Sa*Da, Sc*(1 - Da) + Dc*(1 - Sa) + min(Sc, Dc)] */
	IPP_BLENDING_DARKEN,
	/* [Sa + Da - Sa*Da, Sc*(1 - Da) + Dc*(1 - Sa) + max(Sc, Dc)] */
	IPP_BLENDING_LIGHTEN,
	/* [Sa * Da, Sc * Dc] */
	IPP_BLENDING_MULTIPLY,
	/* [Sa + Da - Sa * Da, Sc + Dc - Sc * Dc] */
	IPP_BLENDING_SCREEN,
	/* Saturate(S + D) */
	IPP_BLENDING_ADD,
	/* Max */
	IPP_BLENDING_MAX,
};

/*
 * FIXME: H/W cannot distinguish the number of bits used for dithering.
 * So, these useless options must be removed after co-working with upper layer.
 */
/* define of dithering operation */
enum drm_exynos_ipp_dithering {
	IPP_DITHERING_NO,
	IPP_DITHERING_8BIT,
	IPP_DITHERING_6BIT,
	IPP_DITHERING_5BIT,
	IPP_DITHERING_4BIT,
	IPP_DITHERING_MAX,
};

/**
 * A structure for ipp property.
 *
 * @config: source, destination config.
 * @cmd: definition of command.
 * @ipp_id: id of ipp driver.
 * @prop_id: id of property.
 * @refresh_rate: refresh rate.
 * @range: dynamic range for csc.
 * @blending: blending opeation config.
 * @dithering: dithering opeation config.
 * @color_fill: color fill value.
 */
struct drm_exynos_ipp_property {
	struct drm_exynos_ipp_config config[EXYNOS_DRM_OPS_MAX];
	__u32	cmd;
	__u32	ipp_id;
	__u32	prop_id;
	__u32	refresh_rate;
	__u32	range;
	__u32	blending;
	__u32	dithering;
	__u32	color_fill;
};

enum drm_exynos_ipp_buf_type {
	IPP_BUF_ENQUEUE,
	IPP_BUF_DEQUEUE,
};

/**
 * A structure for ipp buffer operations.
 *
 * @ops_id: operation directions.
 * @buf_type: definition of buffer.
 * @prop_id: id of property.
 * @buf_id: id of buffer.
 * @handle: Y, Cb, Cr each planar handle.
 * @user_data: user data.
 */
struct drm_exynos_ipp_queue_buf {
	__u32	ops_id;
	__u32	buf_type;
	__u32	prop_id;
	__u32	buf_id;
	__u32	handle[EXYNOS_DRM_PLANAR_MAX];
	__u32	reserved;
	__u64	user_data;
};

enum drm_exynos_ipp_ctrl {
	IPP_CTRL_PLAY,
	IPP_CTRL_STOP,
	IPP_CTRL_PAUSE,
	IPP_CTRL_RESUME,
	IPP_CTRL_MAX,
};

/**
 * A structure for ipp start/stop operations.
 *
 * @prop_id: id of property.
 * @ctrl: definition of control.
 */
struct drm_exynos_ipp_cmd_ctrl {
	__u32	prop_id;
	__u32	ctrl;
};

#define DRM_EXYNOS_GEM_CREATE		0x00
#define DRM_EXYNOS_GEM_MAP_OFFSET	0x01
#define DRM_EXYNOS_GEM_MMAP		0x02
/* Reserved 0x03 ~ 0x05 for exynos specific gem ioctl */
#define DRM_EXYNOS_GEM_GET		0x04
#define DRM_EXYNOS_VIDI_CONNECTION	0x07

/* G2D */
#define DRM_EXYNOS_G2D_GET_VER		0x20
#define DRM_EXYNOS_G2D_SET_CMDLIST	0x21
#define DRM_EXYNOS_G2D_EXEC		0x22

/* IPP - Image Post Processing */
#define DRM_EXYNOS_IPP_GET_PROPERTY	0x30
#define DRM_EXYNOS_IPP_SET_PROPERTY	0x31
#define DRM_EXYNOS_IPP_QUEUE_BUF	0x32
#define DRM_EXYNOS_IPP_CMD_CTRL	0x33

#define DRM_IOCTL_EXYNOS_GEM_CREATE		DRM_IOWR(DRM_COMMAND_BASE + \
		DRM_EXYNOS_GEM_CREATE, struct drm_exynos_gem_create)

#define DRM_IOCTL_EXYNOS_GEM_MAP_OFFSET	DRM_IOWR(DRM_COMMAND_BASE + \
		DRM_EXYNOS_GEM_MAP_OFFSET, struct drm_exynos_gem_map_off)

#define DRM_IOCTL_EXYNOS_GEM_MMAP	DRM_IOWR(DRM_COMMAND_BASE + \
		DRM_EXYNOS_GEM_MMAP, struct drm_exynos_gem_mmap)

#define DRM_IOCTL_EXYNOS_GEM_GET	DRM_IOWR(DRM_COMMAND_BASE + \
		DRM_EXYNOS_GEM_GET,	struct drm_exynos_gem_info)

#define DRM_IOCTL_EXYNOS_VIDI_CONNECTION	DRM_IOWR(DRM_COMMAND_BASE + \
		DRM_EXYNOS_VIDI_CONNECTION, struct drm_exynos_vidi_connection)

#define DRM_IOCTL_EXYNOS_G2D_GET_VER		DRM_IOWR(DRM_COMMAND_BASE + \
		DRM_EXYNOS_G2D_GET_VER, struct drm_exynos_g2d_get_ver)
#define DRM_IOCTL_EXYNOS_G2D_SET_CMDLIST	DRM_IOWR(DRM_COMMAND_BASE + \
		DRM_EXYNOS_G2D_SET_CMDLIST, struct drm_exynos_g2d_set_cmdlist)
#define DRM_IOCTL_EXYNOS_G2D_EXEC		DRM_IOWR(DRM_COMMAND_BASE + \
		DRM_EXYNOS_G2D_EXEC, struct drm_exynos_g2d_exec)

#define DRM_IOCTL_EXYNOS_IPP_GET_PROPERTY	DRM_IOWR(DRM_COMMAND_BASE + \
		DRM_EXYNOS_IPP_GET_PROPERTY, struct drm_exynos_ipp_prop_list)
#define DRM_IOCTL_EXYNOS_IPP_SET_PROPERTY	DRM_IOWR(DRM_COMMAND_BASE + \
		DRM_EXYNOS_IPP_SET_PROPERTY, struct drm_exynos_ipp_property)
#define DRM_IOCTL_EXYNOS_IPP_QUEUE_BUF	DRM_IOWR(DRM_COMMAND_BASE + \
		DRM_EXYNOS_IPP_QUEUE_BUF, struct drm_exynos_ipp_queue_buf)
#define DRM_IOCTL_EXYNOS_IPP_CMD_CTRL		DRM_IOWR(DRM_COMMAND_BASE + \
		DRM_EXYNOS_IPP_CMD_CTRL, struct drm_exynos_ipp_cmd_ctrl)

/* EXYNOS specific events */
#define DRM_EXYNOS_G2D_EVENT		0x80000000
#define DRM_EXYNOS_IPP_EVENT		0x80000001

struct drm_exynos_g2d_event {
	struct drm_event	base;
	__u64			user_data;
	__u32			tv_sec;
	__u32			tv_usec;
	__u32			cmdlist_no;
	__u32			reserved;
};

struct drm_exynos_ipp_event {
	struct drm_event	base;
	__u64			user_data;
	__u32			tv_sec;
	__u32			tv_usec;
	__u32			prop_id;
	__u32			reserved;
	__u32			buf_id[EXYNOS_DRM_OPS_MAX];
};

#endif /* _UAPI_EXYNOS_DRM_H_ */