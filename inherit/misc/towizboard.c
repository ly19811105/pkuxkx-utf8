// towizboard.c

#include <ansi.h>

#define BOARD_CAPACITY query("capacity")

inherit ITEM;
inherit F_SAVE;

void setup()
{
    string loc;

    if( stringp(loc = query("location")) )
    move(loc);
    set("no_get", 1);
    restore();
}

void init()
{
    add_action("do_post", "post");
    add_action("do_read", "read");
    add_action("do_discard", "discard");
}

string query_save_file()
{
    string id;

    if( !stringp(id = query("board_id")) ) return 0;
    return DATA_DIR + "board/" + id;
}

string short()
{
    mapping *notes;
    int i, unread, last_read_time;

    notes = query("notes");
    if( !pointerp(notes) || !sizeof(notes) )
        return ::short() + " [ 没有任何留言 ]";

    if( this_player() ) {
        last_read_time = (int)this_player()->query("board_last_read/" + (string)query("board_id"));
        for(unread = 0, i=sizeof(notes)-1; i>=0; i--, unread ++)
            if( notes[i]["time"] <= last_read_time ) break;
    }
    if( unread )
        return sprintf("%s [ %d 张留言，%d 张未读 ]", ::short(), sizeof(notes), unread);
    else
        return sprintf("%s [ %d 张留言 ]", ::short(), sizeof(notes));
}

string long()
{
    mapping *notes;
    int i, last_time_read;
    string msg, myid;
    string name,status;

    notes = query("notes");
    msg = query("long");
    msg = msg + "留言版的使用方法请见 help board。\n";
    if( !pointerp(notes) || !sizeof(notes) ) return query("long");

    last_time_read = this_player()->query("board_last_read/" + (string)query("board_id"));
    for(i=sizeof(notes)-1; i>=0; i--)
	{
        name = notes[i]["authorid"];
        status = SECURITY_D->get_status(name);
             if ( notes[i]["authorid"] == (string) this_player(1)->query("id")|| status != "(player)"
      || (int)SECURITY_D->get_wiz_level(this_player(1)) > 2 )
	  {
        msg += sprintf("%s[%2d]" "  %-40s %12s (%s)\n"NOR,
          ( notes[i]["time"] > last_time_read ? HIB: ""),
         i+1, notes[i]["title"], notes[i]["author"] + "" + "" + "", ctime(notes[i]["time"])[0..15] );
	  }
	  else
		{
                   msg += sprintf("%s[%2d]" "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX %12s (%s)\n"NOR,
          ( notes[i]["time"] > last_time_read ? HIB: ""),
         i+1, notes[i]["author"] + "" + "" + "", ctime(notes[i]["time"])[0..15] );
	  }
	}
    this_player()->start_more(msg);
    return "";
}

// This is the callback function to process the string returned from the
// editor defined in F_EDIT of player object.

void done_post(object me, mapping note, string text)
{
    mapping *notes;

    note["msg"] = replace_color(text);
    notes = query("notes");
    if( !pointerp(notes) || !sizeof(notes) )
        notes = ({ note });
    else
        notes += ({ note });

    // Truncate the notes if maximum capacity exceeded.

    set("notes", notes);
    tell_object(me, "留言完毕。\n");

    save();
    return;
}

int do_post(string arg)
{
    mapping note;
    if(!arg) return notify_fail("留言请指定一个标题。\n");
    note = allocate_mapping(4);
    note["title"] = replace_color(arg);
    note["author"] = this_player()->name_id();
    note["authorid"] = geteuid(this_player());
    note["time"] = time();
    this_player()->edit( (: done_post, this_player(), note :) );
    return 1;
}

int do_read(string arg)
{
    int num,i;
    mapping *notes, last_read_time;
    string myid,str;
   string name,status;

    i = 0;
    last_read_time = this_player()->query("board_last_read");
    myid = query("board_id");
    notes = query("notes");

    if( !pointerp(notes) || !sizeof(notes) )
        return notify_fail("留言板上目前没有任何留言。\n");

    if( !arg ) return notify_fail("指令格式：read <留言编号>|new|next\n");
    if( arg=="new" || arg=="next" ) {
        if( !mapp(last_read_time) || undefinedp(last_read_time[myid]) )
            num = 1;
        else
            for(num = 1; num<=sizeof(notes); num++)
                if( notes[num-1]["time"] > last_read_time[myid] ) break;

    } else if( !sscanf(arg, "%d", num) )
        return notify_fail("你要读第几张留言？\n");

    if( num < 1 || num > sizeof(notes) )
        return notify_fail("没有这张留言。\n");
    num--;

	name = notes[num]["authorid"];
        status = SECURITY_D->get_status(name);
        if ( notes[num]["authorid"] == (string) this_player(1)->query("id") || status != "(player)"
      || (int)SECURITY_D->get_wiz_level(this_player(1)) > 2)
	{
		this_player()->start_more( sprintf(
        "[%d] %-40s %s(%s)\n----------------------------------------------------------------------\n",
        num + 1, notes[num]["title"], notes[num]["author"], ctime(notes[num]["time"])[0..9])
	    + notes[num]["msg"] );
	}
	else
	{
		return notify_fail("无法查看该留言。\n");
	}

    // Keep track which post we were reading last time.
    if( !mapp(last_read_time) )
        this_player()->set("board_last_read", ([ myid: notes[num]["time"] ]) );
	else 
	if( undefinedp(last_read_time[myid]) || notes[num]["time"] > last_read_time[myid] )
    last_read_time[myid] = notes[num]["time"];

	return 1;
}


int do_discard(string arg)
{
    mapping *notes;
    int num;

    if( !arg || sscanf(arg, "%d", num)!=1 )
        return notify_fail("指令格式：discard <留言编号>\n");
    notes = query("notes");
    if( !arrayp(notes) || num < 1 || num > sizeof(notes) )
        return notify_fail("没有这张留言。\n");
    num--;
    if( notes[num]["authorid"] != (string) this_player(1)->query("id")
      &&        (string)SECURITY_D->get_status(this_player(1)) != "(admin)" 
      &&      (string)SECURITY_D->get_status(this_player(1)) != "(arch)")
        return notify_fail("这个留言不是你写的。\n");

    notes -= ({ notes[num] });
    set("notes", notes);
    save();
    write("删除第 " + (num+1) + " 号留言....Ok。\n");
    return 1;
}
