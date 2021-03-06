#pragma once

enum class EPrimitiveTopology
{
    PointList = 0,
    LineList = 1,
    LineStrip = 2,
    TriangleList = 3,
    TriangleStrip = 4,
    TriangleFan = 5,
    LineListWithAdjacency = 6,
    LineStripWithAdjacency = 7,
    TriangleListWithAdjacency = 8,
    TriangleStripWithAdjacency = 9,
    PatchList = 10,
};

enum class EPolygonMode
{
    Fill = 0,
    Line = 1,
    Point = 2,
};

enum class ECompareOp
{
    Never = 0,
    Less = 1,
    Equal = 2,
    LEqual = 3,
    Greater = 4,
    NotEqual = 5,
    GEqual = 6,
    Always = 7
};

enum class EStencilOp
{
    KEEP = 0,
    ZERO = 1,
    REPLACE = 2,
    INCREMENT_AND_CLAMP = 3,
    DECREMENT_AND_CLAMP = 4,
    INVERT = 5,
    INCREMENT_AND_WRAP = 6,
    DECREMENT_AND_WRAP = 7
};

enum class VkLogicOp
{
    VK_LOGIC_OP_CLEAR = 0,
    VK_LOGIC_OP_AND = 1,
    VK_LOGIC_OP_AND_REVERSE = 2,
    VK_LOGIC_OP_COPY = 3,
    VK_LOGIC_OP_AND_INVERTED = 4,
    VK_LOGIC_OP_NO_OP = 5,
    VK_LOGIC_OP_XOR = 6,
    VK_LOGIC_OP_OR = 7,
    VK_LOGIC_OP_NOR = 8,
    VK_LOGIC_OP_EQUIVALENT = 9,
    VK_LOGIC_OP_INVERT = 10,
    VK_LOGIC_OP_OR_REVERSE = 11,
    VK_LOGIC_OP_COPY_INVERTED = 12,
    VK_LOGIC_OP_OR_INVERTED = 13,
    VK_LOGIC_OP_NAND = 14,
    VK_LOGIC_OP_SET = 15,
    VK_LOGIC_OP_BEGIN_RANGE = VK_LOGIC_OP_CLEAR,
    VK_LOGIC_OP_END_RANGE = VK_LOGIC_OP_SET,
    VK_LOGIC_OP_RANGE_SIZE = (VK_LOGIC_OP_SET - VK_LOGIC_OP_CLEAR + 1),
    VK_LOGIC_OP_MAX_ENUM = 0x7FFFFFFF
};

enum class VkBlendFactor
{
    VK_BLEND_FACTOR_ZERO = 0,
    VK_BLEND_FACTOR_ONE = 1,
    VK_BLEND_FACTOR_SRC_COLOR = 2,
    VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR = 3,
    VK_BLEND_FACTOR_DST_COLOR = 4,
    VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR = 5,
    VK_BLEND_FACTOR_SRC_ALPHA = 6,
    VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA = 7,
    VK_BLEND_FACTOR_DST_ALPHA = 8,
    VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA = 9,
    VK_BLEND_FACTOR_CONSTANT_COLOR = 10,
    VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR = 11,
    VK_BLEND_FACTOR_CONSTANT_ALPHA = 12,
    VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA = 13,
    VK_BLEND_FACTOR_SRC_ALPHA_SATURATE = 14,
    VK_BLEND_FACTOR_SRC1_COLOR = 15,
    VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR = 16,
    VK_BLEND_FACTOR_SRC1_ALPHA = 17,
    VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA = 18,
    VK_BLEND_FACTOR_BEGIN_RANGE = VK_BLEND_FACTOR_ZERO,
    VK_BLEND_FACTOR_END_RANGE = VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA,
    VK_BLEND_FACTOR_RANGE_SIZE = (VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA - VK_BLEND_FACTOR_ZERO + 1),
    VK_BLEND_FACTOR_MAX_ENUM = 0x7FFFFFFF
};

