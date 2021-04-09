// 18muou.c

inherit ITEM;

void create()
{
        set_name("十八木偶", ({ "18 muou", "muou" }));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("treasure",1);set("unit", "盒");
                set("long", 
"这是一个小木盒，盒中垫着棉花，并列着三排木偶，神情或喜
悦不禁，或痛哭流泪，或裂嘴大怒，或慈和可亲，无一相同。\n");
                set("value", 5000);
                set("material", "wood");
                set("skill", ([
                        "name":       "force",  // name of the skill
                        "exp_required": 0,      // minimum combat experience required
                        "jing_cost":    40,     // jing cost every time study this
                        "difficulty":   20,     // the base int to learn this skill
                        "max_skill":    99,     // the maximum level you can learn
                        "min_skill":    60      // the maximum level you can learn
                ]) );
        }
}

void init()
{
        if( this_player() == environment() )
        {
                add_action("do_nie", "nie");
        }
}

int do_nie(string arg)
{
        object me, muou;
        object where;

        if ( !arg )
        {
                return notify_fail("什么？\n");
        }

        me = this_player();

        if ( arg == "niou" || arg=="muou")
        {
                muou = new(__DIR__"18muou");
                where = environment(me);
                message_vision(
"$N轻轻一捏，刷刷刷几声，裹在泥人外面的粉饰、油彩和泥底
纷纷掉落。$N一声“啊哟”，心感可惜，却见泥粉褪落处里面
又有一层油漆的木面。索性再将泥粉剥落一些，里面依稀现出
人形，当下将泥人身上泥粉尽数剥去，露出一个裸体的木偶来。
木偶身上油着一层桐油，绘满了黑线，却无穴道位置。木偶刻
工精巧，面目栩栩如生，张嘴作大笑之状，双手捧腹，神态滑
稽之极，相貌和本来的泥人截然不同。\n", this_player());
                muou->move(file_name(where));
                destruct(this_object());
        }

        return 1;
}

