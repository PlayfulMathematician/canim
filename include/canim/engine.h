// SPDX-License-Identifier: GPL-3.0
// @file node.h
// @brief This header handles nodes in Canim
#pragma once

#include "canim/core.h"
#include "canim/data.h"
#include "canim/gfx.h"
#include "canim/log.h"
#include "canim/math.h"
// @enum CanimNodeType
// @brief This specifies the type of node
typedef enum {
  // @def CANIM_NODE_TYPE_TRI
  // @brief This specifies a 3 dimensional triangle node
  CANIM_NODE_TYPE_TRI,
  // @def CANIM_NODE_TYPE_TARGET_INIT
  // @brief This is a node for a beginning a target
  CANIM_NODE_TYPE_TARGET_BEGIN,
  // @def CANIM_NODE_TYPE_TARGET_END
  // @brief This is a node for ending a target
  CANIM_NODE_TYPE_TARGET_END,
  // @def CANIM_NODE_TYPE_CAM
  // @brief This specifies a camera node
  CANIM_NODE_TYPE_CAM,
  // @def CANIM_NODE_TYPE_TARGET
  // @brief This is when the target starts
  CANIM_NODE_TYPE_TARGET,
  // @def CANIM_NODE_TYPE_END
  // @brief This is when the thing ends
  CANIM_NODE_TYPE_END,
} CanimNodeType;

// @struct CanimNodeTri
// @brief This is the triangle node
typedef struct {
  // @def v
  // @brief This is the triangle vertices with v[3] being the normal
  CanimVec3 v[4];
} CanimNodeTri;

// @struct CanimNodeCam
// @brief This is the camera node
typedef struct {
  // @def p
  // @brief This is the position of the camera in question
  CanimVec3 p;
} CanimNodeCam;

// @struct CanimNodeTargetBegin
// @brief This is the node for a target declaring its existance
typedef struct {
  char _;
} CanimNodeTargetBegin;

// @struct CanimNodeTargetEnd
// @brief This is the node for a target declaring its death
typedef struct {
  char _;
} CanimNodeTargetEnd;

// @struct CanimNodeEnd
// @brief This is the node for declaring that it is now time for parsing
typedef struct {
  char _;
} CanimNodeEnd;

// @struct CanimNodeTargetStart
// @brief This is the node for declaring all future nodes will belong to this
// node
typedef struct {
  CanimUID target_id;
} CanimNodeTargetStart;

// @struct CanimNode
// @brief A canim node
typedef struct {
  // @def node_type
  // @brief This is the type of the node
  CanimNodeType node_type;
  union {
    CanimNodeTri tri;
    CanimNodeCam cam;
    CanimNodeTargetBegin target_begin;
    CanimNodeTargetEnd target_end;
    CanimNodeEnd end;
    CanimNodeTargetStart target_start;
  };
} CanimNode;

typedef enum {
  CANIM_MSG_TARGET_ACTIVE,
  CANIM_MSG_TARGET_INACTIVE,
  CANIM_MSG_HELLO
} CanimMsgType;

typedef struct {
  char _;
} CanimMsgHello;

typedef struct {
  CanimUID target_id;
} CanimMsgTargetActive;

typedef struct {
  CanimUID target_id;
} CanimMsgTargetInactive;

typedef struct {
  CanimMsgType type;
  union {
    CanimMsgHello hello;
    CanimMsgTargetActive target_active;
    CanimMsgTargetInactive target_inactive;
  };
} CanimMsg;

typedef CanimDA *CanimMailbox;
typedef CanimDA *CanimTargetList;
typedef CanimDA *CanimNodeList;
typedef CanimDA *CanimDepList;
typedef struct {
  CanimUID uid;
  bool active;
  CanimMailbox mail;
  CanimDepList deps;
  void *frame_buffer;
  void *full_buffer;
  // note: fix later
  void (*handle_frame)(void *, CanimNodeList);
} CanimTarget;

typedef struct {
  CanimTargetList target;
  CanimNodeList node;
  CanimRenderData *data;
  CanimUID seed;
} CanimContext;

CANIM_API CanimContext *canim_init(CanimLogger *c_log);
CANIM_API CanimUID canim_new_uid(CanimContext *);
CANIM_API CanimTarget *canim_create_and_add_target(
    CanimLogger *c_log, void (*func)(void *, CanimNodeList), CanimContext *ctx);
CANIM_API void canim_generate_frame_data(CanimLogger *c_log, CanimContext *ctx);
