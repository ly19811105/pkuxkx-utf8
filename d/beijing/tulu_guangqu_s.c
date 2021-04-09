
//ROOM: tulu_guangqu_s.c

inherit ROOM;

string TULU_DESC_LONG=@LONG
这是京城东南的土路，连接着左安门和广渠门。土路两
侧绿树成荫，夏天知了的叫声一阵阵的传来，让人心头痒痒
的。西面是京城的城墙，厚实而高大。
LONG;

mapping TULU_EXITS=([
                "north" : __DIR__"guangqumen",
                "west" : __DIR__"tulu_zuoan_e",
        ]);

#include "tulu.h"