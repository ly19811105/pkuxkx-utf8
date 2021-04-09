// all messages board by cbra 1997-12-6
// Put all the board together.
// modify to chinese and name modify to (Board Manager)by ken at 97-12-8
// modify by cbra at 97-12-8
// modify  for autoload boards from BOARD_PATH by ken at 97-12-10
// modify for display message for load board by ken at 97-12-14
// modify for transfer post to document by ken at 98-2-17
// [98-9-2] updated tansfer post by ken@XAJH.

#include <ansi.h>

inherit COMBINED_ITEM;

string short();
string long();
int do_discard(string arg);
int do_display();
int do_post(string arg);
int do_read(string arg);
int do_select(string arg);
int do_help(string arg);
// add for transfer post to document
int do_write(string arg);
// for autoload
void set_amount(int v);
int query_autoload();
// for load board from BOARD_PATH
int load_board();

#define BOARD_PATH "/clone/board/"
// add by fuyo for save a post to save_b.c
#define BACKUP_B "save_b.c"

protected mapping board_db =([]);

void create()
{
	set_name("留言板管理器", ({ "board manager","bmgr", "bm" }) );
	set("no_get", 1);
	set("no_drop",1);
	set("unit","个");
	set("base_unit","个");
	set_amount(1);
	seteuid(ROOT_UID);
}

void init()
{
	if( wiz_level(this_player()) > 0 ) {
		add_action("do_write","write");
		add_action("do_post", "post");
		add_action("do_read", "read");
		add_action("do_discard", "discard");
		add_action("do_select", "select");
		add_action("do_help","help");
		add_action("do_display","index");
	}
}

int do_help(string arg)
{
	if(!arg)	return 0;
	if( arg != "bm" && arg !="board manager" && arg != "bmgr")
		return 0;
	load_board();
	arg = sprintf("%d",sizeof(board_db));
	write("□ 留言板管理器使用方法\n\n"
		"\t选定一个留言板：select <编号：1-"+arg+">。\n"
		"\t在当前选定留言板发表文章：post <标题>。\n"
		"\t在当前选定留言板读取文章：read <编号>。\n"
		"\t在当前选定留言板删除文章：discard <编号>。\n"
		"\t显示当前选定留言板所有文章标题：index。\n"
		"\t将当前选定留言板指定文章永久保留：write。\n"
		"\t相关帮助： help board。\n\n"
		"97-12-11 by cbra & ken。\n");
	return 1;
}

string short()
{
	return ::name(1) + "(" + capitalize(::query("id")) + ")";
}

string long()
{	
	int select,i, rs,us, posts,unRead, X;
	string msg,title1,title2;

	i = posts = unRead = 0;

	load_board();
	select = this_user()->query_temp("bm");
	msg=RED" ★ "NOR"留言板管理器的使用方法请见 help bm。\n\n";
	for(i=0; i<sizeof(board_db); i++) {
		sscanf((BOARD_PATH+board_db[i])->short(),"%s %s",title1,title2);
		X = sscanf( title2, "[ %d 张留言，%d 张未读 ]", rs, us );
		if( X == 1 )
			posts += rs;
		if( X == 2 ) {
			posts += rs;
			unRead += us;
			}
		

		msg += sprintf("\t%s %2d. %-32s %s\n",
			(select == i+1) ? RED"√"NOR:"  ",
			i+1,title1,title2);
	}
	this_user()->start_more(msg);
	msg = sprintf("\n目前「"MUD_NAME"」共有 %d 个留言板，",sizeof(board_db) );
	msg += sprintf("%d 张留言%s", posts, 
						( unRead == 0 ? "。\n"
							:
						sprintf("，其中 %d 张留言你还未读。\n",unRead) ) );

	return msg;
}

int do_display()
{
	string msg;
	int select;

	load_board();
	select = this_user()->query_temp("bm");
	if( select < 1 ) {
		msg=RED" ★ "NOR"留言板管理器的使用方法请见 help bm。\n";
		write(msg);
		return 1;
	}
	msg = (BOARD_PATH+board_db[select-1])->long();
	this_user()->start_more(msg);
	return 1;
}

int do_select(string arg)
{
	string msg;
	int select;

	load_board();

	if (!arg)	{
		if( this_user()->query_temp("bm") )
			select = this_user()->query_temp("bm");
		else	select = 0;
	}
	else {
		if( sscanf(arg,"%d",select) !=1)
			select = 0;
		if( select > sizeof(board_db) )
			select = 0;
	}
	if( select < 1 && arg && upper_case(arg) == "NEXT" ) {
		select = this_user()->query_temp("bm") + 1;
		if( select > sizeof(board_db) )
			select = 0;
	}
	if( select < 1 ) {
		msg = sprintf("请用 select <1-%d>|next 选定正确的留言板编号。\n",sizeof(board_db));
		return notify_fail(msg);
	}
	this_user()->set_temp("bm", select);
	msg = sprintf("您目前选择的是：%d. %s", select,(BOARD_PATH+board_db[select-1])->short());
	this_user()->start_more(msg);
	return 1;
}

