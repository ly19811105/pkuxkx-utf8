//地图生成工具。

#include <ansi.h>　//by mudy
//Created by ldjt
inherit ROOM;
#include <canexpand.h>//DEL
void create()
{
        set("short", "浣纱石");
        set("long", ""
/*DESCRIBE*/"这是一块平整的大石头，孤零零的向湖中伸开一丈有余。这里便成了附近的人们洗衣服的好地方.\n"
/*DESCRIBE*/"临水处有几个年轻的女子，穿着红红绿绿的衣衫，聚在那里唧唧喳喳的不知道说些什么，看见你走过来似\n"
/*DESCRIBE*/"乎有些不好意思，偷偷的看你几眼，一起无端的笑了起来，有几个还羞红了脸儿。\n"
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
"south":"/u/canexpand/hubian6",
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
"/u/canexpand/npc/huannv.c" : 1,
"/u/canexpand/npc/huansha.c" : 1,
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