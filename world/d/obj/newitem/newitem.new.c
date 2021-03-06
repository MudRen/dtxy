/* Created by emotion
 设计说明:
 ==========
 武器--
 武器的物理攻击能力的成长受到其最高能够达到的等级的限制. 一件新的武器诞生在系统中后, 它的最高能够达到的等级就确定了.
 一件武器最高能够达到的等级现在定为7级. 一件武器, 在系统中诞生后, 它当前等级总是为1. 例如: 一件终级武器诞生, 它的
 当前等级为1, 它能够通过升级达到的最高等级为7.

 武器具有如下一些属性: damage.
 武器的当前等级*50为该武器的属性当前可以升到的数值. 比如: 一个当前等级为4的武器, 它的damage属性最多可以升到4*50=200
 升级武器的某一属性一点, 需要消耗该属性当前数值+1然后再平方这么多的wx. 照这个算法, 如果要把一个属性从1升到280, 基本
 需要7.35Mwx. 每次提升属性的成功率=random(提升者的forge(skill)) > random(属性当前数值+1)
 不论提升成功或者失败都会消耗wx. 如果提升者先天悟性和福缘高的话, 有一定的几率wx耗费减半. 几率为
 random(int+kar+400)<int+kar

 武器的当前级别提升到下一级需要消耗(当前级别+1)*1000这么多武器经验. 武器经验由使用该武器的时间决定升级武器需要用掉
 (当前级别+1)*1000这么多gold

 武器和使用者的配合度决定武器的五行攻击属性的发出率. 配合度=使用者使用该武器的经验/(该武器等级*1000). 如果武器升级
 则武器使用经验清零. 如果武器转让给他人, 使用经验清零

 武器上有孔, 可以嵌入魔法宝石. 孔的数量和该武器最高能达到的等级一致. 例如一个最高等级可以达到7的武器, 尽管其当前等
 级只是1, 它还是可以被嵌入7颗魔法宝石以加入五行攻击属性

 宝石--
 基本魔法宝石有5种(金木水火土), 每种宝石拥有对应的魔法攻击属性.五彩宝石是罕见的终极宝石, 同时具有所有的五行属性.
 宝石成长不受等级限制. 基本宝石的属性增长一点需要消耗该属性当前数值+1然后再平方这么多的dx. 五彩宝石则需消耗2倍
 每次提升属性的成功率=random(提升者的alchemy(skill)) > random(属性当前数+1)
 不论提升成功或者失败都会消耗dx. 如果提升者先天悟性和福缘高的话, 有一定的几率wx耗费减半. 几率为
 random(int+kar+600)<int+kar
 宝石一旦嵌入兵器后就不能再拿出来. 此后提升兵器的五行属性将会同时消耗wx和dx, 并同时受到兵器的等级限制

 防具--
 ==========
 */

#include <dbase.h>
#include <ansi.h>

// 以下代码从dt2的公开代码的newitems.c中找来
inherit __DIR__"newitemname.c";
string *shuxing = ( {"str","int","con","cor","cps","per","spi","kar"});
object get_weapon(object me, object killer);
object get_armor(object me, object killer);
object get_baoshi(object me, object killer);
// 以上代码从dt2的公开代码的newitems.c中找来

int is_newitem() {
	return 1;
}

// 如果该物品已经有主人的话, 是不会被别人使用的, 或着丢的
// 但是主人可以把物品转让给他人
void init() {
	object env;
	string owner_id;
	env = environment();
	if (!objectp(env))
		return;
	owner_id = query("newitem_owner_id");
	if (stringp(owner_id) && owner_id != env->query("id")) {
		call_out("self_destruct", 1, env);
	}
}

void self_destruct(object env) {
	tell_object(env, HIC"\n只见一阵烟雾飘然而至, 从中跳出一神猴, 对你呲牙笑道: 这见宝贝是有主人的\n然后抓起"
			+ query("name") +", 立时踪迹不见\n\n"NOR);
	destruct(this_object());
}

