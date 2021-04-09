// youming.c    幽冥庄，幽冥任逍遥（增加内功，并提供改善先天属性的几率）  
// Modified by iszt@pkuxkx, 2007-04-03, added set_temp("linji")
// Rewrote by iszt@pkuxkx, 2007-05-18

#include <ansi.h>
#include "linjizhuang.h";

int inc(object me, int duration);

int exert(object me, string arg)
{
        string linji = "幽冥庄";

		int pflv;
		string* ljz;
		ljz = linji_zhuang_count(me);
		pflv = (int)me->query("purefamily/level");
		if (pflv>0 && me->query("purefamily/family_name") != "峨嵋派")  pflv=0;

		if (buff_full(pflv, ljz))
			return notify_fail("你已经运行了"+show_buff(ljz)+"，无法再运行"+linji+"。\n");
//        if(me->query_temp("linji"))
//                return notify_fail("你正在运行"+me->query_temp("linji")+"，无法运行"+linji+"。\n");
        if(me->is_busy())
                return notify_fail("你现在正忙着呢。\n");
        if( me->is_fighting() )
                return notify_fail("战斗中运气练功，好象只有神仙才能做到。\n");
        if( me->query("class") != "bonze" && me->query("chushi/last_family")!="峨嵋派")
                return notify_fail("你尘心未灭，无法运行临济十二庄"+linji+"。\n");
        if((int)me->query("neili") < 1000 )
                return notify_fail("你的真气不够。\n");
        if((int)me->query_skill("linji-zhuang",1) < 180)
                return notify_fail("你的临济十二庄修为太低，无法运行"+linji+"。\n");

//        me->set_temp("linji", linji);
        me->set_temp("linji_zhuang/"+linji, 1);
        me->start_busy(6);

        message_vision(HIB"\n$N盘膝坐下，双目微闭，存想丹田，脸色阴森可怖，内息流动出入幽冥......\n"NOR, me);
        call_out("inc", 5, me, 6);

        return 1;
}

int inc(object me, int duration)
{
        int inc=(int)me->query_skill("linji-zhuang",1)*(int)me->query("int")/80;

        if (duration)
        {
                write(BLU"你固守一片清明，内息上达中府，下至幽冥，丝丝缕缕，盘旋流动......\n"NOR);
                me->improve_skill("force",inc);
                me->improve_skill("linji-zhuang",inc);
                duration --;
                me->start_busy(6);
                call_out("inc", 5, me, duration);
                return 1;
        }

        message_vision(HIB"\n$N长吐一口浊气，收回内息，脸色恢复了正常。\n"NOR,me);
        me->delete_temp("linji_zhuang/幽冥庄");
        if (me->query("youming")>4)
                return 1;
        if (random(9000) && !wizardp(me))
                return 1;
        me->add("youming",1);
        switch(random(4))
        {
        case 0:
                me->add("str",1);
                me->add("xiantian/str/youming",1);
                break;
        case 1:
                me->add("int",1);
                me->add("xiantian/int/youming",1);
                break;
        case 2:
                me->add("con",1);
                me->add("xiantian/con/youming",1);
                break;
        case 3:
                me->add("dex",1);
                me->add("xiantian/dex/youming",1);
                break;
        }
        message_vision(HIR"$N突然心头一震，一股巨大的力量冲向$N的顶门，冲击过后却是心清气爽！\n", me);
        CHANNEL_D->do_channel(this_object(), "jh", HIM"听说"+me->name()+HIM"运行幽冥庄连日苦练，先天属性得到了提高！", -1);
        log_file("static/youming",sprintf(" %s(%s) 于%s,打通幽冥庄！\n",
                me->query("name"),me->query("id"),ctime(time())));   

        return 1;
}
