#ifndef _STATEMENT_H_
#define _STATEMENT_H_

#include <stdlib.h>
#include <stdio.h>
#include "row.h"
#include "table.h"
#include "input.h"

typedef enum {
    EXECUTE_TABLE_FULL,
    EXECUTE_SUCCESS
} ExecuteResult;

typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

typedef struct Statement {
    StatementType type;
    Row row_to_insert; // only used by insert statement
} Statement;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_NEGATIVE_ID,
    PREPARE_STRING_TOO_LONG,
    PREPARE_UNRECOGNISED_STATEMENT,
    PREPARE_SYNTAX_ERROR
} PrepareResult;

typedef enum {
    META_COMMAND_SUCCESS,
    META_UNRECOGNISED_COMMAND
} MetaCommandResult;

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement);

ExecuteResult execute_statement(Statement* statement, Table* table);

MetaCommandResult do_meta_command(InputBuffer* input_buffer, Table* table);

#endif
