//zheng.c kugu 2006.9.15
//xs busy pfm 命中一般
#include <ansi.h>
inherit SSERVER;
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap,dp;

        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||	!me->is_fighting(target)
        ||      target==me)
           return notify_fail("你要攻击谁？\n");
        if( me->query("family/family_name")!="大雪山" )
          	return notify_fail("[百鸟争鸣]只有雪山弟子才可以用！\n");
        if( me->query("force") < 1200 )
		return notify_fail("你内力不足。\n");
	if( me->query("mana") < 1200 )
		return notify_fail("你法力不足。\n");
	if( me->query_skill("bainiao-jian",1) < 180 )
		return notify_fail("你的百鸟剑法太低了。\n");
	if( me->query_skill("spells") < 200 )
		return notify_fail("你的法术太低了。\n");
	if(target->is_busy())
           	return notify_fail("对方正在忙乱，哪有心思欣赏你的表演？！\n");
      	weapon = me->query_temp("weapon");
        ap = me->query("combat_exp")/10000;
        ap = 1+random(ap);
	dp = target->query("combat_exp")/12000;
        msg = HIM"$N左手捏了个法诀，口中念了几句含糊涂不清的咒语，再往右手" + weapon->name() + HIM"上一指。\n"NOR;
        msg += weapon->name() + HIC"铮然而鸣，有如百鸟齐至，相互争鸣！\n"NOR;
        if( ap > dp / 3 )
        {
        	msg += HIB"$n被着突如其来的百鸟之音吵的心烦意乱，渐渐失了方寸。\n"NOR;
        	target->start_busy(3+random(3));
        }
        else if( ap > dp / 5 )
        {
        	msg += HIY"$n连忙发出一阵清啸，与$N的百鸟之音斗了个旗鼓相当，谁也没占到什么便宜。\n"NOR;
        	target->start_busy(1);
        	me->start_busy(1);
        }
        else
        {
        	msg += HIR"$n不慌不忙，口中发出一阵虎啸龙吟，$N的百鸟之音反被$n压制了。\n"NOR;
        	me->start_busy(1);
        }
        me->add("force",-100);
        me->add("mana",-100);
        message_vision(msg, me, target);
        return 1;
}
