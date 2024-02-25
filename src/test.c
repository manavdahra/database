#include <stdio.h>
#include "input.h"
#include "statement.h"
#include "minunit.h"

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

MU_TEST(test_prepare_insert_statement_username_string_too_long) {
    char input[] = "insert 1 aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa dahra@gmail.com";
    input_buffer->buffer = input;
    input_buffer->buffer_length = strlen(input);
    input_buffer->input_length = strlen(input);
    Statement statement;
	mu_assert(prepare_statement(input_buffer, &statement) == PREPARE_STRING_TOO_LONG, "result should be PREPARE_STRING_TOO_LONG");
}

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char* long_string() {
    char* result = "";
    for (uint16_t i = 0; i < 256; i++) {
        result = concat(result, "a");
    }
    return result;
}

MU_TEST(test_prepare_insert_statement_email_string_too_long) {
    char input[] = "insert 1 manav ";
    input_buffer->buffer = concat(input, long_string());
    input_buffer->buffer_length = strlen(input);
    input_buffer->input_length = strlen(input);
    Statement statement;
	mu_assert(prepare_statement(input_buffer, &statement) == PREPARE_STRING_TOO_LONG, "result should be PREPARE_STRING_TOO_LONG");
}

MU_TEST(test_prepare_insert_statement_id_negative) {
    char input[] = "insert -1 manav dahra@gmail.com";
    input_buffer->buffer = input;
    input_buffer->buffer_length = strlen(input);
    input_buffer->input_length = strlen(input);
    Statement statement;
	mu_assert(prepare_statement(input_buffer, &statement) == PREPARE_NEGATIVE_ID, "result should be PREPARE_NEGATIVE_ID");
}

void test_setup(void) {
    table = new_table();
	input_buffer = new_input_buffer();
}

void test_teardown(void) {
    free_table(table);
	close_input_buffer(input_buffer);
}

MU_TEST_SUITE(test_suite_prepare_statement) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	MU_RUN_TEST(test_meta_command_unrecognised_command);
    MU_RUN_TEST(test_prepare_insert_statement_fail);
    MU_RUN_TEST(test_prepare_insert_statement_username_string_too_long);
    MU_RUN_TEST(test_prepare_insert_statement_email_string_too_long);
    MU_RUN_TEST(test_prepare_insert_statement_id_negative);
    MU_RUN_TEST(test_prepare_insert_statement_success);
    MU_RUN_TEST(test_prepare_select_statement_fail);
    MU_RUN_TEST(test_prepare_select_statement_success);
}

MU_TEST_SUITE(test_suite_execute_statement) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

    MU_RUN_TEST(test_execute_insert_statement_success);
}

int main(int argc, char **argv)
{
    MU_RUN_SUITE(test_suite_prepare_statement);
    MU_RUN_SUITE(test_suite_execute_statement);

	MU_REPORT();
	return MU_EXIT_CODE;
}
