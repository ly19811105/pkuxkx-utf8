
inherit ROOM;
void create()
{
	set("short", "帅府大厅");
	set("long", @LONG
	这里是襄阳驻军的帅府,郭靖统领襄阳守军,就在这里办理军务.
     里面的人都是来去匆匆,一脸严肃的表情,各项事物井然有序.
LONG
	);

        set("shuaifu", 1);//保卫襄阳帅府．
	set("exits", ([
//		"south" : __DIR__"shuaifu",
		"north" : __DIR__"sfgate"          
	]));

if(!(load_object("/adm/daemons/xytaskd.c"))->query("begin"))
	set("objects", ([
		__DIR__"npc/shjiang1" : 2,
                __DIR__"npc/guojing" :1,
        ]));

	setup();
}


