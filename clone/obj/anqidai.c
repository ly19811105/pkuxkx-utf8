
#include <ansi.h>
inherit F_SAVE;
inherit ITEM;

int down_price();
void create()
{
  string* color = ({ HIR, RED, HIY, YEL, HIB, BLU, HIG, HIC, CYN, MAG, HIM, HIW, WHT });
  set_name( color[random(sizeof(color))] + "麂皮暗器袋" + NOR, ({ "anqi dai", "anqidai", "dai", "anqi package", "package" }));
  set_weight(1);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("long", "一个用上好麂皮制成的暗器袋，有了它可以随身携带很多暗器。\n你可以查看(view)袋中的暗器，也可以把暗器收入(takein)袋中或从袋中拿出(pull)。\n");
    set("material", "cloth");
    set("unit", "个");
    set("value", 1);
    set("no_get", "这个袋子拿不起来。\n");
    set("no_drop", "这个袋子不能扔。\n");
    set("no_give", "这个袋子不能给别人。\n");
    set("no_steal", "这个袋子不能偷。\n");
    set("no_store",1);
    set("no_pawn", 1);
	set("max_pack", 800);
    set("anqi_package", "throwing");
  }
  setup();
  call_out("down_price", 1);
}

int move(mixed dest, int silently)
{
	object me, box=this_object();
	if( objectp(dest) ) 
	{
		me = dest;
		if (userp(me)) box->check_weight(me, box);
	}
	return ::move(dest, silently);
}

int down_price()
{
  set("value", 0);
}

void init()
{
  add_action("do_takein", "takein");
  add_action("do_lookin", "view");
  add_action("do_takeout", "pull");
}

void check_weight(object carrier, object anqibox)
{	
	object ob;
	int weight, w, i;
	mapping box;
	string *slot;
	weight=0;
	if (!mapp(box = carrier->query("anqi_package_number")))
      return ;
	slot = keys(box);
	for (i = 0; i < sizeof(slot); i++) {
		ob = new(carrier->query("anqi_package_slot/"+ slot[i]));
		w = (int)ob->query("base_weight");
		w *= (int)carrier->query("anqi_package_number/" + slot[i]);
		weight += w;
		ob->move("/obj/void");
		destruct(ob);
	}
	anqibox->set_weight(1+weight);
}

int do_lookin(string arg)
{
  object me;
  mapping box, num, obj;
  string msg, *slot;
  int i, pc;
  me = this_player();
  if (!arg)
    return notify_fail("请用view anqidai命令来查看暗器袋。\n");
  if (arg != "dai" && arg != "anqi dai" && arg != "anqidai" && arg != "anqi package" && arg != "package")
    return notify_fail("请用view anqidai命令来查看暗器袋。\n");

  if (!me->query("anqi_package_count"))
  {
    tell_object(me, "你的暗器袋里空空荡荡，看样子能够装下"+ chinese_number( this_object()->query("max_pack") ) +"件暗器。\n");
    return 1;
  }  
  if (!mapp(box = me->query("anqi_package_number")))
  {
    tell_object(me, "你的暗器袋里空空荡荡，看样子能够装下"+ chinese_number( this_object()->query("max_pack") ) +"件暗器。\n");
    return 1;
  }

  slot = keys(box);
  msg = CYN"\n≡━━◎麂皮暗器袋◎━━━━━━━━━━━━━━━━━━━━━━━━━≡\n" NOR;
  pc = 0;
  for (i = 0; i < sizeof(slot); i++) {
	pc += me->query("anqi_package_number/" + slot[i]);
    msg += sprintf("  ★  %-19s  ★" + NOR + "  %s件\n",
	  COLOR_D->uncolor(me->query("anqi_package_name/" + slot[i]))+"("+slot[i]+")", chinese_number( me->query("anqi_package_number/" + slot[i]) )) ;
  }
  
  msg += CYN"≡━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━≡\n"NOR;
  msg += "你的暗器袋里整整齐齐地排着" + chinese_number( pc ) + "件暗器，";
  me->set("anqi_package_count", pc);
  pc = this_object()->query("max_pack") - pc;
  if (pc>0)
  {
	msg += "剩余空间估计还能装下"+ chinese_number( pc ) +"件。"NOR;
  }
  else 
  {
	msg += "装得满满当当的。"NOR;
  }
  me->start_more(msg);  
  return 1;
}

