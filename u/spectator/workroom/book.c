// feihuwaizhuan.c
// created by spectator Jal.2003

#include ansi.h
inherit ITEM;

void create()
{
    set_name(MAG "飞狐外传" NOR, ({ "feihu waizhuan", "feihu" }));
    set("long", @LONG
这是金庸先生所著小说「飞狐外传」，传说里面包藏着一部绝世武功。
由于年代久远，该书纸张已经变成黄色。
LONG );
    set_weight(200);
    set("unit", "本");
    set("value", 500);
    set("material", "paper");

    setup();
}
