//地图生成工具。

#include <ansi.h>　//by mudy
//Created by ldjt
inherit ROOM;
#include <canexpand.h>//DEL
void create()
{
        set("short", "雪崖");
        set("long", ""
/*DESCRIBE*/"你在峭壁中竟然有这样平坦的立足之处，让你十分惊讶。耳边忽忽的刮着凛冽的风,你\n"
/*DESCRIBE*/"不禁打了个冷战。你仔细打量，发现这是块凸出的岩石，虽然平滑，但是立足很稳，你\n"
/*DESCRIBE*/"环顾四周，背后的崖壁生满了一道道的裂纹，不知是不是会突然的崩塌下\n"
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//DESCRIBE
//OVERDESCRIBE
        );
        set("exits", ([
"up":"/u/canexpand/shengu",
"north":"/u/canexpand/shifeng.c",
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//OVER
                 ]));
set("objects", ([
//OBJECT
//OBJECT
//OBJECT
//OBJECT
//OBJECT
//OBJECT
//OBJECT
//OBJECT
//OBJECT
//OBJECT
//OBJECT
//OBJECT
//OBJECT
//OBJECT
//OVEROBJECT           
            ]));
        set("canexpand",1);//DEL
        setup();
//如果该房间没有出口自动会被删除！
if(!sizeof(query("exits"))&&file_name(this_object())!=__DIR__"sample") rm(file_name(this_object())+".c");//DEL

}