inherit ROOM;
void create()
{
  set("short","药房");
  set("long",
      "这里是间药房，靠墙放着一只大药柜。屋子里有张桌子，上边摆\n"
  "满了炼药用的瓶瓶罐罐。其中一个药瓶(bottle)里只装了清水。炼药\n"
  "师是位小姑娘，正在那里发呆，不知在想什么。北面是气派的长廊。\n"
     );
  set("exits",([
      "north" : __DIR__"changlang",
     ]));
  set("item_desc",([
      "bottle" : "药罐上贴着标签：『蛇胆膏』，乃珍贵补品，生精补气，效果奇佳。\n"
            +"但是药罐已经空了！\n",
      ]));
  set("objects",([
// __DIR__"obj/wan" :1,
    __DIR__"npc/xiaoqing" : 1,
    ]));
 setup();
 replace_program(ROOM);
}
