// 游方和尚 By Zine
               
#include <ansi.h> 
inherit NPC; 

int ask_build();
void create()
{
	set_name("泥瓦匠", ({ "niwa jiang","jiang"}));
        
	set("long",
	"他是一个泥瓦匠，专门替人盖房子营生。\n"
         );
	set("title",HIW"大工匠"NOR);
	set("gender", "男性");
	
	set("age", 40);
	set("attitude", "peaceful");
	set("shen_type", 1);
   	set("str", 30);
	set("int", 25);
	set("con", 25);
	set("dex", 25);
	set("per", 25);
    set("uni_target",1);
    set("no_get",1);
	set("max_qi", 1000);
    set("qi", 1000);
    set("max_jing", 1000);
    set("jing", 1000);
    set("max_jingli", 1000);
    set("jingli", 1000);
    set("neili", 900);
	set("max_neili", 900);
	set("jiali", 5);
    set_skill("hand", 50);
	set_skill("parry",50);
	set_skill("dodge", 50);
	set_skill("force",50);
	set_skill("literate",50);
	set("combat_exp", 65000);
	
    set("inquiry", ([
			"盖房子" : (: ask_build :),
            "build" : (: ask_build :),
     
       	]) );    
        setup();
        carry_object("clone/cloth/cloth")->wear();
}
void init()
{
    add_action("do_mkroom","zine");
}
int do_mkroom(string arg)
{
    object me=this_player();
    object room=environment(me);
	string file,short_name,dir,r_dir,code;
    int flag,i,limit=(int)me->query("self_building/limit");
    mapping exits;
    seteuid(geteuid(me));
    if (!room)//不许建房种种条件
    {
        return 0;
    }
    file = resolve_path(this_player()->query("self_building/area"),"room0") + ".c";
    for (i=0;i<limit;i++)
    {
        if( file_size(file)!=-1 )
		file = resolve_path(this_player()->query("self_building/area"),"room"+i) + ".c";
        else
        flag =1;
    }
    if (flag==0)
        return notify_fail("已经达到这里运行建房的极限了，你无法再修建新的房屋。\n");
	if( !arg ) 
        return notify_fail("指令格式：mkroom <房间名称> [<方向>]\n");
	if( sscanf(arg, "%s %s", short_name, dir)!=2 )
		return notify_fail("指令格式：mkroom <房间名称> [<方向>]\n");
    if (dir=="south")
    {
        r_dir="north";
    }
    if (dir=="north")
    {
        r_dir="south";
    }
    if (dir=="east")
    {
        r_dir="west";
    }
    if (dir=="west")
    {
        r_dir="east";
    }
    if (dir=="southwest")
    {
        r_dir="northeast";
    }
    if (dir=="southeast")
    {
        r_dir="northwest";
    }
    if (dir=="northwest")
    {
        r_dir="southeast";
    }
    if (dir=="northeast")
    {
        r_dir="southwest";
    }
    if (dir=="up")
    {
        r_dir="down";
    }
    if (dir=="enter")
    {
        r_dir="out";
    }
	if( !write_file(file, @ROOM_CODE
// This is a room made by roommaker.

inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", short_name);
	set("long", "这是一间什麽也没有的空房间。\n");
	setup();
	replace_program(ROOM);
}

ROOM_CODE ) ) return notify_fail("你没有写入档案(" + file +")的权利。\n");
	message_vision("只听到$N的房间编辑器「哔」的一声，你觉得这个世界又变大了一点。\n", this_player());
    exits = room->query("exits");
    if( mapp(exits) )
		exits[dir] = file;
	else
		room->set("exits", ([ dir: file ]) );
    file->set("exits",([r_dir: base_name(room)]) );
	return 1;
}

int do_connect(string arg)
{
	mapping exits;
	string dir, file;

	if( !arg || sscanf(arg, "%s %s", dir, file)!=2 )
		return notify_fail("指令格式：connect <方向> <房间档名>\n");
	file = resolve_path(this_player()->query("cwd"), file);
	exits = environment(this_player())->query("exits");
	if( mapp(exits) )
		exits[dir] = file;
	else
		environment(this_player())->set("exits", ([ dir: file ]) );
	write("Ok.\n");
	return 1;
}