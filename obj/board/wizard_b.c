#pragma save_binary
// wizard_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("巫师留言板", ({ "board" }) );
	set("location", "/d/wiz/hall1");
	set("board_id", "wizard_b");
	set("long",
		"这是一个供人留言记事的留言板。\n" );
	setup();
	set("capacity", 50);
	replace_program(BULLETIN_BOARD);
}
