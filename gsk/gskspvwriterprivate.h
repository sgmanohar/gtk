/* GTK - The GIMP Toolkit
 *
 * Copyright © 2017 Benjamin Otte <otte@gnome.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __GSK_SPV_WRITER_PRIVATE_H__
#define __GSK_SPV_WRITER_PRIVATE_H__

#include <glib.h>

#include "gsksltypesprivate.h"

G_BEGIN_DECLS

#define GSK_SPV_MAGIC_NUMBER 0x07230203
#define GSK_SPV_VERSION_MAJOR 1
#define GSK_SPV_VERSION_MINOR 0
#define GSK_SPV_GENERATOR 0

typedef enum {
  GSK_SPV_OP_NOP = 0,
  GSK_SPV_OP_UNDEF = 1,
  GSK_SPV_OP_SOURCE_CONTINUED = 2,
  GSK_SPV_OP_SOURCE = 3,
  GSK_SPV_OP_SOURCE_EXTENSION = 4,
  GSK_SPV_OP_NAME = 5,
  GSK_SPV_OP_MEMBER_NAME = 6,
  GSK_SPV_OP_STRING = 7,
  GSK_SPV_OP_LINE = 8,
  GSK_SPV_OP_EXTENSION = 10,
  GSK_SPV_OP_EXT_INST_IMPORT = 11,
  GSK_SPV_OP_EXT_INST = 12,
  GSK_SPV_OP_MEMORY_MODEL = 14,
  GSK_SPV_OP_ENTRY_POINT = 15,
  GSK_SPV_OP_EXECUTION_MODE = 16,
  GSK_SPV_OP_CAPABILITY = 17,
  GSK_SPV_OP_TYPE_VOID = 19,
  GSK_SPV_OP_TYPE_BOOL = 20,
  GSK_SPV_OP_TYPE_INT = 21,
  GSK_SPV_OP_TYPE_FLOAT = 22,
  GSK_SPV_OP_TYPE_VECTOR = 23,
  GSK_SPV_OP_TYPE_MATRIX = 24,
  GSK_SPV_OP_TYPE_IMAGE = 25,
  GSK_SPV_OP_TYPE_SAMPLER = 26,
  GSK_SPV_OP_TYPE_SAMPLED_IMAGE = 27,
  GSK_SPV_OP_TYPE_ARRAY = 28,
  GSK_SPV_OP_TYPE_RUNTIME_ARRAY = 29,
  GSK_SPV_OP_TYPE_STRUCT = 30,
  GSK_SPV_OP_TYPE_OPAQUE = 31,
  GSK_SPV_OP_TYPE_POINTER = 32,
  GSK_SPV_OP_TYPE_FUNCTION = 33,
  GSK_SPV_OP_TYPE_EVENT = 34,
  GSK_SPV_OP_TYPE_DEVICE_EVENT = 35,
  GSK_SPV_OP_TYPE_RESERVE_ID = 36,
  GSK_SPV_OP_TYPE_QUEUE = 37,
  GSK_SPV_OP_TYPE_PIPE = 38,
  GSK_SPV_OP_TYPE_FORWARD_POINTER = 39,
  GSK_SPV_OP_CONSTANT_TRUE = 41,
  GSK_SPV_OP_CONSTANT_FALSE = 42,
  GSK_SPV_OP_CONSTANT = 43,
  GSK_SPV_OP_CONSTANT_COMPOSITE = 44,
  GSK_SPV_OP_CONSTANT_SAMPLER = 45,
  GSK_SPV_OP_CONSTANT_NULL = 46,
  GSK_SPV_OP_SPEC_CONSTANT_TRUE = 48,
  GSK_SPV_OP_SPEC_CONSTANT_FALSE = 49,
  GSK_SPV_OP_SPEC_CONSTANT = 50,
  GSK_SPV_OP_SPEC_CONSTANT_COMPOSITE = 51,
  GSK_SPV_OP_SPEC_CONSTANT_OP = 52,
  GSK_SPV_OP_FUNCTION = 54,
  GSK_SPV_OP_FUNCTION_PARAMETER = 55,
  GSK_SPV_OP_FUNCTION_END = 56,
  GSK_SPV_OP_FUNCTION_CALL = 57,
  GSK_SPV_OP_VARIABLE = 59,
  GSK_SPV_OP_IMAGE_TEXEL_POINTER = 60,
  GSK_SPV_OP_LOAD = 61,
  GSK_SPV_OP_STORE = 62,
  GSK_SPV_OP_COPY_MEMORY = 63,
  GSK_SPV_OP_COPY_MEMORY_SIZED = 64,
  GSK_SPV_OP_ACCESS_CHAIN = 65,
  GSK_SPV_OP_IN_BOUNDS_ACCESS_CHAIN = 66,
  GSK_SPV_OP_PTR_ACCESS_CHAIN = 67,
  GSK_SPV_OP_ARRAY_LENGTH = 68,
  GSK_SPV_OP_GENERIC_PTR_MEM_SEMANTICS = 69,
  GSK_SPV_OP_IN_BOUNDS_PTR_ACCESS_CHAIN = 70,
  GSK_SPV_OP_DECORATE = 71,
  GSK_SPV_OP_MEMBER_DECORATE = 72,
  GSK_SPV_OP_DECORATION_GROUP = 73,
  GSK_SPV_OP_GROUP_DECORATE = 74,
  GSK_SPV_OP_GROUP_MEMBER_DECORATE = 75,
  GSK_SPV_OP_VECTOR_EXTRACT_DYNAMIC = 77,
  GSK_SPV_OP_VECTOR_INSERT_DYNAMIC = 78,
  GSK_SPV_OP_VECTOR_SHUFFLE = 79,
  GSK_SPV_OP_COMPOSITE_CONSTRUCT = 80,
  GSK_SPV_OP_COMPOSITE_EXTRACT = 81,
  GSK_SPV_OP_COMPOSITE_INSERT = 82,
  GSK_SPV_OP_COPY_OBJECT = 83,
  GSK_SPV_OP_TRANSPOSE = 84,
  GSK_SPV_OP_CONVERT_F_TO_U = 109,
  GSK_SPV_OP_CONVERT_F_TO_S = 110,
  GSK_SPV_OP_CONVERT_S_TO_F = 111,
  GSK_SPV_OP_CONVERT_U_TO_F = 112,
  GSK_SPV_OP_U_CONVERT = 113,
  GSK_SPV_OP_S_CONVERT = 114,
  GSK_SPV_OP_F_CONVERT = 115,
  GSK_SPV_OP_QUANTIZE_TO_F16 = 116,
  GSK_SPV_OP_CONVERT_PTR_TO_U = 117,
  GSK_SPV_OP_SAT_CONVERT_S_TO_U = 118,
  GSK_SPV_OP_SAT_CONVERT_U_TO_S = 119,
  GSK_SPV_OP_CONVERT_U_TO_PTR = 120,
  GSK_SPV_OP_PTR_CAST_TO_GENERIC = 121,
  GSK_SPV_OP_GENERIC_CAST_TO_PTR = 122,
  GSK_SPV_OP_GENERIC_CAST_TO_PTR_EXPLICIT = 123,
  GSK_SPV_OP_BITCAST = 124,
  GSK_SPV_OP_S_NEGATE = 126,
  GSK_SPV_OP_F_NEGATE = 127,
  GSK_SPV_OP_I_ADD = 128,
  GSK_SPV_OP_F_ADD = 129,
  GSK_SPV_OP_I_SUB = 130,
  GSK_SPV_OP_F_SUB = 131,
  GSK_SPV_OP_I_MUL = 132,
  GSK_SPV_OP_F_MUL = 133,
  GSK_SPV_OP_U_DIV = 134,
  GSK_SPV_OP_S_DIV = 135,
  GSK_SPV_OP_F_DIV = 136,
  GSK_SPV_OP_U_MOD = 137,
  GSK_SPV_OP_S_REM = 138,
  GSK_SPV_OP_S_MOD = 139,
  GSK_SPV_OP_F_REM = 140,
  GSK_SPV_OP_F_MOD = 141,
  GSK_SPV_OP_VECTOR_TIMES_SCALAR = 142,
  GSK_SPV_OP_MATRIX_TIMES_SCALAR = 143,
  GSK_SPV_OP_VECTOR_TIMES_MATRIX = 144,
  GSK_SPV_OP_MATRIX_TIMES_VECTOR = 145,
  GSK_SPV_OP_MATRIX_TIMES_MATRIX = 146,
  GSK_SPV_OP_OUTER_PRODUCT = 147,
  GSK_SPV_OP_DOT = 148,
  GSK_SPV_OP_I_ADD_CARRY = 149,
  GSK_SPV_OP_I_SUB_BORROW = 150,
  GSK_SPV_OP_U_MUL_EXTENDED = 151,
  GSK_SPV_OP_S_MUL_EXTENDED = 152,
  GSK_SPV_OP_ANY = 154,
  GSK_SPV_OP_ALL = 155,
  GSK_SPV_OP_IS_NAN = 156,
  GSK_SPV_OP_IS_INF = 157,
  GSK_SPV_OP_IS_FINITE = 158,
  GSK_SPV_OP_IS_NORMAL = 159,
  GSK_SPV_OP_SIGN_BIT_SET = 160,
  GSK_SPV_OP_LESS_OR_GREATER = 161,
  GSK_SPV_OP_ORDERED = 162,
  GSK_SPV_OP_UNORDERED = 163,
  GSK_SPV_OP_LOGICAL_EQUAL = 164,
  GSK_SPV_OP_LOGICAL_NOT_EQUAL = 165,
  GSK_SPV_OP_LOGICAL_OR = 166,
  GSK_SPV_OP_LOGICAL_AND = 167,
  GSK_SPV_OP_LOGICAL_NOT = 168,
  GSK_SPV_OP_SELECT = 169,
  GSK_SPV_OP_I_EQUAL = 170,
  GSK_SPV_OP_I_NOT_EQUAL = 171,
  GSK_SPV_OP_U_GREATER_THAN = 172,
  GSK_SPV_OP_S_GREATER_THAN = 173,
  GSK_SPV_OP_U_GREATER_THAN_EQUAL = 174,
  GSK_SPV_OP_S_GREATER_THAN_EQUAL = 175,
  GSK_SPV_OP_U_LESS_THAN = 176,
  GSK_SPV_OP_S_LESS_THAN = 177,
  GSK_SPV_OP_U_LESS_THAN_EQUAL = 178,
  GSK_SPV_OP_S_LESS_THAN_EQUAL = 179,
  GSK_SPV_OP_F_ORD_EQUAL = 180,
  GSK_SPV_OP_F_UNORD_EQUAL = 181,
  GSK_SPV_OP_F_ORD_NOT_EQUAL = 182,
  GSK_SPV_OP_F_UNORD_NOT_EQUAL = 183,
  GSK_SPV_OP_F_ORD_LESS_THAN = 184,
  GSK_SPV_OP_F_UNORD_LESS_THAN = 185,
  GSK_SPV_OP_F_ORD_GREATER_THAN = 186,
  GSK_SPV_OP_F_UNORD_GREATER_THAN = 187,
  GSK_SPV_OP_F_ORD_LESS_THAN_EQUAL = 188,
  GSK_SPV_OP_F_UNORD_LESS_THAN_EQUAL = 189,
  GSK_SPV_OP_F_ORD_GREATER_THAN_EQUAL = 190,
  GSK_SPV_OP_F_UNORD_GREATER_THAN_EQUAL = 191,
  GSK_SPV_OP_PHI = 245,
  GSK_SPV_OP_LOOP_MERGE = 246,
  GSK_SPV_OP_SELECTION_MERGE = 247,
  GSK_SPV_OP_LABEL = 248,
  GSK_SPV_OP_BRANCH = 249,
  GSK_SPV_OP_BRANCH_CONDITIONAL = 250,
  GSK_SPV_OP_SWITCH = 251,
  GSK_SPV_OP_KILL = 252,
  GSK_SPV_OP_RETURN = 253,
  GSK_SPV_OP_RETURN_VALUE = 254,
  GSK_SPV_OP_UNREACHABLE = 255,
  GSK_SPV_OP_LIFETIME_START = 256,
  GSK_SPV_OP_LIFETIME_STOP = 257,
  GSK_SPV_OP_SIZE_OF = 321,
  GSK_SPV_OP_TYPE_PIPE_STORAGE = 322,
  GSK_SPV_OP_TYPE_NAMED_BARRIER = 327,
  GSK_SPV_OP_DECORATE_ID = 332
} GskSpvOpcode;

typedef enum {
  GSK_SPV_CAPABILITY_MATRIX = 0,
  GSK_SPV_CAPABILITY_SHADER = 1
} GskSpvCapability;

typedef enum {
  GSK_SPV_ADDRESSING_LOGICAL = 0,
  GSK_SPV_ADDRESSING_PHYSICAL32 = 1,
  GSK_SPV_ADDRESSING_PHYSICAL64 = 2,
} GskSpvAddressingModel;

typedef enum {
  GSK_SPV_MEMORY_SIMPLE = 0,
  GSK_SPV_MEMORY_GLSL450 = 1,
  GSK_SPV_MEMORY_OPEN_CL = 2
} GskSpvMemoryModel;

typedef enum {
  GSK_SPV_EXECUTION_MODEL_VERTEX = 0,
  GSK_SPV_EXECUTION_MODEL_TESSELATION_CONTROL = 1,
  GSK_SPV_EXECUTION_MODEL_TESSELATION_EVALUATION = 2,
  GSK_SPV_EXECUTION_MODEL_GEOMETRY = 3,
  GSK_SPV_EXECUTION_MODEL_FRAGMENT = 4,
  GSK_SPV_EXECUTION_MODEL_GL_COMPUTE = 5,
  GSK_SPV_EXECUTION_MODEL_KERNEL = 6,
} GskSpvExecutionModel;

typedef enum {
  GSK_SPV_EXECUTION_MODE_ORIGIN_UPPER_LEFT = 7
} GskSpvExecutionMode;

typedef enum {
  GSK_SPV_STORAGE_CLASS_UNIFORM_CONSTANT = 0,
  GSK_SPV_STORAGE_CLASS_INPUT = 1,
  GSK_SPV_STORAGE_CLASS_UNIFORM = 2,
  GSK_SPV_STORAGE_CLASS_OUTPUT = 3,
  GSK_SPV_STORAGE_CLASS_WORKGROUP = 4,
  GSK_SPV_STORAGE_CLASS_CROSS_WORKGROUP = 5,
  GSK_SPV_STORAGE_CLASS_PRIVATE = 6,
  GSK_SPV_STORAGE_CLASS_FUNCTION = 7,
  GSK_SPV_STORAGE_CLASS_GENERIC = 8,
  GSK_SPV_STORAGE_CLASS_PUSH_CONSTANT = 9,
  GSK_SPV_STORAGE_CLASS_ATOMIC_COUNTER = 10,
  GSK_SPV_STORAGE_CLASS_IMAGE = 11,
  GSK_SPV_STORAGE_CLASS_STORAGE_BUFFER = 12
} GskSpvStorageClass;

typedef enum {
  GSK_SPV_DECORATION_RELAXED_PRECISION = 0,
  GSK_SPV_DECORATION_SPEC_ID = 1,
  GSK_SPV_DECORATION_BLOCK = 2,
  GSK_SPV_DECORATION_BUFFER_BLOCK = 3,
  GSK_SPV_DECORATION_ROW_MAJOR = 4,
  GSK_SPV_DECORATION_COLUMN_MAJOR = 5,
  GSK_SPV_DECORATION_ARRAY_STRIDE = 6,
  GSK_SPV_DECORATION_MATRIX_STRIDE = 7,
  GSK_SPV_DECORATION_GLSL_SHARED = 8,
  GSK_SPV_DECORATION_GLSL_PACKED = 9,
  GSK_SPV_DECORATION_C_PACKED = 10,
  GSK_SPV_DECORATION_BUILTIN = 11,
  GSK_SPV_DECORATION_NO_PERSPECTIVE = 13,
  GSK_SPV_DECORATION_FLAT = 14,
  GSK_SPV_DECORATION_PATCH = 15,
  GSK_SPV_DECORATION_CENTROID = 16,
  GSK_SPV_DECORATION_SAMPLE = 17,
  GSK_SPV_DECORATION_INVARIANT = 18,
  GSK_SPV_DECORATION_RESTRICT = 19,
  GSK_SPV_DECORATION_ALIASED = 20
} GskSpvDecoration;

typedef enum {
  GSK_SPV_WRITER_SECTION_HEADER,
  GSK_SPV_WRITER_SECTION_DEBUG,
  GSK_SPV_WRITER_SECTION_DECLARE,
  GSK_SPV_WRITER_SECTION_CODE,
  /* add more */
  GSK_SPV_WRITER_N_SECTIONS
} GskSpvWriterSection;

