//created by pal
//cometh@tom.com
//2003.10.8
//家丁模板头文件
string query_save_file()
{
		string str,*filename,owner;
		str = file_name();
		owner = query("owner");
		filename = explode(str,"/");
		str=filename[sizeof(filename)-1];
		filename = explode(str,"#");
		str=filename[0];
        if( !stringp(str) || !stringp(owner) ) return 0;
        return sprintf("/data/home/save/" + owner[0..0] + "/" + owner + "/npc/" + str);
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
	if(this_player()->query("id")==query("owner"))
	{
		add_action("do_adddescribe","add_describe");//设置家丁的描述
	}
}


int do_adddescribe(string arg)
{
	if (!arg)
		return notify_fail("格式：add_describe <描述>\n");
	arg=check_str(arg);
	set("long",arg+"\n");
	save();
	restore();
	return 1;
}

int self_destruct(object obj)//删除档案，死亡或者走掉
{
	string str,*filename,owner,name,name1,roomname,objname;
	object here,room;
	mapping obs,all_ob,objs;
	mixed *ob;
	int i;

	here=environment(obj);
	roomname=file_name(here);
	printf("调用了self_destruct函数.\n");
	str = file_name(obj);
	owner = obj->query("owner");
	filename = explode(str,"/");
	str=filename[sizeof(filename)-1];
	filename = explode(str,"#");
	str=filename[0];
	if( !stringp(str) || !stringp(owner) ) return notify_fail("文件错误，请通知巫师！\n");
	obs=here->query("objects");
	if( !obs ) return notify_fail("这个房间有错误，请通知巫师！\n");
	ob=keys(obs);
	all_ob=([ ]);
	name=sprintf("/data/home/save/" + owner[0..0] + "/" + owner + "/npc/" + str + ".o");
	name1=sprintf("/data/home/file/" + owner[0..0] + "/" + owner + "/npc/" + str );
	for(i=0;i<sizeof(obs);i++)
	{
		if(ob[i]==name1) continue;
		all_ob[ob[i]]=1;
	}
	here->delete("objects");
	if(all_ob!=([ ]))
		here->set("objects",all_ob);
	here->save();
	here->restore();
	name1 += ".c";
//	printf("save=%s,file=%s\n",name,name1);
	seteuid(ROOT_UID);
	if( file_size(name)>0 )
		if( !rm(name) )
			return notify_fail("删除档案"+name+"失败，请通知巫师。\n");
	if( file_size(name1)>0 )
		if( !rm(name1) )
			return notify_fail("删除档案"+name1+"失败，请通知巫师。\n");
	seteuid(geteuid());
	return 1;
}

void unconcious()
{
		die();
}

void die()
{
	message_vision("$N惨叫一声，倒在血泊中。\n",this_object());
	self_destruct(this_object());
	::die();
	return;
}