//城墙 /d/jinyang/citywall
// By Zine 23 Nov 2010

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "内城墙");
        set("long", @LONG
这是长安城宫城的城墙，东面是宫城的入口承天门，
南面是皇城，四周守卫森严。
LONG     );
        set("exits", ([
                "west" : __DIR__"anfumenlou",
                "eastdown" : __DIR__"chengtianmen",
                "east" : __DIR__"chengtianmenlou"
        ]));
        
        set("objects", ([
		      __DIR__"npc/jinwu-5": 1,
          __DIR__"npc/jinwu-2": 2
        ]));
        
        set("locate_level",4);
        
        set("outdoors", "changan");
        set("changan", 4); // 0-郊外 1-外城 2-皇城 3-禁宫 4-城墙
        setup();
}

void init()
{
        object ob, *inv;
        int lp;
        
        if (interactive(ob = this_player()) ) 
        {
                if (ob->query("special_skill/sociability"))
                    	 return;  //sociability不被追杀
                inv=all_inventory(this_object());
                for(lp=0;lp<sizeof(inv);lp++)
                {
                	if ( inv[lp]->query("id")=="jin wu" )
                	{
                		message_vision("$N大喝道：大胆毛贼，这个地方也是你等能够闯的？\n", inv[lp]);
                		ob->apply_condition("cakiller", 60);
                		inv[lp]->kill_ob(ob);
                	}
                }
        }
}