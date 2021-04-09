inherit ROOM; 
#include <ansi.h>

void create() 
{ 
        set("short", "古战场遗址");
        set("long", @LONG
这里一处古战场遗址，到处都是散落的骨骸。
LONG
        );
	
        set("exits", ([ /* sizeof() == 3 */
   //"south" : __DIR__"zoudao2.c",
]));
        set("no_clean_up", 1);
        set("no_die",1);
		set("no_reset",1);
		setup();



}
void ResetTest(object loser)
{
	object npc,npc2;
	npc=query("npc");
	npc2=query("npc2");
	if (npc==loser)
	add("lose",1);
	else
	add("win",1);
}

void start()
{
	object npc,npc2;
	npc=new(__DIR__"npc/target");
	npc->set("combat_exp",100000000);
	npc->set_huashan1(npc,1000,1);
	npc->set("test_npc",1);
	npc->set("chat_msg_combat", ({
		(: perform_action, "sword.sanqingfeng" :),
	}));
	npc2=new(__DIR__"npc/target");
	npc2->set("test_npc",2);
	npc2->set("combat_exp",100000000);
	npc2->family_skill(npc2, "random", 1000, 1);
	set("npc",npc);
	set("npc2",npc2);
	npc->kill_ob(npc2);
	npc2->kill_ob(npc);
}