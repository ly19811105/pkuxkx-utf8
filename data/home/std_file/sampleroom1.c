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
	set("short", "ROOM_NAME");//房间短描述，模板为ROOM_NAME
	set("long", @LONG
这是一个新的房间，你可以对它进行装修。
LONG
	);
	set("valid_startroom",0);
	set("host","pkuxkx");//所有者，模板里固定为pkuxkx
	set("roomvalue",50);//房间价值，初始为50，降到0就倒了
	set("room_ok",1);//是否好的房间
	set("selfcreate",1);
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
	object link_ob,me,*inv;
	string id,mes;
	int roomvalue,createtime,checktime,i;
	me=this_player();
	link_ob=me->query_temp("link_ob");
	if(!link_ob) return;
	id=link_ob->query("id");

//这里加上判断房间物品时间，损坏程度等等
	roomvalue=(int)query("roomvalue");
	checktime=(int)query("checktime");
	createtime=(int)query("createtime");
	if( !checktime )
		checktime=createtime;
//	一年，24小时=86400
	roomvalue-=(int)((time()-checktime)/17280);//一天降5点roomvalue
	if(roomvalue<0) roomvalue=0;
	set("ckecktime",time());
	if(roomvalue==0)
	{
		if(query("room_ok"))
		{
			delete("room_ok");
			CHANNEL_D->do_channel(this_object(), "rumor", "听说" + query("host") + "的" + query("short") + "由于修缮不力倒塌了。");
		}
		tell_object(me,HIR+BNK"你发现这个房间马上就要倒了，看来需要赶紧离开了。\n"NOR);
		set("short","倒塌的小屋");
		set("long","这是一间倒塌了的房间，你还是尽快离开得好。\n");
		call_out("kickplayer",5,me,environment(me));//5秒钟后不离开，房子倒塌，玩家被砸晕
	}
	set("roomvalue",roomvalue);
	save();
//检查房间完毕，检查物品

	inv=all_inventory(this_object());
	for(i=0;i<sizeof(inv);i++)
	{
		if(inv[i]->query("selfcreate"))//表明是自己创建得
		{
			//暂时什么都不做，需要把物品也做成需要save得object
		}
	}
//add_action
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
		//add_action("do_listitem","listitem");//列出玩家已购买物品，已经放到/cmds/usr下
		add_action("do_setguard","setguard");//在当前房间加入guard
		add_action("do_repaire","repaire");//修缮房间
	}
//	else
//	{
		if(roomvalue==0)
			mes=HIR"你发现这间房子摇摇欲坠，不禁害怕起来。\n"NOR;
		else if(roomvalue<100)
			mes="这是一间很普通的房子。\n";
		else if(roomvalue<500)
			mes="这是一间装修过得房子，看起来马马虎虎。\n";
		else if(roomvalue<1000)
			mes="很不错的房间，看起来很舒适。\n";
		else if(roomvalue<2000)
			mes="这是一间很不错的房间，看起来很豪华。\n";
		else if(roomvalue<3000)
			mes="一间金壁辉煌的房间，看起来已经有点奢侈了。\n";
		else
			mes=HIY"这个房间看起来如同皇宫一样，看得出主人真是奢侈极了。\n"NOR;
		tell_object(me,mes);
//	}

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
	write("Ok.\n");
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
	write("Ok.\n");
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
	write("Ok.\n");
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
	newroom=replace_string(newroom,"ROOM_NAME",me->query("selfcreate/castlename"),1,1);
	assure_file(filename);
	seteuid(ROOT_UID);
	if( !write_file(filename,newroom,1) )
		return notify_fail("文件写入失败。\n");
	if(!( room = find_object(filename)) )
		room = load_object(filename);
	room->set("exits/" + direction2,file_name());
	room->set("createtime",time());
	room->save();
	destruct(room);
	//创建新房间完毕
	set("exits/" + direction1,replace_string(filename,".c",""));
	save();
	restore();
	me->set("selfcreate/roomnum",roomnum);
	write("新房间创建成功！\n");
	seteuid(geteuid());
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
		case "enter":
			direction1="enter";
			direction2="out";
			break;
		case "out":
			direction1="out";
			direction2="enter";
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
	seteuid(ROOT_UID);
	if( rm(filename) && rm(replace_string(replace_string(filename,"file","save"),".c",".o")) )
		tell_object(me,"你把"+direction1+"方向的房间关掉了。\n");
	else
		return notify_fail("文件删除失败！请通知巫师！\n");
	room = find_object(filename);
	if( room && objectp(room) )
		destruct(room);
	return 1;
}

