// SPDX-License-Identifier: GPL-3.0
// @file node.h
// @brief This header handles nodes in Canim
#pragma once

#include "canim/math.h"
// @enum CanimNodeType
// @brief This specifies the type of node
typedef enum {
  // @def CANIM_NODE_TYPE_TRI
  // @brief This specifies a triangle node
  CANIM_NODE_TYPE_TRI,

  // @def CANIM_NODE_TYPE_CAM
  // @brief This specifies a camera node
  CANIM_NODE_TYPE_CAM
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
    CanimNodeTri *tri;
    // @def cam
    // @brief This is a pointer to a camera node, use in case the node_type
    // is camera
    CanimNodeCam *cam;
  };
} CanimNode;

typedef struct {
  CanimNode *nodes;
  int length;
} CanimNodeList;