int do_takein(string arg)
{
  object  me, ob, box;
  int amount, count, p_count, obpack, weight;
  string files, slot;
  mapping num, ob_dbase;
  string *list;
  me = this_player();
  box = this_object();
 
  if (!arg) return notify_fail("你要把什么东西收入暗器袋？\n");
  if (!objectp(ob = present(arg, me)))
  {
    tell_object(me, "你要把什么东西收入暗器袋？\n");
    return 1;
  }
  if (ob->query("skill_type")!="throwing")
  {
    tell_object(me, "只有暗器才能收入暗器袋。\n");
    return 1;
  }
  amount=ob->query_amount();
  count=me->query("anqi_package_count");
  obpack= this_object()->query("max_pack");
  if (obpack<100) obpack=100;
  if (count >= obpack)
  {
    tell_object(me, "你的暗器袋已经装满了，放不下更多暗器。\n");
    return 1;
  }
  if ((amount+count)> obpack)
  {
    p_count= obpack-count;
    amount=amount-p_count;
	weight= (int)ob->query("base_weight") * p_count;
  }
  else 
  {
    p_count=amount;
    amount=0;
	weight=ob->query_weight();
  }

  slot = ob->query("id"); 
  files = base_name(ob) + ".c";
  me->set("anqi_package_slot/" + slot, files);
  me->set("anqi_package_name/" + slot, ob->query("name"));
  me->add("anqi_package_number/" + slot, p_count);
  me->add("anqi_package_count", p_count);
  if (amount>0)
  {
    message_vision("$N将手中的部分" + ob->query("name") + "收入暗器袋。\n", me);
    ob->set_amount(amount);
  }
  else
  {
    message_vision("$N将手中的" + ob->query("name") + "收入暗器袋。\n", me);
    ob->move("/obj/void");
    destruct(ob);
  }
  box->set_weight( box->query_weight() + weight );
  return 1;
}

int do_takeout(string arg)
{
	object tho, aqn=this_object();
	object me=this_player();
	mapping box;
	int weight, n;
	string anqi, *slot;
	if (!arg) return notify_fail("你要把什么东西从暗器袋里拿出来？\n");
	if (sscanf(arg, "%d %s", n, anqi)!= 2)
	{
		anqi = arg;
		n = 1;
	}
	if (!mapp(me->query("anqi_package_number")))
      return notify_fail("你的暗器袋里空空的，啥也没有。\n");
	if (!me->query("anqi_package_number/"+ anqi ))
      return notify_fail("你的暗器袋里没有这样暗器。\n");
	if (n>(int)me->query("anqi_package_number/"+ anqi))
      return notify_fail("你的暗器袋里没有那么多"+me->query("anqi_package_name/" + anqi)+"。\n");
  
	me->add("anqi_package_number/"+ anqi, -n);
	tho=new(me->query("anqi_package_slot/"+ anqi));
	tho->set_amount(n);
	tho->move(me);
	weight = aqn->weight() - n*(int)tho->query("base_weight");
	if (weight<1) weight=1;
	aqn->set_weight(weight);
	me->add("anqi_package_count",-n);
	if (me->query("anqi_package_count") <= 0)
	me->delete("anqi_package_count");
	if (!me->query("anqi_package_number/" + anqi))
	{
		me->delete("anqi_package_number/" + anqi);
		me->delete("anqi_package_slot/" + anqi);
		me->delete("anqi_package_name/" + anqi);
	}
	tell_object(me, HIC "\n你探手往" + aqn->query("name") + HIC + "中轻轻一摸，取出了"+ chinese_number(n) + tho->query("base_unit") + tho->name() + HIC + "。\n" NOR);
	message("vision", HIC "\n只见" + me->name() + HIC + "伸手在" + aqn->query("name") + HIC + "中一摸，把一些东西捏在了手中。\n" NOR, environment(me), ({ me }));
	return 1;
  
}
