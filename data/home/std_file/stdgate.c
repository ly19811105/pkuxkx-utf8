//所有的动作都要加上判断，看玩家是否有能力创建这个房间
//created by Pal
//cometh@tom.com
//2003.10.8
//山庄大门头文件
void init()
{
	object me;
	string host;
	host=query("host");
	me=this_player();
	if( host!=me->query("id") )
	{
		add_action("do_knock","knock");
		add_action("do_breakin","breakin");
	}
	else
	{
		tell_object(me,"你一阵欢喜，总算到家了，直接north进去吧。\n");
		add_action("do_north","north");
		if( !me->query("selfcreate/closed") )
			add_action("do_close","closehome");
		else
			add_action("do_open","openhome");
	}
}

int do_knock(string arg)
{
	object body,me;
	string host;
	me=this_player();
	host=query("host");
	if( !arg || arg!="gate" )
	{
		return notify_fail("你要敲什么？\n");
	}
	if( !(objectp(body = find_player(host)) && geteuid(body)==host 
                  && me->visible(body)) )
	{
		return notify_fail("主人不在，还是请回吧。\n");
	}
	if( sizeof(query("exits")) >1 )
	{
		return notify_fail("门开着呢，敲什么敲？\n");
	}
	if( body->query("selfcreate/closed") && !wizardp(me))//关闭后将不能用山庄赚钱等
		return notify_fail("山庄已经关闭了，还是换个时间来吧。\n");
	if( body->query("selfcreate/novisit") && !wizardp(me))//主人设置了不想让人进入
	{
		return notify_fail("主人现在不欢迎客人，你想要强行闯入(breakin)么？\n");
	}
	set("exits/north","/data/home/file/"+host[0..0]+"/"+host+"/room1.c");
	remove_call_out("close_door");
	call_out("close_door",20);
	tell_object(me,"你敲了敲门，家丁把门打开了。\n");
	return 1;
}

int close_door()
{
	delete("exits/north");
	printf("大门砰的一声关上了。\n");
	return 1;
}

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

int do_north()
{
	string filename,str;
	object room,me;
	me=this_player();
	str=query("host");
	if(str==me->query("id"))
	{
		filename="/data/home/file/"+str[0..0]+"/"+str+"/room1.c";
		if( !(room = find_object(filename)) )
			room = load_object(filename);
		if( !room->query("room_ok") )
		{
			if( room->query("host")==me->query("id") )
				tell_object(me,HIR"north方向的房间已经倒塌了，你需要修理(repaire)它。\n"NOR);
			else
				return notify_fail("north方向的房间已经倒塌了，为了你的个人安全，还是不要过去了吧。\n");
		}
		message_vision("家丁打开大门，$N大摇大摆走了进去，门立刻关上了。\n",me);
		me->move("/data/home/file/"+str[0..0]+"/"+str+"/room1.c");
		return 1;
	}
	return notify_fail("硬闯太没礼貌了，先敲门吧。\n");
}

int valid_leave(object me, string dir)
{
	string direction,filename,str;
	object room;
	int namelen,canenter;
	if(me->query_temp("issitting"))
		return notify_fail("你还坐着呢，先起来再走吧。\n");

	//这里判断目标房子是否可去，如果不是正常房间就不让过去。
	direction=format_dir(dir);
	filename=query("exits/"+direction);
	if(wizardp(me))
		printf("filename=%s\n",filename);
	str=query("host");
/*	canenter=0;
	if(str==me->query("id"))
	{
		if(direction=="north")
		{
			canenter=1;
			filename="/data/home/file/"+str[0..0]+"/"+str+"/room1.c";
		}
	}
*/
	if(!filename)
		return notify_fail("那个方向没有出路啊，你想撞墙吗？\n");
	if( sscanf(filename,"/data/home/file/%*s") )
	{
		namelen=strwidth(filename);
//		if(filename[(namelen-2)..(namelen-1)]!=".c")
//			filename+=".c";
		if( !(room = find_object(filename)) )
			room = load_object(filename);
		if( !room->query("room_ok") )
		{
			if( room->query("host")==me->query("id") )
				tell_object(me,HIR+direction+"方向的房间已经倒塌了，你需要修理(repaire)它。\n"NOR);
			else
				return notify_fail(direction+"方向的房间已经倒塌了，为了你的个人安全，还是不要过去了吧。\n");
		}
	//这里还要判断是否收到主人邀请
		if( (str!=me->query("id")) && !me->query_temp("selfcreate/invite/"+str) )
			return notify_fail("主人没有邀请你啊，你想硬闯(breakin)进去么？\n");
	}
/*	if(canenter)
	{
		tell_object(me,"家丁打开大门，你大摇大摆走了进去，门立刻关上了。\n");
		me->move("/data/home/file/"+str[0..0]+"/"+str+"/room1.c");
		return 0;
	}
*/
	//判断完毕

	return ::valid_leave(me, dir);
}

int do_breakin()
{
	object me,body;
	string host;
	host=query("host");
	me=this_player();
	if( !(objectp(body = find_player(host)) && geteuid(body)==host 
                  && me->visible(body)) )
		return notify_fail("乘着主人不在硬闯太没有英雄气概了。\n");
	if(body->query("selfcreate/closed"))//主人设置了山庄关闭，关闭后将没有人能够进入，npc也不会出现。
		return notify_fail("山庄现在关闭了，你看着高高地围墙不禁发起呆来。\n");
	//处理
	me->set_temp("selfcreate/breakin",1);
	return 1;
}

int do_close()//关闭山庄
{
	return 1;
}

int do_open()//开放山庄
{
	string filename,str;
	object ob,me;
	int i;
	me=this_player();
	str=me->query("id");
	if(str!=query("host")) return 0;
	for(i=1;i<=me->query("selfcreate/hotel");i++)
	{
		filename="/data/home/file/"+str[0..0]+"/"+str+"/hotel"+i+"/npc/waiter.c";
		if(wizardp(me))
			printf("filename=%s\n",filename);
		if( file_size(filename)<1 )
			continue;
		if(!( ob = find_object(filename)) )
			ob = load_object(filename);
		if( objectp(ob) && living(ob) )
		{
			if(wizardp(me))
				printf("找到一个.\n");
		}

		ob->delete("closed");
		ob->save();
		ob->restore();
	}
	return 1;
}