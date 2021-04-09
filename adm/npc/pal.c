#pragma save_binary
inherit NPC;
#include <ansi.h>
#include <changecolor.h>

string changecolor(string);

void create()
{
		set_name("周彦钦", ({"zhou yanqin","pal chow","pal"}));
		set("gender", "男性");
		set("age", 23);
		set("long","一个很普通的人。\n可以向他申请(apply)创建山庄\n");
		set("attitude", "friendly");
		set("combat_exp", 1);
		set("per", 25);
		set("no_get",1);
		set("no_fight",1);
		set("shen_type",1);set("score",200);setup();

                carry_object("/clone/misc/cloth")->wear();
		add_money("gold", 1);

}

void init()
{
	add_action("do_apply", "apply");
//	add_action("do_enter", "enter");
	if(this_player()->query("id")=="pal")
	{
		add_action("do_destory", "destory");//关闭山庄，现在只是用于测试
		add_action("do_makeitem","makeitem");
		add_action("do_full", "dofull");
	}
}

int do_apply(string arg)
{
	object me,room;
	string newroom,filename,str,castlename,act;

	me = this_player();

	if(!arg || (!sscanf(arg,"%s %s",act,castlename)) || act!="创建")
		return notify_fail("格式：apply 创建 山庄名称\n");
	//这里是检查条件
	//首先判断是否有资格
	//这里另外写一个函数，输入山庄的名称
	str=me->query("id");
	castlename=changecolor(castlename);
	filename="/data/home/file/"+str[0..0]+"/"+str+"/"+"gate.c";//固定入口文件名
	if(file_size(filename) > 0)
		return notify_fail("你已经有了自己山庄，还瞎凑什么热闹？\n");
	///////////////
	me->delete("selfcreate");
	newroom=read_file("/data/home/std_file/gate.c");
	newroom=replace_string(newroom,"pkuxkx",str,1,1);
	newroom=replace_string(newroom,"ROOM_NAME",castlename+"入口",1,1);
	newroom=replace_string(newroom,"山庄大门","这里就是"+str+"得"+castlename+"了。");
	newroom=replace_string(newroom,"山庄入口房间","/data/home/file/"+str[0..0]+"/"+str+"/room1.c");
	seteuid(ROOT_UID);
	assure_file(filename);
	if( !write_file(filename,newroom,1) )
		return notify_fail("文件写入失败\n");
	filename="/data/home/file/"+str[0..0]+"/"+str+"/room1.c";
	if( file_size(filename) <1 )
	{
		newroom=read_file("/data/home/std_file/sampleroom.c");
		newroom=replace_string(newroom,"pkuxkx",str,1,1);
		newroom=replace_string(newroom,"ROOM_NAME",castlename,1,1);
		assure_file(filename);
		if( !write_file(filename,newroom,1) )
			return notify_fail("文件写入失败\n");
	}
	if(!( room = find_object(filename)) )
		room = load_object(filename);
	room->set("exits/south","/data/home/file/"+str[0..0]+"/"+str+"/gate");
	room->set("createtime",time());
	room->save();
	destruct(room);
	room=environment(this_object());
	room->restore();
	newroom=room->query("item_desc/list");
	if( !newroom || newroom=="" )
		newroom=sprintf("%-40s主人为：%s\n",castlename,str);
	else
		newroom += sprintf("%-40s主人为：%s\n",castlename,str);
	room->set("item_desc/list",newroom);
	room->save();
	room->restore();
	seteuid(geteuid());
	me->set("selfcreate/castlename",castlename);
	me->set("selfcreate/havecreated",1);
	me->set("selfcreate/createtime",time());
	me->save();
	CHANNEL_D->do_channel(this_object(), "chat", str+"经过不懈努力，终于成功创立"+castlename);
	message_vision("$N说道：我已经给你准备好了入口，你输入enter "+str+"就可以进入了\n",this_object(),me);

	return 1;
}

/*
int do_enter(string arg)//这个函数以后放到房间里去
{
	object me,room;
	string newroom,filename,str;

	me = this_player();
	str=me->query("id");
	if( str != arg)
		return notify_fail("你要到哪儿去？\n");
	filename="/data/home/file/"+str[0..0]+"/"+str+"/"+"gate.c";//固定入口文件名
	if(!( room = find_object(filename)) )
		room = load_object(filename);
	me->move(room);
	return 1;
}
*/
int do_destory()
{
	//这里先写着测试，以后再说。
	object room;
	seteuid(ROOT_UID);
	rm("/data/home/file/p/pal/gate.c");
	rm("/data/home/save/p/pal/gate.o");
	room=find_object("/data/home/file/p/pal/gate.c");
	if( room && objectp(room) )
		destruct(room);
	seteuid(geteuid());
	return 1;
}

void unconcious()
{
		die();
}

void die()
{
		this_object()->set("eff_qi",this_object()->query("max_qi"));
		this_object()->set("qi",this_object()->query("max_qi"));
		this_object()->set("eff_jing",this_object()->query("max_jing"));
		this_object()->set("jing",this_object()->query("max_jing"));
		return;
}

int do_makeitem(string arg)
{
	string id1,id2,shortname,longname;
	int value;
	if(!arg && !sscanf(arg,"%s %s %s %s %d",id1,id2,shortname,longname,value))
		return notify_fail("指令格式：id(中间有一个空格) 短描述 长描述 价值。\n");
	return 1;
}

int do_full() {
	object obj;
	int i;
	string *gifts=({ "qi","jing" });
	string *gifts1=({"jingli","neili" });

	obj = this_player();

    for( i = 0; i < sizeof(gifts); i++ )
    {
        obj->set(gifts[i],obj->query("max_"+gifts[i]));
        obj->set("eff_"+gifts[i],obj->query("max_"+gifts[i]));
    }
    for( i = 0; i < sizeof(gifts1); i++ )
    {
        obj->set(gifts1[i],obj->query("max_"+gifts1[i]));
    }
    obj->set("food",obj->max_food_capacity());
    obj->set("water",obj->max_water_capacity());
	obj->start_busy(0);
    write("恢复成功。\n");
    return 1;

}