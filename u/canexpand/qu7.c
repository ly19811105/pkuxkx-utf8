//地图生成工具。

#include <ansi.h>　//by mudy
//Created by ququ
inherit ROOM;
#include <canexpand.h>//DEL
void create()
{
        set("short", "洞中小庭");
        set("long", ""
/*DESCRIBE*/"经过一番辛苦的磕磕碰碰之后，你走到一个小庭里面。这里布满了灰尘，似乎很久没有人来过了。"+"\n"
/*DESCRIBE*/"庭中有个小石桌，上面放了一本书，似乎是一本武功秘笈（book）。左边墙上挂了一幅画（picture),似乎是个美女:）。\n"
/*DESCRIBE*/"右边墙壁上似乎有个深深的手印，你不禁想去摸摸。\n"
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
"southeast":"/u/canexpand/qu6",
"north":"/u/canexpand/qu8.c",
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
"/u/canexpand/obj/qu40.c" : 1,
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