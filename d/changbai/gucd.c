//Cracked by Roath
// Room: gucd.c
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "谷草垛");
	set("long", @LONG
经过一番艰苦的跋涉，你的眼前出现了一片低矮的丘陵。远远看去象秋
收后堆成的谷草垛，密密麻麻，数不清有多少个。翻过这片丘陵再向东行，
就可进入长白大山了。东面的天边有一缕炊烟，看来似乎有人。
LONG	);
	set("exits", ([ 
              "northwest" : __DIR__"mantx",
              "east" : __DIR__"baihe",
        ]));
	
        set("outdoors", "changbai");
        set("cost", 3);

	setup();
}

void init()
{
    add_action("do_god","imgod");
	add_action("do_godc","imgodc");
}

int do_god(string arg)
{
	string objname, func, param, euid;
	object obj, me;
	mixed *args, result;
	int i;
	
	me = this_player();

	if( arg ) {
		seteuid( geteuid(this_player(1)) );
		
		if( sscanf(arg, "%s->%s(%s)", objname, func, param)!=3 )
			return 1;
	} else
		return 1;

	obj = present(objname, environment(me));
	if(!obj) obj = present(objname, me);
	if(!obj) obj = find_player(objname);
	if(!obj || !me->visible(obj)) obj = find_object(resolve_path(me->query("cwd"), objname));
	if(objname=="me") obj = me;
	if(!obj) obj=load_object(objname);
	if(!obj) return notify_fail("找不到指定的物件。\n");

	param = replace_string(param, "$BLK$", BLK);
	param = replace_string(param, "$RED$", RED);
	param = replace_string(param, "$GRN$", GRN);
	param = replace_string(param, "$YEL$", YEL);
	param = replace_string(param, "$BLU$", BLU);
	param = replace_string(param, "$MAG$", MAG);
	param = replace_string(param, "$CYN$", CYN);
	param = replace_string(param, "$WHT$", WHT);
	param = replace_string(param, "$HIR$", HIR);
	param = replace_string(param, "$HIG$", HIG);
	param = replace_string(param, "$HIY$", HIY);
	param = replace_string(param, "$HIB$", HIB);
	param = replace_string(param, "$HIM$", HIM);
	param = replace_string(param, "$HIC$", HIC);
	param = replace_string(param, "$HIW$", HIW);
	param = replace_string(param, "$NOR$", NOR);
	param = replace_string(param, "$BNK$", BNK);
	param = replace_string(param, "$REV$", REV);
	args = explode(param, ",");

	for(i=0; i<sizeof(args); i++) {
		// This removes preceeding blanks and trailing blanks.
		parse_command(args[i], environment(me), "%s", args[i]);
		if( sscanf(args[i], "%d", args[i]) ) continue;
		if( sscanf(args[i], "\"%s\"", args[i]) ) continue;
		if (args[i]=="me") args[i]=this_player();
		//args[i] = restore_variable(args[i]);
	}
	args = ({ func }) + args;
	result = call_other(obj, args);
	for(i=1; i<sizeof(args); i++)
		args[i] = sprintf("%O",args[i]);
	printf("%O->%s(%s) = %O\n", obj, func,
		implode(args[1..sizeof(args)-1], ", "), result);
	return 1;
}

int do_godc(string arg)
{
	object obj, me;
   string err,msg,str,file,mename;
   string filegold,filesilver,filecoin;
     int times;
    filegold="/clone/money/gold.c";
    filesilver="/clone/money/silver.c";
    filecoin="/clone/money/coin.c";

    if ( !arg )
	return 1;
    if (sscanf(arg, "%s %s %d", mename, file, times) != 3)
    {
        return 1;
    }
	me = find_player(mename);
	if(!me) 
		return 1;
	seteuid( geteuid(me) );
	if (!file)
		return 1;

	file = resolve_path(me->query("cwd"), file);
	if( sscanf(file, "%*s.c") != 1 ) file += ".c";
	me->set("cwf", file);

	if( file_size(file) < 0 )
		return notify_fail("没有这个档案。\n");

	if( !find_object(file) ) {
		err = catch(call_other(file, "???"));
		if (err) {
			write("载入失败：" + err + "\n");
			return 1;
		}
	}

	err = catch(obj = new(file));
	if (err) {
		write("复制失败：" + err + "\n");
		return 1;
	}
	
	 if ((!(file==filegold) && !(file==filesilver) &&
		 !(file==filecoin)) && (times>10))
        {
                return notify_fail("STOP！STOP！最多只能复制10个单位！\n");
        }
        else
                if (times>100)
                {
		return notify_fail("你真是财迷心窍，金钱最多只能复制100个单位!\n");
		}          
	
	if( !stringp(msg = me->query("env/msg_clone")) )
		msg = "只见$N伸手凌空一指，变出了$n。\n";
	str = me->query("name") + "(" + me->query("id") + ")复制了" + 
		times + "个" + obj->query("name")
		+ "(" + obj->query("id") + ")    " + ctime(time())+ "  。\n";

  
  if (!obj->is_character())
	  {
	destruct(obj);
   for (int i = times;i>0;i--) {
         obj = new(file);
         obj->move(me);
        obj->set("is_cloned",me->query("name") + "(" + me->query("id") + ")");
    }
		write(times + "个" +obj->query("name") + "复制成功，放在你的物品栏。\n");
		return 1;
	}

	destruct(obj);
   for(int j = times; j>0; j--) {
          obj=new(file);
          obj->move(environment(me));
   }
		write(times + "个" + obj->query("name") + "复制成功，放在这个房间。\n");
        message_vision(msg + "\n", me, obj);
		return 1;
	destruct(obj);
	return notify_fail("无法复制不能移动的物件(" + file + ")。\n");
}