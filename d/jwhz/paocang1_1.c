#include "second.h"
#include "chuan.h"
#include "paocang.h"
void create()
{
	object jwhz;
	int height,wide;
	object room;
	room=load_object("/d/yashan/waneast3.c");
	if(room) room->set("exits/"+PATHNAME,file_name(this_object()));
	jwhz=load_object("/adm/daemons/jwhz.c");
	wide=jwhz->query("wide");
	height=jwhz->query("height");
	set("short","第一炮舱");
	set("id","c22");
	set("long",@LONG
这是广乙号的第一炮舱，在这里有一个了望口让你可以
看到海域上的情况，一门大炮安安静静地躺在那里，在这里
你可以用打炮给日本侵略者以坚决的还击！打炮的用法全部
都写在旁边的一个操作说明上(directions),你可以通过阅
读说明来熟悉如何使用大炮。
LONG
		);
	set("shoot_x",wide/2);
	set("shoot_y",height/2);
	set("exits",([
      "out": "/d/yashan/waneast3.c",
		"north": __DIR__"jiashishi_1.c",
		"south": __DIR__"paocang2_1.c"
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
	object room;
	room=load_object("/d/yashan/waneast3.c");
	if(room) room->set("exits/"+PATHNAME,file_name(this_object()));
	jwhz=load_object("/adm/daemons/jwhz.c");
	wide=jwhz->query("wide");
	height=jwhz->query("height");
	set("long",@LONG
这是广乙号的第一炮舱，在这里有一个了望口让你可以
看到海域上的情况，一门大炮安安静静地躺在那里，在这里
你可以用打炮给日本侵略者以坚决的还击！打炮的用法全部
都写在旁边的一个操作说明上(directions),你可以通过阅
读说明来熟悉如何使用大炮。
LONG
		);
	set("shoot_x",wide/2);
	set("shoot_y",height/2);
	set("exits",([
        "out": "/d/yashan/waneast3.c",
		"north": __DIR__"jiashishi_1.c",
		"south": __DIR__"paocang2_1.c"
		]));
	ini_create_chuan();
	ini_create();
	ini_create_special();
	return 1;
}
