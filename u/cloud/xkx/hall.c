//hall.c

#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "云中城大厅");
        set("long", "这里是云中城大厅，朵朵祥云穿梭其间。主人cloud正与天使们\n
        在聊天，悠闲自得，令你羡慕不已。他对你的到来表示极大的欢迎！\n");
        set("valid_startroom", 1);
        set("exits", ([
                "out" : __DIR__"gate",
                  "wz": "/d/wizard/wizard_room",
           "xiangyang": "/d/xiangyang/xycenter.c",
                "emei": "/d/emei/dadian",
                "city": "/d/city/guangchang",
                "fumo": "/d/shaolin/fumoquan",
              "ruzhou": "/d/shaolin/ruzhou",
             "taishan": "/d/taishan/fengchan",
                "gumu": "/d/gumu/dating",
             "shaolin": "/d/shaolin/dxbdian",
             "huashan": "/d/huashan/houhuayuan1",
            "mingjiao": "/d/mingjiao/dadian",
              "guiyun": "/d/guiyunzhuang/guiyunting",
            "quanzhen": "/d/quanzhen/gongmen",
     	        "biwu": "/hslj/biwu",
	         "reg": "/hslj/register",
 ])); 
        set("no_fight", 1);
              
        set("objects", ([ /* sizeof() == 4 */
                          __DIR__"npc/angel" :4,
        setup();
 }