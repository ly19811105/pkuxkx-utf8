//地图生成工具。

#include <ansi.h>　//by mudy
//Created by ldjt
inherit ROOM;
#include <canexpand.h>//DEL
void create()
{
        set("short", "堂屋");
        set("long", ""
/*DESCRIBE*/"这是雷动九天的居所，正对你的是几个龙飞凤舞的大字：“雷动于九天之上”，字体中透露着一股\n"
/*DESCRIBE*/"豪气。堂屋正中是一张檀木桌子，上面转文隐约，似乎不是普通之物。桌子两旁各有一张扶手椅子，\n"
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
"south":"/u/canexpand/neiyuan",
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