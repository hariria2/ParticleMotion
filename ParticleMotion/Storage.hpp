//
//  Storage.hpp
//  ParticleFlow
//
//  Created by Sahand Hariri on 9/25/15.
//  Copyright © 2015 Sahand Hariri. All rights reserved.
//

#ifndef Storage_hpp
#define Storage_hpp

#include <stdio.h>
#include <iostream>

#include <string>
#include <mysql.h>

using namespace std;


class Storage{
public:
    Storage(const char *server, const char *user, const char *password, const char *database, string version, int storeq);
    
    virtual ~Storage();
    
    void CreateDB(string db);
    void CreateTable(string table);
    void InsertValue(string table, string vals, bool paren=false);
    void Init(string dbname);
private:
    string timeStamp;
    MYSQL *conn, mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    
};



#endif /* Storage_hpp */
