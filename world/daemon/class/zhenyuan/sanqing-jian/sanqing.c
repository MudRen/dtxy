// sanqing.c 一剑化三清

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>
inherit SSERVER;
 
int perform(object me, object target)
{
        object weapon, ob;
        string msg, string1;
        int count;
 	if( !target ) target = offensive_target(me);

        if( !me->is_fighting(target) )
                return notify_fail("「一剑化三清」只能在战斗中使用。\n");
 
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("「一剑化三清」开始时必须拿着一把剑！\n");
	if( time()-(int)me->query_temp("sqpfm_end") < 4 )
                return notify_fail("绝招用多就不灵了！\n");
        //if (me->query_temp("jianmang"))
        //   return notify_fail("你正在施用剑芒，没有余力出「一剑化三清」！\n");
        if(!wizardp(me) && me->query("family/family_name") != "五庄观")
                return notify_fail("[一剑化三清]是五庄观不传之密！\n");
        if( (int)me->query("force") < 500 )
                return notify_fail("你的内力不够！\n");
	me->add("force", -100);
        if( (int)me->query_skill("sanqing-jian",1) < 50 )
                return notify_fail("你的三清剑法还不到家，无法使用「一剑化三清」！\n");
        me->set_temp("sqpfm_end", time());
	me->add_temp("apply/attack", (int)me->query_skill("sanqin-jiang",1)/4);
	me->add_temp("apply/damage", (int)me->query_skill("sanqin-jiang",1)/4);
        msg = HIY "\n$N使出三清剑法的绝技「一剑化三清」，手中的"+ weapon->name()+  HIY"闪电般攻出连环三剑！\n\n" NOR;
        message_vision(msg, me);
        msg = HIB "只见$N右手一抖，"+ weapon->name()+ HIB"划向$n的左肩！\n" NOR;
        message_vision(msg, me,target);
        me->set_temp("sq_perform", 7);
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR);
        msg =  HIW "$N凌空使出第二剑,"+ weapon->name()+ HIW"削向$n的右肩！\n" NOR;
        message_vision(msg, me,target);
        me->set_temp("sq_perform", 8);
       	COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR);
        msg = HIC "$N清啸一声，聚气于剑，朝$n的胸前攻出第三剑！\n" NOR;
        message_vision(msg, me,target);
        me->set_temp("sq_perform", 9);
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR);
        me->add_temp("apply/attack", -(int)me->query_skill("sanqin-jiang",1)/4);
	me->add_temp("apply/damage", -(int)me->query_skill("sanqin-jiang",1)/4);
	me->delete_temp("sq_perform");
        //me->start_busy(1+random(2));
        return 1;
}