// 以下代码从dt2的公开代码的newitems.c中找来并做修改
//added by huarong 2004/11
void setname_weapon(object weapon) {
	int k, mark;
	string type;
	string temp_name, *temp_id, long;

	type = weapon->query("skill_type");
	k = weapon->query("maximum_level");
	//if (type=="mace") return 0;
	if (random(100) > 90)
		return 0;
	switch (type) {
	case "sword":
		if (weapon->query("anqi/allow")) {
			temp_name = name_qin1[k][0];
			temp_name += "琴";
			temp_id = ( {"qin"+random(10000), name_qin1[k][1]+" qin","qin"});
		} else if (random(2)) {
			weapon->set("music/type", "xiao");
			temp_name = name_xiao1[k][0];
			temp_name += "箫";
			temp_id
					= ( {	"xiao"+random(10000), name_xiao1[k][1]+" xiao","xiao"});
		} else {
			if (random(2)) {
				temp_name = name_sword1[k][0];
				mark = 1;
			} else {
				temp_name = name_sword2[k][0];
				mark = 2;
			}
			temp_name += random(2) ? "剑" : "牙";
			if (mark == 1)
				temp_id
						= ( {	"sword"+random(10000), name_sword1[k][1]+" sword","sword"});
			else
				temp_id
						= ( {	"sword"+random(10000), name_sword2[k][1]+" sword","sword"});
		}
		break;
	case "blade":
		if (random(2)) {
			temp_name = name_blade1[k][0];
			mark = 1;
		} else {
			temp_name = name_blade2[k][0];
			mark = 2;
		}
		if (k > 5)
			temp_name += random(2) ? "神" : "妖";
		temp_name += random(2) ? "刀" : "斩";
		if (mark == 1)
			temp_id
					= ( {	"blade"+random(10000), name_blade1[k][1]+" blade","blade"});
		else
			temp_id
					= ( {	"blade"+random(10000), name_blade2[k][1]+" blade","blade"});
		break;
	case "fork":
		if (random(2)) {
			temp_name = name_fork1[k][0];
			mark = 1;
		} else {
			temp_name = name_fork2[k][0];
			mark = 2;
		}
		if (k > 5)
			temp_name += random(2) ? "飞" : "灵";
		temp_name += "叉";
		if (mark == 1)
			temp_id
					= ( {	"fork"+random(10000), name_fork1[k][1]+" fork","fork"});
		else
			temp_id
					= ( {	"fork"+random(10000), name_fork2[k][1]+" fork","fork"});
		break;
	case "stick":
		if (random(2)) {
			temp_name = name_stick1[k][0];
			mark = 1;
		} else {
			temp_name = name_stick2[k][0];
			mark = 2;
		}
		temp_name += random(2) ? "棍" : "棒";
		if (mark == 1)
			temp_id
					= ( {	"stick"+random(10000), name_stick1[k][1]+" stick","stick"});
		else
			temp_id
					= ( {	"stick"+random(10000), name_stick2[k][1]+" stick","stick"});
		break;
	case "whip":
		if (random(2)) {
			temp_name = name_whip3[k][0];
			mark = 1;
		} else {
			temp_name = name_whip4[k][0];
			mark = 2;
		}
		if (k < 6)
			temp_name += random(2) ? "绸" : "丝";
		else {
			temp_name += random(2) ? "仙" : "青";
			temp_name += "绫";
		}
		if (mark == 1)
			temp_id
					= ( {	"whip"+random(10000), name_whip3[k][1]+" whip","whip"});
		else
			temp_id
					= ( {	"whip"+random(10000), name_whip4[k][1]+" whip","whip"});
		break;
	case "mace":
		if (random(2)) {
			temp_name = name_whip1[k][0];
			mark = 1;
		} else {
			temp_name = name_whip2[k][0];
			mark = 2;
		}
		temp_name += random(2) ? "鞭" : "锏";
		if (mark == 1)
			temp_id
					= ( {	"mace"+random(10000), name_whip1[k][1]+" mace","mace"});
		else
			temp_id
					= ( {	"mace"+random(10000), name_whip2[k][1]+" mace","mace"});
		break;
	case "hammer":
		if (random(2)) {
			temp_name = name_hammer1[k][0];
			mark = 1;
		} else {
			temp_name = name_hammer2[k][0];
			mark = 2;
		}
		if (k > 5)
			temp_name += random(2) ? "神" : "雷";
		temp_name += "锤";
		if (mark == 1)
			temp_id
					= ( {	"hammer"+random(10000), name_hammer1[k][1]+" hammer","hammer"});
		else
			temp_id
					= ( {	"hammer"+random(10000), name_hammer2[k][1]+" hammer","hammer"});
		break;
	case "spear":
		if (random(2)) {
			temp_name = name_spear1[k][0];
			mark = 1;
		} else {
			temp_name = name_spear2[k][0];
			mark = 2;
		}
		temp_name += random(2) ? "枪" : "戟";
		if (mark == 1)
			temp_id
					= ( {	"spear"+random(10000), name_spear1[k][1]+" spear","spear"});
		else
			temp_id
					= ( {	"spear"+random(10000), name_spear2[k][1]+" spear","spear"});
		break;
	case "staff":
		if (random(2)) {
			temp_name = name_staff1[k][0];
			mark = 1;
		} else {
			temp_name = name_staff2[k][0];
			mark = 2;
		}
		if (k > 5)
			temp_name += random(2) ? "禅" : "佛";
		temp_name += "杖";
		if (mark == 1)
			temp_id
					= ( {	"staff"+random(10000), name_staff1[k][1]+" staff","staff"});
		else
			temp_id
					= ( {	"staff"+random(10000), name_staff2[k][1]+" staff","staff"});
		break;
	case "axe":
		if (random(2)) {
			temp_name = name_axe1[k][0];
			mark = 1;
		} else {
			temp_name = name_axe2[k][0];
			mark = 2;
		}
		if (k > 5)
			temp_name += random(2) ? "之" : "玄";
		temp_name += "斧";
		if (mark == 1)
			temp_id = ( {"axe"+random(10000), name_axe1[k][1]+" axe","axe"});
		else
			temp_id = ( {"axe"+random(10000), name_axe2[k][1]+" axe","axe"});
		break;
	default:
		break;
	}
	temp_name=temp_name+""NOR;
	if (temp_name)
		weapon->set_name(temp_name, temp_id);
}
// 以上代码从dt2的公开代码的newitems.c中找来并做修改

