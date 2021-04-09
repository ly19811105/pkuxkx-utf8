#include <dbase.h>
#include <move.h>
#include <ansi.h>
inherit ROOM;
inherit F_UNIOBJ;
void create()
{
	set("short", HIC"内室"NOR);
	set("long", @LONG
这是一间卧房，一张床铺，屋里有个大柜子(guizi)。
LONG
	);

	set("exits", ([
		"out" : __DIR__"houyuan",
	]));
    set("item_desc",
        ([
        "gui":"一个大木柜，你可以放(fang)东西，也可以取(qu)东西。\n",
        ]));
    set("sleep_room",1);
    set("max_contain_items",10);
	setup();
}

void init()
{
    add_action("do_store","fang");
    add_action("do_getout","qu");
    add_action("do_check","check");
}
int do_store(string arg)
{ 
	 object ob,me;
	 mapping this_store;
	 mapping *all_ob;
	 string *autoloads;
	 object *list;
	 int i;
	 int find;
     int extraroom=0;
	 me=this_player();
     extraroom=(int)me->query("chaoting/jiawang")*4;
     extraroom=(int)me->query("chaoting/wang")*10;
	 
 
	if(me->query("id")!=this_object()->query("owner"))//
		return notify_fail("你发神经呀，好好的把自己的东西往别人家里存？\n"); 
	if( !arg||!(ob = present(arg, this_player())) )
		return notify_fail("你要把什么放到柜子里呢？\n");
	if( ob->query("money_id") )	  
		return notify_fail("你要把钱往柜子里放，但又觉得不保险，只得作罢！\n");
	if( (int)ob->query("skill_type") && (int)ob->query("rigidity")<50) 
        return notify_fail("一把破破烂烂的兵器不值得保存！\n");
	if( first_inventory(ob))
		return notify_fail("还是先把"+ob->name()+"里面的东西取出来再往柜子里放吧。\n");
	if (ob->is_character())
		return notify_fail("活物可不能生塞到柜子里呀！\n");
	if(ob->query("no_store"))
		return notify_fail("这个东西不值得保存!\n");
	if(ob->query("unique"))
		return notify_fail("这种宝物你也敢存在家里？亏你也想得出来!\n");
	if(!ob->query("value"))
		return notify_fail("这个东西不值得保存!\n");
	if(ob->query("task_owner"))
		return notify_fail("task物件不能存放。\n");
	all_ob = me->query("store_ob");
	

	if(!all_ob) all_ob = ({});
        if((me->query("grandmaster")<1 && (sizeof(all_ob)) >= 10+extraroom) || (me->query("grandmaster")>=1 && (sizeof(all_ob)) >= 20+extraroom))
		return notify_fail("柜子里已经塞了太多的东西了，还是先拿出一点再放吧。\n");
    if (ob->query("equipped")) ob->unequip();
	this_store = ([ ]);
	this_store["file"] = base_name(ob);
	this_store["name"] = ob->name();
	this_store["attribute"] = ob->query("attribute");

	if ( arrayp(autoloads = me->query("auto_load")) &&
		member_array( this_store["file"] + ".c", autoloads ) != -1 )
	{
		autoloads -= ({ this_store["file"] + ".c" });
		me->set("auto_load", autoloads);
	}

	all_ob += ({this_store});
	message_vision("$N把身上的" + ob->name() + "拿出来放进柜子里了。\n", me);

	me->set("store_ob",all_ob);
	me->save();
	destruct(ob);

	return 1;
}

int do_check()
{
	int i;
	string str,name;
	mapping this_store;
	mapping *all_store;
	object me,lover,ob;
	me=this_player();
	
	if(me->query("id")!=this_object()->query("owner"))//
	{
		write("你发神经呀，乱翻别人的柜子作什么？\n");
		return 1;
	}
	
		all_store = me->query("store_ob");

		if(!all_store )
		{
			write("柜子里空空如也，啥也没有！\n");
			return 1;
		}

		write("\n柜子里目前存放的物品有：\n");
		for(i=0;i<sizeof(all_store);i++)
		{
			this_store = all_store[i];
			if(mapp(this_store))
			{
				str=sprintf("%d          %s\n",i,this_store["name"]); 
				write(str);
			}
		}
		all_store -= ({0});
		set("store_ob",all_store);
		return 1;
}

/**************************************************/
int do_getout( string arg )
{
	object ob,me;
	int num, attribute;
	string file,err,aload,name,lovername;
	mapping this_store;
	mapping *all_store;
	object *list;
	int i;
	int find;

	me = this_player();
       if( me->is_busy() ) return notify_fail("你上一个动作还没有完成。\n");
	
	if(me->query("id")!=this_object()->query("owner"))//
		return notify_fail("你发神经呀，乱翻别人的柜子作什么？\n"); 

	notify_fail("你要把什么从柜子里拿出来？\n");
	if(!arg) return 0;
	if( !sscanf(arg, "%d" , num ) ) return 0;
	all_store = me->query("store_ob");
	
	if((num<0)|| (num>=sizeof(all_store)) )
		return 0;

	this_store = all_store[num];					
	file = this_store["file"] ;
	err = catch(ob = new(file));
	if( err || !ob )
	{
		write("你觉得似乎失落了什麽重要的东西，最好通知一下巫师。\n");
		log_file("AUTOLOAD", sprintf("Fail to autoload %s of %s, error \n",
		file, this_object()->query("name"), err));
		all_store[num] = 0;
		all_store -= ({0});
		me->set("store_ob",all_store);
		return 1;
	}

	export_uid(ob);
	if((int)me->query_encumbrance() + ob->weight()
		> (int)me->query_max_encumbrance() )
	{
		write(ob->name()+"对你来说太重了。\n");
		return 1;
	}
	ob->move(me);
	if( (name = this_store["name"]) != ob->name() )
		ob->set("name",name);
	attribute = this_store["attribute"];
	reset_attribute(me, ob, attribute);
	all_store[num] = 0;
	all_store -= ({0});

	if(!sizeof(all_store))me->delete("store_ob");
		else me->set("store_ob",all_store);
 
		if ( ob->query("auto_load") && (sscanf(base_name(ob), "%*s/" + me->query("id") + "%*d") == 2) )
			me->add("auto_load", ({ base_name(ob) + ".c"}));

		me->save();
	message_vision("$N从柜子里取出了"+ob->name()+"\n",me );
	return 1;
}