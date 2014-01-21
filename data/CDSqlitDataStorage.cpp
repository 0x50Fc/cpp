//
//  CDSqlitDataStorage.cpp
//  hcppdata
//
//  Created by zhang hailong on 12-12-25.
//  Copyright (c) 2012年 9vteam. All rights reserved.
//

#include "hconfig.h"
#include "CDSqlitDataStorage.h"
#include "hbuffer.h"
#include "hstr.h"
#include "hlog.h"
#include "Coder.h"

#include <sqlite3.h>

#include <map>
#include <string>

namespace CD {
    
    
    static void CDSqlitDataStorageObjectToSql(Object * value,hbuffer_t sql,InvokeTickDeclare);
    static Dictionary * CDSqlitDataStorageStmtToValues(sqlite3_stmt *stmt,std::map<std::string,CDDataEntityField * > * fields);
    
    class CDSqlitCursor : public CDCursor{
    public:
        
        CDSqlitCursor(void);
        
        CDSqlitCursor(CDDataEntity * dataEntity,sqlite3_stmt * stmt);
        
        virtual ~CDSqlitCursor(void);
        
        virtual bool next();
        
        virtual void close();
        
        virtual CDID rawId();
        
        virtual Dictionary * values();
        
        DEC_CLASS
        
    private:
        sqlite3_stmt * _stmt;
        std::map<std::string,CDDataEntityField * > _fields;
        CDID _rawId;
    };
    
    IMP_CLASS(CDSqlitCursor, CDCursor)
    
    IMP_CLASS(CDSqlitDataStorage, CDDataStorage)
    
    CDSqlitDataStorage::CDSqlitDataStorage(void){
        _sqlite = NULL;
    }
    
    CDSqlitDataStorage::CDSqlitDataStorage(const char * dbPath){
        _sqlite = NULL;
        sqlite3_open(dbPath, &_sqlite);
    }
    
    CDSqlitDataStorage::~CDSqlitDataStorage(void){
        sqlite3_close(_sqlite);
    }
    
    void CDSqlitDataStorage::beginTransaction(){
        sqlite3_exec(_sqlite, "BEGIN", NULL, NULL, NULL);
    }
    
    void CDSqlitDataStorage::commentTransaction(){
        sqlite3_exec(_sqlite, "COMMIT", NULL, NULL, NULL);
    }
    
    void CDSqlitDataStorage::rerollTransaction(){
        sqlite3_exec(_sqlite, "ROLLBACK", NULL, NULL, NULL);
    }
    
