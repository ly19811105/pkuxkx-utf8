//created by Pal
//cometh@tom.com
//2003.10.9
//自建山庄入口
#pragma save_binary

#include <ansi.h>
inherit ROOM;
int save();
int restore();
void create()
{
	set("short", "自建山庄入口");//描述需要修改
	set("long", @LONG
自建山庄入口
LONG
	);
	set("valid_startroom",0);
	set("exits", ([
//房间出口
		]));
	set("item_desc", ([
                "sign" : "一块牌子\n",
				"list" : "这里是已经创建了山庄的玩家名单：\n",
		]));
	set("objects", ([
//房间有的物品
		"/adm/npc/pal":1,
		]));
	restore();
	setup();
}

string query_save_file()
{
	return "/data/home/save/entrance";
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

void init()
{
	add_action("do_enter","enter");
}

int do_enter(string arg)
{
	object me,room;
	string filename;

	me = this_player();
	if( !arg )
		return notify_fail("你要到哪儿去？\n");
	filename="/data/home/file/"+arg[0..0]+"/"+arg+"/"+"gate.c";//固定入口文件名
	if(file_size(filename) < 1 )
		return notify_fail("他/她还没有创建自己的山庄呢。\n");
	if(!( room = find_object(filename)) )
		room = load_object(filename);
	tell_object(me,"你信步来到"+arg+"的山庄。\n");
	me->move(room);
	return 1;
}