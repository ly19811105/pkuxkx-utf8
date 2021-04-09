#include "first.h"
#include "chuan.h"
#include "paocang.h"
void create()
{
	object jwhz;
	int height,wide;
	jwhz=load_object("/adm/daemons/jwhz.c");
	wide=jwhz->query("wide");
	height=jwhz->query("height");
	set("short","第三炮舱");
	set("id","c14");
	set("long",@LONG
这是济远号的第三炮舱，在这里有一个了望口让你可以
看到海域上的情况，一门大炮安安静静地躺在那里，在这里
你可以用打炮给日本侵略者以坚决的还击！打炮的用法全部
都写在旁边的一个操作说明上(directions),你可以通过阅
读说明来熟悉如何使用大炮。
LONG
		);
	set("shoot_x",wide/2);
	set("shoot_y",height/2);
	set("exits",([
		"north": __DIR__"paocang2.c",
		"south": __DIR__"paocang4.c",
		]));
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
这是济远号的第三炮舱，在这里有一个了望口让你可以
看到海域上的情况，一门大炮安安静静地躺在那里，在这里
你可以用打炮给日本侵略者以坚决的还击！打炮的用法全部
都写在旁边的一个操作说明上(directions),你可以通过阅
读说明来熟悉如何使用大炮。
LONG
		);
	set("shoot_x",wide/2);
	set("shoot_y",height/2);
	ini_create_chuan();
	ini_create();
	ini_create_special();
	return 1;
}
