// Wangqing-jue.c 忘情诀
// Cracked by 凌惊雪 4-17-2003

#include <ansi.h>
inherit SKILL;

mapping *action = ({
	([	"name":		"天意诀",
                "action":       "$N使出忘情诀中的"+HIC"「天意诀」"NOR+"$N已仿佛与天融合在一起，在刹那间便是苍苍天穹，永无底止，也没有感情。",
		"dodge":	-30,
		"parry" :	-30,
		"force":	20,
        	"damage" :      70,
		"damage_type":	"刺伤"
	]),
	([	"name":		"天意诀",
                "action":       "$N使出忘情诀中的"+HIC"「天意诀」"NOR+"$N已仿佛与天融合在一起，在刹那间便是苍苍天穹，永无底止，也没有感情。",
		"dodge":	-30,
		"parry" :	-30,
		"force":	20,
        	"damage" :      70,
		"damage_type":	"刺伤"
	]),
	([	"name":		"地势诀",
             "action":       "$N使出忘情诀中的"+YEL"「地势诀」"NOR+"，$N立时觑出死角，觅得虚隙，乘机而入",
		"dodge":	-30,
		"parry" :	-30,
		"force":	30,
        	"damage" :      70,
		"damage_type":	"刺伤"
	]),
	([	"name":		"君王诀",
		"action":	"$N举剑齐眉，容庄神凝，$w剑尖凝在半空，遥指$n。使出忘情剑法中的"+HIR"「君王诀」"NOR,
		"dodge":	-30,
		"parry" :	-30,
		"force":	40,
        	"damage" :      70,
		"damage_type":	"刺伤"
	]),
	([	"name":		"亲思诀",
		"action":	"$N使出忘情诀中的"+HIB"「亲思诀」"NOR+"，以一些声音、手势、音乐、景象吸引住$n，以惊人数倍的内力，使$n坠入了往事尘烟之中",
		"dodge":	-30,
		"parry" :	-30,
		"force":	50,
        	"damage" :      70,
		"damage_type":	"刺伤"
	]),
	([	"name":		"师教诀",
		"action":	"$N使出忘情诀中的"+HIY"「师教诀」"NOR+"，倏地一个箭步就抢过去，一伸手，就摘下背后的$w，“玎玎”两声，一剑削出，",
		"dodge":	-30,
		"parry" :	-30,
		"force":	60,
        	"damage" :      80,
		"damage_type":	"刺伤"
	]),
	([	"name":		"日明诀",
		"action":	"$N只觉一股共天地久长的浩气，自心中激游全身，使出忘情诀中的"+HIW"「日明诀」"NOR+"，飞袭$n",
		"dodge":	-30,
		"parry" :	-30,
		"force":	70,
        	"damage" :      90,
		"damage_type":	"刺伤"
	]),
	([	"name":		"风流诀",
		"action":	"$n只觉有一股强大的压力，铺天盖地的涌压而来，额上隐然有汗，正是忘情诀中的"+HIG"「风流诀」"NOR,
		"dodge":	-30,
		"parry" :	-30,
		"force":	80,
        	"damage" :      100,
		"damage_type":	"刺伤"
	]),
	([	"name":		"云翳诀",
		"action":	"$n刚要刺出，忽然觉得凤涌云动，反被$N一剑自顶至胯，串了进去,   中了"+HIC"「云翳诀」"NOR,
		"dodge":	-30,
		"parry" :	-30,
		"force":	90,
        	"damage" :      100,
		"damage_type":	"刺伤"
	]),
});

int valid_learn(object me)
{
//        if (me->query("mark/jinlong")!="wangqing")
//                return notify_fail("可能你实在无法领悟这项剑法，怎么学好象都没有任何长进？\n"); 
	return 1;
}

int valid_enable(string usage)
{
        return  (usage=="parry") || (usage=="sword") || (usage=="dodge");
}

mapping query_action(object me, object weapon)
{
	int i;
	i = me->query_temp("WQJ");
	if( !me->query_temp("WQJ") ) {
        return action[random(9)];
	}
	else
	{
	return action[i];
	}
}

int practice_skill(object me)
{
        if( (int)me->query("kee") < 30 
        ||    (int)me->query("force") < 5  )
                return
	notify_fail("你的体力不够练这门功夫，还是先休息休息吧。\n");
//        if (me->query("mark/jinlong")!="wangqing")
//                return notify_fail("你怎么练好象都没有任何长进？\n"); 
        if( (int)me->query_skill("wangqing-jue",1) < 40 )
                return notify_fail("你对忘情诀的领悟还不够，没有办法自行练习这套剑法。\n");
        me->receive_damage("kee", 20);
        me->add("force", -5);
	return 1;
}

string *dodge_msg = ({
       "$n施出"+HIC"“天意”"NOR+"诀，$n人如大鸟般跃起，平飞掠出，轻轻一点，宛似飞燕在天空一折，又掠了出去。\n",
       "$n施出"+HIB"“地势”"NOR+"诀，身未回，身形却从地倒飞而出，宛若流星，斜挂纵落。\n",
       "$n一点，又疾地冲天而起，去势劲急，$n在骄阳下映耀，犹如孔雀开屏，破空而去。正是"+HIY"“日明”"NOR+"一诀。\n",
	"$n施展了“忘情诀”中的"+HIC"“月映”"+NOR"法，在月色寒光中消失了。\n",   
       "剑割微风，造成急卷的气流割体,$n轻如落叶，已飘到$N背后。正是"+HIG"“风流”"NOR+"一诀。\n",
});

string *parry_msg = ({
       "$n以"+HIY"「金断诀」"NOR+"之势，竟随在$N之后,竟让$N产生一种错觉.\n",
      "$n在这刹那间，身体变得如一根朽木。在这瞬间将所有的穴道全部闭死.正是"+HIG"「木顽诀」"NOR"\n",
       "$n运用"+HIC"「水逝诀」"NOR+"在$n周围激起了无数串水柱，$N的武器全打在水墙上，都无法透过.\n",
	"$n仗着遥远的火光摇晃，以"+HIR"「火延诀」"NOR+"之势，掩人眼目,急闪一旁.\n",
	"$n用"+YEL"「土掩诀」"NOR+"迅速的在地上掘开洞,$n不见了\n",
});


string query_parry_msg(object weapon)
{
                return parry_msg[random(sizeof(parry_msg))];
}

string query_dodge_msg(string limb)
{
    return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_effect(object me, object weapon, string name, int skill)
{
}

string perform_action_file(string func)
{
return CLASS_D("suburb") + "/wangqing-jue/" + func;
}