// 以下代码从dt2的公开代码的newitems.c中找来并做修改
//added by huarong 2004/11
void setname_armor(object armor) {
	int k, mark;
	string type;
	string temp_name, *temp_id, long;
	string temp_id1;

	type = armor->query("armor_type");
	k = armor->query("maximum_level");
	//if (type == "shield")
	//	return 0;
	switch (type) {
	case "shield":
		if (!random(k*20)) {
			temp_name = name_zbtz[k][0];
			temp_id1  = name_zbtz[k][1];
			armor->set("mod/level",k);
		} else {
			return 0;
		}
		temp_name += "盾";
		temp_id	= ( {	"shield" + random(10000), temp_id1+" shield","shield"});
		break;
	case "armor":
		if (!random(k*20)) {
			temp_name = name_zbtz[k][0];
			temp_id1  = name_zbtz[k][1];
			armor->set("mod/level",k);
		} else if (random(2)) {
			temp_name = name_armor1[k][0];
			temp_id1  = name_armor1[k][1];
		} else {
			temp_name = name_armor2[k][0];
			temp_id1  = name_armor1[k][1];
		}
		if (k > 10)
			temp_name += random(2) ? "宝" : "异";
		temp_name += random(2) ? "甲" : "铠";
		temp_id	= ( {	"armor" + random(10000), temp_id1+" armor","armor"});
		break;
	case "cloth":
		if (random(2)) {
			if (!random(k*20)) {
				temp_name = name_zbtz[k][0];
				temp_id1  = name_zbtz[k][1];
				armor->set("mod/level",k);
			} else if (random(2)) {
				temp_name = name_cloth11[k][0];
				temp_id1  = name_cloth11[k][1];
			} else {
				temp_name = name_cloth12[k][0];
				temp_id1  = name_cloth12[k][1];
			}
			if (k > 10)
				temp_name += random(2) ? "奇" : "神";
			temp_name += random(2) ? "衫" : "衣";
			temp_id	= ( {	"cloth" + random(10000), temp_id1+" cloth","cloth"});
			armor->set("male_only", 1);
		} else {
			if (!random(k*20)) {
				temp_name = name_zbtz[k][0];
				temp_id1  = name_zbtz[k][1];
				armor->set("mod/level",k);
			} else if (random(2)) {
				temp_name = name_cloth21[k][0];
				temp_id1  = name_cloth21[k][1];
			} else {
				temp_name = name_cloth22[k][0];
				temp_id1  = name_cloth22[k][1];
			}
			if (k > 10)
				temp_name += random(2) ? "霓裳" : "霞帔";
			else
				temp_name += random(2) ? "裳" : "裙";
			temp_id = ( {	"cloth" + random(10000), temp_id1+" cloth","cloth"});
			armor->set("female_only", 1);
		}
		break;
	case "head":
		if (random(2)) {
			if (!random(k*20)) {
				temp_name = name_zbtz[k][0];
				temp_id1  = name_zbtz[k][1];
				armor->set("mod/level",k);
			} else if (random(2)) {
				temp_name = name_head11[k][0];
				temp_id1  = name_head11[k][1];
			} else {
				temp_name = name_head12[k][0];
				temp_id1  = name_head12[k][1];
			}
			if (k > 10)
				temp_name += random(2) ? "之" : "神";
			temp_name += random(2) ? "盔" : "冠";
			temp_id	= ( {	"hat" + random(10000), temp_id1+" hat","hat"});
			armor->set("male_only", 1);
		} else {
			if (!random(k*20)) {
				temp_name = name_zbtz[k][0];
				temp_id1  = name_zbtz[k][1];
				armor->set("mod/level",k);
			} else if (random(2)) {
				temp_name = name_head21[k][0];
				temp_id1  = name_head21[k][1];
			} else {
				temp_name = name_head22[k][0];
				temp_id1  = name_head22[k][1];
			}
			if (k > 10)
				temp_name += random(2) ? "魔" : "神";
			temp_name += random(2) ? "巾" : "钗";
			temp_id = ( {	"hat" + random(10000), temp_id1+" hat","hat"});
			armor->set("female_only", 1);
		}
		break;
	case "boots":
		if (!random(k*20)) {
			temp_name = name_zbtz[k][0];
			temp_id1  = name_zbtz[k][1];
			armor->set("mod/level",k);
		} else if (random(2)) {
			temp_name = name_boots1[k][0];
			temp_id1  = name_boots1[k][1];
		} else {
			temp_name = name_boots2[k][0];
			temp_id1  = name_boots2[k][1];
		}
		if (k > 10)
			temp_name += random(2) ? "神" : "魔";
		temp_name += random(2) ? "靴" : "鞋";
		if (random(2))
			temp_id	= ( {	"boots" + random(10000), temp_id1+" boots","boots"});
		else
			temp_id	= ( {	"shoes" + random(10000), temp_id1+" shoes","shoes"});
		break;
	case "neck":
		if (!random(k*20)) {
			temp_name = name_zbtz[k][0];
			temp_id1  = name_zbtz[k][1];
			armor->set("mod/level",k);
		} else if (random(2)) {
			temp_name = name_neck1[k][0];
			temp_id1  = name_neck1[k][1];
		} else {
			temp_name = name_neck2[k][0];
			temp_id1  = name_neck2[k][1];
		}
		temp_name += random(2) ? "护身符" : "项链";
		temp_id = ( {	"neck" + random(10000), temp_id1+" neck","neck"});
		break;
	case "wrists":
		if (!random(k*20)) {
			temp_name = name_zbtz[k][0];
			temp_id1  = name_zbtz[k][1];
			armor->set("mod/level",k);
		} else if (random(2)) {
			temp_name = name_wrists1[k][0];
			temp_id1  = name_wrists1[k][1];
		} else {
			temp_name = name_wrists2[k][0];
			temp_id1  = name_wrists2[k][1];
		}
		if (k > 10)
			temp_name += random(2) ? "神" : "幻";
		temp_name += random(2) ? "护腕" : "镯";
		temp_id = ( {	"wrists" + random(10000), temp_id1+" wrists","wrists"});
		break;
	case "finger":
		if (!random(k*20)) {
			temp_name = name_zbtz[k][0];
			temp_id1  = name_zbtz[k][1];
			armor->set("mod/level",k);
		} else {
			temp_name = name_ring[k][0];
			temp_id1  = name_ring[k][1];
		}
		if (k > 0 && k <= 10)
			temp_name += "之戒";
		else
			temp_name += "戒";
		temp_id = ( {"ring" + random(10000), temp_id1+" ring","ring"});
		break;
	case "waist":
		if (!random(k*20)) {
			temp_name = name_zbtz[k][0];
			temp_id1  = name_zbtz[k][1];
			armor->set("mod/level",k);
		} else {
			temp_name = name_waist[k][0];
			temp_id1  = name_waist[k][1];
		}
		if (k > 0 && k <= 10)
			temp_name += "腰带";
		if (random(2))
			temp_id	= ( {	"belt" + random(10000), temp_id1+" belt","belt"});
		else
			temp_id	= ( {	"waist" + random(10000), temp_id1+" waist","waist"});
		break;
	case "surcoat":
		if (!random(k*20)) {
			temp_name = name_zbtz[k][0];
			temp_id1  = name_zbtz[k][1];
			armor->set("mod/level",k);
		} else if (random(2)) {
			temp_name = name_surcoat1[k][0];
			temp_id1  = name_surcoat1[k][1];
		} else {
			temp_name = name_surcoat2[k][0];
			temp_id1  = name_surcoat2[k][1];
		}
		if (k > 0 && k <= 10)
			temp_name += random(2) ? "披风" : "斗篷";
		temp_id = ( {	"cloak" + random(10000), temp_id1+" cloak","cloak"});
		break;
	case "hands":
		if (!random(k*20)) {
			temp_name = name_zbtz[k][0];
			temp_id1  = name_zbtz[k][1];
			armor->set("mod/level",k);
		} else if (random(2)) {
			temp_name = name_hands1[k][0];
			temp_id1  = name_hands1[k][1];
		} else {
			temp_name = name_hands2[k][0];
			temp_id1  = name_hands2[k][1];
		}
		if (k > 0 && k <= 10)
			temp_name += random(2) ? "手套" : "护手";
		temp_id = ( {	"gloves" + random(10000), temp_id1+" gloves","gloves"});
		break;
	default:
		break;
	}
	temp_name=temp_name+""NOR;
	if (temp_name)
		armor->set_name(temp_name, temp_id);
}
// 以上代码从dt2的公开代码的newitems.c中找来并做修改

