#include "table.h"

Table *new_table()
{
    Table *table = (Table *)malloc(sizeof(Table));
    table->num_rows = 0;
    for (uint32_t index = 0; index < TABLE_MAX_PAGES; index++)
    {
        table->pages[index] = NULL;
    }
    return table;
}

void free_table(Table *table)
{
    for (uint32_t index = 0; table->pages[index]; index++)
    {
        free(table->pages[index]);
    }
    free(table);
}

void *row_slot(Table *table, uint32_t row_num)
{
    uint32_t page_num = row_num / ROWS_PER_PAGE;
    void *page = table->pages[page_num];
    if (page == NULL)
    {
        page = table->pages[page_num] = malloc(PAGE_SIZE);
    }

    uint32_t row_offset = row_num % ROWS_PER_PAGE;
    uint32_t byte_offset = row_offset * ROW_SIZE;

    return page + byte_offset;
}
