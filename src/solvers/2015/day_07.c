#include "../solvers.h"
#include "../../lib/strutils.h"
#include "../../lib/collections/hashmap.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

typedef enum ExpressionType {
    EXPR_LITERAL,
    EXPR_NOT,
    EXPR_AND,
    EXPR_OR,
    EXPR_LSHIFT,
    EXPR_RSHIFT
} ExpressionType;

typedef enum ValueType {
    VAL_CONST,
    VAL_VAR
} ValueType;

typedef struct Value {
    ValueType type;
    union {
        uint16_t constant;
        const char* variable;
    };
} Value;

typedef struct Expression {
    ExpressionType type;
    Value left;
    Value right;
} Expression;

static Value parse_value(const char* input) {
    if (is_digit(*input)) {
        return (Value) {
            .type = VAL_CONST,
            .constant = atoi(input)
        };
    }

    return (Value) {
        .type = VAL_VAR,
        .variable = input
    };
}

static void parse_expr(char* input, HashMap* map) {
    const char* delim = " ";
    const char* left = strtok(input, delim);

    Expression expr;
    if (!strcmp("NOT", left)) {
        expr.type = EXPR_NOT;
        expr.left = parse_value(strtok(NULL, delim));
    } else {
        expr.left = parse_value(left);
        const char* operator = strtok(NULL, delim);

        if (!strcmp("AND", operator)) expr.type = EXPR_AND;
        else if (!strcmp("OR", operator)) expr.type = EXPR_OR;
        else if (!strcmp("LSHIFT", operator)) expr.type = EXPR_LSHIFT;
        else if (!strcmp("RSHIFT", operator)) expr.type = EXPR_RSHIFT;
        else if (!strcmp("->", operator)) expr.type = EXPR_LITERAL;

        if (expr.type != EXPR_LITERAL)
        {
            expr.right = parse_value(strtok(NULL, delim));
        }
    }

    if (expr.type != EXPR_LITERAL)
    {
        (void) strtok(NULL, delim); // void " -> "
    }

    const char* var = strtok(NULL, delim);
    hashmap_insert(map, &var, &expr);
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

static HashMap build_circuit(char* input) {
    HashMapOptions options = hashmap_default_options();
    options.key_comparer = hashmap_str_eq;
    options.hash_function = hashmap_str_hash;

    HashMap circuit = hashmap_new(sizeof(const char*), sizeof(Expression), options);
    
    char* line = strtok_r(input, "\n", &input);
    while (line)
    {
        parse_expr(line, &circuit);
        line = strtok_r(NULL, "\n", &input);
    }

    return circuit;
}

static uint16_t solve_circuit(HashMap circuit, const char* variable) {
    HashMapOptions options = hashmap_default_options();
    options.hash_function = hashmap_str_hash;
    options.key_comparer = hashmap_str_eq;

    HashMap cache = hashmap_new(sizeof(const char*), sizeof(uint16_t), options);
    Value value = (Value) {
        .type = VAL_VAR,
        .variable = variable
    };

    uint16_t result = value_eval(circuit, cache, value);

    hashmap_destroy(cache);

    return result;
}

SolverResult solve_2015_day_07_part_1(const char* _input)
{
    char* input = strdup(_input);
    HashMap circuit = build_circuit(input);

    uint16_t result = solve_circuit(circuit, "a");

    hashmap_destroy(circuit);
    free(input);

    return (SolverResult) {
        .type = RESULT_INT,
        .integer_result = result
    };
}

static const char* THE_LETTER_B = "b";

SolverResult solve_2015_day_07_part_2(const char* _input)
{
    char* input = strdup(_input);
    HashMap circuit = build_circuit(input);

    Expression b;
    b.type = EXPR_LITERAL;
    b.left = (Value) {
        .type = VAL_CONST,
        .constant = solve_circuit(circuit, "a")
    };

    hashmap_insert(&circuit, &THE_LETTER_B, &b);
    uint16_t result = solve_circuit(circuit, "a");

    hashmap_destroy(circuit);
    free(input);

    return (SolverResult) {
        .type = RESULT_INT,
        .integer_result = result
    };
}