int do_additem(string arg)//添加物品，好像有问题，主要是添加的物品似乎会不对。
{
	object me,room,*inv,here;
	mapping *item,goods,obs,objs,*item1;
	string itemname,str,newitem,filename;
	int i,j,goodsfind,itemnum,roomvalue;

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
	newitem=replace_string(newitem,"VALUE",sprintf("%d",goods["value"]*100));
	seteuid(ROOT_UID);
	assure_file(filename);
	if( !write_file(filename,newitem,1) )
		return notify_fail("文件写入失败。\n");
	me->set("selfcreate/itemnum",itemnum);
	//物品创建完毕
	//这里删掉玩家买得部分
	item1=({ });
	for(j=0;j<sizeof(item);j++)
	{
//		printf("i=%d,j=%d\n",i,j);
		if(j==i) continue;
		item1+=({item[j]});
	}
	me->delete_temp("selfitem");
	me->set_temp("selfitem",item1);
	//删除完毕
	roomvalue=query("roomvalue");
	roomvalue+=goods["value"]/10;
	set("roomvalue",roomvalue);//这里增加房间豪华度。
	obs=query("objects");
	if( !obs ) obs=([ ]);
	objs=([ ]);
	objs["/data/home/file/"+str[0..0]+"/"+str+"/obj/obj"+sprintf("%d",itemnum)]=1;
	obs += objs;
	set("objects",obs);
	save();
	restore();

	here=this_object();
	room=new("/adm/single/temproom");
	inv=all_inventory(this_object());
	for(i=0;i<sizeof(inv);i++)
	{
		if(!inv[i]->query("selfcreate"))
			inv[i]->move(room);
	}
	::reset();
	inv=all_inventory(room);
	for(i=0;i<sizeof(inv);i++)
	{
		if(!inv[i]->query("selfcreate"))
			inv[i]->move(here);
	}
	tell_object(me,sprintf("你往这个房间添加了一%s%s\n",goods["unit"],goods["name"]));
	return 1;
}

int do_destitem(string arg)//去掉物品
{
	string id,id1,id2,filename,*file;
	object me,room,*inv;
	mapping all_ob,obs;
	mixed *ob;
	int num,i,j,roomvalue;
	if(!arg)
		return notify_fail("你要销毁什么？");
	me=this_player();
	if(!sscanf(arg,"%s %s %d",id1,id2,num))
	{
		num=0;
		if(!sscanf(arg,"%s %s",id1,id2))
			return notify_fail("指令格式：destitem id [num]\n");
	}
	id=id1+" "+id2;
	if(num<1) num=1;
	inv=all_inventory(this_object());
	if(!inv)
		return notify_fail("这里没有任何物品。\n");
	for(i=0,j=0;i<sizeof(inv);i++)
	{
		if(!inv[i]->query("selfcreate")) continue;
		if(inv[i]->query("id")==id) j++;
		if(j==num) break;//找到这个物品为inv[i]
	}
	if(j!=num)
		return notify_fail("这里没有这个物品。\n");
	num=i;
	filename=file_name(inv[num]);
	file=explode(filename,"#");
	filename=file[0];//得到这个物件的文件名，以便删除。
	if(wizardp(me)) printf("filename=%s\n",filename);
	//从房间里删除。
	obs=query("objects");
	if(!obs || sizeof(obs)<1)
		return notify_fail("房间出错，请通知巫师。\n");
	ob=keys(obs);
	all_ob=([ ]);
	id1=replace_string(filename,"/file/","/save/")+".o";
	id2=filename+".c";
	for(i=0;i<sizeof(obs);i++)
	{
		if(ob[i]==filename) continue;
		all_ob[ob[i]]=1;
	}
	delete("objects");
	if(sizeof(all_ob)>0)
		set("objects",all_ob);
	save();
	seteuid(ROOT_UID);
	//删除文件
	if( file_size(id1)>0 )
		if( !rm(id1) )
			return notify_fail("删除档案"+id1+"失败，请通知巫师。\n");
	if( file_size(id2)>0 )
		if( !rm(id2) )
			return notify_fail("删除档案"+id2+"失败，请通知巫师。\n");
	roomvalue=query("roomvalue");
	roomvalue-=inv[num]->query("value")/1000;
	if(roomvalue<0) roomvalue=0;
	set("roomvalue",roomvalue);//设置房间豪华程度
	//从房间删除完毕。

	destruct(inv[num]);
	tell_object(me,"你把"+id+"销毁了。\n");
	return 1;
}

