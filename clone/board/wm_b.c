inherit "/inherit/misc/wmboard.c";

void create()
{
        set_name("善缘簿", ({ "board" }) );
        set("location","/d/city/wumiao");
        set("board_id", "shanyuan bu");
        set("long", "四方宾客，广结善缘。\n" );
        setup();
        set("capacity",100);
        replace_program("/inherit/misc/wmboard.c");
}

