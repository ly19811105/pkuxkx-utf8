//地图生成工具。

#include <ansi.h>　//by mudy
//Created by ququ
inherit ROOM;
#include <canexpand.h>//DEL
void create()
{
        set("short", "浩然居");
        set("long", ""
/*DESCRIBE*/"                     “浩然居”\n"
/*DESCRIBE*/"竹门的牌匾上书写着这三个苍劲有力的大字，下书“独孤浩然”，一定是世外高人的隐居所在了。\n"
/*DESCRIBE*/"这是一个小巧别致的庭院，院子里躺着一只懒洋洋的小狗狗，看到你走近院子，狗狗警觉起来，\n"
/*DESCRIBE*/"院子的左边是一块用篱笆围起来的田地，里面种满了庄稼，好像有很多讨厌的麻雀们再偷吃粮食。\n"
/*DESCRIBE*/"院子的右边是一块绿油油的菜园子，里面种满了蔬菜，看来主人在菜园上花费了不少功夫。\n"
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
"south":"/u/canexpand/qu20",
"north":"/u/canexpand/qu22.c",
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