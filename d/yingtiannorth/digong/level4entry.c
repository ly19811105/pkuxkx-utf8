inherit __DIR__"karma_room.c";
#include <ansi.h>

void create()
{
	set("short", HIY"珊瑚境入口"NOR);
	set("long", @LONG
这里是地宫第四层珊瑚境的入口。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 4);
	set("entry", 1);
	set("exits", ([
		//"up" : (:get_path:),
		"up" : __DIR__"level3exit",
		"enter" : __DIR__"level4path1",
		//"west" : __DIR__"wall1",
	]));

	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	set("SKILLS",({"logger","logger2","carpenter","handicraftsman","captain","oar"}));
	setup();
}
void Obtain_Skill(object me)
{
	string *skills,skill;
	mapping sk=(["logger":"伐木","logger2":"伐木","carpenter":"木匠","handicraftsman":"手工艺","captain":"开船","oar":"划桨"]);
	mapping cmd=(["logger":"kan","logger2":"kan","carpenter":"zaochuan","handicraftsman":"xiao","captain":"start","oar":"hua"]);
	if (sizeof(skills=query("SKILLS"))<1)
	return;
	if (!me->query_temp("karma/level4/skill"))
	{
		skill=skills[random(sizeof(skills))];
		me->set_temp("karma/level4/skill",skill);
		if (me->query_temp("karma/level4/skill")=="carpenter")
		me->set_temp("karma/level4/skill_carpen",5+random(10));
		tell_object(me,HBWHT+HIR+"你临时获得了"+sk[skill]+"的技能，命令是"+cmd[skill]+"，可能需要在特定地方使用。\n"+NOR);
		skills-=({skill});
		set("SKILLS",skills);
	}
}
void gene_tool()
{
	object tool;
	string *places=({"treea","treeb","treec","treed","treee","treef","treeg","treeh","path1","path2","river"}),*trees=({"treea","treeb","treec","treed","treee","treef","treeg","treeh"});
	set("tool_gened",1);
	tool=new(__DIR__"obj/axe");
	tool->move(load_object(__DIR__"level4"+places[random(sizeof(places))]));
	tool=new(__DIR__"obj/axe");
	tool->move(load_object(__DIR__"level4"+places[random(sizeof(places))]));
	for (int i=0;i<sizeof(trees);i++)
	load_object(__DIR__"level4"+trees[i])->set("chop",3+random(4));
}
void init()
{
	object me=this_player(),migong=load_object(__DIR__"level5maze");
	tell_object(this_player(),HBWHT+HIY+"在这一关中，玩家被分配不同的技能，需要合作造出一艘小船，载着所有人抵达对岸。\n"+NOR);
	Obtain_Skill(me);
	if (!query("tool_gened"))
	gene_tool();
	if (!migong->query("generating")&&!migong->query("fully_generated"))
	migong->start();
	::init();
}