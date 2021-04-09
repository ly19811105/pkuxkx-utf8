//By Pal
//新房间模板
//所有的动作都要加上判断，看玩家是否有能力创建这个房间
#pragma save_binary

#include <ansi.h>
inherit ROOM;
int save();
int restore();
string query_save_file();
void create()
{
	set("short", "新房间");
	set("long", @LONG
这是一个新的房间，你可以对它进行装修。
LONG
	);
	set("valid_startroom",0);
	set("host","pal");//所有者
	set("roomvalue",0);//房间价值
	set("room_ok",1);//是否好的房间
	set("exits", ([
//房间出口
		]));
	set("objects", ([
//房间有的物品
		]));
	restore();
	setup();
}

void init()
{
	object link_ob;
	string id;
	link_ob=this_player()->query_temp("link_ob");
	id=link_ob->query("id");
	if( id==query("host") )
	{
		add_action("do_help","help_createroom");//帮助
		add_action("do_set_short","set_short");//设置短描述
		add_action("do_set_long","set_long");//设置长描述
		add_action("set_start","set_startroom");//设置start_room
		add_action("make_new_room","makeroom");//创建新房间
		add_action("close_room","closeroom");//关闭删除房间
		add_action("do_additem","additem");//添加物品objects
		add_action("do_destitem","destitem");//去掉物品objects
		add_action("do_listitem","listitem");//列出玩家已购买物品
	}
}

string query_save_file()//.o文件放在/data/home/save/目录下，.c文件放在/data/home/file/目录下
{
		string str,*filename,host;
		str = file_name();
		host = query("host");
		filename = explode(str,"/");
		str=filename[sizeof(filename)-1];
        if( !stringp(str) || !stringp(host) ) return 0;
        return sprintf("/data/home/save/" + host[0..0] + "/" + host + "/" + str);
}

int save()
{
        string file;
		int result;
        if( stringp(file = this_object()->query_save_file()) ) {
                assure_file(file+ __SAVE_EXTENSION__);
                result = save_object(file,1);
                return result;
        }
        return 0;
}

int restore()
{
        string file;

        if( stringp(file = this_object()->query_save_file()) )
        if(restore_object(file,1))
        {
                return 1;
        }
        return 0;
}

string check_str(string str)
{ 
    str=replace_string(str,"\"","");
    str=replace_string(str,";","");
    str=replace_string(str,"\\","");
    str=replace_string(str,"/","");
    str=replace_string(str,"'","");
    str=replace_string(str,"`","");
    str=replace_string(str,",","");
    str=replace_string(str,"!","");
    str=replace_string(str,"~","");
    str=replace_string(str,"{","");
    str=replace_string(str,"}","");
    str=replace_string(str,"$","");
    str=replace_string(str,"&","");
    return str;
}

int do_help()
{
	return 1;
}

int set_start()//设置startroom
{
	if(query("valid_startroom"))
		set("valid_startroom",0);
	else
		set("valid_startroom",1);
	save();
	restore();
	return 1;
}

int do_set_short(string arg)
{
	if (!arg)
		return notify_fail("格式：set_short <描述>\n");
	arg=check_str(arg);
	set("short",arg);
	save();
	restore();
	return 1;
}

int do_set_long(string arg)
{
	if (!arg)
		return notify_fail("格式：set_long <描述>\n");
	arg=check_str(arg);
	set("long",arg+"\n");
	save();
	restore();
	return 1;
}

