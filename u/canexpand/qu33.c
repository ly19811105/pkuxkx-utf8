//地图生成工具。

#include <ansi.h>　//by mudy
//Created by ququ
inherit ROOM;
#include <canexpand.h>//DEL
void create()
{
        set("short", "阁楼");
        set("long", ""
/*DESCRIBE*/"这是浩然居的阁楼，也是大侠“独孤浩然”休息的地方。"+"\n"
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
//DESCRIBE
//DESCRIBE
//OVERDESCRIBE
        );
        set("exits", ([
"down":"/u/canexpand/qu23",
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
//EXIT
//OVER
                 ]));
set("objects", ([
"/u/canexpand/obj/qu34.c" : 1,
"/u/canexpand/obj/qu35.c" : 1,
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