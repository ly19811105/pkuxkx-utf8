//地图生成工具。

#include <ansi.h>　//by mudy
//Created by ququ
inherit ROOM;
#include <canexpand.h>//DEL
void create()
{
        set("short", "正厅");
        set("long", ""
/*DESCRIBE*/"                     “浩然正气”"+"\n"
/*DESCRIBE*/"这里就是一代侠客“曲清”易名“独孤浩然”淡出江湖后的隐居所在。\n"
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
"south":"/u/canexpand/qu22",
"up":"/u/canexpand/qu33.c",
"down":"/u/canexpand/qu28.c",
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
"/u/canexpand/npc/qu24.c" : 1,
"/u/canexpand/npc/qu26.c" : 1,
"/u/canexpand/obj/qu27.c" : 1,
"/u/canexpand/obj/qu36.c" : 1,
"/u/canexpand/obj/qu37.c" : 1,
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