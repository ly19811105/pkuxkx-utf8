//城墙 /d/jinyang/citywall
// By Zine 23 Nov 2010

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "外城墙");
        set("long", 
"这里一段雄奇的古城墙。\n"

        );
        set("exits", ([
                
                "north" : __DIR__"tonghuamenlou",
                "northdown" : __DIR__"tonghuamen",
                "southdown" : __DIR__"eastgate",
                "south" : __DIR__"chunmingmenlou"
                
        ]));
        
        set("objects", ([
		      __DIR__"npc/jinwu-2": 1,
          __DIR__"npc/jinwu-1": 2
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