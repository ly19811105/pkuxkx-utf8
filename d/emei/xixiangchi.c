// Room: /d/emei/xixiangchi.c
// modified by Zine@pkuxkx 2013/1/22 修改一些提示信息细节

inherit ROOM;
#include <ansi.h>
#include <command.h>
string look_chi();

void create()
{
        set("short",HIW "洗象池边" NOR);
        set("long", @LONG
洗象池原只是一亭，亭前有一个石砌的小池(pool)，池边不远就是危岩。
洗象池寓于一片冷杉林中，有若白云深处的仙山琼阁。若是云收雾敛、碧空万
里、月朗中天时，便觉万籁俱寂，清光无限，宛若身在天宫，彻体生凉。这正
是著名的「象池池夜」。由此向南上攀，便至雷洞坪，东下至莲花石。

小亭的桌上摆放着茶饮(tea)和鲜果(guo)。
LONG
        );
        set("outdoors", "峨嵋山");
        set("item_desc",([          
            "pool" : (: look_chi :),
			"tea" : "这里的茶饮任人取用(drink)。\n",
			"guo" : "鲜果看起来不错，让人忍不住一试(eat)。\n",
        ]));
        set("exits", ([ 
          "southup" : __DIR__"lingyunti",
          ]));

        setup();
}
void move_to(object ob);
void init()
{
        add_action("do_jump", "xi");
        add_action("do_halt", "halt");
		add_action("drinktea","drink");
		add_action("eatguo","eat");
}
int drinktea()
{
	int current_water;
	int max_water;
	object me;
	me = this_player();
	current_water = me->query("water");
	max_water = (int)me->max_water_capacity();
	if (current_water<max_water-50) 
	{
		me->add("water", 50);
		message_vision("$N端起桌上的茶盏，润了润口。\n",me);
	}
	else write("你现在并不是太渴。\n");
	return 1;
}
int eatguo()
{
	int current_food;
	int max_food;
	object me;
	string* food=({HIM"蟠桃"NOR,RED"李子"NOR,HIY"梨子"NOR,HIY"香蕉"NOR,HIY"芒果"NOR,HIG"西瓜"NOR,HIR"苹果"NOR,HIY"桔子"NOR});
	me = this_player();
	current_food = me->query("food");
	max_food = (int)me->max_food_capacity();
	if (current_food<max_food-50) 
	{
		me->add("food", 50);
		message_vision("$N捡起桌上的一只"+food[random(sizeof(food))]+"，浅浅尝了几口。\n",me);
	}
	else write("你现在并不是太饿。\n");
	return 1;
}
int do_halt(string arg)
{
        object me = this_player();

        if (!me->is_busy() && !me->is_fighting())
                me->add_busy(2);
        return 0;
}

int do_jump(string arg)
{       
        int i, j;
        object me, room, *ob, *inv2;
        me = this_player();
        if ( me->query("gender") == "男性" ) {
            tell_object(me, "你一个大老爷们做那些事情干什么？\n");
            return 1;
        }
        if(!living(me) ) return 0;
        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着哪！\n");

        if( !arg || arg == "" || arg != "pool" )
                return notify_fail("你要干什么？\n");

	inv2=all_inventory(me);
        for (j=0;j<sizeof(inv2);j++)
        {
            if (userp(inv2[j]))
            {
                return notify_fail("背人洗澡？不怕都淹死么？\n");
            }
        }
                
        
/*
        if((me->query_encumbrance()*20) > me->query_max_encumbrance())
                return notify_fail("你身上的东西太多了！\n");
*/
     
        if (me->query("jingli")<50)
                return notify_fail("你现在精力不济，洗澡会晕的。\n");
		me->add_busy(1);
		if (!(room = find_object(__DIR__"chi")))
              room = load_object(__DIR__"chi");
        ob = all_inventory(room);
        j = sizeof(ob);
        //inv = all_inventory(me);
/*换一种存放的方法 by whuan
        for (i = 0; i < sizeof(inv); i++){
               if(!inv[i]->query("no_drop"))
                       DROP_CMD->do_drop(me, inv[i]);
               else if(inv[i]->query("equipped"))
                       inv[i]->unequip();
               else
                       tell_object(me, "你将"+inv[i]->name()+"用衣物仔细包好。\n");         
        }
*/      move_to(me);
        //call_out("move_to",0,me);
        tell_object(me, GRN "你走到池边，除去衣物，便要跳进洗象池。\n"NOR);
        tell_room(environment(me), me->name()+"转身走到池边，好象是要跳进池里游水去。\n", ({ me }));
		if(j>0)
		{
			if(j>4) 
			{
				write(HIR"你突然发现池水中有好几个人影，连忙退了回来。\n"NOR);
				call_out("get_ob",1,me);
				return 1;
			}
			tell_object(me, "你突然发现池水中有人！\n");
			for(i=0; i<sizeof(ob); i++) 
			{
				if(!living(ob[i])) continue;
				if(me->query("gender") == ob[i]->query("gender"))
				{
					if(me->query("gender") == "女性")
					tell_object(me, "定眼一看，原来也是个女子。你轻轻一笑，纵身跳下水去。\n");
					if(me->query("gender") != "女性")
					tell_object(me, "定眼一看，对方不是女子。你深深叹了口气，纵身跳下水去。\n");
					me->move(room);
					room->notice(me);
				} 
				else 
				{
					tell_object(me, "定眼一看，原来对方是位。。。。你脸上一红，连忙穿上衣服退了回来。\n");
					tell_room(environment(me), me->name()+"转身走到池边，顿了一顿，又退了回来。\n", ({ me })); 
					call_out("get_ob",1,me);
				}
				return 1;
			}
			return 1; 
        } 
        me->move(room);
		room->notice(me);//用notice()，代替原来的init()触发，否则触发n次。Zine
        return 1;
}

