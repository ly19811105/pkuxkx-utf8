//地图生成工具。

#include <ansi.h>　//by mudy
//Created by ldjt
inherit ROOM;
#include <canexpand.h>//DEL
void create()
{
        set("short", "后庭");
        set("long", ""
/*DESCRIBE*/"你走进一道门，看见四周栽种着一些马蹄莲，白色的花朵迎风微笑，似乎羞羞答答的看着你走近来。"+"\n"
/*DESCRIBE*/"庭院深处种着一课高大的梧桐树，树下摆着一张木桌，你走过去一看，上面散乱的放着几张便笺。\n"
/*DESCRIBE*/"你走过去一看，上面写着几行字，由于自己潦草你只看出其中有“梧桐花香云。。”几个字。\n"
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
"east":"/u/canexpand/tingyuan1",
"north":"/u/canexpand/neiyuan.c",
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
"/u/canexpand/obj/putizi.c" : 1,
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