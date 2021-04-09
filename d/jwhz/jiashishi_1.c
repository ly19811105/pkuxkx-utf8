#include "second.h"
#include "chuan.h"
#include "jiashishi.h"
void create()
{
	object jwhz;
	int height,wide;
	jwhz=load_object("/adm/daemons/jwhz.c");
	wide=jwhz->query("wide");
	height=jwhz->query("height");
	set("short","驾驶室");
	set("id","c21");
	set("long",@LONG
这是广乙号的驾驶室，在这里你可以控制广乙号前进的
方向。你向前望去，前面是茫茫的大海，你可以眺望(view)
整个海域。具体如何操纵广乙号，你可以看旁边的操作规程
(directions)。
LONG
		);
	set("x",2);
	set("y",height-1);
	jwhz->write_position(query("y"),query("x"),FRIEND);
	set("speed",1);
	set("objects", ([
		 "/d/yashan/npc/lin.c": 1, 
		]));
	set("exits",([
		"south": __DIR__"paocang1_1.c"
		]));
	ini_create_chuan();//chuan.h
	ini_create();//jiashishi.h
	ini_create_special();//second.h
	setup();
	jwhz->update_all();
}
int renew()
{
	object jwhz;
	int height,wide;
	jwhz=load_object("/adm/daemons/jwhz.c");
	wide=jwhz->query("wide");
	height=jwhz->query("height");
	set("long",@LONG
这是广乙号的驾驶室，在这里你可以控制广乙号前进的
方向。你向前望去，前面是茫茫的大海，你可以眺望(view)
整个海域。具体如何操纵广乙号，你可以看旁边的操作规程
(directions)。
LONG
		);
	set("x",2);
	set("y",height-1);
	jwhz->write_position(query("y"),query("x"),FRIEND);
	set("speed",1);
	ini_create_chuan();//chuan.h
	ini_create();//jiashishi.h
	ini_create_special();//second.h
	return 1;
}


