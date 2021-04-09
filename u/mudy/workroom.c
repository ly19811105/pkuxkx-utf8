#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", MAG"千面工作室"NOR);
        set("long", @LONG
千面巫师的行宫。
LONG
        );
        set("exits", ([
                "out" : "/d/city/guangchang",
                "east":"/u/male/workroom.c",
"north":"/u/mudy/1.c",
"north":"/u/mudy/north1.c",
"eastup":"/u/mudy/east1.c",
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//OVER
                 ]));
set("objects", ([
            
            ]));
        set("valid_startroom", 1);
        setup();

}
//CUTHERE
//为以后cut做一个记号
int do_write(string arg,string dir,object me);
int get_shortname(string arg);
int get_longname(string arg);
string convert_dir(string dir);
int insert_path(string this_filename,string path);
int delete_dir(string this_filename,string dir);
int do_update(string path);
string shortname,longname,filename;
void init()
{
	set("canexpand",1);
	add_action("do_update","upd");
	add_action("do_cut","cut");
	add_action("do_maken","maken");
	add_action("do_makes","makes");
	add_action("do_makew","makew");
	add_action("do_makee","makee");
	add_action("do_makenw","makenw");
	add_action("do_makene","makne");
	add_action("do_makesw","makesw");
	add_action("do_makese","makese");
	add_action("do_enter","makeenter");
	add_action("do_out","makeout");
	add_action("do_makenu","makenu");
	add_action("do_makend","makend");
	add_action("do_makesu","makesu");
	add_action("do_makesd","makesd");
	add_action("do_makewu","makewu");
	add_action("do_makewd","makewd");
	add_action("do_makeeu","makeeu");
	add_action("do_makeed","makeed");
	add_action("do_link","link");
	add_action("do_makeup","makeu");
	add_action("do_maked","maked");
	add_action("do_del","del");

}
int do_del(string arg)
{
	string this_filename,that_filename;
	object to_room;
	this_filename=file_name(this_object())+".c";
	if(!arg) return notify_fail("请加入你要del的路径：del dir!\n");
	if(!query("exits/"+arg)) return notify_fail("这里没有这一条路径!");
	to_room=load_object(query("exits/"+arg));
	if(!to_room)
	{
		delete_dir(this_filename,arg);
//		call_out("update_later",1,this_filename,this_player());
		return notify_fail("路径那一头的房间已经不在了！\n");
	}
	if(!to_room->query("canexpand")) return notify_fail("这条路径不属于本系统，不能删除!\n");
	if(sizeof(this_object()->query("exits"))==1&&file_name(this_object())!=__DIR__+"sample") return notify_fail("再删这里就没有路径了!\n");
	delete_dir(this_filename,arg);
//	call_out("update_later",1,this_filename,this_player());
	that_filename=file_name(to_room)+".c";
	delete_dir(that_filename,convert_dir(arg));
	tell_object(this_object(),HIW"路径成功删除!\n"NOR);
	if(sizeof(to_room->query("exits"))<1)
	{
		rm(that_filename);
		tell_object(this_player(),"由于"+that_filename+"没有出口，已经被删除了!\n");
		return 1;
	}
//	call_out("update_later_nomove",1,this_filename);
	return 1;
}
int delete_dir(string this_filename,string dir)
{
	string *line,*des_line,this_file,remainder;
	int i;
	this_file=read_file(this_filename);
	if(!this_file) 
	{
		tell_object(this_player(),"read error!\n");
		return 1;
	}
		des_line=({});
		line=explode(this_file,"\n");
		for(i=0;i<sizeof(line);i++)
		{
			if(sscanf(line[i],"\""+dir+"\"%s",remainder)==1)
			{
				des_line+=({"//EXIT"});
				continue;
			}
			des_line+=({line[i]});
		}
		this_file=implode(des_line,"\n");
		write_file(this_filename,this_file,1);
	return 1;
}
int do_link(string arg)
{
	object me;
	string this_filename,from_filename,link_dir;
	me=this_player();
	if(arg)
	{
		this_filename=file_name(this_object())+".c";
		me->set_temp("makeroom/filename",this_filename);
		me->set_temp("makeroom/dir",arg);
		tell_object(me,HIW"你预备从这里往"+arg+"连到哪里呢？\n请在要连的地方在下一次link命令!\n"NOR);
		return 1;
	}
	else
	{
		from_filename=me->query_temp("makeroom/filename");
		link_dir=me->query_temp("makeroom/dir");
		if(!from_filename||!link_dir)
		{
			tell_object(me,HIW"请先在房间里用link dir命令指出你想从那个房间往哪个方向连!\n"NOR);
			return 1;
		}
		if(file_size(from_filename)<0)
		{
			tell_object(me,HIW"请重新用link dir命令，你先前指定的地方已经不存在了！\n");
			return 1;
		}
		this_filename=file_name(this_object())+".c";
		insert_path(from_filename,"\""+link_dir+"\" : \""+this_filename+"\",");
//		call_out("update_later_nomove",1,this_filename);
		insert_path(this_filename,"\""+convert_dir(link_dir)+"\" : \""+from_filename+"\",");
		tell_object(me,HIW+load_object(from_filename)->query("short")+HIW"通过"+link_dir+HIW"与这里相连!\n");
//		call_out("update_later",1,this_filename,this_player());
		return 1;
	}

}
int insert_path(string this_filename,string path)
{
	string *line,*des_line,this_file;
	int i;
	this_file=read_file(this_filename);
	if(!this_file) 
	{
		tell_object(this_player(),"read error!\n");
		return 1;
	}
		des_line=({});
		line=explode(this_file,"\n");
		for(i=0;i<sizeof(line);i++)
		{
			if(line[i]=="//EXIT")
			{
				des_line+=({path});
				break;
			}
			if(line[i]=="//OVER")
			{
				tell_object(this_player(),"这里的路径太多了。\n");
				return 1;
			}
			des_line+=({line[i]});
		}
		for(i=i+1;i<sizeof(line);i++)
		{
			des_line+=({line[i]});
		}
		this_file=implode(des_line,"\n");
		write_file(this_filename,this_file,1);
	return 1;
}
int do_makeup(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"up",me);
	return 1;
}
int do_maked(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"down",me);
	return 1;
}
int do_makeed(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"eastdown",me);
	return 1;
}
int do_makeeu(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"eastup",me);
	return 1;
}
int do_makewd(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"westdown",me);
	return 1;
}
int do_makewu(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"westup",me);
	return 1;
}
int do_makesd(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"southdown",me);
	return 1;
}
int do_makesu(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"southup",me);
	return 1;
}
int do_makend(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"northdown",me);
	return 1;
}
int do_makenu(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"northup",me);
	return 1;
}
int do_makeout(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"out",me);
	return 1;
}
int do_enter(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"enter",me);
	return 1;
}
int do_makese(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"southeast",me);
	return 1;
}

