#define DRUGPATH "/d/taishan/obj/"
#include "alchemy.h"
#define VER 1
int query_verison()
{
	return VER;
}
int *animal_code()
{
	return ({16,20,32});
}
mapping * List()
{
	return ({
	(["id":1,"name":"鸡血藤","file_name":DRUGPATH+"jixueteng.c","gather_lv":25,]),
	(["id":2,"name":"薄荷","file_name":DRUGPATH+"bohe.c","gather_lv":0,]),
	(["id":3,"name":"鱼腥草","file_name":DRUGPATH+"yuxingcao.c","gather_lv":5,]),
	(["id":4,"name":"常山","file_name":DRUGPATH+"changshan.c","gather_lv":5,]),
	(["id":5,"name":"当归","file_name":DRUGPATH+"danggui.c","gather_lv":15,]),
	(["id":6,"name":"丁香","file_name":DRUGPATH+"dingxiang.c","gather_lv":15,]),
	(["id":7,"name":"茯苓","file_name":DRUGPATH+"fuling.c","gather_lv":25,]),
	(["id":8,"name":"覆盆子","file_name":DRUGPATH+"fupengzi.c","gather_lv":5,]),
	(["id":9,"name":"合欢","file_name":DRUGPATH+"hehuan.c","gather_lv":15,]),
	(["id":10,"name":"荆芥","file_name":DRUGPATH+"jingjie.c","gather_lv":1,]),
	(["id":11,"name":"地骨皮","file_name":DRUGPATH+"digupi.c","gather_lv":15,]),
	(["id":12,"name":"蛇床子","file_name":DRUGPATH+"shechuangzi.c","gather_lv":15,]),
	(["id":13,"name":"生甘草","file_name":DRUGPATH+"shenggancao.c","gather_lv":25,]),
	(["id":14,"name":"甘草","file_name":DRUGPATH+"gancao.c","gather_lv":35,]),
	(["id":15,"name":"枸杞","file_name":DRUGPATH+"gouqi.c","gather_lv":1,]),
	(["id":16,"name":"鹿鞭","file_name":DRUGPATH+"lubian.c","gather_lv":35,"animal_source":1]),
	(["id":17,"name":"芦荟","file_name":DRUGPATH+"luhui.c","gather_lv":5,]),
	(["id":18,"name":"枇杷叶","file_name":DRUGPATH+"pipaye.c","gather_lv":5,]),
	(["id":19,"name":"桑枝","file_name":DRUGPATH+"sangzhi.c","gather_lv":15,]),
	(["id":20,"name":"麝香","file_name":DRUGPATH+"shexiang.c","gather_lv":35,"animal_source":1]),
	(["id":21,"name":"松节","file_name":DRUGPATH+"songjie.c","gather_lv":35,]),
	(["id":22,"name":"紫苏子","file_name":DRUGPATH+"suzizi.c","gather_lv":35,]),
	(["id":23,"name":"雄黄","file_name":DRUGPATH+"xionghuang.c","gather_lv":35,]),
	(["id":24,"name":"浙贝母","file_name":DRUGPATH+"zhebeimu.c","gather_lv":25,]),
	(["id":25,"name":"血竭","file_name":DRUGPATH+"xuejie.c","gather_lv":0,]),
	(["id":26,"name":"胆南星","file_name":DRUGPATH+"dannanxing.c","gather_lv":0,]),
	(["id":27,"name":"远志","file_name":DRUGPATH+"yuanzhi.c","gather_lv":0,]),
	(["id":28,"name":"朱砂","file_name":DRUGPATH+"zhusha.c","gather_lv":0,]),
	(["id":29,"name":"党参","file_name":DRUGPATH+"dangshen.c","gather_lv":15,]),
	(["id":30,"name":"千年人参片","file_name":DRUGPATH+"renshenpian.c","gather_lv":-1,]),//gather_lv -1不能通过采药获得
	(["id":31,"name":"千年灵芝片","file_name":DRUGPATH+"lingzhipian.c","gather_lv":-1,]),
	(["id":32,"name":"毒蛇胆","file_name":"/d/guiyunzhuang/npc/obj/shedan.c","gather_lv":1,"animal_source":1]),
	(["id":33,"name":"川贝","file_name":DRUGPATH+"chuanbei.c","gather_lv":15,]),
	(["id":34,"name":"首乌","file_name":DRUGPATH+"shouwu.c","gather_lv":45,]),
	(["id":35,"name":"鹿茸","file_name":DRUGPATH+"lurong.c","gather_lv":40,"animal_source":1]),
	(["id":36,"name":"熊胆","file_name":DRUGPATH+"xiongdan.c","gather_lv":40,"animal_source":1]),
	(["id":37,"name":"灵脂","file_name":DRUGPATH+"lingzhi.c","gather_lv":50,]),
	(["id":38,"name":"三七","file_name":DRUGPATH+"sanqi.c","gather_lv":50,]),
	(["id":39,"name":"千年人参","file_name":"/d/city/npc/obj/renshen2.c","gather_lv":-1,]),
	});
}
mapping random_drug(string type,int lv)//返回随机一直药物code，type为herb或者animal，gather_lv小于lv。
{
	mapping *list=List(),*res=({});
	for (int i=0;i<sizeof(list);i++)
	{
		if (list[i]["gather_lv"]!=-1&&list[i]["gather_lv"]<=lv&&((type=="animal"&&list[i]["animal_source"])||(!list[i]["animal_source"]&&type!="animal")))
		res+=({list[i]});
	}
	if (sizeof(res)<1) return (["id":0]);
	else return res[random(sizeof(res))];
}
object ObtainDrug(mixed index)
{
	mapping *list=List();
	object obj;
	if (!intp(index)&&!stringp(index))
	return obj;
	for (int i=0;i<sizeof(list);i++)
	{
		if ((intp(index)&&list[i]["id"]==index)||(stringp(index)&&list[i]["name"]==index))
		{
			obj=new(list[i]["file_name"]);
			break;
		}
	}
	return obj;
}
string prescription(mapping raws)
{
	string pres="",*materials=keys(raws);
	int *amounts=values(raws);
	for (int i=0;i<sizeof(materials);i++)
	{
		pres+=interpret(materials[i])+"："+HIG+amounts[i]+NOR;
		if (i==sizeof(materials)-1)
		pres+="。";
		else
		pres+="，";
	}
	return pres;
}
mapping * all_prescriptions()
{
	return ({
(["name":"金创药","raws":(["*25":2,"*26":2,"*5":1]),"product":"/d/city/obj/jinchuang","product_no":3,"period":18,
"maker_level":0,"improve_level":30,"skill_points":6,"fail_possibility":40,"furnace_lv":0,"phase_color":({0,1,2}),]),
(["name":"养精丹","raws":(["*27":2,"*28":2,"*29":1]),"product":"/d/city/obj/yangjing","product_no":3,"period":18,
"maker_level":0,"improve_level":30,"skill_points":6,"fail_possibility":40,"furnace_lv":0,"phase_color":({0,2,1}),]),
(["name":"上等金创药","raws":(["*25":6,"*26":6,"*5":4,]),"product":"/d/city/obj/jinchuang_adv","product_no":2,"period":15,
"maker_level":25,"improve_level":55,"skill_points":9,"fail_possibility":45,"furnace_lv":0,"phase_color":({0,1,2}),]),
(["name":"上等养精丹","raws":(["*27":6,"*28":6,"*29":4,]),"product":"/d/city/obj/yangjing_adv","product_no":2,"period":15,
"maker_level":25,"improve_level":55,"skill_points":9,"fail_possibility":45,"furnace_lv":0,"phase_color":({0,2,1}),]),
(["name":"百草丹","raws":(["*5":2,"*12":2,"#2#mu":1]),"product":"/d/ludingshan/obj/special/dan4.c","product_no":1,"period":20,
"maker_level":35,"improve_level":65,"skill_points":30,"fail_possibility":75,"furnace_lv":2,"phase_color":({2,1,0}),]),
(["name":"雪参玉蟾丹","raws":(["*9":2,"*19":2,"*29":3]),"product":"/d/beijing/npc/obj/yuchandan.c","product_no":6,"period":18,
"maker_level":35,"improve_level":65,"skill_points":12,"fail_possibility":50,"furnace_lv":2,"phase_color":({2,1,0}),]),
(["name":"千年参王丸","raws":(["*27":2,"*30":1]),"product":"/obj/remedy/drug/shenwangwan.c","product_no":2,"period":14,
"maker_level":50,"improve_level":75,"skill_points":12,"fail_possibility":45,"furnace_lv":2,"phase_color":({1,0,2}),]),
(["name":"千年灵芝丹","raws":(["*27":2,"*31":1]),"product":"/obj/remedy/drug/lingzhidan.c","product_no":2,"period":16,
"maker_level":50,"improve_level":75,"skill_points":15,"fail_possibility":45,"furnace_lv":2,"phase_color":({1,0,2}),]),
(["name":"千年灵芝丹","raws":(["*27":2,"*31":1]),"product":"/obj/remedy/drug/lingzhidan.c","product_no":2,"period":16,
"maker_level":50,"improve_level":75,"skill_points":15,"fail_possibility":45,"furnace_lv":2,"phase_color":({1,0,2}),]),
(["name":"蛇胆川贝枇杷膏","raws":(["*32":1,"*33":1,"*18":1]),"product":"/obj/remedy/drug/shedangao.c","product_no":2,"period":18,
"maker_level":65,"improve_level":90,"skill_points":18,"fail_possibility":40,"furnace_lv":2,"phase_color":({0,1,2}),]),
(["name":"极品金创药","raws":(["*25":8,"*26":8,"*5":5,]),"product":"/d/city/obj/jinchuang_adv1","product_no":1,"period":15,
"maker_level":80,"improve_level":110,"skill_points":18,"fail_possibility":50,"furnace_lv":2,"phase_color":({0,1,2}),]),
(["name":"极品养精丹","raws":(["*27":8,"*28":8,"*29":5,]),"product":"/d/city/obj/yangjing_adv1","product_no":1,"period":15,
"maker_level":80,"improve_level":110,"skill_points":18,"fail_possibility":50,"furnace_lv":2,"phase_color":({2,1,0}),]),
(["name":"上品参王丸","raws":(["#1#mu":1,"*30":12]),"product":"/obj/remedy/drug/shenwangwan2.c","product_no":1,"period":140,
"maker_level":85,"improve_level":135,"skill_points":125,"fail_possibility":35,"furnace_lv":2,"phase_color":({1,0,2}),]),
(["name":"上品灵参丹","raws":(["#1#bing":1,"*30":12]),"product":"/obj/remedy/drug/lingshendan.c","product_no":1,"period":140,
"maker_level":85,"improve_level":135,"skill_points":125,"fail_possibility":35,"furnace_lv":2,"phase_color":({1,0,2}),]),
(["name":"毒草类初级解药","raws":(["*28":1,"*30":1]),"product":"/obj/remedy/drug/detox_dan"+(1+random(3))+".c","product_no":1,"period":15,
"maker_level":135,"improve_level":140,"skill_points":18,"fail_possibility":30,"furnace_lv":2,"phase_color":({0,1,2}),"detox_entry":1]),
(["name":"毒虫类初级解药","raws":(["*28":1,"*31":1]),"product":"/obj/remedy/drug/detox_dan"+(4+random(3))+".c","product_no":1,"period":15,
"maker_level":135,"improve_level":140,"skill_points":18,"fail_possibility":30,"furnace_lv":2,"phase_color":({2,1,0}),"detox_entry":1]),
(["name":"续命八丸","raws":(["*39":1,"*7":1,"*31":1,"*34":1,"*35":1,"*36":1,"*37":1,"*38":1,"*20":1,]),"product":"/obj/remedy/drug/xumingwan.c","product_no":1,"period":600,
"maker_level":135,"improve_level":170,"skill_points":700,"fail_possibility":35,"furnace_lv":2,"phase_color":({2,1,0}),]),
});//高级解毒药mark "adv_detox"
}//raws是药材配方数量，product是药品目录，product_no是炼成最大产量，period是炼成时间，maker_level是玩家允许炼药最低级别，improve_level是在多少级alchemy之前可以提升，phase_color只能使用0,1,2(MAG,HIW,HIR三种颜色)，代表火焰颜色。skill_points和提升alchemy技能有关，furnace_lv是要求的药炉等级。
mapping * player_formulae()
{
	return ({
	(["name":"大始丹","raws":(["*7":2,"*12":1,"*13":4,"*20":1,"#2#sui":1,"#4#sui":1]),"product":"/obj/remedy/drug/dashi","product_no":3,"period":9,
"maker_level":75,"improve_level":201,"skill_points":120,"fail_possibility":30,"furnace_lv":2,"phase_color":({2,0,1}),"DailyProductLimit":1]),//每天可服用一颗，30分钟内职业技能药师等加速，武者30分钟获取经验速度提升
	(["name":"坎离丹","raws":(["*2":3,"*5":1,"*8":1,"*11":1,"*20":1,"#4#bing":1,"#5#gu":1,]),"product":"/obj/remedy/drug/kanli","product_no":1,"period":40,
"maker_level":75,"improve_level":201,"skill_points":60,"fail_possibility":60,"furnace_lv":2,"phase_color":({2,1,0}),"DailyProductLimit":3]),//帮助通脉
	(["name":"噬嗑丹","raws":(["*3":1,"*9":1,"*10":1,"*20":1,"#2#yan":1,"#1#bing":1]),"product":"/obj/remedy/drug/shike","product_no":5,"period":9,
"maker_level":75,"improve_level":201,"skill_points":50,"fail_possibility":30,"furnace_lv":2,"phase_color":({0,1,2}),"DailyProductLimit":3]),//解除中毒状态
	(["name":"九转紫金丹","raws":(["*1":3,"*3":2,"*4":2,"*7":1,"*11":4,"*20":1,"#2#jia":1,"#4#sui":1,"#2#ri":1]),"product":"/obj/remedy/drug/jiuzhuan","product_no":3,"period":99,
"maker_level":201,"improve_level":210,"skill_points":5,"fail_possibility":60,"furnace_lv":2,"phase_color":({2,0,1}),"chance":780]),
	(["name":"蛇胆川贝散","raws":(["*32":1,"*33":1,]),"product":"/obj/remedy/drug/shedansan.c","product_no":1,"period":18,
"maker_level":65,"improve_level":90,"skill_points":18,"fail_possibility":40,"furnace_lv":2,"phase_color":({0,1,2}),]),
	//通脉药
	(["name":"天羽丸","raws":(["#5#yu":1,"#3#sui":1,"*3":1,"*7":1]),"product":"/obj/vein/dan7","product_no":1,"period":45,
	"maker_level":55,"improve_level":60,"skill_points":2,"fail_possibility":50,"furnace_lv":0,"phase_color":({1,0,2})]),
	(["name":"双灵丸","raws":(["#6#jiao":1,"#6#jia":1,"*2":1,"*4":1,"*10":1]),"product":"/obj/vein/dan12","product_no":1,"period":45,
	"maker_level":70,"improve_level":75,"skill_points":2,"fail_possibility":55,"furnace_lv":0,"phase_color":({0,1,2})]),
	(["name":"双灵丹","raws":(["#6#gu":1,"#6#yu":1,"*6":1,"*7":1,"*8":1]),"product":"/obj/vein/dan11","product_no":1,"period":45,
	"maker_level":70,"improve_level":75,"skill_points":2,"fail_possibility":55,"furnace_lv":0,"phase_color":({0,1,2})]),
	(["name":"凝真丹","raws":(["#3#jia":1,"#3#bing":1,"*5":1]),"product":"/obj/vein/dan2","product_no":1,"period":50,
	"maker_level":35,"improve_level":40,"skill_points":2,"fail_possibility":50,"furnace_lv":0,"phase_color":({0,1,2})]),
	(["name":"凝元丸","raws":(["#3#gu":1,"#2#jin":1,"*9":1]),"product":"/obj/vein/dan1","product_no":1,"period":49,
	"maker_level":35,"improve_level":40,"skill_points":2,"fail_possibility":50,"furnace_lv":0,"phase_color":({0,1,2})]),
	(["name":"木骨茶","raws":(["#5#gu":1,"#5#mu":1,"*2":1,"*3":1,"*4":1]),"product":"/obj/vein/dan10","product_no":3,"period":120,
	"maker_level":70,"improve_level":75,"skill_points":2,"fail_possibility":55,"furnace_lv":0,"phase_color":({0,1,2})]),
	(["name":"聚气散","raws":(["#4#yu":1,"#3#mu":1,"*3":1]),"product":"/obj/vein/dan3","product_no":6,"period":50,
	"maker_level":35,"improve_level":40,"skill_points":2,"fail_possibility":50,"furnace_lv":0,"phase_color":({0,1,2})]),
	(["name":"聚精剂","raws":(["#5#jia":1,"#5#jin":1,"*5":1,"*6":1,"*9":1]),"product":"/obj/vein/dan9","product_no":3,"period":120,
	"maker_level":70,"improve_level":75,"skill_points":2,"fail_possibility":55,"furnace_lv":0,"phase_color":({0,1,2})]),
	(["name":"集气散","raws":(["#4#jia":1,"#4#sui":1,"*6":1,"*9":1]),"product":"/obj/vein/dan5","product_no":1,"period":45,
	"maker_level":55,"improve_level":60,"skill_points":2,"fail_possibility":50,"furnace_lv":0,"phase_color":({0,2,1})]),
	(["name":"合气散","raws":(["#4#jiao":1,"#3#yan":1,"*2":1]),"product":"/obj/vein/dan4","product_no":6,"period":50,
	"maker_level":35,"improve_level":40,"skill_points":2,"fail_possibility":50,"furnace_lv":0,"phase_color":({0,1,2})]),
	(["name":"冰龙散","raws":(["#4#gu":1,"#4#bing":1,"*5":1,"*8":1]),"product":"/obj/vein/dan6","product_no":1,"period":45,
	"maker_level":55,"improve_level":60,"skill_points":2,"fail_possibility":50,"furnace_lv":0,"phase_color":({1,2,0})]),
	(["name":"冰麟丹","raws":(["#5#jiao":1,"#3#bing":1,"*1":1,"*2":1]),"product":"/obj/vein/dan8","product_no":1,"period":45,
	"maker_level":55,"improve_level":60,"skill_points":2,"fail_possibility":50,"furnace_lv":0,"phase_color":({1,0,2})]),
	});
}//玩家可获得药方,could be modified and synchronized.
mapping *player_formula(string *names)
{
	mapping *player_pres=player_formulae(),*res=({});
	for (int i=0;i<sizeof(player_pres);i++)
	if (member_array(player_pres[i]["name"],names)!=-1)
	res+=({player_pres[i]});
	return res;
}
void synchronize(object me)
{
	mapping *player_pres=player_formulae(),*myPres,*new_pres=({});
	if (!me->query("myPrescriptions")||!arrayp(me->query("myPrescriptions"))||sizeof(me->query("myPrescriptions"))<1)
	{
		me->set("MyAlchemy/Version",VER);
		return;
	}
	myPres=me->query("myPrescriptions");
	for (int i=0;i<sizeof(player_pres);i++)
	for (int j=0;j<sizeof(myPres);j++)
	if (player_pres[i]["name"]==myPres[j]["name"])
	new_pres+=({player_pres[i]});
	me->set("myPrescriptions",new_pres);
	me->set("MyAlchemy/Version",VER);
	return;
}
int DailyProductLimit(string drug)//有些药物有每日炼制的限制
{
	mapping *player_pres=player_formulae();
	for (int i=0;i<sizeof(player_pres);i++)
	if (player_pres[i]["name"]==drug)
	return player_pres[i]["DailyProductLimit"];
}