// 以下代码从dt2的公开代码的newitems.c中找来并做修改
object get_item(object me, object killer) {
	//object item;
	int i, j;
	j = killer->query_temp("mieyao/level");
	// add by yekai for test taozhuang
	if (1 && wizardp(killer))
		j = 1;
	else if (j < 7)
		return 0;
	else
		j = random(17-j);
	switch (j) {
	case 0:
		return get_weapon(me, killer);
		break;
	case 1:
		return get_armor(me, killer);
		break;
	case 2:
		return get_baoshi(me, killer);
		break;
	default:
		return 0;
	}
}
// 以上代码从dt2的公开代码的newitems.c中找来并做修改

// 以下代码从dt2的公开代码的newitems.c中找来并做修改
object get_weapon(object me, object killer) {
	object weapon;
	int i, j, value, zs;
	int myexp, taexp, exp, max_level, iceblade_flag = 0;
	string att;
	string *file = ( {
				"/d/obj/newitem/newweapon/qin.c",
				"/d/obj/newitem/newweapon/sword.c",
				"/d/obj/newitem/newweapon/blade.c",
				"/d/obj/newitem/newweapon/fork.c",
				"/d/obj/newitem/newweapon/stick.c",
				"/d/obj/newitem/newweapon/whip.c",
				"/d/obj/newitem/newweapon/hammer.c",
				"/d/obj/newitem/newweapon/spear.c",
				"/d/obj/newitem/newweapon/staff.c",
				"/d/obj/newitem/newweapon/axe.c",
				"/d/obj/newitem/newweapon/mace.c"});

