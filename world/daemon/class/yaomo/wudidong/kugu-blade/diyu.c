#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
 string msg;
 int extra,lvl,lv;
 int i, zx;
 object weapon;
 
 if( !target ) target = offensive_target(me);
 if( !target
 || !target->is_character()
 || !me->is_fighting(target) )
 	return notify_fail("无边地狱只能对战斗中的对手使用。\n");
 if(me->query("family/family_name")!="陷空山无底洞")
 	return notify_fail("“无边地狱”只有无底洞门人才可以用！\n");
 weapon = me->query_temp("weapon");
 if( (string)weapon->query("skill_type") != "blade" )
 	return notify_fail("你手上无刀，不能使用无边地狱！\n");
//      if( me->query_temp("zxzx") ) 
//        return notify_fail("你正在运功,不能分心他用！\n");
 if( (int)me->query("force") <= 1000 )
 	return notify_fail("你内力不够，不能使用无边地狱！\n");
 if( me->query_temp("zxzx") )
 {
	zx = 1;
	me->delete_temp("zxzx");
 }
 extra = me->query_skill("kugu-blade",1) / 5;
 me->add_temp("apply/attack", extra);
 me->add_temp("apply/damage", extra);
 msg = HIR  "$N使出［枯骨刀法］的无边地狱，手中的"+ weapon->name() + HIR + "斜斜劈出，$n顿觉呼吸一窒！" NOR;
 message_vision(msg, me, target);
 COMBAT_D->do_attack(me,target, weapon, TYPE_REGULAR);
 msg =  HIW "$N刀光连闪，$n周围鬼哭神号，恰似无边地狱！\n" NOR;
        message_vision(msg, me, target);
lvl=extra/10;
if(lvl>8) lvl =8;
//  lvl = lvl/2 + random(lvl/2) + 1;
for(i=0;i<=lvl;i++)
 {
 if( ! target ) return 1; 
 msg = HIY "$N劈出一刀！\n" NOR;
 COMBAT_D->do_attack(me,target, weapon, TYPE_REGULAR);
 message_vision(msg,me,target);
}
 me->add_temp("apply/attack", -extra);
 me->add_temp("apply/damage", -extra);
   me->add("force", -100);
 me->start_busy(2);
 if( zx ) me->set_temp("zxzx", 1);
 return 1;
}