GskSpvWriter *          gsk_spv_writer_new                      (void);

GskSpvWriter *          gsk_spv_writer_ref                      (GskSpvWriter           *writer);
void                    gsk_spv_writer_unref                    (GskSpvWriter           *writer);

GBytes *                gsk_spv_writer_write                    (GskSpvWriter           *writer);
void                    gsk_spv_writer_set_entry_point          (GskSpvWriter           *writer,
                                                                 guint32                 entry_point);

guint32                 gsk_spv_writer_get_id_for_type          (GskSpvWriter           *writer,
                                                                 GskSlType              *type);
guint32                 gsk_spv_writer_get_id_for_pointer_type  (GskSpvWriter           *writer,
                                                                 GskSlPointerType       *type);
guint32                 gsk_spv_writer_get_id_for_value         (GskSpvWriter           *writer,
                                                                 GskSlValue             *value);
guint32                 gsk_spv_writer_get_id_for_zero          (GskSpvWriter           *writer,
                                                                 GskSlScalarType         scalar);
guint32                 gsk_spv_writer_get_id_for_one           (GskSpvWriter           *writer,
                                                                 GskSlScalarType         scalar);
guint32                 gsk_spv_writer_get_id_for_variable      (GskSpvWriter           *writer,
                                                                 GskSlVariable          *variable);

guint32                 gsk_spv_writer_next_id                  (GskSpvWriter           *writer);
void                    gsk_spv_writer_add                      (GskSpvWriter           *writer,
                                                                 GskSpvWriterSection     section,
                                                                 guint16                 word_count,
                                                                 guint16                 opcode,
                                                                 guint32                *words);

guint32                 gsk_spv_writer_add_conversion           (GskSpvWriter           *writer,
                                                                 guint32                 id,
                                                                 GskSlType              *type,
                                                                 GskSlType              *new_type);

G_END_DECLS

#endif /* __GSK_SPV_WRITER_PRIVATE_H__ */