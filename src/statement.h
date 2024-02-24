#ifndef __STATEMENT_H__
#define __STATEMENT_H__

#include <stdlib.h>
#include <stdio.h>
#include "row.h"
#include "table.h"

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
    PREPARE_UNRECOGNISED_STATEMENT,
    PREPARE_SYNTAX_ERROR
} PrepareResult;

typedef enum {
    META_COMMAND_SUCCESS,
    META_UNRECOGNISED_COMMAND
} MetaCommandResult;

typedef struct InputBuffer {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer();
void close_input_buffer(InputBuffer* input_buffer);

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement);

ExecuteResult execute_statement(Statement* statement, Table* table);

MetaCommandResult do_meta_command(InputBuffer* input_buffer);

#endif