int do_makesw(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"soutwest",me);
	return 1;
}

int do_makene(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"northeast",me);
	return 1;
}

int do_makenw(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"northwest",me);
	return 1;
}

int do_update(string file)
{
object me = this_player();
object obj;
object* inv;
int i;
string err;

seteuid(ROOT_UID);
file = resolve_path(me->query("cwd"), file);
if( !sscanf(file, "%*s.c") ) file += ".c"; 
        me->set("cwf", file);

        if (obj = find_object(file)) {
                if( obj==environment(me) ) {
                        if( file_name(obj)==VOID_OB )
                                return notify_fail("你不能在 VOID_OB 里重新编译 VOID_OB。\n");
                        inv = all_inventory(obj);
                        i = sizeof(inv);
                        while(i--)
                                if( userp(inv[i]) ) inv[i]->move(VOID_OB, 1);
                                else inv[i] = 0;
                }
                destruct(obj);
        }
        if (obj) return notify_fail("无法清除旧程式码。\n");

    write(HIR"重新编译 " + file + "：");
        err = catch( call_other(file, "???") );
        if (err)
                printf( "发生错误：\n%s\n"NOR, err );
        else {
                write("成功！\n"NOR);
                if( (i=sizeof(inv)) && (obj = find_object(file))) {
                        while(i--)
                                if( inv[i] && userp(inv[i]) ) inv[i]->move(obj, 1);
                }
        }

return 1;
}
int do_maken(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"north",me);
	return 1;
}
int do_makes(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"south",me);
	return 1;
}
int do_makew(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"west",me);
	return 1;
}

int do_makee(string arg)
{
	object me;
	me=this_player();
	if(!arg) return notify_fail("请输入文件名字！\n");
	do_write(arg,"east",me);
	return 1;
}