	mixed *name = ( {
				( {	YEL"青铜","bronz",3500,2000,100,10}),
				( {	HIC"精钢","steel",2500,5000,500,10}),
				( {	HIB"寒铁","iron",3000,15000,1000,20}),
				( {	HIY"乌金","gold",4000,25000,2000,20}),
				( {	HIR"赤金","gold",4000,25000,4000,30}),
				( {	HIG"灵玉","jade",2000,50000,10000,40}),
				( {	HIR"血玉","jade",2000,50000,20000,40}),
				( {	HIG"仙灵","jade",2000,100000,50000,60}),
				( {	HIW"无尘","jade",2000,200000,100000,80})
			});
	mixed *iceblade_name = ( {
				( {	WHT"寒风怒号","hfnh"}),
				( {	WHT"碎雪漫天","sxmt"}),
				( {	WHT"小雪初晴","xxcq"}),
				( {	WHT"鹅毛大雪","emdx"}),
				( {	WHT"玄天冰凌","xtbl"}),
				( {	HIG"春雪碎寒","cxsh"}),
				( {	HIW"飘雪穿云","pxcy"}),
				( {	HIG"虚空翠寒","xkch"}),
				( {	HIW"混沌冰焰","hdby"})
			});
	myexp = me->query("daoxing", 1) / 1000;
	taexp = killer->query("daoxing", 1) / 1000;
	if (random(myexp + taexp) < taexp / 2 && !wizardp(killer))//myexp<taexp/1.5 &&
		return 0;
	//得到绿色装备
	i = random(11);
	weapon = new(file[i]);
	if (i == 2 && random(10) < 4)
		iceblade_flag = 1;
	//得到武器的材料,对目标道行取随机值
	zs = killer->query("lunhui_zhuanshi");
	if (!zs && myexp > 20000) {
		myexp = 20000;
	} else if (zs < 5) {
		myexp += zs * 10000;
		if (myexp > (zs + 2) * 10000)
			myexp = (zs + 2) * 10000;
	} else {
		if (myexp < 150000)
			myexp += 50000;
	}
	exp = random(myexp);
	if (exp > 100000)
		i = random(9);
	else if (exp > 50000)
		i = random(8);
	else if (exp > 20000)
		i = random(7);
	else if (exp > 10000)
		i = random(6);
	else if (exp > 4000)
		i = random(5);
	else if (exp > 2000)
		i = random(4);
	else if (exp > 1000)
		i = random(3);
	else if (exp > 500)
		i = random(2);
	else
		i = 0;
	weapon->set("no_break", 1);
	weapon->set_name(
			name[i][0] + weapon->query("name") + NOR,
			( {	weapon->query("id") + random(10000), name[i][1]+" "+weapon->query("id"),weapon->query("id")}));
	weapon->set_weight((name[i][2] + weapon->query_weight()) / 2);
	/*switch(i)
	 {
	 case 0: att="是由青铜制成的。\n";break;
	 case 1: att="是由百炼精铸成的。\n";break;
	 case 2: att="是由千年寒铁铸成的。\n";break;
	 case 3: att="是由万年乌金铸成的。\n";break;
	 case 4: att="是由上古灵玉铸成的。\n";break;
	 case 5: att="是由传说中的月亮之石化成的。\n";break;
	 case 6: att="是由传说中的大唐西游太阳之石化成的。\n";break;
	 }
	 weapon->set("long",HIG+weapon->query("long")+att+NOR);*/
	weapon->set("material", name[i][1]);
	weapon->set("maximum_level", i + 1);//等级 1－9
	weapon->set("max_level", i + 1);//等级 1－9
	weapon->set("level", 1); // 当前等级1

