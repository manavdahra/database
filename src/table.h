#ifndef _TABLE_H_
#define _TABLE_H_

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "row.h"

static const uint32_t PAGE_SIZE = 4096;
#define TABLE_MAX_PAGES 4096
static const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
static const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

typedef struct {
    int file_descriptor;
    uint32_t file_length;
    void* pages[TABLE_MAX_PAGES];
} Pager;

typedef struct {
    uint32_t num_rows;
    Pager* pager;
} Table;

Table* db_open(const char* filename);
Pager *pager_open(const char *filename);
void* row_slot(Table* table, uint32_t row_num);
void* get_page(Pager* pager, uint32_t page_num);
void db_close(Table* table);

#endif