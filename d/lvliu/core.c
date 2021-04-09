#include <ansi.h>
#include "nodie.h"
inherit ROOM;
void do_change_pingyuan();

void create()
{
	set("short", HIY"机关房"NOR);
	set("long",
HIC"这是绿柳山庄的机关房。靠墙的位置上有一大排的机关(jiguan)，
用于控制平原的地形改变。
"NOR
	);
	set("item_desc", ([
		"jiguan" : "这是一大排机关，推动机关(push)可以重新调整平原的地形。\n",
	]));
	set("exits", ([
		"out" : __DIR__"pingyuan1"
	]));
	set("no_clean_up", 1);
	setup();
	call_out("do_change_pingyuan", 1);
}

void init()
{
	object me=this_player();
	if (!wizardp(me))
	{
		message("vision", HIC"\n一名侍卫说道：「闲杂人等请到外间休息。」客客气气地把" + me->name() + HIC"请了出去。\n\n"NOR, environment(me));
		me->move(__DIR__"xiaolu.c");
		return;
	}
	add_action("do_push","push");
}

void check_change()
{
	object ob = this_object();
	if (time() - (int)ob->query("last_change") > 900)
	{
		remove_call_out("do_change_pingyuan");
		call_out("do_change_pingyuan",1);
	}
}

int do_push(string arg)
{
	object me=this_player();
	if (!arg || arg!="jiguan")
	{
		write("你能推的只有那一排机关(jiguan)。\n");
		return 1;
	}
	if (!wizardp(me))
	{
		message("vision", HIC"\n一名侍卫说道：「闲杂人等请到外间休息。」客客气气地把" + me->name() + HIC"请了出去。\n\n"NOR, environment(me));
		me->move(__DIR__"xiaolu.c");
		return 1;
	}
	message("vision", HIW "" + me->name() + HIW"用力推动了墙边的机关。\n"NOR, environment(me));
	remove_call_out("do_change_pingyuan");
	call_out("do_change_pingyuan",1);
	return 1;
}

int rooms_num()
{
	int i;
	i=1;
	while (file_size(__DIR__"pingyuan"+i+".c")!=-1 )
		i++;
	i--;
	return i;
}

object get_room(int i)
{
	object room;
	if (i<=0) {
		room = find_object( __DIR__"gate.c" );
		if (!objectp(room))
			room = load_object( __DIR__"gate.c" );
	}
	else {
		room = find_object( __DIR__"pingyuan"+i+".c" );
		if (!objectp(room))
			room = load_object( __DIR__"pingyuan"+i+".c" );
	}
	if (!objectp(room))
		write("error: room load fail.\n");
	return room;
}

void do_change_pingyuan()
{
	int i, j, all, count, bc, x, y;
	object me = this_object();
	object *rooms, re, rs, animal;
	string* dirs1 = ({ "north", "east", "northeast", "northwest", "eastup", "eastdown", "northup", "northdown", "up", "enter",
						"south", "west", "southwest", "southeast", "westdown", "westup", "southdown", "southup", "down", "out", });
	string* dirs2 = ({ "south", "west", "southwest", "southeast", "westdown", "westup", "southdown", "southup", "down", "out",
						"north", "east", "northeast", "northwest", "eastup", "eastdown", "northup", "northdown", "up", "enter",});
	string dir1, dir2;
	all = rooms_num();
	message("vision", "机关运转，开始变换平原。\n", me);
	message("vision", "房间总数: " + all +"\n", me);
	// 更改房间名称和描述
	rooms = allocate(all);
	for (i=0;i<all;i++)
	{
		rooms[i] = get_room(i+1);
		if (!objectp(rooms[i]))	continue;
		rooms[i]->delete("exits");
		rooms[i]->delete_temp("mixed_long");
		rooms[i]->delete("realmap");
		rooms[i]->reset_name();
		rooms[i]->reset_object();
		message("vision", HIY"\n你忽然听到不知何处传来一阵奇怪的碌碌声响，紧接着就是一阵天旋地转……\n"
						+"待你扶着额头定了定神，凝目细看时，发现四周的一切全都变了样。\n\n"NOR, rooms[i]);
	}
	// 更改房间出口
	// 先建立一条路径，以保证至少有一条路能够通畅
	message("vision", "建立路径。\n", me);
	re = get_room(0);
	if (objectp(re) && objectp(rooms[all-1]))
	{
		re->delete("realmap");
		re->set("exits/south", file_name(rooms[all-1]));
		rooms[all-1]->set("exits/north", file_name(re));
	}
	if (objectp(rooms[0]))
		rooms[0]->set("exits/south", __DIR__"xiaolu");
	rs = find_object( __DIR__"xiaolu.c" );
	if (objectp(rs)) rs->delete("realmap");
	for (i=1;i<all;i++)
	{
		if (!objectp(rooms[i-1]) || !objectp(rooms[i]))	continue;
		do {
			j = random(sizeof(dirs1));
			dir1 = dirs1[j];
			dir2 = dirs2[j];
		}
		while (rooms[i-1]->query("exits/"+dir1, 1) || rooms[i]->query("exits/"+dir2, 1));
		rooms[i-1]->set("exits/"+dir1, file_name(rooms[i]));
		rooms[i]->set("exits/"+dir2, file_name(rooms[i-1]));
		if (random(2))
		{
			animal = new(__DIR__"npc/animal");
			if (objectp(animal))
				animal->move(rooms[i]);
		} 
	}
	// 建立随机路径
	count = all * 2;
	for (i=1;i<=count;i++)
	{
		bc = 0;
		do	{
			x = random(all);
			bc++;
			if (bc>10) break;
		}while (objectp(rooms[x]) && sizeof(rooms[x]->query("exits"))>=6);
		if (bc>10) continue;
		bc = 0;
		do	{
			y = random(all);
			bc++;
			if (bc>10) break;
		}while (objectp(rooms[y]) && (x==y || sizeof(rooms[y]->query("exits"))>=6));
		if (bc>10) continue;
		bc = 0;
		do	{
			j = random(sizeof(dirs1));
			dir1 = dirs1[j];
			dir2 = dirs2[j];
			bc++;
			if (bc>10) break;
		}while(rooms[x]->query("exits/"+dir1, 1) || rooms[y]->query("exits/"+dir2, 1));
		if (bc>10) continue;
		rooms[x]->set("exits/"+dir1, file_name(rooms[y]));
		rooms[y]->set("exits/"+dir2, file_name(rooms[x]));
	}
	animal = new(__DIR__"npc/baixi");
	if (objectp(animal))
		animal->move(rooms[random(sizeof(rooms))]);
	message("vision", "所有路径重建完成。\n", me);
	me->set("last_change", time());
	call_out("do_change_pingyuan",900);
}
