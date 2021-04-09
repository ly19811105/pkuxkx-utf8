// Room: /d/shaolin/hsyuan6.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
	set("short", "和尚院六部");
	set("long", @LONG
这里是僧众们饮食起居的地方。靠墙一溜摆着几张木床，床
上铺的是篾席。床头叠着床薄被，冬天想必很冷，僧侣们全靠扎
实的内功根基御寒。地上整齐的放着几个蒲团和木鱼。
LONG
	);
	set("sleep_room",1);

	set("exits", ([
		"west" : __DIR__"zhulin6",
		"south" : __DIR__"hsyuan5",
	]));
  	set("least_msg",1);

	set("objects",([
		CLASS_D("shaolin") + "/hui-jie" : 1,
                CLASS_D("shaolin") + "/xu-dai" : 1,
	]));
	setup();
	replace_program(ROOM);
}



