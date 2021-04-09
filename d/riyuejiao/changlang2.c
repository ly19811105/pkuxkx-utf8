//changlang2.c	长廊
//by bing
#include <room.h>
inherit ROOM;
#define CANGKU "/d/riyuejiao/obj/cangku.c"
void enter_ry();
void out_ry();

void create()
{
	set("short","长廊");
	set("long",@LONG 
这里是一道长廊，两边雕梁画栋，美不胜收。似是到了帝王之居，而不是
一个江湖帮会的所在。长廊之上非常寂静，似乎没人敢高声说话，更显庄严肃
穆。长廊尽头是一道大铁门。
LONG
	);
	set("exits", ([
                "south" : "/d/riyuejiao/changlang1",
                "enter" : "/d/riyuejiao/dadian1",
	]));
        set("objects", ([
                __DIR__"npc/shizhe": 4,
        ]));

	set("outdoors", "riyuejiao");
	setup();
}

void init()
{
//        add_action("do_enter","enter");
}

void enter_ry()
{
	object me = this_player();
	object* inv;
        object *old_basket,*basket;
        object cangku;
	int i;
        inv = deep_inventory(me);
	
        basket = allocate(sizeof(inv));
        cangku = find_object(CANGKU);
         if (! objectp(cangku)) {
                  cangku = load_object(CANGKU);
                  if (!objectp(cangku)) {
                                message_vision("$N请告诉 wiz: cangku not found\n", me);
                                return;
                  }
         }
        if ( me->query("save_ren") || me->query("family/master_id") == "ren woxing")
        {
                return;
        }
        for(i=sizeof(inv)-1; i>=0; i--)
            if(inv[i]->query("weapon_prop"))
            {
                basket[i] = inv[i];
                inv[i]->move(cangku);
                message_vision("$N将一" + inv[i]->query("unit")+ 
inv[i]->query("name")+"交给紫衣使者.\n", me);
	}
         old_basket = cangku->query("basket/" + me->query("id"));
         if (arrayp(old_basket)) basket = basket + old_basket;
         cangku->set("basket/" + me->query("id"), basket);
         return;
}

void out_ry()
{
         object player = this_player();
         object *inv, cangku, *basket;
         int i;
         string id;

  cangku = find_object(CANGKU);
  if (! objectp(cangku)) {
         cangku = load_object(CANGKU);
         if (!objectp(cangku)) {
                message_vision("$N请告诉 wiz: cangku not found\n", player);
                return;
         }
  }

  basket = cangku->query("basket/"+player->query("id"));

  if (basket) {
         for (i=0; i<sizeof(basket); i++) {
                if (objectp(basket[i])&&basket[i]->query("weapon_prop")) {
                  basket[i]->move(player);
                  message_vision("$N从紫衫使者手里拿回一"+
                                         basket[i]->query("unit")+
                                         basket[i]->query("name")+"。\n", player);
                }
         }
         cangku->delete("basket/"+player->query("id"));
  }
  else message_vision("紫衫使者说：$N什么也没存在我这里，小子你想找K阿。\n", player);
  return;
}

int valid_leave(object player, string dir) {
    object *inv;
    int i;
    inv = all_inventory(player);
    if (player->query("family/family_name")!="日月神教" && dir == "south")
    	return ::valid_leave(player, dir);
    if (player->query("family/family_name")!="日月神教" && dir == "enter")
    	return notify_fail("日月教可不好惹，惹怒了教主有你好看，你还是赶紧走吧。\n");  
        if ( dir == "enter" )
       {
                 //enter_ry();autoload武器有bug，可以无限复制，暂时删掉收武器。by becool
        if ( player->query("save_ren") || player->query("family/master_id") == "ren woxing")
        {
         player->delete("sjsz/entrance");
                player->move("/d/riyuejiao/dadian2");
             return notify_fail("怀着激动的心情，你看到了任我行\n");
        }
  }
         else if ( dir == "south" )
         {
          for (i=0; i<sizeof(inv); i++) {
                  if (inv[i]->is_character())
                  return notify_fail("你不能带着其他玩家离开。\n");
          }
                 //out_ry(); autoload武器有bug，可以无限复制，暂时删掉收武器。by becool
         }

         player->delete("sjsz/entrance");
         return ::valid_leave(player, dir);
}
