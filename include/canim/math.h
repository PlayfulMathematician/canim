// SPDX-License-Identifier: GPL-3.0
#pragma once
#include "canim/core.h"
#include <stdbool.h>

/// @struct CanimVec2
/// @brief This stores Canim 2 dimensional Vectors
typedef struct {
  CanimNumber x; /// The x position
  CanimNumber y; /// The y position
} CanimVec2;

/// @brief This clamps a value
/// @param x The value to be clamped
/// @param lo The minimum
/// @param hi The maximum
/// @return The clamped value
CANIM_API CanimNumber canim_clamp(CanimNumber x, CanimNumber lo,
                                  CanimNumber hi);

/// @brief This lerps a value
/// @param a The start
/// @param b The end
/// @param t The amount of betweeness
/// @return The lerped value
CANIM_API CanimNumber canim_lerp(CanimNumber a, CanimNumber b, CanimNumber t);

/// @brief This determines if two values are kinda close
/// @param a The first value
/// @param b The second one
/// @return If they are nearly equal
CANIM_API bool canim_nearly_equal(CanimNumber a, CanimNumber b);

/// @brief This adds to CanimVec2's
/// @param a The first one
/// @param b The second one
/// @return The summation
CANIM_API CanimVec2 canim_add_vec2(CanimVec2 a, CanimVec2 b);

/// @brief This negates a CanimVec2
/// @param a The vector to be negated
/// @return The negation
CANIM_API CanimVec2 canim_negative_vec2(CanimVec2 a);

/// @brief This subtracts to CanimVec2's
/// @param a The first one
/// @param b The second one
/// @return The subtraction
CANIM_API CanimVec2 canim_sub_vec2(CanimVec2 a, CanimVec2 b);

/// @brief This computes the dot product of two vec2's
/// @param a The first one
/// @param b The second one
/// @return The dot product
CANIM_API CanimNumber canim_dot_vec2(CanimVec2 a, CanimVec2 b);

/// @brief This scales
/// @param a This is the first vector
/// @param scaler This is the second vector
/// @return The scaled version
CANIM_API CanimVec2 canim_scale_vec2(CanimVec2 a, CanimNumber scaler);

/// @brief This computes the magnitude of a CanimVec2
/// @param a The vector
/// @return The magnitude
CANIM_API CanimNumber canim_magnitude_vec2(CanimVec2 a);

/// @brief This normalizes a CanimVec2
/// @param a The vector
/// @return The normalized version
CANIM_API CanimVec2 canim_normalize_vec2(CanimVec2 a);

/// @brief This lerps vec2
/// @param a The start
/// @param b The end
/// @param t The tweenness
/// @return The vector
CANIM_API CanimVec2 canim_lerp_vec2(CanimVec2 a, CanimVec2 b, CanimNumber t);

/// @struct CanimVec3
/// @brief This stores Canim 3 dimensional Vectors
typedef struct {
  CanimNumber x; /// The x position
  CanimNumber y; /// The y position
  CanimNumber z; /// The z position
} CanimVec3;

/// @brief This adds to CanimVec3's
/// @param a The first one
/// @param b The second one
/// @return The summation
CANIM_API CanimVec3 canim_add_vec3(CanimVec3 a, CanimVec3 b);

/// @brief This negates a CanimVec3
/// @param a The vector to be negated
/// @return The negation
CANIM_API CanimVec3 canim_negative_vec3(CanimVec3 a);

/// @brief This subtracts to CanimVec3's
/// @param a The first one
/// @param b The second one
/// @return The subtraction
CANIM_API CanimVec3 canim_sub_vec3(CanimVec3 a, CanimVec3 b);

/// @brief This computes the dot product of two vec3's
/// @param a The first one
/// @param b The second one
/// @return The dot product
CANIM_API CanimNumber canim_dot_vec3(CanimVec3 a, CanimVec3 b);

/// @brief This scales
/// @param a This is the first vector
/// @param scaler This is the second vector
/// @return The scaled version
CANIM_API CanimVec3 canim_scale_vec3(CanimVec3 a, CanimNumber scaler);

/// @brief This computes the magnitude of a CanimVec3
/// @param a The vector
/// @return The magnitude
CANIM_API CanimNumber canim_magnitude_vec3(CanimVec3 a);

/// @brief This normalizes a CanimVec3
/// @param a The vector
/// @return The normalized version
CANIM_API CanimVec3 canim_normalize_vec3(CanimVec3 a);

/// @brief This lerps vec3
/// @param a The start
/// @param b The end
/// @param t The tweenness
/// @return The vector
CANIM_API CanimVec3 canim_lerp_vec3(CanimVec3 a, CanimVec3 b, CanimNumber t);

/// @brief This crosses vec3's
/// @param a The first
/// @param b The second
/// @return The vector
CANIM_API CanimVec3 canim_cross_vec3(CanimVec3 a, CanimVec3 b);

/// @brief This adds vec's (CanimVec2 or CanimVec3, it is generic)
/// @param a The first
/// @param b The second
/// @return The vector
#define canim_add_vec(a, b)                                                    \
  _Generic((a), CanimVec2: canim_add_vec2, CanimVec3: canim_add_vec3)((a), (b))

/// @brief This subtracts vec's (CanimVec2 or CanimVec3, it is generic)
/// @param a The first
/// @param b The second
/// @return The vector
#define canim_sub_vec(a, b)                                                    \
  _Generic((a), CanimVec2: canim_sub_vec2, CanimVec3: canim_sub_vec3)((a), (b))

/// @brief This computes the magnitude of vec's (CanimVec2 or CanimVec3, it is
/// generic)
/// @param a The Vector
/// @return The magnitude
#define canim_magnitude_vec(a)                                                 \
  _Generic((a),                                                                \
      CanimVec2: canim_magnitude_vec2,                                         \
      CanimVec3: canim_magnitude_vec3)((a))

/// @brief This normalizes vec's (CanimVec2 or CanimVec3, it is
/// generic)
/// @param a The Vector
/// @return The normalized version
#define canim_normalize_vec(a)                                                 \
  _Generic((a),                                                                \
      CanimVec2: canim_normalize_vec2,                                         \
      CanimVec3: canim_normalize_vec3)((a))

/// @brief This computes the dot product (CanimVec2 or CanimVec3, it is
/// generic)
/// @param a The Vector
/// @param b The second vector
/// @return The dot product
#define canim_dot_vec(a, b)                                                    \
  _Generic((a), CanimVec2: canim_dot_vec2, CanimVec3: canim_dot_vec3)((a), (b))

/// @brief This scales a vec (CanimVec2 or CanimVec3, it is
/// generic)
/// @param a The Vector
/// @param b The scaler
/// @return The scaling
#define canim_scale_vec(a, b)                                                  \
  _Generic((a), CanimVec2: canim_scale_vec2, CanimVec3: canim_scale_vec3)((a), \
                                                                          (b))

/// @brief This negates a vec (CanimVec2 or CanimVec3)
/// @param a The vector
/// @return The negation
#define canim_negative_vec(a)                                                  \
  _Generic((a),                                                                \
      CanimVec2: canim_negative_vec2,                                          \
      CanimVec3: canim_negative_vec3)((a))

/// @brief This lerps a vec (CanimVec2 or CanimVec3)
/// @param a The vector
/// @param b The second vector
/// @param t the inbetweeness
/// @return The lerp
#define canim_lerp_vec(a, b, t)                                                \
  _Generic((a), CanimVec2: canim_lerp_vec2, CanimVec3: canim_lerp_vec3)(       \
      (a), (b), (t))