	//附加属性
	weapon->set("weapon_prop/damage", 30 + i * 15 + random((i + 1) * 5));//攻击力
	switch (random(5)) {
	case 0:
		weapon->set("weapon_prop/gold_attack", 10 + random(i * 10));
		break;
	case 1:
		weapon->set("weapon_prop/wood_attack", 10 + random(i * 10));
		break;
	case 2:
		weapon->set("weapon_prop/earth_attack", 10 + random(i * 10));
		break;
	case 3:
		weapon->set("weapon_prop/water_attack", 10 + random(i * 10));
		break;
	case 4:
		weapon->set("weapon_prop/fire_attack", 10 + random(i * 10));
		break;
	}
	/*if (random(2100) > 2090) {
	 weapon->add("weapon_prop/damage", 30);
	 if ( random(500) > 400 )
	 weapon->add("weapon_prop/damage", 20);
	 }*/
	weapon->set("sockets/max", random(i + 2));//安放宝石数
	weapon->set("sockets/now", 0);
	weapon->set("wield/daoxing", name[i][4]);
	weapon->set("wield/" + shuxing[random(sizeof(shuxing))], name[i][5] / 2 + 1
			+ random(name[i][5] / 2));
	//价值
	value = name[i][3];
	value += weapon->query("sockets/max") * 2000;
	value += weapon->query("weapon_prop/damage") * 1000;
	weapon->set("value", value * (i + 1));

