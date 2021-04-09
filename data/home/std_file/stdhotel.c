string query_save_file()
{
		string str,*filename,host;
		str = file_name();
		host = query("host");
		filename = explode(str,"/");
		str=filename[sizeof(filename)-1];
		filename = explode(str,"#");
		str=filename[0];
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

void init()
{
	object link_ob,me,*inv;
	string id,mes,outroom;
	int roomvalue,createtime,checktime,i,closetime;
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
	//这里要加上再减roomvalue的语句，客栈越豪华，赚钱越多，roomvalue减得越快
	if(roomvalue<0) roomvalue=0;
	set("checktime",time());
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
//应该把物品都destruct掉
	inv=all_inventory(this_object());
	for(i=0;i<sizeof(inv);i++)
	{
		if(inv[i]->query("selfcreate"))//表明是自己创建得
		{
			//暂时什么都不做，需要把物品也做成需要save得object
		}
	}
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

	if( id==query("host") )
	{//短描述固定
		add_action("do_set_long","set_long");//设定房间描述
		if( !query("opened") )//表明没有开张
		{
			add_action("do_open","openhotel");//创建客栈的其他房间，开张客栈
		}
		else
		{
			add_action("do_close","closehotel");//关闭客栈，删除其他房间
		}
	}
}

int do_set_long(string arg)
{
	if (!arg)
		return notify_fail("格式：set_long <描述>\n");
	arg=check_str(arg);
	set("long",changecolor(arg)+"\n");
	save();
	restore();
	tell_object(this_player(),"修改描述成功。\n");
	return 1;
}

/*
int do_repaire(string arg)
{
	object me;
	string id,id1,id2;
	int num;
	if(!arg)
		return notify_fail("你要修理什么？\n");
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
*/

int do_open()
{
	//需要创建一个小二，创建3个房间，up一个,然后东西各一个
	string roomtype,direction,direction1,direction2;
	string newroom,str,filename,roomname,roomname1,*rname,newitem;
	object room,me,ob;
	mapping obs,objs;
	int roomnum;
	if( query("opened") )
		return notify_fail("客栈已经开张了。\n");
	//加一个判断，如果没有招募到店小二，则不让开张
	if( !this_player()->query_temp("selfcreate/waiternum") )
	{
		return notify_fail("你首先得招募一个店小二，然后才能开张。\n");
	}
	roomtype="hotel";//房间类型
	str=query("host");
	roomname=file_name();
	rname = explode(roomname,"/");
	roomname=rname[sizeof(rname)-1];
	seteuid(ROOT_UID);
	for(roomnum=1;roomnum<4;roomnum++)
	{
		filename="/data/home/file/"+str[0..0]+"/"+str+"/"+roomname+"/"+roomtype+roomnum+".c";
		newroom=read_file("/data/home/std_file/"+roomtype+roomnum+".c");
		newroom=replace_string(newroom,"pkuxkx",str,1,1);
		roomname1=query("short");
		switch(roomnum)
		{
			case 1:roomname1+="内厅";break;
			case 2:roomname1+="第一休息室";break;
			case 3:roomname1+="第二休息室";break;
			default:
				return notify_fail("error\n");
		}
		newroom=replace_string(newroom,"ROOM_NAME",roomname1,1,1);
		assure_file(filename);
		if( !write_file(filename,newroom,1) )
			return notify_fail("文件写入失败。\n");
		if(!( room = find_object(filename)) )
			room = load_object(filename);
		switch(roomnum)
		{
			case 1://内厅
				room->set("exits/east","/data/home/file/"+str[0..0]+"/"+str+"/"+roomname+"/"+roomtype+"2");//第一休息室
				room->set("exits/west","/data/home/file/"+str[0..0]+"/"+str+"/"+roomname+"/"+roomtype+"3");//第二休息室
				room->set("exits/down",file_name());
				break;
			case 2://第一休息室
				room->set("exits/west","/data/home/file/"+str[0..0]+"/"+str+"/"+roomname+"/"+roomtype+"1");
				break;
			case 3://第二休息室
				room->set("exits/east","/data/home/file/"+str[0..0]+"/"+str+"/"+roomname+"/"+roomtype+"1");
				break;
			default:
				return notify_fail("error\n");
		}
		room->set("createtime",time());
		room->save();
		destruct(room);
	}//三个房间创建完毕
	set("exits/up","/data/home/file/"+str[0..0]+"/"+str+"/"+roomname+"/"+roomtype+"1");
	save();
	restore();
	//这里创建一个店小二
	filename="/data/home/file/"+str[0..0]+"/"+str+"/"+roomname+"/npc/waiter.c";
	if(file_size("/data/home/std_file/npc/waiter.c")<1)
		return notify_fail("文件读取错误，请通知巫师。\n");
	newitem=read_file("/data/home/std_file/npc/waiter.c");
	newitem=replace_string(newitem,"pkuxkx",str,1,1);
	newitem=replace_string(newitem,"这是一个标准店小二模板。","这是"+query("short")+"的店小二。",1,1);
	assure_file(filename);
	if( !write_file(filename,newitem,1) )
		return notify_fail("文件写入失败。\n");
	//删除完毕
	obs=query("objects");
	if( !obs ) obs=([ ]);
	objs=([ ]);
	objs["/data/home/file/"+str[0..0]+"/"+str+"/"+roomname+"/npc/waiter"]=1;
	obs += objs;
	set("objects",obs);
	save();
	restore();
	if(!( ob = find_object(filename)) )
		ob = load_object(filename);
	ob->move(this_object());
	set("opened",1);//表示开张了
	seteuid(geteuid());
	return 1;
}

int do_close()
{
	string filename,filename1,str,roomname,*rname,roomtype;
	int roomnum,i;
	object room,me,ob;
	mapping obs,objs;

	str=query("host");
	roomtype="hotel";
	roomname=file_name();
	rname = explode(roomname,"/");
	roomname=rname[sizeof(rname)-1];
	seteuid(ROOT_UID);
	//首先删除出口和小二
	obs=query("objects");
	if( !obs ) obs=([ ]);
	objs=([ ]);
	filename="/data/home/file/"+str[0..0]+"/"+str+"/"+roomname+"/npc/waiter";
/*	objs[filename]=1;
	obs -= objs;//这里不能这样删除
*/
	delete("objects");//这里偷懒了，如果有其他物品就不能这样，但是我没时间想怎么删除一个物品了，等有空再改吧。
	if( ob = find_object(filename) )
			destruct(ob);
	set("opened",0);
	delete("exits/up");
	save();
	restore();

	//删除文件，目录可以保留
	for(roomnum=1;roomnum<4;roomnum++)
	{
		filename="/data/home/file/"+str[0..0]+"/"+str+"/"+roomname+"/"+roomtype+roomnum;
		filename1=replace_string(filename,"/file/","/save/")+".o";
		filename+=".c";
		if(file_size(filename)>1)
			if( !rm(filename) )
				return notify_fail("文件"+filename+"删除错误");
		if(file_size(filename1)>1)
			if( !rm(filename1) )
				return notify_fail("文件"+filename1+"删除错误");
		if( room = find_object(filename) )
			destruct(room);
	}
	filename="/data/home/file/"+str[0..0]+"/"+str+"/"+roomname+"/npc/waiter";
	filename1=replace_string(filename,"/file/","/save/")+".o";
	filename+=".c";
	if(file_size(filename)>1)
		if( !rm(filename) )
			return notify_fail("文件"+filename+"删除错误");
	if(file_size(filename1)>1)
		if( !rm(filename1) )
			return notify_fail("文件"+filename1+"删除错误");
	if( ob = find_object(filename) )
		destruct(ob);
	//文件删除完毕
	seteuid(geteuid());
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

int valid_leave(object me, string dir)
{
	string direction,filename;
	object room,*inv;
	int namelen,i;
	if(me->query_temp("issitting"))
		return notify_fail("你还坐着呢，先起来再走吧。\n");

	//这里判断目标房子是否可去，如果不是正常房间就不让过去。
	direction=format_dir(dir);
	filename=query("exits/"+direction);
	if(wizardp(me))
		printf("filename=%s\n",filename);
	if(!filename)
		return notify_fail("那个方向没有出路啊，你想撞墙吗？\n");
	if( sscanf(filename,"/data/home/file/%*s") )
	{
		namelen=strwidth(filename);
//		if(filename[(namelen-2)..(namelen-1)]!=".c")
//			filename+=".c";
		if( !(room = find_object(filename)) )
			room = load_object(filename);
		if( !room->query("room_ok") && !room->query("roomvalue") )
		{
			if( room->query("host")==me->query("id") )
				tell_object(me,HIR+direction+"方向的房间已经倒塌了，你需要修理(repaire)它。\n"NOR);
			else
				return notify_fail(direction+"方向的房间已经倒塌了，为了你的个人安全，还是不要过去了吧。\n");
		}
	}
	//判断完毕
	if( me->query("id")!=query("host") )
	{
		if(me->query_temp("selfcreate/breakin"))//正在踢场子
		{
			inv=all_inventory(this_object());
			for(i=0;i<sizeof(inv);i++)
			{
				if( living(inv[i]) && inv[i]->query("selfcreate") )
					inv[i]->kill_ob(me);
			}
			return 0;
		}
		if( !me->query_temp("selfcreate/hotelfee") && direction=="up")        //这个标记表示付了钱
			return notify_fail("店小二拦住你，住店还是要钱的。");
	}
	return ::valid_leave(me, dir);
}