void kan_pool(object me, object room)
{
        int i, j;
        object *ob;

        if (!me || !room)
                return;
        ob = all_inventory(room);
        j = sizeof(ob);
        if (j>0){
                if (me->query("gender") == "女性")
                        return;
                tell_object(me, HIY "结果发现池中有人在裸身游水！你远远看着那模糊的雪白背影，不禁呆了。。。\n"NOR);
                if (!wizardp(me))
                        tell_room(environment(me), HIY +me->name()+"突然两眼发直，张大了口，口水滴嗒滴嗒直往外流。\n"NOR, ({ me }));
                for(i=0; i<sizeof(ob); i++) {
                        if(!living(ob[i])) continue;
                        tell_object(ob[i], HIR"\n你不经意一回头，发现有人鬼鬼祟祟在池边偷看！\n"NOR);
                        ob[i]->set_temp("looked", 1);
                        if(ob[i]->query("gender") == "女性"){
                               tell_object(ob[i], HIR"你血气上冲，顿时感到一阵旋晕！\n"NOR);           
                               if(ob[i]->query("jing")>=100)
                                       ob[i]->add("jing",-100);
                               else
                                       ob[i]->unconcious();
                               ob[i]->set_temp("apply/short", ({ob[i]->name()+"("+ob[i]->query("id")+")"HIR" <全裸> "NOR}));       
                        }else{
                               tell_object(ob[i], "\n你虽不以为意，但已经没有兴趣再继续游水了。\n");
                               ob[i]->force_me("halt");     
                        }
               }
               return;
        }
        return;
}

string look_chi()
{
        object me, room;
        me = this_player();
        if (!(room = find_object(__DIR__"chi")))
                room = load_object(__DIR__"chi");

        if (me->is_busy())
                return "你正忙着呢。\n";
        if (!wizardp(me)) {
                message_vision("$N悄悄转到池边，伸长脖子往池里望去。\n", me);
                me->start_busy(30);
        }
        "/cmds/std/look.c"->look_room(this_player(), room);
        remove_call_out("kan_pool");
        call_out("kan_pool", 1, me, room); 
        return "";
}

int valid_leave(object me, string dir)
{
        if (dir == "southup" && (int)me->query_skill("dodge", 1) < 101 ) {
                me->improve_skill("dodge", (int)me->query("dex"));
                me->receive_damage("qi", (int)me->query("dex"));
                return 1; 
        }     
        return ::valid_leave(me, dir);
} 
void move_to(object ob)
{
        int i;
        object *inv;
        object temproom;
        if (!objectp(ob))
        return;
        inv = all_inventory(ob);
        temproom = new(VOID_OB);
        temproom->set("no_clean_up",1);
        temproom->set("no_reset",1);
        ob->set_temp("bath/temproom",temproom);
        for(i=0; i<sizeof(inv); i++) 
        inv[i]->move(temproom);
        tell_object(ob, "你将身上诸多物品用衣物仔细包好。\n");
        return;
}
void get_ob(object me)
{
        object *inv;            	     
        object temproom;
        int i;
        if (me&&me->query_temp("bath/temproom")&&objectp(temproom = me->query_temp("bath/temproom")))
        {
            inv = all_inventory(temproom);
            for(i=0; i<sizeof(inv); i++) 
            {
            inv[i]->move(me);
            }
            tell_object(me,"你把衣服打开，把东西拿了出来。\n");
            "/cmds/std/wear"->main(me,"all");
            destruct(temproom);
            me->delete_temp("bath/temproom");
        }
        return;
}                  