int do_setguard(string arg)//添加物品
{
	object me,room,*inv,here;
	mapping obs,objs;
	string str,newitem,filename;
	int i,j,guardnum,num;

	if( !arg )
		return notify_fail("你要干什么？\n");
	if( sizeof(query("objects")) > 3)
		return notify_fail("这个房间已经满了，再也放不下东西了。\n");
	me=this_player();
	num=(int)me->query_temp("selfcreate/rencainum");//selfitem标记
	if( !num )
		return notify_fail("你并没有招募到任何家丁。\n");
	
	guardnum=(int)me->query("selfcreate/guardnum");
	guardnum++;
	str=query("host");
	filename="/data/home/file/"+str[0..0]+"/"+str+"/npc/guard"+sprintf("%d",guardnum)+".c";
	while(file_size(filename)!=-1)
	{
		guardnum++;
		filename="/data/home/file/"+str[0..0]+"/"+str+"/npc/guard"+sprintf("%d",guardnum)+".c";
	}
	//创建新家丁
	if(file_size("/data/home/std_file/npc/guard.c")<1)
		return notify_fail("文件读取错误，请通知巫师。\n");
	newitem=read_file("/data/home/std_file/npc/guard.c");
	newitem=replace_string(newitem,"pkuxkx",str,1,1);
	newitem=replace_string(newitem,"这是一个标准家丁模板。","这是"+str+"的家丁。",1,1);
	seteuid(ROOT_UID);
	assure_file(filename);
	if( !write_file(filename,newitem,1) )
		return notify_fail("文件写入失败。\n");
	me->set("selfcreate/guardnum",guardnum);
	//家丁创建完毕
	//这里删掉玩家买得部分
	num--;
	me->set_temp("selfcreate/rencainum",num);
	//删除完毕
	obs=query("objects");
	if( !obs ) obs=([ ]);
	objs=([ ]);
	objs["/data/home/file/"+str[0..0]+"/"+str+"/npc/guard"+sprintf("%d",guardnum)]=1;
	obs += objs;
	set("objects",obs);
	save();
	restore();

	here=this_object();
	room=new("/adm/single/temproom");
	inv=all_inventory(this_object());
	for(i=0;i<sizeof(inv);i++)
	{
		if(!inv[i]->query("selfcreate"))
			inv[i]->move(room);
	}
	::reset();
	inv=all_inventory(room);
	for(i=0;i<sizeof(inv);i++)
	{
		if(!inv[i]->query("selfcreate"))
			inv[i]->move(here);
	}
	tell_object(me,"你往这个房间添加了一位家丁\n");
	return 1;
}
/*
int do_listitem()
{
	object me;
	mapping *item,goods;
	string itemname,str;
	int i;

	me=this_player();
	item=me->query_temp("selfitem");//selfitem标记
	if( !item || !sizeof(item))
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
*/

string format_dir(string arg)
{
	string direction1;
	switch(arg)
	{
		case "n":
		case "north":
			direction1="north";
			break;
		case "s":
		case "south":
			direction1="south";
			break;
		case "e":
		case "east":
			direction1="east";
			break;
		case "w":
		case "west":
			direction1="west";
			break;
		case "nw":
		case "northwest":
			direction1="northwest";
			break;
		case "ne":
		case "northeast":
			direction1="northeast";
			break;
		case "sw":
		case "southwest":
			direction1="southwest";
			break;
		case "se":
		case "southeast":
			direction1="southeast";
			break;
		case "u":
		case "up":
			direction1="up";
			break;
		case "d":
		case "down":
			direction1="down";
			break;
		default:
			direction1=arg;
	}
	return direction1;
}
int valid_leave(object me, string dir)
{
	string direction,filename;
	object room;
	if(me->query_temp("issitting"))
		return notify_fail("你还坐着呢，先起来再走吧。\n");

	//这里判断目标房子是否可去，如果不是正常房间就不让过去。
	direction=format_dir(dir);
	filename=query("exits/"+direction);
	if(wizardp(me))
		printf("filename=%s\n",filename);
	if(!filename)
		return notify_fail("那个方向没有出路啊，你想撞墙吗？\n");
	if(!( room = find_object(filename)) )
		room = load_object(filename);
	if( !room->query("room_ok") )
	{
		if( room->query("host")==me->query("id") )
			tell_object(me,HIR+direction+"方向的房间已经倒塌了，你需要修理(repaire)它。\n"NOR);
		else
			return notify_fail(direction+"方向的房间已经倒塌了，为了你的个人安全，还是不要过去了吧。\n");
	}
	//判断完毕

	return ::valid_leave(me, dir);
}

int kickplayer(object me,object here)
{
	if(environment(me)==here)//表示玩家还在这个房间
	{
		//进行惩罚
		CHANNEL_D->do_channel(this_object(), "rumor", "听说" + me->name(1) + "被压在" + here->query("short") + "下了。");
		me->move("/d/city/wumiao");
		me->unconcious();
		return 1;
	}
	return 1;
}

int do_repaire(string arg)
{
	object me;
	string id,id1,id2;
	int num;
	if(!arg)
		return notify_fail("你要修理什么？");
	me=this_player();
	if(arg=="here" || arg=="room")//表明是修缮这个房间
	{
		//考虑一下需要的材料，耗费的金钱等等
		set("room_ok",1);
		set("roomvalue",50);
		set("short",me->query("selfcreate/castlename"));
		set("long","这是一个刚刚修缮一新的房间，你可以对它进行装修。\n");
		set("checktime",time());
		save();
		restore();
		remove_call_out("kickplayer");//不再踢人。这里如果同时有几个玩家会怎么样呢？
		me->save();
		tell_object(me,"你将这个房间修缮一新。\n");
		return 1;
	}
	if(!sscanf(arg,"%s %s %d",id1,id2,num))
	{
		num=0;
		if(!sscanf(arg,"%s %s",id1,id2))
			return notify_fail("指令格式：repaire id [num]\n");
	}
	id=id1+" "+id2;
	if(num<1)
		num=1;
	//修缮物品
	return 1;
}