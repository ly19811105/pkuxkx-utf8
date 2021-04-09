int min_cooking_level = 0;              //最低制作要求cooking技能等级（最好与菜谱的最低要求学习等级对应）
int max_cooking_level = 30;             //最高能提升cooking至此等级
mapping stuff = ([                      //原材料文件名及数量
	"/obj/recipe/material/rice.c" : 1,
]);
mapping product = ([                    //成品文件名及数量
	"/clone/food/yangzhou-chaofan.c" : 1,
]);
int cook_time = 5;                      //烹饪所需时间
int skill_bonus = 500;                  //烹饪一次能够提升的技能小点数(建议设置为max*max/2附近的值)
string *describe =({                    //制作此食品时的特殊动作描述（可以设置一组）
	"$N运勺如飞，米粒的清香弥漫在四周，引得人垂涎欲滴。",
	"$N动作熟练，做个扬州炒饭看来一点也不在话下。"
});


#include "/kungfu/profession/cooking.h"