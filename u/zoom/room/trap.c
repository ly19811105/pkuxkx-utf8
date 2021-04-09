// Room: /u/zoom/trap.c
// by zoom
// 2003.4.6
#include <ansi.h>
inherit ROOM;
#define CANGKU "/u/zoom/cangku.c"

void create()
{
	set("short", HIR"智力陷阱"NOR);
	set("long", @LONG
这里是是智力陷阱，外面的人想进来，里面的人想出去，真是个奇怪的地方。
这里陈设相当简单，刚粉刷过的四周墙壁上光秃秃的什么都没有，屋子的正中央
放着一张楠木桌，俨然和巫师休息室差不多...
墙上一块醒目的牌子上写着：建设中...
你看了看牌子，不禁觉得好笑，忽然又想起应该考虑怎么出去了。
LONG
	);
	set("exits", ([
	
	]));
	setup();
}
void init()
{
	add_action("do_goto","goto");
	add_action("do_goto","home");
	add_action("do_none","ls");
	add_action("do_none","more");
	add_action("do_none","cat");
	add_action("do_none","call");
	add_action("do_none","cd");
	add_action("do_none","edit");
	add_action("do_none","pwd");
	add_action("do_none","dest");
	add_action("do_none","clone");
	this_player()->start_busy(10);
        call_out("kickout",120,this_player());
        call_out("enter_trap",1);
}
int do_none()
{
	message_vision("很可惜，你现在什么都做不了，还是想想其他办法吧。\n",this_player());
return 1;
}
int do_goto()
{
	object me = this_player();
	if(me->query("id")!="zoom")
	{
		message_vision("哼哼，这里是你想进来就进来想出去就出去的地方么？\n",me);
                return notify_fail("哈哈，这里岂是这么容易出去的，你就老老实实呆在这里吧:(\n");
	}
	else
	{
		remove_call_out("kickout");
		message_vision("恩，你可以走了。\n",me);
		me->set_temp("zoom/trap",1);
		me->start_busy(0);
		me->move("/u/zoom/wizard_room_zoom");
        	call_out("out_trap",1);		
	}
return 1;		
}
void kickout(object me)
{
	string where;
	if(me->query_temp("zoom/trap"))
		return;
	if(!wizardp(me))
		where = "/d/city/wumiao";
	else 
		where = "/d/wizard/wizard_room";
	message_vision("恍然间，不知从哪里伸出一只大脚，把$N一脚踹了出去！\n",me);
	me->move(where);
	message_vision("$N从天而落，摔到地上，晕了过去！\n",me);
	if(me->query("id")!="zoom")
	{
		me->start_busy(0);
	}
	else
	{

		me->start_busy(30);	
		me->unconcious();
	}
	return;
}

void enter_trap()
{
         object me = this_player();
         object *inv;
         object *old_basket, *basket;
         object cangku;
         int i;

         inv = all_inventory(me);
         basket = allocate(sizeof(inv));
         cangku = find_object(CANGKU);
         if (! objectp(cangku)) {
                  cangku = load_object(CANGKU);
                  if (!objectp(cangku)) {
                                message_vision("$N请告诉 wiz: cangku not found\n", me);
                                return;
                  }
         }

         for (i=0; i<sizeof(inv); i++) {
                                basket[i] = inv[i];
                                inv[i]->move(cangku);
                                message_vision("$N将一" + inv[i]->query("unit")+ inv[i]->query("name")+"交给小厮。\n", me);
         }

         old_basket = cangku->query("basket/" + me->query("id"));
         if (arrayp(old_basket)) basket = basket + old_basket;
         cangku->set("basket/" + me->query("id"), basket);
         return;
}
void out_trap() {
         object player = this_player();
         object *inv, cangku, *basket;
         int i;
         string id;

  cangku = find_object(CANGKU);
  if (! objectp(cangku)) {
         cangku = load_object(CANGKU);
         if (!objectp(cangku)) {
                message_vision("$N请告诉 wiz: cangku not found\n", player);
                return 0;
         }
  }

  basket = cangku->query("basket/"+player->query("id"));

  if (basket) {
         for (i=0; i<sizeof(basket); i++) {
                if (objectp(basket[i])) {
                  basket[i]->move(player);
                  message_vision("$N从主持人手里拿回一"+
                                         basket[i]->query("unit")+
                                         basket[i]->query("name")+"。\n", player);
                }
         }
         cangku->delete("basket/"+player->query("id"));
  }
  else message_vision("主持人说：$N什么也没存在我这里，可别赖我贪污喔！\n", player);

  return;
}
