//地图生成工具。

#include <ansi.h>　//by mudy
//Created by xxx
inherit ROOM;
#include <canexpand.h>//DEL
void create()
{
        set("short", "五指山脚");
        set("long", ""
/*DESCRIBE*/"    这里就是五指山，该山以其形似五指而得名，相传当年齐天大圣曾被\n"
/*DESCRIBE*/"如来佛祖压与此山下。听说最近这里来了一伙土匪，为首的叫做至尊宝，\n"
/*DESCRIBE*/"据说此人无恶不作，强奸大肚子，非礼老太婆乃是家常便饭，最近还抢了\n"
/*DESCRIBE*/"一个小女孩的糖吃，奈何这里天高皇帝远，官府也懒得搭理，看来还是速\n"
/*DESCRIBE*/"速离开这里为妙！\n"
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
"east":"/u/canexpand/wzsroad2",
"westup":"/u/canexpand/wzsroad3.c",
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