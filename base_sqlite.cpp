//
// Created by Tr on 13.01.2023.
// c-style, in a future put property, function to class
//

#include "base_sqlite.h"

static sqlite3 *bd; //handle of BD

void testBd() {
    openBd("test.bd\0");
    request_insert_create("CREATE TABLE IF NOT EXISTS temp(id integer primary key autoincrement, name varchar(32));");
    request_insert_create("INSERT INTO temp(name) VALUES ('test'),('test1'),('test2'),('test3');");

    request_select("SELECT count() FROM temp;");
    request_select("SELECT * FROM temp;");

    closeBd();
}
/*
 *  opend base data with name
 */
bool openBd(const char* bdName) {
    int status = sqlite3_open(bdName, &bd);
    assert(status == SQLITE_OK);

    return status;
}

bool closeBd() {
    int status = sqlite3_close(bd);
    assert(status == SQLITE_OK);
    return status;
}

bool request_insert_create(const char* sqlString) {
    char* errMsg;
    int er = sqlite3_exec(bd, sqlString, nullptr, nullptr, &errMsg);
    if (er) {
        std::cerr << "error request " << sqlString << " : " << errMsg << std::endl;   //std::cout
    }

    return er;
}
int getLastRowId() {
    int last_id = sqlite3_last_insert_rowid(bd);
    return last_id;
}

int callback(void* outputStruct, int countRec, char** argv, char** colName) {
    //void* -- c-style
    //outputStructure allow to return back the data for processing....
    for (int i = 0; i < countRec; i++) {
        std::cout << "\t" << colName[i] << " '" << argv[i] << "'";
    }
    std::cout << std::endl;
    return 0;
}

bool request_select(const char* sqlString) {
    char* errMsg;
    int er = sqlite3_exec(bd, sqlString, callback, nullptr /*input arguments*/, &errMsg);

    if (er != SQLITE_OK) {
        std::cerr << "error request " << sqlString << " : " << errMsg << std::endl;
    }
    assert(er == SQLITE_OK);

    return er;
}