#include <stdio.h>
#include "statement.h"

#include "minunit.h"

InputBuffer* new_input_buffer() {
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

void close_input_buffer(InputBuffer* input_buffer) {
    // free(input_buffer->buffer);
    free(input_buffer);
}

InputBuffer* input_buffer;
Table* table;

MU_TEST(test_meta_command_unrecognised_command) {
    char input[] = ".table";
    input_buffer->buffer = input;
    input_buffer->buffer_length = strlen(input);
    input_buffer->input_length = strlen(input);
	mu_assert(do_meta_command(input_buffer) == META_UNRECOGNISED_COMMAND, "result should be META_UNRECOGNISED_COMMAND");
}

MU_TEST(test_prepare_insert_statement_fail) {
    char input[] = "insert fail";
    input_buffer->buffer = input;
    input_buffer->buffer_length = strlen(input);
    input_buffer->input_length = strlen(input);
    Statement statement;
    mu_assert(prepare_statement(input_buffer, &statement) == PREPARE_SYNTAX_ERROR, "result should be PREPARE_SYNTAX_ERROR");
}

MU_TEST(test_prepare_insert_statement_success) {
    char input[] = "insert 1 manav dahar@gmail.com";
    input_buffer->buffer = input;
    input_buffer->buffer_length = strlen(input);
    input_buffer->input_length = strlen(input);
    Statement statement;
    mu_assert(prepare_statement(input_buffer, &statement) == PREPARE_SUCCESS, "result should be PREPARE_SUCCESS");
}

MU_TEST(test_prepare_select_statement_success) {
    char input[] = "select 1";
    input_buffer->buffer = input;
    input_buffer->buffer_length = strlen(input);
    input_buffer->input_length = strlen(input);
    Statement statement;
    mu_assert(prepare_statement(input_buffer, &statement) == PREPARE_SUCCESS, "result should be PREPARE_SUCCESS");
}

MU_TEST(test_prepare_select_statement_fail) {
    char input[] = " select ";
    input_buffer->buffer = input;
    input_buffer->buffer_length = strlen(input);
    input_buffer->input_length = strlen(input);
    Statement statement;
    mu_assert(prepare_statement(input_buffer, &statement) == PREPARE_UNRECOGNISED_STATEMENT, "result should be PREPARE_UNRECOGNISED_STATEMENT");
}

void assert_execute_insert_table_success() {
    uint32_t id = 1;
    while (table->num_rows < TABLE_MAX_ROWS) {
        Row row_to_insert = {.id = id, .username = "manav", .email = "dahra@gmail.com"};
        Statement statement = {.row_to_insert = row_to_insert, .type = STATEMENT_INSERT};
        
        mu_assert(execute_statement(&statement, table) == EXECUTE_SUCCESS, "result should be EXECUTE_SUCCESS");
        id++;
    }
}

void assert_execute_insert_table_full() {
    Row row_to_insert = {.id = TABLE_MAX_ROWS, .username = "manav", .email = "dahra@gmail.com"};
    Statement statement = {.row_to_insert = row_to_insert, .type = STATEMENT_INSERT};
    
    mu_assert(execute_statement(&statement, table) == EXECUTE_TABLE_FULL, "result should be EXECUTE_TABLE_FULL");
}

MU_TEST(test_execute_insert_statement_success) {
    assert_execute_insert_table_success();
    
    Statement statement = {.row_to_insert = {}, .type = STATEMENT_SELECT};
    mu_assert(execute_statement(&statement, table) == EXECUTE_SUCCESS, "result should be EXECUTE_SUCCESS");
    
    assert_execute_insert_table_full();
}

void test_setup(void) {
    table = new_table();
	input_buffer = new_input_buffer();
}

void test_teardown(void) {
    free_table(table);
	close_input_buffer(input_buffer);
}

MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	MU_RUN_TEST(test_meta_command_unrecognised_command);
    MU_RUN_TEST(test_prepare_insert_statement_fail);
    MU_RUN_TEST(test_prepare_insert_statement_success);
    MU_RUN_TEST(test_prepare_select_statement_fail);
    MU_RUN_TEST(test_prepare_select_statement_success);
    MU_RUN_TEST(test_execute_insert_statement_success);
}

int main(int argc, char **argv)
{
    MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
