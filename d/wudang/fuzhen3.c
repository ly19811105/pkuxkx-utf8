// fuzhen3.c 复真观三层
// 05/30/96 Marz

inherit ROOM;

string* books = ({
	"laozi1",
	"daodejing-i",
	"laozi2",
	"daodejing-i",
	"laozi8",
	"daodejing-i",
	"laozi13",
	"laozi1",
	"laozi16",
	"daodejing-i",
	"laozi18"
});

void create()
{
	set("short", "复真观三层");
	set("long", 
"这里是复真观三层，是武当收藏道教典籍的地方。靠墙是\n"
"一排书架，摆满了道教的典籍。中央有一个长方形的大桌子，\n"
"上面也堆满了书。一个道童正在整理书籍。\n"
	);

	set("exits", ([
		"down" : __DIR__"fuzhen2",
		"up" : __DIR__"fuzhen4"
	]));

	set("objects", ([
		CLASS_D("wudang") + "/daotong" : 1,
		__DIR__"obj/"+books[random(sizeof(books))] : 1,
		__DIR__"obj/"+books[random(sizeof(books))] : 1
	]));

	setup();
	replace_program(ROOM);
}
