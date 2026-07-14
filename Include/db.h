#include <sqlite3/sqlite3.h>

#ifndef DB_H
#define DB_H

sqlite3* database;

void initDB();
void openDB();

#endif //DH_H
