// more work needed to use this object to make poison
inherit ITEM;
void init()
{
        add_action("do_eat", "eat");
}
void create()
{
        set_name("蛇胆", ({"she dan","dan"}));
        set("unit", "只");
        set("long", "这是一只绿莹莹的蛇胆。\n");
        set("value", 100);
        setup();
}
int do_eat(string arg)
{
        if (!id(arg))
                return notify_fail("你要吃什么？\n");
        return notify_fail("你找死啊。\n");
}