	setname_weapon(weapon);
	if (iceblade_flag == 1) {
		weapon->set_name(
				iceblade_name[i][0] + "刀" + NOR,
				( {	"blade" + random(10000), iceblade_name[i][1]+" blade","blade"}));
		weapon->set("material", "ice");
	}
	if (wizardp(this_player()))
	tell_object(this_player(),HIM+"类型："+weapon->query("skill_type")+"     最高等级："+weapon->query("max_level")+"\n"NOR);
	return weapon;
}
// 以上代码从dt2的公开代码的newitems.c中找来并做修改

// 以下代码从dt2的公开代码的newitems.c中找来并做修改
object get_armor(object me, object killer) {
	object armor;
	int i, j, value, a1, a2, a3, bind_pro, bind_type, zs;
	int myexp, taexp, exp;
	string att;
	string *file = ( {
				"/d/obj/newitem/newarmor/armor.c",
				"/d/obj/newitem/newarmor/boots.c",
				"/d/obj/newitem/newarmor/cloth.c",
				"/d/obj/newitem/newarmor/finger.c",
				"/d/obj/newitem/newarmor/hands.c",
				"/d/obj/newitem/newarmor/head.c",
				"/d/obj/newitem/newarmor/neck.c",
				"/d/obj/newitem/newarmor/shield.c",
				"/d/obj/newitem/newarmor/surcoat.c",
				"/d/obj/newitem/newarmor/waist.c",
				"/d/obj/newitem/newarmor/wrists.c"});
	mixed *name = ( {
				( {	HIY"蟒皮","boa",3000,2000,100,10}),
				( {	HIR+BLK"黑金","gold",2500,5000,500,10}),
				( {	CYN"鳄鱼","crocodile",3000,10000,1000,10}),
				( {	HIM"彩玉","jade",2500,20000,2000,20}),
				( {	HIG"猛犸","mammoth",4000,30000,3000,20}),
				( {	YEL"琥珀","amber",2000,40000,4000,20}),
				( {	MAG"麒麟","kylin",2500,60000,6000,20}),
				( {	HIM"翡翠","emerald",2000,80000,8000,30}),
				( {	HIC"龙鳞","dragon",2500,100000,10000,30}),
				( {	HIY"水晶","crystal",1500,120000,20000,40}),
				( {	HIR"战神","mars",3000,140000,40000,40}),
				( {	HIB"灵魂","spirit",1000,160000,60000,60}),
				( {	HIW"无敌","sunshine",2000,180000,80000,60}),
				( {	HIR+BLK"大唐","dark",1000,200000,100000,80})
			});
	myexp = me->query("combat_exp", 1) / 1000;
	taexp = killer->query("combat_exp", 1) / 1000;
	if (random(myexp + taexp) < taexp / 2 && !wizardp(killer))
		return 0;
	//得到绿色装备
	i = random(11);
	armor = new(file[i]);
	if (!armor)
		return 0;

	//得到防具的材料,对目标道行取随机值
	zs = killer->query("lunhui_zhuanshi");
	if (!zs && myexp > 20000) {
		myexp = 20000;
	} else if (zs < 5) {
		myexp += zs * 10000;
		if (myexp > (zs + 2) * 10000)
			myexp = (zs + 2) * 10000;
	} else {
		if (myexp < 150000)
			myexp += 50000;
	}
	exp = random(myexp);
	if (exp > 100000)
		i = random(14);
	else if (exp > 80000)
		i = random(13);
	else if (exp > 60000)
		i = random(12);
	else if (exp > 40000)
		i = random(11);
	else if (exp > 20000)
		i = random(10);
	else if (exp > 10000)
		i = random(9);
	else if (exp > 8000)
		i = random(8);
	else if (exp > 6000)
		i = random(7);
	else if (exp > 4000)
		i = random(6);
	else if (exp > 3000)
		i = random(5);
	else if (exp > 2000)
		i = random(4);
	else if (exp > 1000)
		i = random(3);
	else if (exp > 500)
		i = random(2);
	else
		i = 0;
	//i=6;
	armor->set("no_break", 1);//有此属性，兵器不能被打断，同时应该修改weapond.c及可打断兵器的pfm和cast
	//龙宫huntian-hammer,perform break,cast dragonfire,方寸的perform leiting
	armor->set_name(
			name[i][0] + armor->query("name") + NOR,
			( {	armor->query("id") + random(10000), name[i][1]+" "+armor->query("id"),armor->query("id")}));
	armor->set_weight((name[i][2] + armor->query_weight()) / 2);
	armor->set("long", "附有特殊力量的装备，是大唐西游的新产物。");
	armor->set("material", name[i][1]);
	armor->set("maximum_level", i + 1);//等级 1－14maximum_level
	armor->set("max_level", i + 1);//等级 1－14
	armor->set("level", 1);

