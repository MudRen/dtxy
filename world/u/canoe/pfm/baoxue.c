#include <ansi.h>
inherit SSERVER;
int perform(object me, object target)
{
object weapon;
int damage;
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ��һ�С���ѩ��������\n");
    if(!wizardp(me)&&(string)me->query("family/family_name") != "��ѩɽ" )
   return notify_fail("��ı��Ǻ����Ǵ�����͵ѧ���ģ�\n");
        if(!me->is_fighting())
                return notify_fail("����ѩ������ֻ����ս����ʹ�ã�\n");
        if((int)me->query("max_force") < 500 )
                return notify_fail("�������������\n");
        if((int)me->query("force") < 500 )
                return notify_fail("����������㣡\n");
        if((int)me->query("sen") < 500 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");
        if((int)me->query_skill("bingpo-blade", 1) < 100)
                return notify_fail("��ı��Ǻ������𻹲�����ʹ����һ�л������ѣ�\n");
        if (me->query_temp("xs_pfm_busy")) return notify_fail("�����õ�̫��̫�ľͲ����ˡ�\n");
 message_vision(HIC"\n$N������������һת�����ܶ�ʱ�������ߣ������к�������$nֻ�������ǵĵֿ���\n"NOR,me,target);
 me->set_temp("noauto",1);
 target->start_busy(random(2));
 damage=random(((int)me->query_skill("blade")));
 target->receive_wound("kee",damage);
 message_vision(HIC"\n$N�ٺ�һ����Ц����Ȼ����ѩ��֮�С�$n�󼱣�������Ѱ$N����Ȼ����һ��������\n"NOR,me,target);
 message_vision(HIC"\n�����Ϯ����������\n"NOR,me,target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
 if(random(me->query("combat_exp"))>random(target->query("combat_exp"))/2)
 {
message_vision(HIY"\n����,һֻ��ɫ������ԶԶ������$N��$n�������ˣ�\n"NOR,me,target);
message_vision(HIY"\nͻȻ�������ó��һ��,��ʱ��������\n"NOR,me,target);
if(me->query("force_factor")>random(target->query("force_factor")))
{
 message_vision(HIR"\n$N��������ʧ,��æ����һ�У�\n"NOR,me,target);
 target->receive_damage("kee",damage*2); 
 target->receive_damage("sen",damage*2); 
 message_vision(HIR"\n����������ʯ�������,��$n�ҵñ������ˣ�\n"NOR,me,target);
 target->receive_wound("kee",damage);
 target->receive_wound("sen",damage);
 COMBAT_D->report_status(target);
}  
 else if(random(me->query("force_factor"))>target->query("force_factor")/2)
{
message_vision(HIR"\n����������ʯ�������,��$n�ҵñ������ˣ�\n"NOR,me,target);
target->receive_wound("kee",damage);
COMBAT_D->report_status(target);
}
else  
{
message_vision(HIR"\n����������ʯ�������,��$N��$n�ҵñ������ˣ�\n"NOR,me,target); 
target->receive_wound("kee",damage);
target->receive_wound("sen",damage);
COMBAT_D->report_status(target);
me->receive_wound("kee",damage/10);
COMBAT_D->report_status(me);
}        
}
 me->delete_temp("noauto");
 me->receive_damage("sen", 100);
 me->add("force", -500);
/* if( !target->is_fighting(me) ) {
               if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
        }

*/
          me->start_busy(2);
      me->set_temp("xs_pfm_busy",1);
//  me->set_temp("no_move",1);
//  call_out("remove_no_move",5,me);
        call_out("remove_effect",2+random(3),me);
        return 1;
}

void remove_effect(object me) {
  if (!me) return;
  me->delete_temp("xs_pfm_busy");
}
/*
void remove_no_move(object me) {
  if (me) me->delete_temp("no_move");
}
*/
