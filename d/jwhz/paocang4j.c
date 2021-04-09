#include "firstj.h"
#include "chuan.h"
#include "paocang.h"
void create()
{
	object jwhz;
	int height,wide;
	jwhz=load_object("/adm/daemons/jwhz.c");
	wide=jwhz->query("wide");
	height=jwhz->query("height");
	set("short","第四炮舱");
	set("id","j15");
	set("long",@LONG
这是浪速号的第四炮舱，有一门大炮躺在这里．
LONG
		);
	set("shoot_x",-wide/2);
	set("shoot_y",-height/2);
	set("exits",([
		"north": __DIR__"paocang3j.c",
		"south": __DIR__"paocang5j.c",
		]));
	set("outdoors","jwhz");
	ini_create_chuan();
	ini_create();
	ini_create_special();
	setup();
}
int renew()
{
	object jwhz;
	int height,wide;
	jwhz=load_object("/adm/daemons/jwhz.c");
	wide=jwhz->query("wide");
	height=jwhz->query("height");
	set("long",@LONG
这是浪速号的第四炮舱，有一门大炮躺在这里．
LONG
		);
	set("shoot_x",-wide/2);
	set("shoot_y",-height/2);
	ini_create_chuan();
	ini_create();
	ini_create_special();
	return 1;
}