int do_cut(string arg)
{
	string this_file,this_filename,*line,*des_line;
	int i;
	object me;
	me=this_player();
	
	if(me->query("id")!="mudy"&&me->query("id")!="male")
	{
		tell_object(me,"你不是屋子的主人!不能做清除操作！!\n");
		return 1;
	}
	
	this_filename=file_name(this_object())+".c";
	this_file=read_file(this_filename);
	if(!this_file) 
	{
		tell_object(this_player(),"read error!\n");
		return 1;
	}
	des_line=({});
	line=explode(this_file,"\n");
	for(i=0;i<sizeof(line);i++)
	{
		if(line[i]=="//EXIT"||line[i]=="//OVER") continue;
		if(line[i]=="//CUTHERE") break;
		des_line+=({line[i]});
	}
	this_file=implode(des_line,"\n");
	//write_file(this_filename,this_file,1);
	tell_object(me,this_file);

	return 1;
}
int do_write(string arg,string dir,object me)
{
	string this_file,this_filename,*line,*des_line,sample_file,sample_filename;
	int i;
	filename=__DIR__+arg;
	sample_filename="/u/mudy/sample.c";
	if(file_size(sample_filename)<0)
	{
		sample_filename=__DIR__+"sample.c";
		if(file_size(sample_filename)<0)
		{
			tell_object(me,"样本文件丢失!\n");
			return 1;
		}
	}
	if(sscanf(filename,"%s.c",this_file)!=1)
		filename=filename+".c";
	if(file_size(filename)>0) 
	{
		tell_object(me,"此文件已存在，且不为空，请更换文件名！\n");
		return 1;
	}

	if(me->query("id")!="mudy"&&me->query("id")!="male")
	{
		tell_object(me,"你不是屋子的主人!不能开辟房间!\n");
		return 1;
	}
	
	this_filename=file_name(this_object())+".c";
	this_file=read_file(this_filename);
	if(!this_file) 
	{
		tell_object(this_player(),"read error!\n");
		return 1;
	}
		des_line=({});
		line=explode(this_file,"\n");
		for(i=0;i<sizeof(line);i++)
		{
			if(line[i]=="//EXIT")
			{
				des_line+=({"\""+dir+"\":\""+filename+"\","});
				break;
			}
			if(line[i]=="//OVER")
			{
				tell_object(this_player(),"这里的路径太多了。\n");
				return 1;
			}
			des_line+=({line[i]});
		}
		for(i=i+1;i<sizeof(line);i++)
		{
			des_line+=({line[i]});
		}
		this_file=implode(des_line,"\n");
		write_file(this_filename,this_file,1);
	tell_object(me,HIW"请输入房间名字：\n"NOR);
	input_to((:get_shortname:));
	sample_file=read_file(sample_filename);
	write_file(filename,sample_file,1);
	insert_path(filename,"\""+convert_dir(dir)+"\":\""+file_name(this_object())+"\",");
/*	write_file(filename,"#include <ansi.h>\n
inherit ROOM;\n
void create()\n
{
      set(\"short\",\"SHORTNAME\");
      set(\"long\", @LONG\nLONGNAME
LONG
      );
      set(\"exits\", ([
	       \""+convert_dir(dir)+"\":\""+file_name(this_object())+"\",
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//EXIT
//OVER
		   ]));
		   setup();
}"
	,1);*/
	
	tell_object(this_object(),HIW"路径成功添加!\n"NOR);
	return 1;
}
int get_shortname(string arg)
{
	string file;
	file=read_file(filename);
	if(!arg)
	{
		tell_object(this_player(),HIW"请输入房间名字：\n"NOR);
		input_to((:get_shortname:));
		return 1;
	}
	shortname=arg;
	file=replace_string(file,"SHOR"+"TNAME",shortname);
	write_file(filename,file,1);	
	tell_object(this_player(),HIW"请输入房间描述：\n"NOR);
	input_to((:get_longname:));
	return 1;
}
int get_longname(string arg)
{
	string file;
	file=read_file(filename);
	if(!arg)
	{
		tell_object(this_player(),HIW"请输入房间描述：\n"NOR);
		input_to((:get_longname:));
		return 1;
	}
	longname=arg;
	file=replace_string(file,"LONG"+"NAME",longname);
	write_file(filename,file,1);
//	call_out("update_later_nomove",1,filename,this_object());
//	call_out("update_later",5,file_name(this_object())+".c",this_object());
	return 1;
}
string convert_dir(string dir)
{
	if(dir=="north")
		return "south";
	else if(dir=="south")
		return "north";
	else if(dir=="east")
		return  "west";
	else if(dir=="west")
		return "east";
	else if(dir=="northwest")
		return "southeast";
	else if(dir=="southeast")
		return "northwest";
	else if(dir=="northeast")
		return "southeast";
	else if(dir=="out")
		return "enter";

	else if(dir=="northup")
		return "southdown";
	else if(dir=="southdown")
		return "northup";

	else if(dir=="southup")
		return "northdown";
	else if(dir=="northdown")
		return "southup";

	else if(dir=="westup")
		return "eastdown";
	else if(dir=="eastdown")
		return "westup";

	else if(dir=="westdown")
		return "eastup";
	else if(dir=="eastup")
		return "westdown";

	else if(dir=="up")
		return "down";
	else if(dir=="down")
		return "up";


	else if(dir=="enter")
		return "out";
	else if(dir=="out")
		return "enter";
	else
		return "none";
}
/*
int update_later(string this_filename,object me)
{
	do_update(this_filename);
	//me->move(load_object(this_filename));
	call_out("movebak",5,me,this_filename);
	return 1;
}
int movebak(object me,string this_filename)
{
	me->move(load_object(this_filename));
	tell_object(me,"moveback!\n");
	return 1;
}
int update_later_nomove(string this_filename)
{
	do_update(this_filename);
	return 1;
}*/