    void CDSqlitDataStorage::registerEntity(CDDataEntity * dataEntity){
        InvokeTickBegin
        hbuffer_t sql = buffer_alloc(128, 128);
        hbuffer_t msql = buffer_alloc(128, 128);
        hbuffer_t sfield = buffer_alloc(128, 128);
        sqlite3_stmt *stmt = NULL;
        
        buffer_append_format(sql, "SELECT [sql] FROM sqlite_master WHERE [type]='table' and [name]='%s'", InvokeTickArg,dataEntity->name);
        
        sqlite3_prepare_v2(_sqlite, buffer_to_str(sql), buffer_length(sql), &stmt, NULL);
        
        if(sqlite3_step(stmt) == SQLITE_ROW){
            buffer_append_str(msql, (const char *)sqlite3_column_text(stmt, 0));
            
            for(int i=0;i<dataEntity->fieldCount;i++){
                CDDataEntityField * field = dataEntity->fields + i;
                buffer_clear(sfield);
                buffer_append_format(sfield, "[%s]",InvokeTickArg,field->name);
                if(!str_exist(buffer_to_str(msql), buffer_to_str(sfield))){
                    buffer_clear(sql);
                    buffer_append_format(sql, "ALTER TABLE [%s] ADD COLUMN [%s] ", InvokeTickArg,dataEntity->name,field->name);
                    if(field->valueType == ValueTypeInteger){
                        if(field->length ==0){
                            buffer_append_str(sql, "INT");
                        }
                        else{
                            buffer_append_format(sql, "INT(%d)", InvokeTickArg,field->length);
                        }
                    }
                    else if(field->valueType == ValueTypeInt64){
                        if(field->length ==0){
                            buffer_append_str(sql, "BIGINT");
                        }
                        else{
                            buffer_append_format(sql, "BIGINT(%d)", InvokeTickArg,field->length);
                        }
                    }
                    else if(field->valueType == ValueTypeString){
                        if(field->length ==0){
                            buffer_append_str(sql, "VARCHAR(45)");
                        }
                        else{
                            buffer_append_format(sql, "VARCHAR(%d)", InvokeTickArg,field->length);
                        }
                    }
                    else if(field->valueType == ValueTypeFloat || field->valueType == ValueTypeDouble){
                        if(field->length ==0){
                            buffer_append_str(sql, "DOUBLE");
                        }
                        else{
                            buffer_append_format(sql, "DOUBLE(%d)", InvokeTickArg,field->length);
                        }
                    }
                    else if(field->valueType == ValueTypeBytes){
                        if(field->length ==0){
                            buffer_append_str(sql, "BLOB");
                        }
                        else{
                            buffer_append_format(sql, "BLOB(%d)", InvokeTickArg,field->length);
                        }
                    }
                    else{
                        buffer_append_str(sql, "VARCHAR(45)");
                    }
                    sqlite3_exec(_sqlite, buffer_to_str(sql), NULL, NULL, NULL);
                }
            }
        }
        else{
            buffer_clear(sql);
            
            buffer_append_format(sql, "CREATE TABLE IF NOT EXISTS [%s] (", InvokeTickArg,dataEntity->name);
            
            buffer_append_str(sql, "[rawid] integer NOT NULL PRIMARY KEY AUTOINCREMENT");
            
            for(int i=0;i<dataEntity->fieldCount;i++){
                CDDataEntityField * field = dataEntity->fields + i;
                buffer_append_format(sql, ",[%s] ", InvokeTickArg,field->name);
                if(field->valueType == ValueTypeInteger || field->valueType == ValueTypeBoolean){
                    if(field->length ==0){
                        buffer_append_str(sql, "INT");
                    }
                    else{
                        buffer_append_format(sql, "INT(%d)", InvokeTickArg,field->length);
                    }
                }
                else if(field->valueType == ValueTypeInt64){
                    if(field->length ==0){
                        buffer_append_str(sql, "BIGINT");
                    }
                    else{
                        buffer_append_format(sql, "BIGINT(%d)", InvokeTickArg,field->length);
                    }
                }
                else if(field->valueType == ValueTypeString){
                    if(field->length ==0){
                        buffer_append_str(sql, "VARCHAR(45)");
                    }
                    else{
                        buffer_append_format(sql, "VARCHAR(%d)", InvokeTickArg,field->length);
                    }
                }
                else if(field->valueType == ValueTypeFloat || field->valueType == ValueTypeDouble){
                    if(field->length ==0){
                        buffer_append_str(sql, "DOUBLE");
                    }
                    else{
                        buffer_append_format(sql, "DOUBLE(%d)", InvokeTickArg,field->length);
                    }
                }
                else if(field->valueType == ValueTypeObject){
                    if(field->length ==0){
                        buffer_append_str(sql, "TEXT");
                    }
                    else{
                        buffer_append_format(sql, "TEXT(%d)", InvokeTickArg,field->length);
                    }
                }
                else{
                    buffer_append_str(sql, "VARCHAR(45)");
                }
            }
            buffer_append_str(sql, ");");
            
            for(int i=0;i<dataEntity->indexCount;i++){
                CDDataEntityIndex * index = dataEntity->indexes + i;
                buffer_append_format(sql, "CREATE INDEX IF NOT EXISTS [%s_%s] ON [%s]([%s] %s);",InvokeTickArg,dataEntity->name,index->name,dataEntity->name,index->field->name,index->type == CDDataEntityIndexTypeDESC ? "DESC":"ASC");
                
            }
            //hlog("%s\n",buffer_to_str(sql));
            sqlite3_exec(_sqlite, buffer_to_str(sql), NULL, NULL, NULL);
        }
        
        sqlite3_finalize(stmt);
        
        buffer_dealloc(sql);
        buffer_dealloc(msql);
        buffer_dealloc(sfield);
    }
    