	//附加属性
	switch (random(5)) {
	case 0:
		armor->set("armor_prop/gold_defense", 5 + random(i * 5));
		break;
	case 1:
		armor->set("armor_prop/wood_defense", 5 + random(i * 5));
		break;
	case 2:
		armor->set("armor_prop/water_defense", 5 + random(i * 5));
		break;
	case 3:
		armor->set("armor_prop/fire_defense", 5 + random(i * 5));
		break;
	case 4:
		armor->set("armor_prop/earth_defense", 5 + random(i * 5));
		break;
	}
	armor->set("armor_prop/armor", 15 + i * 4 + random((i + 1) * 2));//防御力
	if (!armor->is_acc()) {
		armor->set("sockets/max", 1 + random((i + 1) / 3));//安放宝石数
		armor->set("sockets/now", 0);
	}
	armor->set("wield/daoxing", name[i][4]);
	armor->set("wield/" + shuxing[random(sizeof(shuxing))], name[i][5] / 2 + 1
			+ random(name[i][5] / 2));
	//价值
	value = name[i][3];
	value += armor->query("sockets/max") * 2000;
	value += armor->query("armor_prop/armor") * 1000;
	armor->set("value", value * ((i + 1) / 2));

	setname_armor(armor);
	if (wizardp(this_player()))
	tell_object(this_player(),HIM+"类型："+armor->query("armor_type")+"     最高等级："+armor->query("max_level")+"\n"NOR);
	return armor;
}
// 以上代码从dt2的公开代码的newitems.c中找来并做修改

// 以下代码从dt2的公开代码的newitems.c中找来并做修改
object get_baoshi(object me, object killer) {
	object baoshi;
	int i, j, value, temp, zs;
	int myexp, taexp, exp;
	myexp = me->query("combat_exp", 1);
	taexp = killer->query("combat_exp", 1);
	if (random(myexp + taexp) < taexp / 2 && !wizardp(killer))
		return 0;
	zs = killer->query("lunhui_zhuanshi");
	temp = random(5010 + zs * 10);
	if (temp <= 999)
		baoshi = new("/d/obj/newitem/baoshi/magic_stone1");
	else if (temp <= 1999)
		baoshi = new("/d/obj/newitem/baoshi/magic_stone2");
	else if (temp <= 2999)
		baoshi = new("/d/obj/newitem/baoshi/magic_stone3");
	else if (temp <= 3999)
		baoshi = new("/d/obj/newitem/baoshi/magic_stone4");
	else if (temp <= 4999)
		baoshi = new("/d/obj/newitem/baoshi/magic_stone5");
	else {
		baoshi = new("/d/obj/newitem/baoshi/super_magic_stone");
		log_file("magic_stone", "诞生了一颗五彩宝石!\n");
	}
	return baoshi;
}
// 以上代码从dt2的公开代码的newitems.c中找来并做修改

// 重设物品属性
void set_item_attr(string attr, mixed value, object holder) {
	set(attr, value);
	if (!objectp(holder))
		return;
	if (query("newitem_owner_id") == holder->query("id")) {
		holder->set("newitem/" + query("id") + "/attr/" + attr, value);
	}
}

// 升级经验准备度
int fight_exp_rate() {
	int temp_value;
	object me;
	me = this_object();
	if (me->is_weapon()) {
		temp_value = me->query("fight_exp") * 100 / ((me->query("level") + 1)
				* 1000);
	} else if (me->is_armor()) {
		temp_value = me->query("fight_exp") * 100 / ((me->query("level") + 1)
				* 500);
	} else if (me->is_acc()) {
		temp_value = me->query("fight_exp") * 100 / ((me->query("level") + 1)
				* 500);
	} else
		temp_value = 0;
	if (temp_value > 100)
		temp_value = 100;
	return temp_value;
}

// 武器熟练度
int op_exp_rate() {
	int temp_value;
	object me;
	me = this_object();
	if (me->is_weapon()) {
		temp_value = me->query("op_exp") * 100 / (me->query("level")
				* me->query("level") * 500);
	} else
		temp_value = 0;
	if (temp_value > 100)
		temp_value = 100;
	return temp_value;
}

