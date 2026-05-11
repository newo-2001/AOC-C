#include "regex.h"
#include "collections/list.h"
#include <string.h>

typedef enum NodeType
{
    NODE_LITERAL,
    NODE_WILDCARD,
    NODE_GROUP,
    NODE_CAPTURE_GROUP,
    NODE_OR,
} NodeType;

typedef struct LiteralNode
{
    str_t str;
} LiteralNode;

typedef struct GroupNode
{
    Node* child;
} GroupNode;

typedef enum Quantifier
{
    QUANT_ONCE,
    QUANT_MANY,
    QUANT_MANY1
} Quantifier;

typedef struct RepeatMode
{
    Quantifier quantifier;
    bool is_lazy;
} RepeatMode;

typedef struct Node
{
    NodeType type;
    RepeatMode repeat_mode;

    union
    {
        LiteralNode literal;
        GroupNode group;
    } value;
} Node;

typedef struct Regex
{
    Node root_node;
    int capture_group_count;
} Regex;

bool regex_compile(str_t str, Regex* out_regex) {}

bool static read_node(str_t* str, Node* out_node)
{
    out_node->repeat_mode = read_repeat_mode(out_node);

    return true;
}

static Quantifier read_quantifier(str_t* str)
{
    Quantifier quantifier;

    if (str->length == 0)
    {
        return QUANT_ONCE;
    }

    switch (*str->data)
    {
        case '*':
            quantifier = QUANT_MANY;
            break;
        case '+':
            quantifier = QUANT_MANY1;
            break;
        default:
            return QUANT_ONCE;
    }

    *str = str_sub(*str, 1, str->length);
    return quantifier;
}

static RepeatMode read_repeat_mode(str_t* str)
{
    RepeatMode repeat_mode;
    repeat_mode.quantifier = read_quantifier(str);

    if (repeat_mode.quantifier == QUANT_ONCE)
    {
        return repeat_mode;
    }

    if (str->length > 0 && *str->data == '?')
    {
        repeat_mode.is_lazy = true;
        *str = str_sub(*str, 1, str->length);
    }

    return repeat_mode;
}

void regex_captures(Regex* regex, str_t str) {}

void regex_destroy(Regex* regex) {}

// regex := <expr>
//
// expr  := | <quantified_sub_expr>
//          | <expr> <quantified_sub_expr>
//
// quantified_sub_expr := | <sub_expr>
//                        | <sub_expr> <quantifier>
//
// sub_expr := | <literal>
//             | <wildcard>
//             | <non_capture_group>
//             | <capture_group>
//             | <or_pattern>
//             | <set>
//             | <negated_set>
//             | <start_anchor>
//             | <end_anchor>
//
// quantifier := | '*'
//               | '+'
//               | '?'
//               | <range_quantifier>
//
// range_quantifier := | '{' <number> '}'
//                     | '{' <number> ',}'
//                     | '{' <number> ',' <number> '}'
//
// number := | <digit>
//           | <number> <digit>
//
// digit := any_of('0123456789')
//
// string_literal := | <literal>
//                   | <string_literal> <literal>
//
// literal := | not(<special_char>)
//            | '\' any()
//
// special_char := any_of('.^$*+?()[{\|')
//
// wildcard          := '.'
// non_capture_group := '(?' <expr> ')'
// capture_group     := '(' <expr> ')'
// start_anchor      := '^'
// end_anchor        := '$'
//
// or_pattern := | <expr> '|' <expr>
//               | <or_pattern> '|' <expr>
//
// set         := '[' <set_expr> ']'
// negated_set := '[^' <set_expr> ']'
//
// set_expr := | <set_value>
//             | <set_expr> <set_value>
//
// set_value := | <string_literal>
//              | <character_range>
//
// character_range := any() '-' any()