    void CDSqlitDataStorage::remove(CDDataEntity * dataEntity,CDID rawId){
        InvokeTickBegin
        hbuffer_t sql = buffer_alloc(128, 128);
        
        buffer_append_format(sql, "DELETE FROM [%s] WHERE [rawid]=%lld", InvokeTickArg,dataEntity->name,rawId);
        
        sqlite3_exec(_sqlite, buffer_to_str(sql), NULL, NULL, NULL);
        
        buffer_dealloc(sql);
    }
    
    static void CDSqlitDataStorageObjectToSql(Object * value,hbuffer_t sql,InvokeTickDeclare){
        if(value && value->isKindOfClass(&Value::oClass)){
            Value * v = (Value *) value;
            ValueType valueType = v->valueType();
            if(valueType == ValueTypeInteger ){
                buffer_append_format(sql, "%d",InvokeTickArg, v->intValue());
            }
            else if(valueType == ValueTypeBoolean){
                buffer_append_format(sql, "%d",InvokeTickArg,v->booleanValue());
            }
            else if(valueType == ValueTypeInt64){
                buffer_append_format(sql, "%lld",InvokeTickArg,v->int64Value());
            }
            else if(valueType == ValueTypeFloat){
                buffer_append_format(sql, "%f",InvokeTickArg,v->floatValue());
            }
            else if(valueType == ValueTypeDouble){
                buffer_append_format(sql, "%f",InvokeTickArg,v->doubleValue());
            }
            else if(valueType == ValueTypeString){
                buffer_append_str(sql, "'");
                char * p = (char *) v->stringValue();
                while( p && *p != '\0'){
                    if(*p == '\''){
                        buffer_append_str(sql, "''");
                    }
                    else{
                        buffer_append(sql,p,1);
                    }
                    p++;
                }
                buffer_append_str(sql, "'");
            }
            else{
                buffer_append_str(sql, "NULL");
            }
        }
        else if(value){
            JSONCoder coder;
            coder.encode(value);
            buffer_append_str(sql, "'");
            char * p = (char *) coder.JSONString();
            while( p && *p != '\0'){
                if(*p == '\''){
                    buffer_append_str(sql, "''");
                }
                else{
                    buffer_append(sql,p,1);
                }
                p++;
            }
            buffer_append_str(sql, "'");
        }
        else{
            buffer_append_str(sql, "NULL");
        }
    }
    
    static Dictionary * CDSqlitDataStorageStmtToValues(sqlite3_stmt *stmt,std::map<std::string,CDDataEntityField * > * fields){
        Dictionary * values = new Dictionary();
        int c = sqlite3_column_count(stmt);
        for(int i=0;i<c;i++){
            std::string name(sqlite3_column_name(stmt, i));
            std::map<std::string,CDDataEntityField * >::iterator ii = fields->find(name);
            if(ii != fields->end()){
                CDDataEntityField * field = ii->second;
                if(field->valueType == ValueTypeInteger){
                    Value * v = new Value(sqlite3_column_int(stmt, i));
                    values->setObjectForKey(name.c_str(), v);
                    v->release();
                }
                else if(field->valueType == ValueTypeInt64){
                    Value * v = new Value(sqlite3_column_int64(stmt, i));
                    values->setObjectForKey(name.c_str(), v);
                    v->release();
                }
                else if(field->valueType == ValueTypeBoolean){
                    Value * v = new Value((bool)sqlite3_column_int(stmt, i));
                    values->setObjectForKey(name.c_str(), v);
                    v->release();
                }
                else if(field->valueType == ValueTypeFloat){
                    Value * v = new Value((float)sqlite3_column_double(stmt, i));
                    values->setObjectForKey(name.c_str(), v);
                    v->release();
                }
                else if(field->valueType == ValueTypeDouble){
                    Value * v = new Value((double)sqlite3_column_double(stmt, i));
                    values->setObjectForKey(name.c_str(), v);
                    v->release();
                }
                else if(field->valueType == ValueTypeString){
                    const char * cv = (const char *)sqlite3_column_text(stmt, i);
                    if(cv){
                        Value * v = new Value(cv);
                        values->setObjectForKey(name.c_str(), v);
                        v->release();
                    }
                }
                else if(field->valueType == ValueTypeObject){
                    const char * cv = (const char *)sqlite3_column_text(stmt, i);
                    if(cv){
                        JSONCoder coder;
                        coder.setJSONString(cv);
                        values->setObjectForKey(name.c_str(), coder.decode());
                    }
                }
            }
        }
        return (Dictionary *) values->autorelease();
    }
    
