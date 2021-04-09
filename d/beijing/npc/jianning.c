inherit NPC;
string ask_book();
void create()
{
   set_name("建宁公主",({"jianning gongzhu", "gongzhu", "jianning"}));
   set("gender","女性");
//   set("nickname","小宫女");
   set("age",17);
   set("combat_exp", 1000);
   set("per", 15 + random(15));
   set("chat_chance",4);
	 set("inquiry", ([
	     "四十二章经" : (: ask_book :),
	]));
   setup();
   carry_object("/clone/cloth/female5-cloth.c")->wear();
}

string ask_book()
{
	object book, room;
	object me = this_player();
	int age = me->query("mud_age");

	if (me->query("class") != "officer")
	return RANK_D->query_respect(me) + "与朝廷素无来往，此话从何提起？";

	if (!me->query("book/jing"))
	{
		me->set("book/jing", me->query("mud_age") + 200 + random(150));
		return "好吧，我去看看，你过两天再来找我吧，不过不一定能拿到哦。";
	}

	if (me->query("book/jing") && (age - me->query("book/jing")) < 0)
	return "你急什么啊，再等一等吧。";

	if (!objectp(room = find_object("/d/beijing/zijin/shangshufang")));
	room = load_object("/d/beijing/zijin/shangshufang");
	if (room->query("count") > 0)
	{
		book = new("/d/beijing/npc/obj/book42_2");
		book->move(me);
		room->set("count", 0);
		me->delete("book/jing");
		return "经书就在这里了，你赏我些什么啊？嘻嘻";
	}
	else return "我在皇帝哥哥的书房里找不到书啊，你过一段时间再来吧。";
}

