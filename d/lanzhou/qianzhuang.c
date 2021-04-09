inherit __DIR__"lanzhou.c";

void create()
{
	set("short","钱庄");
	set("long", @LONG
这是一家老字号的钱庄，已有几百年的历史，在全国各地都有分店。它发行
的银票信誉非常好，通行全国。在对面的墙上挂了块牌子(paizi)。
LONG);
 
        set("item_desc", ([
                "paizi" : @TEXT
本钱庄提供以下服务：
      存钱        deposit或者cun
      取钱        withdraw或者qu
      钱币兑换    convert或者duihuan
      查帐        check或者chazhang
TEXT
        ]) );

        set("no_fight", 1);
	set("exits", ([
		"west" : __DIR__"east_lane1",
	]));

	set("objects", ([
		"/d/yueyang/npc/zhanggui":1,
	]));
	setup();
}
