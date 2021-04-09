#include "secondj.h"
#include "chuan.h"
#include "paocang.h"
void create()
{
	object jwhz;
	int height,wide;
	jwhz=load_object("/adm/daemons/jwhz.c");
	wide=jwhz->query("wide");
	height=jwhz->query("height");
	set("short","第二炮舱");
	set("id","j23");
	set("long",@LONG
这是秋津洲号的第二炮舱，有一门大炮躺在这里．
LONG
		);
	set("shoot_x",-wide/2);
	set("shoot_y",-height/2);
	set("exits",([
		"north": __DIR__"paocang1j_1.c",
		"south": __DIR__"paocang3j_1.c",
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
这是秋津洲号的第二炮舱，有一门大炮躺在这里．
LONG
		);
	set("shoot_x",-wide/2);
	set("shoot_y",-height/2);
	ini_create_chuan();
	ini_create();
	ini_create_special();
	return 1;
}