int make_new_room(string arg)//建设新房间,make_new_room direct
{
	string direction1,direction2,newroom,str,filename;
	object room,me;
	int roomnum;

	//这里需要加判断玩家是否有能力建设新房间

	if (!arg)
	{
		return notify_fail("指令格式：makeroom direction\n");
	}
	switch(arg)
	{
		case "n":
		case "north":
			direction1="north";
			direction2="south";
			break;
		case "s":
		case "south":
			direction1="south";
			direction2="north";
			break;
		case "e":
		case "east":
			direction1="east";
			direction2="west";
			break;
		case "w":
		case "west":
			direction1="west";
			direction2="east";
			break;
		case "nw":
		case "northwest":
			direction1="northwest";
			direction2="southeast";
			break;
		case "ne":
		case "northeast":
			direction1="northeast";
			direction2="southwest";
			break;
		case "sw":
		case "southwest":
			direction1="southwest";
			direction2="northeast";
			break;
		case "se":
		case "southeast":
			direction1="southeast";
			direction2="northwest";
			break;
		case "u":
		case "up":
			direction1="up";
			direction2="down";
			break;
		case "d":
		case "down":
			direction1="down";
			direction2="up";
			break;
		case "in":
			direction1="in";
			direction2="out";
			break;
		case "out":
			direction1="out";
			direction2="in";
			break;
		default:
			return notify_fail("指令格式：makeroom direction，direction为方向。\n");
	}
	me=this_player();
	room=this_object();
	if( query("exits/" + direction1) )
		return notify_fail("这个出口已经有房间了。\n");
	roomnum=(int)me->query("selfcreate/roomnum");
	roomnum++;
	str=room->query("host");
//	printf("host=%s\n",str);
	filename="/data/home/file/"+str[0..0]+"/"+str+"/room"+sprintf("%d",roomnum)+".c";
	while(file_size(filename)!=-1)
	{
		roomnum++;
		filename="/data/home/file/"+str[0..0]+"/"+str+"/room"+sprintf("%d",roomnum)+".c";
	}
	//创建新房间
//	printf("filename=%s\n",filename);
	newroom=read_file("/data/home/std_file/sampleroom.c");
	newroom=replace_string(newroom,"pkuxkx",str,1,1);
	newroom=replace_string(newroom,"ROOM_NAME","新房间",1,1);
	assure_file(filename);
	if( !write_file(filename,newroom,1) )
		return notify_fail("文件写入失败。\n");
	if(!( room = find_object(filename)) )
		room = load_object(filename);
	room->set("exits/" + direction2,file_name());
	room->save();
	room->restore();
	//创建新房间完毕
	set("exits/" + direction1,filename);
	save();
	restore();
	me->set("selfcreate/roomnum",roomnum);
	write("新房间创建成功！\n");
	return 1;
}
int close_room(string arg)
{
	string direction1,direction2,newroom,str,filename;
	object room,me;
	int roomnum;

	if (!arg)
	{
		return notify_fail("指令格式：closeroom direction\n");
	}
	switch(arg)
	{
		case "n":
		case "north":
			direction1="north";
			direction2="south";
			break;
		case "s":
		case "south":
			direction1="south";
			direction2="north";
			break;
		case "e":
		case "east":
			direction1="east";
			direction2="west";
			break;
		case "w":
		case "west":
			direction1="west";
			direction2="east";
			break;
		case "nw":
		case "northwest":
			direction1="northwest";
			direction2="southeast";
			break;
		case "ne":
		case "northeast":
			direction1="northeast";
			direction2="southwest";
			break;
		case "sw":
		case "southwest":
			direction1="southwest";
			direction2="northeast";
			break;
		case "se":
		case "southeast":
			direction1="southeast";
			direction2="northwest";
			break;
		case "u":
		case "up":
			direction1="up";
			direction2="down";
			break;
		case "d":
		case "down":
			direction1="down";
			direction2="up";
			break;
		case "in":
			direction1="in";
			direction2="out";
			break;
		case "out":
			direction1="out";
			direction2="in";
			break;
		default:
			return notify_fail("指令格式：closeroom direction，direction为方向。\n");
	}
	me=this_player();
	if( !(query("exits/" + direction1)) )
		return notify_fail("这个出口方向没有房间。\n");
	filename=query("exits/" + direction1);
	str=query("host");
	if( !sscanf(filename,"/data/home/file/"+str[0..0]+"/"+str+"/%*s") )
		return notify_fail("你不能关掉不是你创建的房间！");
	delete("exits/" + direction1);
	save();
	restore();
	if( rm(filename) && rm(replace_string(replace_string(filename,"file","save"),".c",".o")) )
		tell_object(me,"你已经把"+direction1+"方向的房间关掉了。\n");
	else
		return notify_fail("文件删除失败！请通知巫师！\n");

	return 1;
}

int do_additem(string arg)//添加物品
{
	object me;
	mapping *item,goods,*obs,objs;
	string itemname,str,newitem,filename;
	int i,j,goodsfind,itemnum;

	if( !arg )
		return notify_fail("你要放置什么物品？\n");
	if( sizeof(query("objects")) > 3)
		return notify_fail("你已经往这个房间放置了太多物品了。\n");
	me=this_player();
	item=me->query_temp("selfitem");//selfitem标记
	if( !item )
		return notify_fail("你并没有购买任何物品。\n");
	goodsfind=0;
	for(i=0;i<sizeof(item);i++)
	{
		goods=item[i];
		if(arg==goods["id"])
		{
			goodsfind=1;
			break;
		}
	}
	if( !goodsfind )
		return notify_fail("你没有买这个东西啊，是不是记错了？\n");
	
	itemnum=(int)me->query("selfcreate/itemnum");
	itemnum++;
	str=query("host");
	filename="/data/home/file/"+str[0..0]+"/"+str+"/obj/obj"+sprintf("%d",itemnum)+".c";
	while(file_size(filename)!=-1)
	{
		itemnum++;
		filename="/data/home/file/"+str[0..0]+"/"+str+"/obj/obj"+sprintf("%d",itemnum)+".c";
	}
	//创建新物品
	if(file_size(goods["file"]+".c")<1)
		return notify_fail("文件读取错误，请通知巫师。\n");
	newitem=read_file(goods["file"]+".c");
	newitem=replace_string(newitem,"单位",goods["unit"]);
	newitem=replace_string(newitem,"标准物品",goods["name"]);
	newitem=replace_string(newitem,"biaozhun wupin",goods["realid"]);
	assure_file(filename);
	if( !write_file(filename,newitem,1) )
		return notify_fail("文件写入失败。\n");
	//物品创建完毕
	//这里删掉玩家买得部分

	//删除完毕
	obs=query("objects");
	if( !obs ) obs=({ });
	objs=([ ]);
	objs["/data/home/file/"+str[0..0]+"/"+str+"/obj/obj"+sprintf("%d",itemnum)]=1;
	obs += ({objs});
	delete("objects");
	save();
	restore();
	return 1;
}

int do_destitem()//去掉物品
{
	return 1;
}

int do_listitem()
{
	object me;
	mapping *item,goods;
	string itemname,str;
	int i;

	me=this_player();
	item=me->query_temp("selfitem");//selfitem标记
	if( !item )
		return notify_fail("你并没有购买任何物品。\n");
	str="";
	str="你购买了下列物品：\n";
	for(i=0;i<sizeof(item);i++)
	{
		goods=item[i];
		itemname=sprintf("%s(%s)",goods["name"],goods["id"]);
		str+=sprintf("一%s%-30s\n",goods["unit"],itemname);
	}
	tell_object(me,str);
	return 1;
}

int valid_leave(object me, string dir)
{
	if(me->query_temp("issitting"))
		return notify_fail("你还坐着呢，先起来再走吧。\n");
	return ::valid_leave(me, dir);
}
