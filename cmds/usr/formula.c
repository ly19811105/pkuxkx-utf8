#include <ansi.h>
mapping *pres(object me)
{
	mapping *prescriptions="obj/remedy/reference.c"->prescriptions(),*myPres;
	if (arrayp(myPres=me->query("myPrescriptions"))&&sizeof(myPres)>0)
	for (int i=0;i<sizeof(myPres);i++)
	prescriptions+=({myPres[i]});
	if (mapp(me->query_temp("myTempPrescription")))
	prescriptions+=({me->query_temp("myTempPrescription")});
	return prescriptions;
}
int sort_pres(mapping pre1, mapping pre2)
{
	if(pre1["improve_level"]<=pre2["improve_level"] )
		return -1;
	
	else
		return 1;
}
int main(object me, string arg)
{
	mapping *pres=pres(me);
	string lu_msg,msg="\n";
	if (!arg)
	{
		pres = "obj/remedy/reference.c"->prescriptions();
		pres = sort_array(pres,"sort_pres");
		msg+=HIW+"【公共药方】\n"+NOR;
		for (int i=0;i<sizeof(pres);i++)
		{
			msg+=HBCYN+HIW+sprintf("%|20s","<"+pres[i]["name"]+">")+NOR;
			msg+=sprintf("%-12s","["+pres[i]["maker_level"]+"～"+pres[i]["improve_level"]+"]");
			if (i%2==1) msg+="\n";
		}
		msg+="\n\n";
		pres = me->query("myPrescriptions");
		if (pres)
		{
			pres = sort_array(pres,"sort_pres");
		}
		msg+=HIR+"【个人药方】\n"+NOR;
		for (int i=0;i<sizeof(pres);i++)
		{
			msg+=BCYN+HIR+sprintf("%|20s","<"+pres[i]["name"]+">")+NOR;
			msg+=sprintf("%-12s","["+pres[i]["maker_level"]+"～"+pres[i]["improve_level"]+"]");
			if (i%2==1) msg+="\n";
		}
		write(msg+"\n");
		//write(CHINESE_D->chinese_break(msg,70));
		return 1;
	}
	else
	{
		for (int i=0;i<sizeof(pres);i++)
		if (pres[i]["name"]==arg)
		{
			lu_msg=pres[i]["furnace_lv"]?chinese_number(pres[i]["furnace_lv"])+"级药炉，":"";
			write("『"+HIC+arg+NOR+"』炼制需要"+lu_msg+"炼药等级："+U+(pres[i]["maker_level"])+NOR+" 级，最大提升等级："+U+(pres[i]["improve_level"])+NOR+" 级。\n"+"『"+HIW+"配方"+NOR+"』："+"obj/remedy/reference.c"->prescription(pres[i]["raws"])+"\n");
			return 1;
		}
	}
	write("『"+arg+"』并不存在，或你并未掌握这种配方。\n");
	return 1;
}

int help(object me)
{
    write(@HELP
指令格式 : formula
用这个指令可以查询你可用的所有配方。
formula <配方名>
用这着指令查询某一配方具体信息。
HELP
);
        return 1;
}

