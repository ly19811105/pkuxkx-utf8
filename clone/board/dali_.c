// /clone/board/wiz_b.c
#include <ansi.h>
inherit BULLETIN_BOARD;

void create()
{
        set_name("大理段家留言簿", ({ "board" }) );
        set("location", "/d/dalicheng/wangfu1.c");
	set("board_id", "all_b");
        set("long", "这是一个专供大理玩家使用的留言板。\n" );
	setup();
set("capacity", 50);
	replace_program(BULLETIN_BOARD);
}

