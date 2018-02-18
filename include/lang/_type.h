/* _type.h
 *
 * This file contains generated C type definitions.
 * You should not manually modify the contents of this file.
 */

#ifndef CORTO_LANG__TYPE_H
#define CORTO_LANG__TYPE_H

#include <corto/platform.h>
#ifdef __cplusplus
extern "C" {
#endif

/* -- Native types -- */
#ifndef CORTO_LANG_H
#endif


/* -- Type definitions -- */

/* typeKind */
typedef enum corto_typeKind {
    CORTO_VOID = 0,
    CORTO_ANY = 1,
    CORTO_PRIMITIVE = 2,
    CORTO_COMPOSITE = 3,
    CORTO_COLLECTION = 4,
    CORTO_ITERATOR = 5
} corto_typeKind;

/* bool */
typedef bool corto_bool;

/* attr */
typedef uint32_t corto_attr;
    #define CORTO_ATTR_NAMED (0x1)
    #define CORTO_ATTR_WRITABLE (0x2)
    #define CORTO_ATTR_OBSERVABLE (0x4)
    #define CORTO_ATTR_PERSISTENT (0x8)
    #define CORTO_ATTR_DEFAULT (0x10)

/*  type */
typedef struct corto_type_s *corto_type;

/* state */
typedef uint32_t corto_state;
    #define CORTO_VALID (0x1)
    #define CORTO_DELETED (0x2)
    #define CORTO_DECLARED (0x4)

/*  typeOptions */
typedef struct corto_typeOptions corto_typeOptions;

struct corto_typeOptions {
    corto_type parentType;
    corto_state parentState;
    corto_type defaultType;
    corto_type defaultProcedureType;
};

/* uint16 */
typedef uint16_t corto_uint16;

/* uint32 */
typedef uint32_t corto_uint32;

/* object */
typedef void *corto_object;

typedef struct corto_objectseq {uint32_t length; corto_object *buffer;} corto_objectseq;

/* string */
typedef char* corto_string;

/* inout */
typedef enum corto_inout {
    CORTO_IN = 0,
    CORTO_OUT = 1,
    CORTO_INOUT = 2
} corto_inout;

/*  parameter */
typedef struct corto_parameter corto_parameter;

struct corto_parameter {
    corto_string name;
    corto_type type;
    corto_inout inout;
    bool passByReference;
};

typedef struct corto_parameterseq {uint32_t length; corto_parameter *buffer;} corto_parameterseq;

/* word */
typedef uintptr_t corto_word;

/*  function */
typedef struct corto_function_s *corto_function;

struct corto_function_s {
    corto_type returnType;
    bool returnsReference;
    corto_parameterseq parameters;
    bool overridable;
    bool overloaded;
    uint32_t kind;
    uintptr_t impl;
    uintptr_t fptr;
    uintptr_t fdata;
    uint16_t size;
};

/*  delegatedata */
typedef struct corto_delegatedata corto_delegatedata;

struct corto_delegatedata {
    corto_object instance;
    corto_function procedure;
};

/*  pre_action */
typedef struct corto_pre_action corto_pre_action;

struct corto_pre_action {
    corto_delegatedata super;
};

/*  post_action */
typedef struct corto_post_action corto_post_action;

struct corto_post_action {
    corto_delegatedata super;
};

/*  name_action */
typedef struct corto_name_action corto_name_action;

struct corto_name_action {
    corto_delegatedata super;
};

struct corto_type_s {
    corto_typeKind kind;
    bool reference;
    corto_attr attr;
    corto_typeOptions options;
    uint16_t flags;
    uint32_t size;
    uint16_t alignment;
    corto_objectseq metaprocedures;
    corto_pre_action init;
    corto_post_action deinit;
    corto_name_action nameof;
};

/* modifier */
typedef uint32_t corto_modifier;
    #define CORTO_GLOBAL (0x0)
    #define CORTO_LOCAL (0x1)
    #define CORTO_PRIVATE (0x2)
    #define CORTO_READONLY (0x4)
    #define CORTO_CONST (0x8)
    #define CORTO_NOT_NULL (0x10)
    #define CORTO_HIDDEN (0x20)
    #define CORTO_OPTIONAL (0x40)
    #define CORTO_OBSERVABLE (0x80)
    #define CORTO_KEY (0x104)

/*  unit */
typedef struct corto_unit_s *corto_unit;

/*  quantity */
typedef struct corto_quantity_s *corto_quantity;

struct corto_quantity_s {
    corto_unit base_unit;
};

struct corto_unit_s {
    corto_quantity quantity;
    corto_string symbol;
    corto_string conversion;
    corto_type type;
    uintptr_t toQuantity;
    uintptr_t fromQuantity;
};

/* int8 */
typedef int8_t corto_int8;

/*  tag */
typedef struct corto_tag_s *corto_tag;

struct corto_tag_s {
    int8_t __dummy;
};

#ifndef corto_taglist_DEFINED
#define corto_taglist_DEFINED
typedef corto_ll corto_taglist;
#endif

/*  member */
typedef struct corto_member_s *corto_member;

struct corto_member_s {
    corto_type type;
    corto_modifier modifiers;
    corto_string _default;
    corto_unit unit;
    corto_taglist tags;
    corto_state state;
    corto_string stateCondExpr;
    uint32_t id;
    uint32_t offset;
};

/*  alias */
typedef struct corto_alias_s *corto_alias;

struct corto_alias_s {
    struct corto_member_s super;
    corto_member member;
};

/* any */
typedef struct corto_any {corto_type type; void *value; uint8_t owner;} corto_any;

#ifndef corto_stringlist_DEFINED
#define corto_stringlist_DEFINED
typedef corto_ll corto_stringlist;
#endif

/*  package */
typedef struct corto_package_s *corto_package;

struct corto_package_s {
    corto_string description;
    corto_string version;
    corto_string author;
    corto_string organization;
    corto_string url;
    corto_string repository;
    corto_string license;
    corto_string icon;
    corto_stringlist use;
    bool _public;
    bool managed;
};

/*  application */
typedef struct corto_application_s *corto_application;

struct corto_application_s {
    struct corto_package_s super;
};

/* collectionKind */
typedef enum corto_collectionKind {
    CORTO_ARRAY = 0,
    CORTO_SEQUENCE = 1,
    CORTO_LIST = 2,
    CORTO_MAP = 3
} corto_collectionKind;

/*  collection */
typedef struct corto_collection_s *corto_collection;

struct corto_collection_s {
    struct corto_type_s super;
    corto_collectionKind kind;
    corto_type elementType;
    uint32_t max;
};

/*  array */
typedef struct corto_array_s *corto_array;

struct corto_array_s {
    struct corto_collection_s super;
    corto_type elementType;
};

/* primitiveKind */
typedef enum corto_primitiveKind {
    CORTO_BINARY = 0,
    CORTO_BOOLEAN = 1,
    CORTO_CHARACTER = 2,
    CORTO_INTEGER = 3,
    CORTO_UINTEGER = 4,
    CORTO_FLOAT = 5,
    CORTO_TEXT = 6,
    CORTO_ENUM = 7,
    CORTO_BITMASK = 8
} corto_primitiveKind;

/* width */
typedef enum corto_width {
    CORTO_WIDTH_8 = 0,
    CORTO_WIDTH_16 = 1,
    CORTO_WIDTH_32 = 2,
    CORTO_WIDTH_64 = 3,
    CORTO_WIDTH_WORD = 4
} corto_width;

/* uint8 */
typedef uint8_t corto_uint8;

/*  primitive */
typedef struct corto_primitive_s *corto_primitive;

struct corto_primitive_s {
    struct corto_type_s super;
    corto_primitiveKind kind;
    corto_width width;
    uint8_t convertId;
};

/*  binary */
typedef struct corto_binary_s *corto_binary;

struct corto_binary_s {
    struct corto_primitive_s super;
};

/*  enum */
typedef struct corto_enum_s *corto_enum;

struct corto_enum_s {
    struct corto_primitive_s super;
    corto_objectseq constants;
};

/*  bitmask */
typedef struct corto_bitmask_s *corto_bitmask;

struct corto_bitmask_s {
    struct corto_enum_s super;
};

/*  boolean */
typedef struct corto_boolean_s *corto_boolean;

struct corto_boolean_s {
    struct corto_primitive_s super;
};

/* int32 */
typedef int32_t corto_int32;

typedef struct corto_int32seq {uint32_t length; int32_t *buffer;} corto_int32seq;

/*  case */
typedef struct corto_case_s *corto_case;

struct corto_case_s {
    struct corto_member_s super;
    corto_int32seq discriminator;
};

/* char */
typedef char corto_char;

/*  character */
typedef struct corto_character_s *corto_character;

struct corto_character_s {
    struct corto_primitive_s super;
};

/* compositeKind */
typedef enum corto_compositeKind {
    CORTO_INTERFACE = 0,
    CORTO_STRUCT = 1,
    CORTO_UNION = 2,
    CORTO_CLASS = 3,
    CORTO_DELEGATE = 4,
    CORTO_PROCEDURE = 5
} corto_compositeKind;

/*  interface */
typedef struct corto_interface_s *corto_interface;

struct corto_interface_s {
    struct corto_type_s super;
    corto_compositeKind kind;
    uint32_t nextMemberId;
    corto_objectseq members;
    corto_objectseq methods;
    corto_interface base;
    uintptr_t freeops;
};

typedef struct corto_stringseq {uint32_t length; corto_string *buffer;} corto_stringseq;

/*  struct */
typedef struct corto_struct_s *corto_struct;

struct corto_struct_s {
    struct corto_interface_s super;
    corto_modifier baseAccess;
    corto_stringseq keys;
    corto_objectseq keycache;
};

typedef struct corto_interfaceseq {uint32_t length; corto_interface *buffer;} corto_interfaceseq;

/*  interfaceVector */
typedef struct corto_interfaceVector corto_interfaceVector;

struct corto_interfaceVector {
    corto_interface interface;
    corto_objectseq vector;
};

typedef struct corto_interfaceVectorseq {uint32_t length; corto_interfaceVector *buffer;} corto_interfaceVectorseq;

/*  class */
typedef struct corto_class_s *corto_class;

struct corto_class_s {
    struct corto_struct_s super;
    corto_interfaceseq implements;
    corto_interfaceVectorseq interfaceVector;
    corto_pre_action construct;
    corto_post_action define;
    corto_pre_action validate;
    corto_post_action update;
    corto_post_action destruct;
    corto_post_action _delete;
};

/* constant */
typedef int32_t corto_constant;

/*  container */
typedef struct corto_container_s *corto_container;

struct corto_container_s {
    struct corto_class_s super;
    corto_type type;
    corto_string value;
};

/*  default */
typedef struct corto_default_s *corto_default;

struct corto_default_s {
    struct corto_case_s super;
};

/*  delegate */
typedef struct corto_delegate_s *corto_delegate;

struct corto_delegate_s {
    struct corto_struct_s super;
    corto_type returnType;
    bool returnsReference;
    corto_parameterseq parameters;
};

/* equalityKind */
typedef enum corto_equalityKind {
    CORTO_EQ = 0,
    CORTO_LT = -1,
    CORTO_GT = 1,
    CORTO_NEQ = 2
} corto_equalityKind;

/* float64 */
typedef double corto_float64;

/*  float */
typedef struct corto_float_s *corto_float;

struct corto_float_s {
    struct corto_primitive_s super;
    double min;
    double max;
};

/* float32 */
typedef float corto_float32;

/* int64 */
typedef int64_t corto_int64;

/*  int */
typedef struct corto_int_s *corto_int;

struct corto_int_s {
    struct corto_primitive_s super;
    int64_t min;
    int64_t max;
};

/* int16 */
typedef int16_t corto_int16;

/*  iterator */
typedef struct corto_iterator_s *corto_iterator;

struct corto_iterator_s {
    struct corto_type_s super;
    corto_type elementType;
};

/*  leaf */
typedef struct corto_leaf_s *corto_leaf;

struct corto_leaf_s {
    struct corto_container_s super;
};

/*  list */
typedef struct corto_list_s *corto_list;

struct corto_list_s {
    struct corto_collection_s super;
};

/*  map */
typedef struct corto_map_s *corto_map;

struct corto_map_s {
    struct corto_collection_s super;
    corto_type keyType;
    corto_type elementType;
    uint32_t max;
};

/*  metaprocedure */
typedef struct corto_metaprocedure_s *corto_metaprocedure;

struct corto_metaprocedure_s {
    struct corto_function_s super;
    bool referenceOnly;
};

/*  method */
typedef struct corto_method_s *corto_method;

struct corto_method_s {
    struct corto_function_s super;
    uint32_t index;
};

#ifndef corto_objectlist_DEFINED
#define corto_objectlist_DEFINED
typedef corto_ll corto_objectlist;
#endif

/* octet */
typedef uint8_t corto_octet;

/*  overridable */
typedef struct corto_overridable_s *corto_overridable;

struct corto_overridable_s {
    struct corto_method_s super;
};

/*  override */
typedef struct corto_override_s *corto_override;

struct corto_override_s {
    struct corto_method_s super;
};

/*  procedure */
typedef struct corto_procedure_s *corto_procedure;

struct corto_procedure_s {
    struct corto_class_s super;
    bool hasThis;
    corto_type thisType;
};

/*  sequence */
typedef struct corto_sequence_s *corto_sequence;

struct corto_sequence_s {
    struct corto_collection_s super;
};

/*  table */
typedef struct corto_table_s *corto_table;

struct corto_table_s {
    struct corto_container_s super;
};

/*  tableinstance */
typedef struct corto_tableinstance_s *corto_tableinstance;

struct corto_tableinstance_s {
    corto_type type;
};

/*  target */
typedef struct corto_target_s *corto_target;

struct corto_target_s {
    struct corto_struct_s super;
    corto_type type;
};

/* uint64 */
typedef uint64_t corto_uint64;

/*  text */
typedef struct corto_text_s *corto_text;

struct corto_text_s {
    struct corto_primitive_s super;
    corto_width charWidth;
    uint64_t length;
};

/*  tool */
typedef struct corto_tool_s *corto_tool;

struct corto_tool_s {
    struct corto_package_s super;
};

/*  uint */
typedef struct corto_uint_s *corto_uint;

struct corto_uint_s {
    struct corto_primitive_s super;
    uint64_t min;
    uint64_t max;
};

/*  union */
typedef struct corto_union_s *corto_union;

struct corto_union_s {
    struct corto_interface_s super;
    corto_type discriminator;
};

/* unknown */
typedef void corto_unknown;

/*  verbatim */
typedef struct corto_verbatim_s *corto_verbatim;

struct corto_verbatim_s {
    struct corto_primitive_s super;
    corto_string contentType;
};

/* void */
typedef void corto_void;

typedef struct corto_wordseq {uint32_t length; uintptr_t *buffer;} corto_wordseq;


/* -- Casting macro's -- */
#define corto_typeKind(o) ((corto_typeKind*)corto_assert_type((corto_type)corto_typeKind_o, o))
#define corto_bool(o) ((bool*)corto_assert_type((corto_type)corto_bool_o, o))
#define corto_attr(o) ((corto_attr*)corto_assert_type((corto_type)corto_attr_o, o))
#define corto_state(o) ((corto_state*)corto_assert_type((corto_type)corto_state_o, o))
#define corto_typeOptions(o) ((corto_typeOptions*)corto_assert_type((corto_type)corto_typeOptions_o, o))
#define corto_uint16(o) ((uint16_t*)corto_assert_type((corto_type)corto_uint16_o, o))
#define corto_uint32(o) ((uint32_t*)corto_assert_type((corto_type)corto_uint32_o, o))
#define corto_object(o) ((corto_object)o)
#define corto_objectseq(o) ((corto_objectseq*)corto_assert_type((corto_type)corto_objectseq_o, o))
#define corto_string(o) ((corto_string*)corto_assert_type((corto_type)corto_string_o, o))
#define corto_inout(o) ((corto_inout*)corto_assert_type((corto_type)corto_inout_o, o))
#define corto_parameter(o) ((corto_parameter*)corto_assert_type((corto_type)corto_parameter_o, o))
#define corto_parameterseq(o) ((corto_parameterseq*)corto_assert_type((corto_type)corto_parameterseq_o, o))
#define corto_word(o) ((uintptr_t*)corto_assert_type((corto_type)corto_word_o, o))
#define corto_function(o) ((corto_function)corto_assert_type((corto_type)corto_function_o, o))
#define corto_delegatedata(o) ((corto_delegatedata*)corto_assert_type((corto_type)corto_delegatedata_o, o))
#define corto_pre_action(o) ((corto_pre_action*)corto_assert_type((corto_type)corto_pre_action_o, o))
#define corto_post_action(o) ((corto_post_action*)corto_assert_type((corto_type)corto_post_action_o, o))
#define corto_name_action(o) ((corto_name_action*)corto_assert_type((corto_type)corto_name_action_o, o))
#define corto_type(o) ((corto_type)corto_assert_type((corto_type)corto_type_o, o))
#define corto_modifier(o) ((corto_modifier*)corto_assert_type((corto_type)corto_modifier_o, o))
#define corto_quantity(o) ((corto_quantity)corto_assert_type((corto_type)corto_quantity_o, o))
#define corto_unit(o) ((corto_unit)corto_assert_type((corto_type)corto_unit_o, o))
#define corto_int8(o) ((int8_t*)corto_assert_type((corto_type)corto_int8_o, o))
#define corto_tag(o) ((corto_tag)corto_assert_type((corto_type)corto_tag_o, o))
#define corto_taglist(o) ((corto_taglist*)corto_assert_type((corto_type)corto_taglist_o, o))
#define corto_member(o) ((corto_member)corto_assert_type((corto_type)corto_member_o, o))
#define corto_alias(o) ((corto_alias)corto_assert_type((corto_type)corto_alias_o, o))
#define corto_any(o) ((corto_any*)corto_assert_type((corto_type)corto_any_o, o))
#define corto_stringlist(o) ((corto_stringlist*)corto_assert_type((corto_type)corto_stringlist_o, o))
#define corto_package(o) ((corto_package)corto_assert_type((corto_type)corto_package_o, o))
#define corto_application(o) ((corto_application)corto_assert_type((corto_type)corto_application_o, o))
#define corto_collectionKind(o) ((corto_collectionKind*)corto_assert_type((corto_type)corto_collectionKind_o, o))
#define corto_collection(o) ((corto_collection)corto_assert_type((corto_type)corto_collection_o, o))
#define corto_array(o) ((corto_array)corto_assert_type((corto_type)corto_array_o, o))
#define corto_primitiveKind(o) ((corto_primitiveKind*)corto_assert_type((corto_type)corto_primitiveKind_o, o))
#define corto_width(o) ((corto_width*)corto_assert_type((corto_type)corto_width_o, o))
#define corto_uint8(o) ((uint8_t*)corto_assert_type((corto_type)corto_uint8_o, o))
#define corto_primitive(o) ((corto_primitive)corto_assert_type((corto_type)corto_primitive_o, o))
#define corto_binary(o) ((corto_binary)corto_assert_type((corto_type)corto_binary_o, o))
#define corto_enum(o) ((corto_enum)corto_assert_type((corto_type)corto_enum_o, o))
#define corto_bitmask(o) ((corto_bitmask)corto_assert_type((corto_type)corto_bitmask_o, o))
#define corto_boolean(o) ((corto_boolean)corto_assert_type((corto_type)corto_boolean_o, o))
#define corto_int32(o) ((int32_t*)corto_assert_type((corto_type)corto_int32_o, o))
#define corto_int32seq(o) ((corto_int32seq*)corto_assert_type((corto_type)corto_int32seq_o, o))
#define corto_case(o) ((corto_case)corto_assert_type((corto_type)corto_case_o, o))
#define corto_char(o) ((char*)corto_assert_type((corto_type)corto_char_o, o))
#define corto_character(o) ((corto_character)corto_assert_type((corto_type)corto_character_o, o))
#define corto_compositeKind(o) ((corto_compositeKind*)corto_assert_type((corto_type)corto_compositeKind_o, o))
#define corto_interface(o) ((corto_interface)corto_assert_type((corto_type)corto_interface_o, o))
#define corto_stringseq(o) ((corto_stringseq*)corto_assert_type((corto_type)corto_stringseq_o, o))
#define corto_struct(o) ((corto_struct)corto_assert_type((corto_type)corto_struct_o, o))
#define corto_interfaceseq(o) ((corto_interfaceseq*)corto_assert_type((corto_type)corto_interfaceseq_o, o))
#define corto_interfaceVector(o) ((corto_interfaceVector*)corto_assert_type((corto_type)corto_interfaceVector_o, o))
#define corto_interfaceVectorseq(o) ((corto_interfaceVectorseq*)corto_assert_type((corto_type)corto_interfaceVectorseq_o, o))
#define corto_class(o) ((corto_class)corto_assert_type((corto_type)corto_class_o, o))
#define corto_constant(o) ((int32_t*)corto_assert_type((corto_type)corto_constant_o, o))
#define corto_container(o) ((corto_container)corto_assert_type((corto_type)corto_container_o, o))
#define corto_default(o) ((corto_default)corto_assert_type((corto_type)corto_default_o, o))
#define corto_delegate(o) ((corto_delegate)corto_assert_type((corto_type)corto_delegate_o, o))
#define corto_equalityKind(o) ((corto_equalityKind*)corto_assert_type((corto_type)corto_equalityKind_o, o))
#define corto_float64(o) ((double*)corto_assert_type((corto_type)corto_float64_o, o))
#define corto_float(o) ((corto_float)corto_assert_type((corto_type)corto_float_o, o))
#define corto_float32(o) ((float*)corto_assert_type((corto_type)corto_float32_o, o))
#define corto_int64(o) ((int64_t*)corto_assert_type((corto_type)corto_int64_o, o))
#define corto_int(o) ((corto_int)corto_assert_type((corto_type)corto_int_o, o))
#define corto_int16(o) ((int16_t*)corto_assert_type((corto_type)corto_int16_o, o))
#define corto_iterator(o) ((corto_iterator)corto_assert_type((corto_type)corto_iterator_o, o))
#define corto_leaf(o) ((corto_leaf)corto_assert_type((corto_type)corto_leaf_o, o))
#define corto_list(o) ((corto_list)corto_assert_type((corto_type)corto_list_o, o))
#define corto_map(o) ((corto_map)corto_assert_type((corto_type)corto_map_o, o))
#define corto_metaprocedure(o) ((corto_metaprocedure)corto_assert_type((corto_type)corto_metaprocedure_o, o))
#define corto_method(o) ((corto_method)corto_assert_type((corto_type)corto_method_o, o))
#define corto_objectlist(o) ((corto_objectlist*)corto_assert_type((corto_type)corto_objectlist_o, o))
#define corto_octet(o) ((uint8_t*)corto_assert_type((corto_type)corto_octet_o, o))
#define corto_overridable(o) ((corto_overridable)corto_assert_type((corto_type)corto_overridable_o, o))
#define corto_override(o) ((corto_override)corto_assert_type((corto_type)corto_override_o, o))
#define corto_procedure(o) ((corto_procedure)corto_assert_type((corto_type)corto_procedure_o, o))
#define corto_sequence(o) ((corto_sequence)corto_assert_type((corto_type)corto_sequence_o, o))
#define corto_table(o) ((corto_table)corto_assert_type((corto_type)corto_table_o, o))
#define corto_tableinstance(o) ((corto_tableinstance)corto_assert_type((corto_type)corto_tableinstance_o, o))
#define corto_target(o) ((corto_target)corto_assert_type((corto_type)corto_target_o, o))
#define corto_uint64(o) ((uint64_t*)corto_assert_type((corto_type)corto_uint64_o, o))
#define corto_text(o) ((corto_text)corto_assert_type((corto_type)corto_text_o, o))
#define corto_tool(o) ((corto_tool)corto_assert_type((corto_type)corto_tool_o, o))
#define corto_uint(o) ((corto_uint)corto_assert_type((corto_type)corto_uint_o, o))
#define corto_union(o) ((corto_union)corto_assert_type((corto_type)corto_union_o, o))
#define corto_unknown(o) ((void*)o)
#define corto_verbatim(o) ((corto_verbatim)corto_assert_type((corto_type)corto_verbatim_o, o))
#define corto_void(o) ((void*)o)
#define corto_wordseq(o) ((corto_wordseq*)corto_assert_type((corto_type)corto_wordseq_o, o))

/* -- Non-expanding typedefs -- */
typedef corto_typeKind _type_corto_typeKind;
typedef corto_bool _type_corto_bool;
typedef corto_attr _type_corto_attr;
typedef corto_state _type_corto_state;
typedef corto_typeOptions _type_corto_typeOptions;
typedef corto_uint16 _type_corto_uint16;
typedef corto_uint32 _type_corto_uint32;
typedef corto_object _type_corto_object;
typedef corto_objectseq _type_corto_objectseq;
typedef corto_string _type_corto_string;
typedef corto_inout _type_corto_inout;
typedef corto_parameter _type_corto_parameter;
typedef corto_parameterseq _type_corto_parameterseq;
typedef corto_word _type_corto_word;
typedef corto_function _type_corto_function;
typedef corto_delegatedata _type_corto_delegatedata;
typedef corto_pre_action _type_corto_pre_action;
typedef corto_post_action _type_corto_post_action;
typedef corto_name_action _type_corto_name_action;
typedef corto_type _type_corto_type;
typedef corto_modifier _type_corto_modifier;
typedef corto_quantity _type_corto_quantity;
typedef corto_unit _type_corto_unit;
typedef corto_int8 _type_corto_int8;
typedef corto_tag _type_corto_tag;
typedef corto_taglist _type_corto_taglist;
typedef corto_member _type_corto_member;
typedef corto_alias _type_corto_alias;
typedef corto_any _type_corto_any;
typedef corto_stringlist _type_corto_stringlist;
typedef corto_package _type_corto_package;
typedef corto_application _type_corto_application;
typedef corto_collectionKind _type_corto_collectionKind;
typedef corto_collection _type_corto_collection;
typedef corto_array _type_corto_array;
typedef corto_primitiveKind _type_corto_primitiveKind;
typedef corto_width _type_corto_width;
typedef corto_uint8 _type_corto_uint8;
typedef corto_primitive _type_corto_primitive;
typedef corto_binary _type_corto_binary;
typedef corto_enum _type_corto_enum;
typedef corto_bitmask _type_corto_bitmask;
typedef corto_boolean _type_corto_boolean;
typedef corto_int32 _type_corto_int32;
typedef corto_int32seq _type_corto_int32seq;
typedef corto_case _type_corto_case;
typedef corto_char _type_corto_char;
typedef corto_character _type_corto_character;
typedef corto_compositeKind _type_corto_compositeKind;
typedef corto_interface _type_corto_interface;
typedef corto_stringseq _type_corto_stringseq;
typedef corto_struct _type_corto_struct;
typedef corto_interfaceseq _type_corto_interfaceseq;
typedef corto_interfaceVector _type_corto_interfaceVector;
typedef corto_interfaceVectorseq _type_corto_interfaceVectorseq;
typedef corto_class _type_corto_class;
typedef corto_constant _type_corto_constant;
typedef corto_container _type_corto_container;
typedef corto_default _type_corto_default;
typedef corto_delegate _type_corto_delegate;
typedef corto_equalityKind _type_corto_equalityKind;
typedef corto_float64 _type_corto_float64;
typedef corto_float _type_corto_float;
typedef corto_float32 _type_corto_float32;
typedef corto_int64 _type_corto_int64;
typedef corto_int _type_corto_int;
typedef corto_int16 _type_corto_int16;
typedef corto_iterator _type_corto_iterator;
typedef corto_leaf _type_corto_leaf;
typedef corto_list _type_corto_list;
typedef corto_map _type_corto_map;
typedef corto_metaprocedure _type_corto_metaprocedure;
typedef corto_method _type_corto_method;
typedef corto_objectlist _type_corto_objectlist;
typedef corto_octet _type_corto_octet;
typedef corto_overridable _type_corto_overridable;
typedef corto_override _type_corto_override;
typedef corto_procedure _type_corto_procedure;
typedef corto_sequence _type_corto_sequence;
typedef corto_table _type_corto_table;
typedef corto_tableinstance _type_corto_tableinstance;
typedef corto_target _type_corto_target;
typedef corto_uint64 _type_corto_uint64;
typedef corto_text _type_corto_text;
typedef corto_tool _type_corto_tool;
typedef corto_uint _type_corto_uint;
typedef corto_union _type_corto_union;
typedef corto_unknown _type_corto_unknown;
typedef corto_verbatim _type_corto_verbatim;
typedef corto_void _type_corto_void;
typedef corto_wordseq _type_corto_wordseq;

#ifdef __cplusplus
}
#endif
#endif