int do_post(string arg)
{
	int select;

	select = this_user()->query_temp("bm");
	if( select < 1 ) {
		write(RED" ★ "NOR"留言板管理器的使用方法请见 help bm。\n");
		return 1;
	}
	select --;
	write("您目前选择的是："+(BOARD_PATH+board_db[select])->name());

	if(strcmp(board_db[select],BACKUP_B)==0)
	{
		write(RED"\n\n对不起，本板为精华存放区，禁止 post。\n\n"NOR);
		return 1;
	}

	write("\n留言标题为："+arg+"\n");
	return (BOARD_PATH+board_db[select])->do_post(arg);
}

int do_read(string arg)
{
	int select;
	string name;

	select = this_user()->query_temp("bm");
	if( select < 1 ) {
		write(RED" ★ "NOR"留言板管理器的使用方法请见 help bm。\n");
		return 1;
	}
	select --;
	name = (BOARD_PATH+board_db[select])->short();
	if( arg == "new" && name[sizeof(name)-6..sizeof(name)-3] != "未读" )
		while( select<sizeof(board_db) ) {
			name = (BOARD_PATH+board_db[select])->short();
			if( name[sizeof(name)-6..sizeof(name)-3] == "未读" ) {
				break;
			}
			else
				select ++;
		}
	if( select > sizeof(board_db) -1 ) {
		select = sizeof(board_db);
		select --;
	}
	this_user()->set_temp("bm", select+1);
	write("您目前选择的是："+name+"\n");
	return (BOARD_PATH+board_db[select])->do_read(arg);
}

int do_discard(string arg)
{
	int select;
	select = this_user()->query_temp("bm");
	if( select < 1 ) {
		write(RED" ★ "NOR"留言板管理器的使用方法请见 help bm。\n");
		return 1;
	}
	select --;

	if(strcmp(board_db[select],BACKUP_B)==0) {
		if( wiz_level(this_player()) < wiz_level("(arch)") )		{
			write(RED"\n对不起，本板为精华存放区，禁止 discard。\n\n"NOR);
			return 1;
		}
	}

	write((BOARD_PATH+board_db[select])->name());
	return (BOARD_PATH+board_db[select])->do_discard(arg);
}

// for autoload

void set_amount(int v)
{
	if( v < 0 ) error("combine:set_amount less than 1.\n");
	if ( v==0 ) call_out("destruct_me", 1);
	else { 
		if (v>1) write(RED"您将身上的"+this_object()->name()+"更新了。\n"NOR);
		amount = 1;
	}
}

int query_autoload() { 
        return 1;
}

// load boards
int load_board() {
	int i,jj;
	mixed *names;

	names = get_dir(BOARD_PATH, -1);
	if( !sizeof(names)) {
		if (file_size(BOARD_PATH) == -2)
			return notify_fail(MUD_NAME+"定义目录中无任何留言版。\n");
		else
			return notify_fail("定义的留言板目录不存在。\n");
	}
	
	jj=0;
	for( i=0; i<sizeof(names);i++) {
		if(strsrch(names[i][0],".c")==-1) continue;
		board_db[jj]=sprintf("%s",names[i][0]);
		if( !find_object(BOARD_PATH+board_db[jj]) ) {
			write("载入"BOLD);
			load_object(BOARD_PATH+board_db[jj]);
			write((BOARD_PATH+board_db[jj])->name());
			write(NOR"("+board_db[jj]+")");
			write("成功。\n");
		}
		jj++;
	}
	return 1;
}

int do_write(string arg)
{
	int select,num;
	string syntax,body;
	object wiz,transfer,source;
	mapping post,notes;

	wiz = this_player();
	syntax="指令格式：write 留言编号。\n";

	select = this_user()->query_temp("bm");

	if( select < 1 ) {
		write(RED" ★ "NOR"留言板管理器的使用方法请见 help bm。\n");
		return 1;
	}

	if(!arg) return notify_fail(syntax);

	if( !arg )
		return notify_fail(syntax);

	select --;

	if(strcmp(board_db[select],BACKUP_B)==0)
	{
		write(RED"\n本板已经是精华区，不能重复收集。\n\n"NOR);
		return 1;
	}

	source = load_object(BOARD_PATH+board_db[select]);

	if( !sscanf(arg, "%d", num) )
		return notify_fail("你要保存哪一张留言？\n");

	num --;

	if( num < 0 || num > sizeof(source->query("notes"))-1 )
		return notify_fail("没有这张留言。\n");

	notes = source->query("notes")[num];
	post = ([]);
	post["title"]	= notes["title"];
	post["author"]	= notes["author"];
	post["time"]	= notes["time"];
	body = notes["msg"];
	body += sprintf(
"\n附：此篇文章是由%s(%s)选自%s。",
	wiz->name(),
	wiz->query("id"),
	source->name()
	);
	
	if( objectp(transfer=find_object(BOARD_PATH+BACKUP_B)) )
	{
		transfer->done_post(wiz,post,body);
		write(BOLD"\n本文章挡案保存到"+(BOARD_PATH+BACKUP_B)->name()+"完毕。\n\n"NOR);
	}

	write("您目前选择的是："+(BOARD_PATH+board_db[select])->name()+"\n");
	return 1;
}