    CDID CDSqlitDataStorage::insert(CDDataEntity * dataEntity,Dictionary * values){
        InvokeTickBegin
        hbuffer_t sql = buffer_alloc(128, 128);
        hbuffer_t sv = buffer_alloc(128, 128);
        
        buffer_append_format(sql, "INSERT INTO [%s](", InvokeTickArg,dataEntity->name);
        buffer_append_str(sv, " VALUES(");
        
        for(int i=0;i<dataEntity->fieldCount;i++){
            CDDataEntityField * field = dataEntity->fields + i;
            if(i !=0){
                buffer_append_str(sql, ",");
                buffer_append_str(sv, ",");
            }
            buffer_append_format(sql, "[%s]", InvokeTickArg,field->name);
            CDSqlitDataStorageObjectToSql(values->objectForKey(field->name),sv,InvokeTickArg);
        }
        
        buffer_append_str(sql, ")");
        buffer_append_str(sv, ")");
        
        buffer_append(sql,buffer_data(sv),buffer_length(sv));
        
        //hlog("%s\n",buffer_to_str(sql));
        
        sqlite3_exec(_sqlite, buffer_to_str(sql), NULL, NULL, NULL);
        
        buffer_dealloc(sql);
        buffer_dealloc(sv);
        
        return sqlite3_last_insert_rowid(_sqlite);
    }
    
    void CDSqlitDataStorage::update(CDDataEntity * dataEntity,CDID rawId,Dictionary * values){
        InvokeTickBegin
        hbuffer_t sql = buffer_alloc(128, 128);
        
        buffer_append_format(sql, "UPDATE [%s] SET", InvokeTickArg,dataEntity->name);
        
 
        for(int i=0;i<dataEntity->fieldCount;i++){
            CDDataEntityField * field = dataEntity->fields + i;
            if(i !=0){
                buffer_append_str(sql, ",");
            }
            buffer_append_format(sql, " [%s]=", InvokeTickArg,field->name);
            CDSqlitDataStorageObjectToSql(values->objectForKey(field->name),sql,InvokeTickArg);
        }
        
        buffer_append_format(sql, " WHERE [rawid]=%lld",InvokeTickArg,rawId);
        
        //hlog("%s\n",buffer_to_str(sql));
        
        sqlite3_exec(_sqlite, buffer_to_str(sql), NULL, NULL, NULL);
        
        buffer_dealloc(sql);
    }
    
    Dictionary * CDSqlitDataStorage::get(CDDataEntity * dataEntity,CDID rawId){
        InvokeTickBegin
        hbuffer_t sql = buffer_alloc(128, 128);
        Dictionary * values = NULL;
        sqlite3_stmt *stmt = NULL;
        std::map<std::string,CDDataEntityField * > fields;
        
        buffer_append_format(sql, "SELECT * FROM [%s] WHERE [rawid]=%lld", InvokeTickArg,dataEntity->name,rawId);
        
        sqlite3_prepare_v2(_sqlite, buffer_to_str(sql), buffer_length(sql), &stmt, NULL);
        
        for(int i=0;i<dataEntity->fieldCount;i++){
            CDDataEntityField * field = dataEntity->fields + i;
            std::string sKey(field->name);
            fields[sKey] = field;
        }
        
        if(sqlite3_step(stmt) == SQLITE_ROW){
            values = CDSqlitDataStorageStmtToValues(stmt,&fields);
        }
        
        sqlite3_finalize(stmt);
        
        buffer_dealloc(sql);
        
        return values;
    }
    
