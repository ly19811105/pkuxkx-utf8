// 游方和尚 By Zine
               
#include <ansi.h> 
inherit NPC; 
string *special_props = ({
	"short", "long" });
int ask_build();
int do_saveroom();
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
    object new_room,room=environment(me);
	string rm_name,file,user_dir,short_name,dir,r_dir,code;
    int flag,flag1,i,limit;
    mapping exits,real_estate;
    object real=load_object("/d/parties/public/obj/real");
    mapping *entry;
    if (!room)//不许建房种种条件
    {
        return 0;
    }
    entry=real->real_estate();
    rm_name=base_name(room);
    for (i=0;i<sizeof(entry);i++)
    {
        if (entry[i]["owner"]==me->query("id"))
        {
            real_estate=entry[i];
            break;
        }
    }
    if (!real_estate)
    {
        command("say 你没有自己的地产，我怎么帮你盖房子呢？");
        return 1;
    }
    limit=real_estate["room_limit"];
    user_dir=real_estate["user_dir"];
    file = resolve_path(user_dir,"room0") + ".c";
    flag=0;
    flag1=0;//清0
    for (i=0;i<limit;i++)
    {
        if( file_size(file)!=-1 )
		file = resolve_path(user_dir,"room"+i) + ".c";
        else
        flag =1;
        if (rm_name==file)
        {
            flag1=1;
        }
    }
    if (room->query("self_build_entry")&&base_name(room)==real_estate["file"])
    {
        flag1=1;
    }
    if (flag1==0)
        return notify_fail("这里不是你的地产，无法修建新的房屋。\n");
    if (flag==0)
        return notify_fail("已经达到这里运行建房的极限了，你无法再修建新的房屋。\n");
	if( !arg ) 
        return notify_fail("指令格式：mkroom <房间名称> [<方向>]\n");
	if( sscanf(arg, "%s %s", short_name, dir)!=2 )
		return notify_fail("指令格式：mkroom <房间名称> [<方向>]\n");
    if (room->query("self_build_entry")&&dir!=real_estate["entry_direction"])
        return notify_fail("在这个通向公共地址的房间，你只能向"+real_estate["entry_direction"]+"方向修建房屋。\n");
    if (dir=="south")
    {
        r_dir="north";
    }
    else if (dir=="north")
    {
        r_dir="south";
    }
    else if (dir=="east")
    {
        r_dir="west";
    }
    else if (dir=="west")
    {
        r_dir="east";
    }
    else if (dir=="southwest")
    {
        r_dir="northeast";
    }
    else if (dir=="southeast")
    {
        r_dir="northwest";
    }
    else if (dir=="northwest")
    {
        r_dir="southeast";
    }
    else if (dir=="northeast")
    {
        r_dir="southwest";
    }
    else if (dir=="up")
    {
        r_dir="down";
    }
    else if (dir=="enter")
    {
        r_dir="out";
    }
    else
    {
        return notify_fail("你可选的方向只有north,south,west,east,northeast,northwest,southeast,southwest,up,down,enter和out。\n");
    }
    exits = room->query("exits");
    if (exits&&exits[dir])
        return notify_fail("这个方向上已经有房间了。\n");
	if( !write_file(file, @ROOM_CODE
// This is a room made by roommaker.

inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "空房间");
	set("long", "这是一间什麽也没有的空房间。\n");
	setup();
	replace_program(ROOM);
}

ROOM_CODE ) ) return notify_fail("你没有写入档案(" + file +")的权利。\n");
	message_vision(HIW"$N开始施工，迅速修好了一件房间，$n看着新房，开心地合不拢嘴。\n"NOR, this_object(),me);
    if (room->query("exits"))
    {
        exits=room->query("exits");
        exits+=([dir: file]);
    }
    else
    {
        exits=([ dir: file ]);
    }
    room->set("exits", exits );
    new_room=load_object(file);
    new_room->set("exits",([r_dir: base_name(room)]) );
    new_room->set("short",short_name);
    do_saveroom();
	return 1;
}

int save_room_file(string file, string str)
{
	rm(file);
	if( write_file(file, str) ) {
		write("新房修好了！\n");
		return 1;
	} else
		return notify_fail("新房修建失败了，假如你确定你有在这里建房的权限，请与巫师联系。\n");
}

int do_saveroom()
{
	object env;
	string str, *name, file;
	mapping prop;
	int i;

	env = environment(this_player());
	file = file_name(env) + ".c";
	str = "// Room: " + file + @ROOM_CODE


inherit ROOM;

void create()
{
ROOM_CODE
	;
	str += sprintf("\tset(\"short\", %O);\n", env->query("short") );
	str += sprintf("\tset(\"long\", @LONG\n%sLONG\n\t);\n", env->query("long") );
	prop = env->query_entire_dbase();
	name = keys(prop);
	for(i=0; i<sizeof(name); i++) {
		if( member_array(name[i], special_props)!=-1 ) continue;
		str += sprintf("\tset(\"%s\", %O);\n", name[i], prop[name[i]] );
	}
	str += "\n\tsetup();\n\treplace_program(ROOM);\n}\n";

	// Replace current directory with __DIR__ macro to make relocatable code.
	i = strwidth(file)-1;
	while( (i > 0) && (file[i]!='/')) i--;
	if( i>0 ) {
		str = replace_string(str, "\"" + file[0..i], "__DIR__\"");
	}


	save_room_file(file, str);
    return 1;
}

