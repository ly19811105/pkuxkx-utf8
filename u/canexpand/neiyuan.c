//地图生成工具。

#include <ansi.h>　//by mudy
//Created by ldjt
inherit ROOM;
#include <canexpand.h>//DEL
void create()
{
        set("short", "内院");
        set("long", ""
/*DESCRIBE*/"一个静悄悄的小院子，打扫的一尘不染的，对面是一座不大不小的屋子，一只黑蓝色的棉布帘子"+"\n"
/*DESCRIBE*/"静静的垂着，左边是一排厢房，没有着漆的木门随意的虚掩着。\n"
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
"south":"/u/canexpand/tingyuan3",
"north":"/u/canexpand/fangzi.c",
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