    CDCursor * CDSqlitDataStorage::query(CDFetchRequest * fetchRequest){
        InvokeTickBegin
        CDDataEntity * dataEntity = fetchRequest->dataEntity();
        hbuffer_t sql = buffer_alloc(128, 128);
        CDCursor * cursor = NULL;
        sqlite3_stmt *stmt = NULL;
        std::map<std::string,CDDataEntityField * > fields;
        CDExp * exp = fetchRequest->dataPredicate();
        CDDataSort * sorts = NULL;
        int sortCount = 0;
        
        buffer_append_format(sql, "SELECT * FROM [%s] ", InvokeTickArg,dataEntity->name);
        
        if(exp){
            Value * v = exp->sql("[", "]");
            if(v){
                buffer_append_format(sql, " WHERE %s ",InvokeTickArg,v->stringValue());
            }
        }
        
        sorts = fetchRequest->dataSorts(&sortCount);
        
        for(int i=0;i<sortCount;i++){
            if(i ==0){
                buffer_append_str(sql, " ORDER BY ");
            }
            else{
                buffer_append_str(sql, ",");
            }
            buffer_append_format(sql, "[%s]",InvokeTickArg,sorts[i].field->name);
            if(sorts[i].type == CDDataSortTypeDESC){
                buffer_append_str(sql, " DESC");
            }
            else{
                buffer_append_str(sql, " ASC");
            }
        }
        
        if(fetchRequest->fetchLimit()){
            buffer_append_format(sql, " LIMIT %d,%d",InvokeTickArg,fetchRequest->fetchOffset(),fetchRequest->fetchLimit());
        }
        
        //hlog("%s\n",buffer_to_str(sql));
        
        if(SQLITE_OK == sqlite3_prepare_v2(_sqlite, buffer_to_str(sql), buffer_length(sql), &stmt, NULL)){
            cursor = new CDSqlitCursor(fetchRequest->dataEntity(),stmt);
            cursor->autorelease();
        }
        else{
            hlog("sqlite3 errormsg: %s\n",sqlite3_errmsg(_sqlite));
            
        }
        
        buffer_dealloc(sql);
        
        return cursor;
    }
    
    
    int CDSqlitDataStorage::errcode(){
        return sqlite3_errcode(_sqlite);
    }
    
    const char * CDSqlitDataStorage::errormsg(){
        return sqlite3_errmsg(_sqlite);
    }
    
    
    CDSqlitCursor::CDSqlitCursor(void){
        _stmt = NULL;
        _rawId = 0;
    }
    
    CDSqlitCursor::CDSqlitCursor(CDDataEntity * dataEntity,sqlite3_stmt * stmt){
        _stmt = stmt;
        _rawId = 0;
        for(int i=0;i<dataEntity->fieldCount;i++){
            CDDataEntityField * field = dataEntity->fields + i;
            std::string sKey(field->name);
            _fields[sKey] = field;
        }
    }
    
    CDSqlitCursor::~CDSqlitCursor(void){
        if(_stmt){
            sqlite3_finalize(_stmt);
        }
    }
    
    bool CDSqlitCursor::next(){
        if(_stmt && sqlite3_step(_stmt) == SQLITE_ROW){
            int i,c = sqlite3_column_count(_stmt);
            
            for(i=0;i<c;i++){
                //hlog("%s\n",sqlite3_column_name(_stmt, i));
                if(strcmp(sqlite3_column_name(_stmt, i), "rawid") ==0){
                    _rawId = sqlite3_column_int64(_stmt, i);
                    break;
                }
            }
            
            return true;
        }
        else{
            _rawId = 0;
        }
        return false;
    }
    
    void CDSqlitCursor::close(){
        if(_stmt){
            sqlite3_finalize(_stmt);
            _stmt = NULL;
        }
    }
    
    CDID CDSqlitCursor::rawId(){
        return _rawId;
    }
    
    Dictionary * CDSqlitCursor::values(){
        if(_stmt){
            return CDSqlitDataStorageStmtToValues(_stmt, &_fields);
        }
        return NULL;
    }
}