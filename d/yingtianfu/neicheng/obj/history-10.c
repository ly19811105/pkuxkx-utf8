#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(CYN"魏书"NOR, ({ "wei shu", "book", "history book" }) );
        set_weight(3000);
        set("unit", "套");
        set("long", "这是一套青皮的古籍。\n");
        set("ming/history",10);
        set("value", 1000);
        set("material", "paper");
               
        setup();
}

