#include "../solvers.h"

#include <stdlib.h>
#include <assert.h>

#include <aoc_lib/strutils.h>
#include <aoc_lib/collections/hashmap.h>

typedef enum ExpressionType
{
    EXPR_LITERAL,
    EXPR_NOT,
    EXPR_AND,
    EXPR_OR,
    EXPR_LSHIFT,
    EXPR_RSHIFT
} ExpressionType;

typedef enum ValueType
{
    VAL_CONST,
    VAL_VAR
} ValueType;

typedef struct Value
{
    ValueType type;
    union
    {
        uint16_t constant;
        str_t variable;
    };
} Value;

typedef struct Expression
{
    ExpressionType type;
    Value left;
    Value right;
} Expression;

static Value parse_value(str_t str)
{
    Value value;

    if (str_parse_int(str, (int*) &value.constant))
    {
        value.type = VAL_CONST;
    }
    else
    {
        value.type = VAL_VAR;
        value.variable = str;
    }

    return value;
}

static void parse_expr(str_t str, HashMap* map)
{
    StrSpliterator it = str_split(str, STR_SLICE(" "));

    str_t token;
    str_split_next(&it, &token);

    Expression expr = { 0 };
    if (!str_cmp(STR_SLICE("NOT"), token))
    {
        expr.type = EXPR_NOT;

        str_split_next(&it, &token);
        expr.left = parse_value(token);
    }
    else
    {
        expr.left = parse_value(token);

        str_split_next(&it, &token);

        if (!str_cmp(STR_SLICE("AND"), token)) expr.type = EXPR_AND;
        else if (!str_cmp(STR_SLICE("OR"), token)) expr.type = EXPR_OR;
        else if (!str_cmp(STR_SLICE("LSHIFT"), token)) expr.type = EXPR_LSHIFT;
        else if (!str_cmp(STR_SLICE("RSHIFT"), token)) expr.type = EXPR_RSHIFT;
        else if (!str_cmp(STR_SLICE("->"), token)) expr.type = EXPR_LITERAL;

        if (expr.type != EXPR_LITERAL)
        {
            str_split_next(&it, &token);
            expr.right = parse_value(token);
        }
    }

    if (expr.type != EXPR_LITERAL)
    {
        // void " -> "
        str_split_next(&it, &token);
    }

    str_split_next(&it, &token);
    hashmap_insert(map, &token, &expr);
}

static uint16_t value_eval(HashMap circuit, HashMap cache, Value value);
static uint16_t expr_eval(HashMap circuit, HashMap cache, Expression expr)
{
    uint16_t left = value_eval(circuit, cache, expr.left);
    if (expr.type == EXPR_NOT) return ~left;
    else if (expr.type == EXPR_LITERAL) return left;

    uint16_t right = value_eval(circuit, cache, expr.right);
    switch (expr.type)
    {
        case EXPR_AND:
            return left & right;
        case EXPR_OR:
            return left | right;
        case EXPR_LSHIFT:
            return left << right;
        case EXPR_RSHIFT:
            return left >> right;
        default:
            assert(false);
    };

    assert(false);
    return 0;
}

static uint16_t value_eval(HashMap circuit, HashMap cache, Value value)
{
    if (value.type == VAL_CONST) return value.constant;
    assert(value.type == VAL_VAR);

    {
        uint16_t* cached_result = hashmap_get(cache, &value.variable);
        if (cached_result != NULL) return *cached_result;
    }

    Expression* expr = hashmap_get(circuit, &value.variable);
    uint16_t result = expr_eval(circuit, cache, *expr);
    hashmap_insert(&cache, &value.variable, &result);
    return result;
}

static HashMap build_circuit(str_t input)
{
    HashMapOptions options = hashmap_default_options();
    options.key_comparer = hashmap_eq_str;
    options.hash_function = hashmap_hash_str;

    HashMap circuit = hashmap_create_with_options(sizeof(str_t), sizeof(Expression), options);

    str_t line;
    StrSpliterator it = str_lines(input);
    while (str_split_next(&it, &line))
    {
        parse_expr(line, &circuit);
    }

    return circuit;
}

static uint16_t solve_circuit(HashMap circuit, str_t variable)
{
    HashMapOptions options = hashmap_default_options();
    options.hash_function = hashmap_hash_str;
    options.key_comparer = hashmap_eq_str;

    HashMap cache = hashmap_create_with_options(sizeof(str_t), sizeof(uint16_t), options);
    Value value = (Value){
        .type = VAL_VAR,
        .variable = variable,
    };

    uint16_t result = value_eval(circuit, cache, value);

    hashmap_destroy(cache);

    return result;
}

SolverResult solve_2015_day_07_part_1(str_t input)
{
    HashMap circuit = build_circuit(input);
    uint16_t result = solve_circuit(circuit, STR_SLICE("a"));

    hashmap_destroy(circuit);

    return (SolverResult){
        .type = RESULT_UNSIGNED_INT,
        .value.unsigned_int = result,
    };
}

SolverResult solve_2015_day_07_part_2(str_t input)
{
    HashMap circuit = build_circuit(input);

    Expression b;
    b.type = EXPR_LITERAL;
    b.left = (Value){
        .type = VAL_CONST,
        .constant = solve_circuit(circuit, STR_SLICE("a")),
    };

    str_t the_letter_b = STR_SLICE("b");
    hashmap_insert(&circuit, &the_letter_b, &b);
    uint16_t result = solve_circuit(circuit, STR_SLICE("a"));

    hashmap_destroy(circuit);

    return (SolverResult){
        .type = RESULT_UNSIGNED_INT,
        .value.unsigned_int = result,
    };
}