enum class VkBlendOp
{
    VK_BLEND_OP_ADD = 0,
    VK_BLEND_OP_SUBTRACT = 1,
    VK_BLEND_OP_REVERSE_SUBTRACT = 2,
    VK_BLEND_OP_MIN = 3,
    VK_BLEND_OP_MAX = 4,
    VK_BLEND_OP_ZERO_EXT = 1000148000,
    VK_BLEND_OP_SRC_EXT = 1000148001,
    VK_BLEND_OP_DST_EXT = 1000148002,
    VK_BLEND_OP_SRC_OVER_EXT = 1000148003,
    VK_BLEND_OP_DST_OVER_EXT = 1000148004,
    VK_BLEND_OP_SRC_IN_EXT = 1000148005,
    VK_BLEND_OP_DST_IN_EXT = 1000148006,
    VK_BLEND_OP_SRC_OUT_EXT = 1000148007,
    VK_BLEND_OP_DST_OUT_EXT = 1000148008,
    VK_BLEND_OP_SRC_ATOP_EXT = 1000148009,
    VK_BLEND_OP_DST_ATOP_EXT = 1000148010,
    VK_BLEND_OP_XOR_EXT = 1000148011,
    VK_BLEND_OP_MULTIPLY_EXT = 1000148012,
    VK_BLEND_OP_SCREEN_EXT = 1000148013,
    VK_BLEND_OP_OVERLAY_EXT = 1000148014,
    VK_BLEND_OP_DARKEN_EXT = 1000148015,
    VK_BLEND_OP_LIGHTEN_EXT = 1000148016,
    VK_BLEND_OP_COLORDODGE_EXT = 1000148017,
    VK_BLEND_OP_COLORBURN_EXT = 1000148018,
    VK_BLEND_OP_HARDLIGHT_EXT = 1000148019,
    VK_BLEND_OP_SOFTLIGHT_EXT = 1000148020,
    VK_BLEND_OP_DIFFERENCE_EXT = 1000148021,
    VK_BLEND_OP_EXCLUSION_EXT = 1000148022,
    VK_BLEND_OP_INVERT_EXT = 1000148023,
    VK_BLEND_OP_INVERT_RGB_EXT = 1000148024,
    VK_BLEND_OP_LINEARDODGE_EXT = 1000148025,
    VK_BLEND_OP_LINEARBURN_EXT = 1000148026,
    VK_BLEND_OP_VIVIDLIGHT_EXT = 1000148027,
    VK_BLEND_OP_LINEARLIGHT_EXT = 1000148028,
    VK_BLEND_OP_PINLIGHT_EXT = 1000148029,
    VK_BLEND_OP_HARDMIX_EXT = 1000148030,
    VK_BLEND_OP_HSL_HUE_EXT = 1000148031,
    VK_BLEND_OP_HSL_SATURATION_EXT = 1000148032,
    VK_BLEND_OP_HSL_COLOR_EXT = 1000148033,
    VK_BLEND_OP_HSL_LUMINOSITY_EXT = 1000148034,
    VK_BLEND_OP_PLUS_EXT = 1000148035,
    VK_BLEND_OP_PLUS_CLAMPED_EXT = 1000148036,
    VK_BLEND_OP_PLUS_CLAMPED_ALPHA_EXT = 1000148037,
    VK_BLEND_OP_PLUS_DARKER_EXT = 1000148038,
    VK_BLEND_OP_MINUS_EXT = 1000148039,
    VK_BLEND_OP_MINUS_CLAMPED_EXT = 1000148040,
    VK_BLEND_OP_CONTRAST_EXT = 1000148041,
    VK_BLEND_OP_INVERT_OVG_EXT = 1000148042,
    VK_BLEND_OP_RED_EXT = 1000148043,
    VK_BLEND_OP_GREEN_EXT = 1000148044,
    VK_BLEND_OP_BLUE_EXT = 1000148045,
    VK_BLEND_OP_BEGIN_RANGE = VK_BLEND_OP_ADD,
    VK_BLEND_OP_END_RANGE = VK_BLEND_OP_MAX,
    VK_BLEND_OP_RANGE_SIZE = (VK_BLEND_OP_MAX - VK_BLEND_OP_ADD + 1),
    VK_BLEND_OP_MAX_ENUM = 0x7FFFFFFF
};

enum VkColorComponentFlags
{
    VK_COLOR_COMPONENT_R_BIT = 0x00000001,
    VK_COLOR_COMPONENT_G_BIT = 0x00000002,
    VK_COLOR_COMPONENT_B_BIT = 0x00000004,
    VK_COLOR_COMPONENT_A_BIT = 0x00000008,
    VK_COLOR_COMPONENT_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
};
