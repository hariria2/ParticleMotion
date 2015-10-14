//
//  Storage.cpp
//  ParticleFlow
//
//  Created by Sahand Hariri on 9/25/15.
//  Copyright © 2015 Sahand Hariri. All rights reserved.
//

#include "Storage.hpp"


using namespace std;

Storage::Storage(const char *server, const char *user, const char *password, const char *database, string version, int storeq){
    
    //===========>>>Figure out the time stamp<<<======================//
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    timeStamp = to_string((now->tm_mon + 1)) + "_" +
    to_string(now->tm_mday) + "_" +
    to_string((now->tm_year + 1900));
    
    //================================================================//
    
    
    //=============>>>Start MySQL conection<<<========================//
    mysql_init(&mysql);
    conn=mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
    if(conn==NULL)
    {
        cout<<mysql_error(&mysql)<<endl<<endl;
        
    }
    //=======================================================================//
    
    string dbname;
    dbname = "partsim_v" + version + "_" + timeStamp;
    
    if (storeq){
        Init(dbname);
    }
    
    
}

void Storage::Init(string dbname){
    CreateDB(dbname);
    CreateTable("Domain");
    CreateTable("Particles");
    CreateTable("ParticleData");
    CreateTable("SystemData");
}
void Storage::CreateDB(string db){
    string purgedb="DROP DATABASE IF EXISTS "+db+";";
    string mydb="CREATE DATABASE "+db+";";
    string sdb ="USE "+db+";";
    
    int query_statep;
    int query_statem;
    int query_states;
    
    query_statep=mysql_query(conn, purgedb.c_str());
    if(query_statep!=0){
        cout<<mysql_error(conn)<<endl<<endl;
    }
    query_statem=mysql_query(conn, mydb.c_str());
    if(query_statem!=0){
        cout<<mysql_error(conn)<<endl<<endl;
    }
    query_states=mysql_query(conn, sdb.c_str());
    if(query_states!=0){
        cout<<mysql_error(conn)<<endl<<endl;
    }
}
void Storage::CreateTable(string table){
    
    string statement;
    int query_states;
    
    if (table == "Domain"){
        statement = "CREATE TABLE " +table+ "(" +
        "ID INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY, "+
        "xmin INT NOT NULL, " +
        "xmax INT NOT NULL, " +
        "ymin INT NOT NULL, " +
        "ymax INT NOT NULL" +
        ");";
        
    }
    
    else if (table == "Particles"){
        statement = "CREATE TABLE " +table+ "(" +
        "ID INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY, " +
        "mass double NOT NULL, " +
        "x0 double NOT NULL, " +
        "y0 double NOT NULL, " +
        "domain INT UNSIGNED NOT NULL REFERENCES Location(ID)" +
        ");";
        
    }
    else if (table == "ParticleData"){
        statement = "CREATE TABLE " +table+ "(" +
        "INDX INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY, " +
        "ParticleID INT UNSIGNED NOT NULL REFERENCES Particles(ID), " +
        "Time DOUBLE UNSIGNED NOT NULL, " +
        "x DOUBLE NOT NULL, " +
        "y DOUBLE NOT NULL, " +
        "vx DOUBLE NOT NULL, " +
        "vy DOUBLE NOT NULL, " +
        "fx DOUBLE NOT NULL, " +
        "fy DOUBLE NOT NULL, " +
        "KE DOUBLE NOT NULL, " +
        "PE DOUBLE NOT NULL" +
        ");";
    }
    else if (table == "SystemData") {
        statement = "CREATE TABLE " +table+ "(" +
        "ID INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY, " +
        "Time DOUBLE UNSIGNED NOT NULL, " +
        "KETotal DOUBLE NOT NULL, " +
        "PETotal DOUBLE NOT NULL, " +
        "VxTotal DOUBLE NOT NULL, " +
        "VyTotal DOUBLE NOT NULL, " +
        "FxTotal DOUBLE NOT NULL, " +
        "FyTotal DOUBLE NOT NULL" +
        ");";
    }
    else {
        cout << "Wrong table name you dummy!!";
    }
    
    query_states = mysql_query(conn, statement.c_str());
    if(query_states!=0){
        cout<<mysql_error(conn)<<endl<<endl;
    }
}
void Storage::InsertValue(string table, string vals, bool paren){
    string statement;
    int query_states;
    
    
    if (paren){
        statement = "INSERT INTO "+table+" VALUES " + vals +";";
    } else {
        statement = "INSERT INTO "+table+" VALUES (" + vals +");";
    }
    // cout << statement << endl;
    
    query_states = mysql_query(conn, statement.c_str());
    
    if(query_states!=0){
        cout<<mysql_error(conn)<<endl<<endl;
    }
}

Storage::~Storage(){
    mysql_close(conn);
}
