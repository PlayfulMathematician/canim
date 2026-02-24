#pragma once

#include "canim/math.h"
typedef enum { CANIM_NODE_TYPE_TRI, CANIM_NODE_TYPE_CAM } CanimNodeType;

typedef struct {
  CanimVec3 v[4];
} CanimNodeTri;

typedef struct {
  CanimVec3 p;
} CanimNodeCam;

typedef struct {
  CanimNodeType node_type;
  union {
    CanimNodeTri *tri;
    CanimNodeCam *cam;
  };
} CanimNode;

typedef struct {
  CanimNode *nodes;
  int length;
} CanimNodeList;
