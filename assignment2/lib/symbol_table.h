#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

void push();             // 進入新 scope
void pop();              // 離開 scope
int insert(const char*); // 嘗試插入變數名稱，若重複回傳 -1
void set_dbg(int x);     // 啟用 debug 輸出（可選）

#endif

