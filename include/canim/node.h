// SPDX-License-Identifier: GPL-3.0
// @file node.h
// @brief This header handles nodes in Canim
#pragma once

#include "canim/math.h"

// @enum CanimNodeType
// @brief This specifies the type of node
typedef enum {
  // @def CANIM_NODE_TYPE_TRI
  // @brief This specifies a 3 dimensional triangle node
  CANIM_NODE_TYPE_TRI,
  // @def CANIM_NODE_TYPE_TARGET_INIT
  // @brief This is a node for a initalizing a target
  CANIM_NODE_TYPE_TARGET_INIT,
  // @def CANIM_NODE_TYPE_TARGET_END
  // @brief This is a node for ending a target
  CANIM_NODE_TYPE_TARGET_END,
  // @def CANIM_NODE_BEGIN_BILLBOARD
  // @brief This starts a billboard (it includes a translation, set .v2 to the
  // translation.
  CANIM_NODE_TYPE_BEGIN_BILLBOARD,
  // @def CANIM_NODE_TYPE_END_BILLBOARD
  // @brief This ends the billboard
  CANIM_NODE_TYPE_END_BILLBOARD,
  // @def CANIM_NODE_TYPE_CAM
  // @brief This specifies a camera node
  CANIM_NODE_TYPE_CAM,
  // @def CANIM_NODE_TYPE_START
  // @brief This is when the thing starts
  CANIM_NODE_TYPE_START,
  // @def CANIM_NODE_TYPE_END
  // @brief This is when the thing ends
  CANIM_NODE_TYPE_END,
  // @def CANIM_NODE_TYPE_END_ROUND
  // @brief This is when each target has completed it's emission, and everything
  // is over
  CANIM_NODE_TYPE_END_ROUND
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

// @struct  CanimNode
// @brief A canim node
typedef struct {
  // @def node_type
  // @brief This is the type of the node
  CanimNodeType node_type;
  union {
    // @def tri
    // @brief This is a pointer to a triangular node, use in case the node_type
    // is triangular
    CanimNodeTri tri;
    // @def cam
    // @brief This is a pointer to a camera node, use in case the node_type
    // is camera
    CanimNodeCam cam;
  };
} CanimNode;
